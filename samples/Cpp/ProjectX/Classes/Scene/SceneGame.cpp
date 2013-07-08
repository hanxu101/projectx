#include "CommonHeaders.h"

#include "SceneGame.h"
#include "GameObject/MainCharacter.h"
#include "GameObject/FireBall/FireBall.h"
#include "GameObject/Monsters/Monster.h"
#include "GameObject/GameObjectManager/GameObjectManager.h"
#include "GameLogic/MonsterGroupLogic.h"
#include "Buff/BuffManager/BuffManager.h"
#include "UISystem.h"
#include "CocoPanel.h"
#include "Gamelogic/MainPlayerLogic.h"
#include "GameLogic/GeneralGroupLogic.h"
#include "GameLogic/GpeLogic.h"

//------------------------------------------------------------------
//
// GameLayer
//
//------------------------------------------------------------------
const CCPoint GameLayer::INVALID_TOUCHPOSITION = CCPoint(-1.0f, -1.0f);
const float GameLayer::FIRE_SLIDE_DISTANCE_MAX = 20.0f;
const float GameLayer::FIRE_SLIDE_DISTANCE_MIN = 5.0f;
const float GameLayer::FIRE_TOUCH_TIME_THRESHOLD = 0.0167f * 5.0f;

const int g_uiZOrder = 3;
const int g_generalZOrder = 2;
const int g_monsterZOder = 1;
const int g_backGroundZOrder = -1;

GameLayer::GameLayer(void)
    : m_pMonsterGroupLogic(NULL)
    , m_pGeneralGroupLogic(NULL)
    , m_pGpeLogic(NULL)
    , m_fireBall(NULL)
    , m_pGameUI(NULL)
{
}

GameLayer::~GameLayer(void)
{
}

bool GameLayer::init()
{
    if (CCLayer::init())
    {
        //setTouchEnabled(true);

        return true;
    }
    return false;
}

std::string GameLayer::title()
{
    return "GameScene";
}

void GameLayer::onEnter()
{
    CCLayer::onEnter();

    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(GameLayer::Update), this, 0, false);

    GameObjectManager::CreateSingleton();
    BuffManager::CreateSingleton();

#ifndef DEBUG_HIDE_TEXT
    // Back ground.
    CCSprite* pBackGround = CCSprite::create("backGround.jpg");

    CCRect rect = pBackGround->getTextureRect();
    float width = rect.getMaxX() - rect.getMinX();
    pBackGround->setScaleX((VisibleRect::right().x - VisibleRect::left().x) / width);
    float height = rect.getMaxY() - rect.getMinY();
    pBackGround->setScaleY((VisibleRect::top().y - VisibleRect::bottom().y) / height);

    pBackGround->setPosition(VisibleRect::center());
    addChild(pBackGround, g_backGroundZOrder);
#endif

    cs::CocoWidget* pWidget = NULL;

#ifndef DEBUG_NO_UI
    // Init UI.
    CCNode* pUiNode = CCNode::create();
    addChild(pUiNode, g_uiZOrder);

    COCOUISYSTEM->resetSystem(pUiNode);
    m_pGameUI = cs::CocoPanel::create();
    COCOUISYSTEM->getCurScene()->addWidget(m_pGameUI);

    pWidget = COCOUISYSTEM->createWidgetFromFile_json("UIGame.json");
    m_pGameUI->addChild(pWidget);
#endif

    MainPlayerLogic::CreateSingleton();
    MainPlayerLogic::Singleton().Init(pWidget);

#ifndef DEBUG_NO_MONSTER
    // Init monster logic.
    m_pMonsterGroupLogic = new MonsterGroupLogic();
    m_pMonsterGroupLogic->autorelease();
    addChild(m_pMonsterGroupLogic, g_monsterZOder);
#endif

#ifndef DEBUG_NO_GENERAL
    // Init general logic.
    std::vector< EGeneralType > generalVec;
    generalVec.push_back(eGT_DiaoChan);
    generalVec.push_back(eGT_MaChao);
    m_pGeneralGroupLogic = new GeneralGroupLogic(generalVec, m_pGameUI);
    m_pGeneralGroupLogic->autorelease();
    addChild(m_pGeneralGroupLogic, g_generalZOrder);
#endif

#ifndef DEBUG_NO_GPE
    // Init Gpe logic.
    m_pGpeLogic = new GpeLogic();
    m_pGpeLogic->autorelease();
    addChild(m_pGpeLogic);
#endif

    //setTouchEnabled(true);

    m_bTouchEnabled = true;
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 2);
}

void GameLayer::onExit()
{
    COCOUISYSTEM->cleanUIScene();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);

    CCLayer::onExit();

    // Destory singletons after base layer exit. (After all children exit)
    GameObjectManager::DestroySingleton();
    BuffManager::DestroySingleton();

    MainPlayerLogic::Singleton().Uninit();
    MainPlayerLogic::DestroySingleton();
}

void GameLayer::Update(float dt)
{
#ifndef DEBUG_NO_MONSTER
    m_pMonsterGroupLogic->StateUpdate(dt);
#endif

    m_pGeneralGroupLogic->Update(dt);

    UpdateTouchInfo(dt);

    GameObjectManager::Singleton().Update(dt);
    BuffManager::Singleton().Update(dt);
}

void GameLayer::UpdateTouchInfo(float dt)
{
    for (UINT8 index = 0; index < m_previousTouchPosVec.size(); ++index)
    {
        for (UINT8 i = 1; i < PREVIOUS_TOUCHPOSITION_CACHE_NUM; ++i)
        {
            m_previousTouchPosVec[index][i-1] = m_previousTouchPosVec[index][i];
        }

        m_previousTouchPosVec[index][PREVIOUS_TOUCHPOSITION_CACHE_NUM-1] = m_isTouching[index] ? m_currentTouchPointMap[index] : INVALID_TOUCHPOSITION;
        m_touchFrameCount[index] = m_isTouching[index] ? ++m_touchFrameCount[index] : 0;
        m_touchTimer[index] = m_isTouching[index] ? (m_touchFrameCount[index] + dt) : 0.0f;
    }
}

UINT GameLayer::GetPreviousTouchPosIndex( UINT rollbackFrameNum, UINT maxCacheNumber )
{
    CCAssert(rollbackFrameNum >= 0, "The Rollback Frame Num must >= 0 .");

    return rollbackFrameNum >= maxCacheNumber ? 0 : (maxCacheNumber - rollbackFrameNum - 1);
}

void GameLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator iter = pTouches->begin();
    for (; iter != pTouches->end(); iter++)
    {
        CCTouch* pTouch = (CCTouch*)(*iter);
        CCPoint touchPos = pTouch->getLocation();

        if (m_currentTouchPointMap.find(pTouch->getID()) == m_currentTouchPointMap.end())
            m_previousTouchPosVec[pTouch->getID()].resize(PREVIOUS_TOUCHPOSITION_CACHE_NUM);

        m_currentTouchPointMap[pTouch->getID()] = touchPos;
        m_isTouching[pTouch->getID()] = true;

        if ( touchPos.y > VisibleRect::top().y / 2)
        {
            Monster* pMonster = new Monster();
            pMonster->setPosition( touchPos.x, VisibleRect::top().y);
            addChild(pMonster);
        }
        else
        {
            m_fireBall = new FireBall();
            m_fireBall->setPosition(touchPos);
            addChild(m_fireBall);

            m_pStreak = CCMotionStreak::create(1.0f, 3.0f, 10.0f, ccWHITE, "streak.png");
            addChild(m_pStreak);
        }
    }
}

void GameLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    if (m_fireBall)
    {
        CCSetIterator iter = pTouches->begin();
        for (; iter != pTouches->end(); iter++)
        {
            CCTouch* pTouch = (CCTouch*)(*iter);
            CCPoint touchPos = pTouch->getLocation();
            m_currentTouchPointMap[pTouch->getID()] = touchPos;

            m_previousTouchPosVec[pTouch->getID()][PREVIOUS_TOUCHPOSITION_CACHE_NUM-1] = touchPos;

            m_fireBall->setPosition(touchPos);
            m_pStreak->setPosition(touchPos);
        }
    }
}

void GameLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    if (m_fireBall)
    {
        CCSetIterator iter = pTouches->begin();
        for (; iter != pTouches->end(); iter++)
        {
            CCTouch* pTouch = (CCTouch*)(*iter);
            CCPoint touchPoint = pTouch->getLocation();
            m_currentTouchPointMap[pTouch->getID()]  = touchPoint;
            m_previousTouchPosVec[pTouch->getID()][PREVIOUS_TOUCHPOSITION_CACHE_NUM-1] = touchPoint;
            m_isTouching[pTouch->getID()] = false;

#ifdef DEBUG_FAKE_FIREBALL_INPUT
            //Debug code
            FakeInput();
#endif

            bool canFire = false;

            if (m_touchFrameCount[pTouch->getID()] >= PREVIOUS_TOUCHPOSITION_CACHE_NUM)
            {
                CCPoint previousTouchPoint = m_previousTouchPosVec[pTouch->getID()][GetPreviousTouchPosIndex(m_touchFrameCount[pTouch->getID()], PREVIOUS_TOUCHPOSITION_CACHE_NUM)];
                float offset = ccpDistance(m_currentTouchPointMap[pTouch->getID()], previousTouchPoint);
                if (offset > FIRE_SLIDE_DISTANCE_MIN && m_touchTimer[pTouch->getID()] > FIRE_TOUCH_TIME_THRESHOLD)
                {
                    canFire = true;

                    m_fireBall->SetDirection(CalculateDirection(pTouch->getID()));
                    m_fireBall->SetSpeedFactor(CalculateSlideSpeedFactor(offset));
                    m_fireBall->SetForce(CalculateSpinForce(pTouch->getID()));
                    m_fireBall->SetMove();

                    PrintMoveInfo();
                }
            }

            if (!canFire)
            {
                m_fireBall->SetAbort();
            }

        }

        m_fireBall = NULL;
    }
}

void GameLayer::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    ccTouchesEnded(pTouches, pEvent);
}

CCPoint GameLayer::CalculateDirection(int touchId)
{
    UINT index = GetPreviousTouchPosIndex(m_touchFrameCount[touchId], PREVIOUS_TOUCHPOSITION_CACHE_NUM);
    CCPoint previousTouchPoint1 = m_previousTouchPosVec[touchId][index];
    CCPoint previousTouchPoint2 = m_previousTouchPosVec[touchId][index+PREVIOUS_TOUCHPOSITION_CACHE_NUM/2];
    //return ccpNormalize(ccpSub(previousTouchPoint2, previousTouchPoint1));
    return ccpSub(previousTouchPoint2, previousTouchPoint1);
}

CCPoint GameLayer::CalculateSpinForce(int touchId)
{
    CCPoint previousTouchPoint1 = m_previousTouchPosVec[touchId][GetPreviousTouchPosIndex(0, PREVIOUS_TOUCHPOSITION_CACHE_NUM)];
    CCPoint previousTouchPoint2 = m_previousTouchPosVec[touchId][GetPreviousTouchPosIndex(PREVIOUS_TOUCHPOSITION_CACHE_NUM/2, PREVIOUS_TOUCHPOSITION_CACHE_NUM)];
    return ccpSub(previousTouchPoint1, previousTouchPoint2);
}

float GameLayer::CalculateSlideSpeedFactor(float slideDistance)
{
    float speed = clampf(slideDistance, FIRE_SLIDE_DISTANCE_MIN, FIRE_SLIDE_DISTANCE_MAX);
    return speed / FIRE_SLIDE_DISTANCE_MAX;
}

//////////////////////////////////////////////////////////////////////////
// Debug
void GameLayer::PrintMoveInfo()
{
    if (m_fireBall)
    {
        CCLOG("DIRECTION :  (%.2f, %.2f)", m_fireBall->GetDirection().x, m_fireBall->GetDirection().y);
        CCLOG("FORCE :      (%.2f, %.2f)", m_fireBall->GetForce().x, m_fireBall->GetForce().y);

        CCPoint previousTouchPoint1 = m_previousTouchPosVec[0][GetPreviousTouchPosIndex(0, PREVIOUS_TOUCHPOSITION_CACHE_NUM)];
        CCPoint previousTouchPoint2 = m_previousTouchPosVec[0][GetPreviousTouchPosIndex(PREVIOUS_TOUCHPOSITION_CACHE_NUM/2, PREVIOUS_TOUCHPOSITION_CACHE_NUM)];
        CCLOG("Force Points: (%.2f, %.2f), (%.2f, %.2f)", previousTouchPoint1.x, previousTouchPoint1.y, previousTouchPoint2.x, previousTouchPoint2.y);
    }

    CCLOG("TouchFrameCount : %d)", m_touchFrameCount[0]);

    for (UINT8 i = 0; i < PREVIOUS_TOUCHPOSITION_CACHE_NUM; ++i)
    {
        CCLOG("TouchPoint%d :(%.2f, %.2f)", i, m_previousTouchPosVec[0][i].x, m_previousTouchPosVec[0][i].y);
    }

    // for Excel format
    CCLOG("Excel format of Pos:");
    string strForX, strForY;
    for (UINT8 i = 0; i < PREVIOUS_TOUCHPOSITION_CACHE_NUM; ++i)
    {
        strForX += CCString::createWithFormat("%.2f\t", m_previousTouchPosVec[0][i].x)->m_sString;
        strForY += CCString::createWithFormat("%.2f\t", m_previousTouchPosVec[0][i].y)->m_sString;
    }
    CCLOG((strForX + "\n" + strForY).c_str());
}

void GameLayer::FakeInput()
{
    // A spin curve to top right
    m_previousTouchPosVec[0][0] = CCPoint(139.87f, 39.49f);
    m_previousTouchPosVec[0][1] = CCPoint(148.2f, 71.73f);
    m_previousTouchPosVec[0][2] = CCPoint(161.2f, 89.93f);
    m_previousTouchPosVec[0][3] = CCPoint(195.0f, 112.81f);
    m_previousTouchPosVec[0][4] = CCPoint(222.04f, 115.41f);

    // Move forward
    /*m_previousTouchPosVec[0][0] = CCPoint(0.0f, 0.0f);
    m_previousTouchPosVec[0][1] = CCPoint(0.0f, 71.73f);
    m_previousTouchPosVec[0][2] = CCPoint(0.0f, 89.93f);
    m_previousTouchPosVec[0][3] = CCPoint(0.0f, 112.81f);
    m_previousTouchPosVec[0][4] = CCPoint(0.0f, 115.41f);
    */
    // Boomerang
    /*m_previousTouchPosVec[0][0] = CCPoint(0.0f, 0.0f);
    m_previousTouchPosVec[0][1] = CCPoint(0.0f, 10.73f);
    m_previousTouchPosVec[0][2] = CCPoint(0.0f, 20.93f);
    m_previousTouchPosVec[0][3] = CCPoint(0.0f, 9.73f);
    m_previousTouchPosVec[0][4] = CCPoint(0.0f, 0.0f);*/
};

//------------------------------------------------------------------
//
// GameScene
//
//------------------------------------------------------------------
void SceneGame::runThisTest()
{
    GameLayer* pLayer = GameLayer::create();
    addChild(pLayer, 0);
    CCDirector::sharedDirector()->replaceScene(this);
}