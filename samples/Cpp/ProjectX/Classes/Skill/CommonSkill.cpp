#include "CommonHeaders.h"

#include "Skill/CommonSkill.h"
#include "GameObject/GameObjectManager/GameObjectManager.h"
#include "GameObject/FireBall/FireBall.h"
#include "Ui/UiManager.h"

const CCPoint CommonSkill::INVALID_TOUCHPOSITION = CCPoint(-1.0f, -1.0f);
const float CommonSkill::FIRE_SLIDE_DISTANCE_MAX = 20.0f;
const float CommonSkill::FIRE_SLIDE_DISTANCE_MIN = 5.0f;
const float CommonSkill::FIRE_TOUCH_TIME_THRESHOLD = 0.0167f * 5.0f;

CommonSkill::CommonSkill()
{

}

CommonSkill::~CommonSkill()
{

}

void CommonSkill::Init()
{
    super::Init();

    m_currentTouchPointMap.clear();
    m_previousTouchPosVec.clear();
    m_isTouching.clear();
    m_touchFrameCount.clear();
    m_touchTimer.clear();
    m_fireBall = NULL;
    m_pStreak = NULL;    
}

void CommonSkill::OnUpdate(float deltaTime)
{
    UpdateTouchInfo(deltaTime);
}

void CommonSkill::UpdateTouchInfo(float dt)
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

UINT CommonSkill::GetPreviousTouchPosIndex( UINT rollbackFrameNum, UINT maxCacheNumber )
{
    CCAssert(rollbackFrameNum >= 0, "The Rollback Frame Num must >= 0 .");

    return rollbackFrameNum >= maxCacheNumber ? 0 : (maxCacheNumber - rollbackFrameNum - 1);
}

void CommonSkill::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    if (UiManager::Singleton().IsInUi())
        return;

    CCSetIterator iter = pTouches->begin();
    for (; iter != pTouches->end(); iter++)
    {
        CCTouch* pTouch = (CCTouch*)(*iter);
        CCPoint touchPos = pTouch->getLocation();

        if (m_currentTouchPointMap.find(pTouch->getID()) == m_currentTouchPointMap.end())
            m_previousTouchPosVec[pTouch->getID()].resize(PREVIOUS_TOUCHPOSITION_CACHE_NUM);

        m_currentTouchPointMap[pTouch->getID()] = touchPos;
        m_isTouching[pTouch->getID()] = true;

        m_fireBall = new FireBall();
        m_fireBall->setPosition(touchPos);

        CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
        pScene->addChild(m_fireBall);

        m_pStreak = CCMotionStreak::create(1.0f, 3.0f, 10.0f, ccWHITE, "streak.png");
        pScene->addChild(m_pStreak);
    }
}

void CommonSkill::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
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

void CommonSkill::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
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

void CommonSkill::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    ccTouchesEnded(pTouches, pEvent);
}

CCPoint CommonSkill::CalculateDirection(int touchId)
{
    UINT index = GetPreviousTouchPosIndex(m_touchFrameCount[touchId], PREVIOUS_TOUCHPOSITION_CACHE_NUM);
    CCPoint previousTouchPoint1 = m_previousTouchPosVec[touchId][index];
    CCPoint previousTouchPoint2 = m_previousTouchPosVec[touchId][index+PREVIOUS_TOUCHPOSITION_CACHE_NUM/2];
    return ccpSub(previousTouchPoint2, previousTouchPoint1);
}

CCPoint CommonSkill::CalculateSpinForce(int touchId)
{
    CCPoint previousTouchPoint1 = m_previousTouchPosVec[touchId][GetPreviousTouchPosIndex(0, PREVIOUS_TOUCHPOSITION_CACHE_NUM)];
    CCPoint previousTouchPoint2 = m_previousTouchPosVec[touchId][GetPreviousTouchPosIndex(PREVIOUS_TOUCHPOSITION_CACHE_NUM/2, PREVIOUS_TOUCHPOSITION_CACHE_NUM)];
    return ccpSub(previousTouchPoint1, previousTouchPoint2);
}

float CommonSkill::CalculateSlideSpeedFactor(float slideDistance)
{
    float speed = clampf(slideDistance, FIRE_SLIDE_DISTANCE_MIN, FIRE_SLIDE_DISTANCE_MAX);
    return speed / FIRE_SLIDE_DISTANCE_MAX;
}

//////////////////////////////////////////////////////////////////////////
// Debug
void CommonSkill::PrintMoveInfo()
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
    std::string strForX, strForY;
    for (UINT8 i = 0; i < PREVIOUS_TOUCHPOSITION_CACHE_NUM; ++i)
    {
        strForX += CCString::createWithFormat("%.2f\t", m_previousTouchPosVec[0][i].x)->m_sString;
        strForY += CCString::createWithFormat("%.2f\t", m_previousTouchPosVec[0][i].y)->m_sString;
    }
    CCLOG((strForX + "\n" + strForY).c_str());
}

void CommonSkill::FakeInput()
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