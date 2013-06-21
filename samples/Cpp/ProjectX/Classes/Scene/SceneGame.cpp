#include "CommonHeaders.h"

#include "SceneGame.h"
#include "GameObject/MainCharacter.h"
#include "GameObject/FireBall/FireBall.h"
#include "GameObject/Monsters/Monster.h"
#include "GameObject/GameObjectManager/GameObjectManager.h"
#include "GameLogic/MonsterGroupLogic.h"
#include "Buff/BuffManager/BuffManager.h"
#include "UISystem.h"
#include "CocoLoadingBar.h"
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

GameLayer::GameLayer(void)
    : m_isTouching(false)
    , m_touchFrameCount(0)
    , m_pMonsterGroupLogic(NULL)
    , m_pGeneralGroupLogic(NULL)
    , m_pGpeLogic(NULL)
    , m_touchTimer(0.0f)
    , m_fireBall(NULL)
    , m_pGameUI(NULL)
{
    m_previousTouchPosVec.resize(PREVIOUS_TOUCHPOSITION_CACHE_NUM);
}

GameLayer::~GameLayer(void)
{
}

bool GameLayer::init()
{
    if (CCLayer::init())
    {
        setTouchEnabled(true);

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
    // Init UI.
    COCOUISYSTEM->resetSystem(this);

    m_pGameUI = cs::CocoPanel::create();
    COCOUISYSTEM->getCurScene()->addWidget(m_pGameUI);

    cs::CocoWidget* pWidget = COCOUISYSTEM->createWidgetFromFile_json("UIGame.json");
    m_pGameUI->addChild(pWidget);


    // Init player logic.
    cs::CocoLoadingBar* pHpBar = dynamic_cast<cs::CocoLoadingBar*>(pWidget->getChildByName("HpBar"));
    MainPlayerLogic::CreateSingleton();
    MainPlayerLogic::Singleton().Init(pHpBar);

#endif

#ifndef DEBUG_NO_MONSTER
    // Init monster logic.
    m_pMonsterGroupLogic = new MonsterGroupLogic();
    m_pMonsterGroupLogic->autorelease();
    addChild(m_pMonsterGroupLogic);
#endif

    // Init general logic.
    std::vector< EGeneralType > generalVec;
    generalVec.push_back(eGT_DiaoChan);
    generalVec.push_back(eGT_DiaoChan);
    m_pGeneralGroupLogic = new GeneralGroupLogic(generalVec, m_pGameUI);
    m_pGeneralGroupLogic->autorelease();
    addChild(m_pGeneralGroupLogic);

    // Init Gpe logic.
    m_pGpeLogic = new GpeLogic();
    m_pGpeLogic->autorelease();
    addChild(m_pGpeLogic);

    setTouchEnabled(true);
}

void GameLayer::onExit()
{
    COCOUISYSTEM->cleanUIScene();

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

    UpdateTouchInfo(dt);

    GameObjectManager::Singleton().Update(dt);
    BuffManager::Singleton().Update(dt);
}

void GameLayer::UpdateTouchInfo(float dt)
{
    for (UINT8 i = 1; i < PREVIOUS_TOUCHPOSITION_CACHE_NUM; ++i)
    {
        m_previousTouchPosVec[i-1] = m_previousTouchPosVec[i];
    }

    m_previousTouchPosVec[PREVIOUS_TOUCHPOSITION_CACHE_NUM-1] = m_isTouching ? m_currentTouchLocation : INVALID_TOUCHPOSITION;
    m_touchFrameCount = m_isTouching ? ++m_touchFrameCount : 0;
    m_touchTimer = m_isTouching ? (m_touchFrameCount + dt) : 0.0f;
}

UINT GameLayer::GetPreviousTouchPosIndex( UINT rollbackFrameNum, UINT maxCacheNumber )
{
    CCAssert(rollbackFrameNum >= 0, "The Rollback Frame Num must >= 0 .");

    return rollbackFrameNum >= maxCacheNumber ? 0 : (maxCacheNumber - rollbackFrameNum - 1);
}

void GameLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    m_isTouching = true;

    CCSetIterator iter = pTouches->begin();
    for (; iter != pTouches->end(); iter++)
    {
        CCTouch* pTouch = (CCTouch*)(*iter);
        m_currentTouchLocation = pTouch->getLocation();

        if (m_currentTouchLocation.y > VisibleRect::top().y / 2)
        {
            Monster* pMonster = new Monster();
            pMonster->setPosition(m_currentTouchLocation.x, VisibleRect::top().y);
            addChild(pMonster);
        }
        else
        {
            m_fireBall = new FireBall();
            m_fireBall->setPosition(m_currentTouchLocation);
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
            m_currentTouchLocation = pTouch->getLocation();
            m_previousTouchPosVec[PREVIOUS_TOUCHPOSITION_CACHE_NUM-1] = m_currentTouchLocation;

            m_fireBall->setPosition(m_currentTouchLocation);
            m_pStreak->setPosition(m_currentTouchLocation);
        }
    }
}

void GameLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    m_isTouching = false;
    if (m_fireBall)
    {
        CCSetIterator iter = pTouches->begin();
        for (; iter != pTouches->end(); iter++)
        {
            CCTouch* pTouch = (CCTouch*)(*iter);
            m_currentTouchLocation = pTouch->getLocation();
            m_previousTouchPosVec[PREVIOUS_TOUCHPOSITION_CACHE_NUM-1] = m_currentTouchLocation;

#ifdef DEBUG_FAKE_FIREBALL_INPUT
            //Debug code
            FakeInput();
#endif

            bool canFire = false;

            if (m_touchFrameCount >= PREVIOUS_TOUCHPOSITION_CACHE_NUM)
            {
                CCPoint previousTouchPoint = m_previousTouchPosVec[GetPreviousTouchPosIndex(m_touchFrameCount, PREVIOUS_TOUCHPOSITION_CACHE_NUM)];
                float offset = ccpDistance(m_currentTouchLocation, previousTouchPoint);
                if (offset > FIRE_SLIDE_DISTANCE_MIN && m_touchTimer > FIRE_TOUCH_TIME_THRESHOLD)
                {
                    canFire = true;

                    m_fireBall->SetDirection(CalculateDirection());
                    m_fireBall->SetSpeedFactor(CalculateSlideSpeedFactor(offset));
                    m_fireBall->SetForce(CalculateSpinForce());
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

CCPoint GameLayer::CalculateDirection()
{
    UINT index = GetPreviousTouchPosIndex(m_touchFrameCount, PREVIOUS_TOUCHPOSITION_CACHE_NUM);
    CCPoint previousTouchPoint1 = m_previousTouchPosVec[index];
    CCPoint previousTouchPoint2 = m_previousTouchPosVec[index+PREVIOUS_TOUCHPOSITION_CACHE_NUM/2];
    //return ccpNormalize(ccpSub(previousTouchPoint2, previousTouchPoint1));
    return ccpSub(previousTouchPoint2, previousTouchPoint1);
}

CCPoint GameLayer::CalculateSpinForce()
{
    CCPoint previousTouchPoint1 = m_previousTouchPosVec[GetPreviousTouchPosIndex(0, PREVIOUS_TOUCHPOSITION_CACHE_NUM)];
    CCPoint previousTouchPoint2 = m_previousTouchPosVec[GetPreviousTouchPosIndex(PREVIOUS_TOUCHPOSITION_CACHE_NUM/2, PREVIOUS_TOUCHPOSITION_CACHE_NUM)];
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

        CCPoint previousTouchPoint1 = m_previousTouchPosVec[GetPreviousTouchPosIndex(0, PREVIOUS_TOUCHPOSITION_CACHE_NUM)];
        CCPoint previousTouchPoint2 = m_previousTouchPosVec[GetPreviousTouchPosIndex(PREVIOUS_TOUCHPOSITION_CACHE_NUM/2, PREVIOUS_TOUCHPOSITION_CACHE_NUM)];
        CCLOG("Force Points: (%.2f, %.2f), (%.2f, %.2f)", previousTouchPoint1.x, previousTouchPoint1.y, previousTouchPoint2.x, previousTouchPoint2.y);
    }

    CCLOG("TouchFrameCount : %d)", m_touchFrameCount);

    for (UINT8 i = 0; i < PREVIOUS_TOUCHPOSITION_CACHE_NUM; ++i)
    {
        CCLOG("TouchPoint%d :(%.2f, %.2f)", i, m_previousTouchPosVec[i].x, m_previousTouchPosVec[i].y);
    }

    // for Excel format
    CCLOG("Excel format of Pos:");
    string strForX, strForY;
    for (UINT8 i = 0; i < PREVIOUS_TOUCHPOSITION_CACHE_NUM; ++i)
    {
        strForX += CCString::createWithFormat("%.2f\t", m_previousTouchPosVec[i].x)->m_sString;
        strForY += CCString::createWithFormat("%.2f\t", m_previousTouchPosVec[i].y)->m_sString;
    }
    CCLOG((strForX + "\n" + strForY).c_str());
}

void GameLayer::FakeInput()
{
    // A spin curve to top right
    /*m_previousTouchPosVec[0] = CCPoint(139.87f, 39.49f);
    m_previousTouchPosVec[1] = CCPoint(148.2f, 71.73f);
    m_previousTouchPosVec[2] = CCPoint(161.2f, 89.93f);
    m_previousTouchPosVec[3] = CCPoint(195.0f, 112.81f);
    m_previousTouchPosVec[4] = CCPoint(222.04f, 115.41f);
    */
    // Move forward
    /*m_previousTouchPosVec[0] = CCPoint(0.0f, 0.0f);
    m_previousTouchPosVec[1] = CCPoint(0.0f, 71.73f);
    m_previousTouchPosVec[2] = CCPoint(0.0f, 89.93f);
    m_previousTouchPosVec[3] = CCPoint(0.0f, 112.81f);
    m_previousTouchPosVec[4] = CCPoint(0.0f, 115.41f);
    */
    // Boomerang
    m_previousTouchPosVec[0] = CCPoint(0.0f, 0.0f);
    m_previousTouchPosVec[1] = CCPoint(0.0f, 10.73f);
    m_previousTouchPosVec[2] = CCPoint(0.0f, 20.93f);
    m_previousTouchPosVec[3] = CCPoint(0.0f, 9.73f);
    m_previousTouchPosVec[4] = CCPoint(0.0f, 0.0f);
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