#include "SceneGame.h"
#include "ResourceDefines.h"
#include "cocos2d.h"
#include "GameObject/MainCharacter.h"
#include "GameObject/FireBall.h"
#include "GameObject/Monster.h"
#include "GameObject/GameObjectManager/GameObjectManager.h"
#include "GameLogic/MonsterGroupLogic.h"

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
    : m_pMonsterGroupLogic(NULL)
    , m_isTouching(false)
    , m_touchFrameCount(0)
    , m_touchTimer(0.0f)
    , m_fireBall(NULL)
{
    m_previousTouchPosVec.resize(PREVIOUS_TOUCHPOSITION_CACHE_NUM+1);
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

    CCLabelTTF* label = CCLabelTTF::create(title().c_str(), "Arial", 32);
    addChild(label, 1);
    label->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y-50) );

    CCLabelTTF* infolabel = CCLabelTTF::create("Tap to Fire", "Arial", 10);
    addChild(infolabel , 1);
    infolabel ->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y-70) );

    m_pMonsterGroupLogic = new MonsterGroupLogic();
    m_pMonsterGroupLogic->autorelease();
    addChild(m_pMonsterGroupLogic);
}

void GameLayer::Update(float dt)
{
    m_pMonsterGroupLogic->StateUpdate(dt);
    
    UpdateTouchInfo(dt);

    GameObjectManager::Get().Update(dt);
}

void GameLayer::UpdateTouchInfo(float dt)
{
    for (UINT8 i = 1; i < PREVIOUS_TOUCHPOSITION_CACHE_NUM+1; ++i)
    {
        m_previousTouchPosVec[i-1] = m_previousTouchPosVec[i];
    }

    m_previousTouchPosVec[PREVIOUS_TOUCHPOSITION_CACHE_NUM] = m_isTouching ? m_currentTouchLocation : INVALID_TOUCHPOSITION;
    m_touchFrameCount = m_isTouching ? ++m_touchFrameCount : 0;
    m_touchTimer = m_isTouching ? (m_touchFrameCount + dt) : 0.0f;
}

CCPoint GameLayer::GetPreviousTouchPos( UINT rollbackFrameNum )
{
    CCAssert(rollbackFrameNum > 0, "The Rollback Frame Num must > 0 .");

    UINT index = rollbackFrameNum > PREVIOUS_TOUCHPOSITION_CACHE_NUM ? 0 : (PREVIOUS_TOUCHPOSITION_CACHE_NUM - rollbackFrameNum);
    return m_previousTouchPosVec[index];
}

static CCDictionary s_dic;

void GameLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
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
        }
    }
}

void GameLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator iter = pTouches->begin();
    for (; iter != pTouches->end(); iter++)
    {
        CCTouch* pTouch = (CCTouch*)(*iter);
        m_currentTouchLocation = pTouch->getLocation();
        m_previousTouchPosVec[PREVIOUS_TOUCHPOSITION_CACHE_NUM] = m_currentTouchLocation;

        m_fireBall->setPosition(m_currentTouchLocation);
    }
}

void GameLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    m_isTouching = false;

    CCSetIterator iter = pTouches->begin();
    for (; iter != pTouches->end(); iter++)
    {
        CCTouch* pTouch = (CCTouch*)(*iter);
        m_currentTouchLocation = pTouch->getLocation();
        m_previousTouchPosVec[PREVIOUS_TOUCHPOSITION_CACHE_NUM] = m_currentTouchLocation;

        CCPoint previousTouchPoint = GetPreviousTouchPos(m_touchFrameCount);
        float offset = ccpDistance(m_currentTouchLocation, previousTouchPoint);
        if (offset > FIRE_SLIDE_DISTANCE_MIN && m_touchTimer > FIRE_TOUCH_TIME_THRESHOLD)
        {
            m_fireBall->SetDirection(ccpNormalize(ccpSub(m_currentTouchLocation, previousTouchPoint)));
            m_fireBall->SetSpeedFactor(CalculateSlideSpeedFactor(offset));
            m_fireBall->SetMove();
        }
        else
        {
            m_fireBall->SetAbort();
        }
    }

    m_fireBall = NULL;
}

void GameLayer::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    ccTouchesEnded(pTouches, pEvent);
}

float GameLayer::CalculateSlideSpeedFactor(float slideDistance)
{
    float speed = clampf(slideDistance, FIRE_SLIDE_DISTANCE_MIN, FIRE_SLIDE_DISTANCE_MAX);
    return speed / FIRE_SLIDE_DISTANCE_MAX;
}

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
