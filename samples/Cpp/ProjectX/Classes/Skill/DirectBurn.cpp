#include "CommonHeaders.h"

#include "Skill/DirectBurn.h"
#include "GameObject/FireBall/FireBall.h"

DirectBurn::DirectBurn()
    : m_fireBall(NULL)
    , m_pStreak(NULL)
{

}

DirectBurn::~DirectBurn()
{

}

void DirectBurn::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator iter = pTouches->begin();
    for (; iter != pTouches->end(); iter++)
    {
        CCTouch* pTouch = (CCTouch*)(*iter);
        CCPoint touchPos = pTouch->getLocation();

        m_fireBall = new FireBall();
        m_fireBall->setPosition(touchPos);
        m_fireBall->SetCanDirectBurn(true);

        CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
        pScene->addChild(m_fireBall);

        m_pStreak = CCMotionStreak::create(1.0f, 3.0f, 10.0f, ccWHITE, "streak.png");
        pScene->addChild(m_pStreak);
    }
}

void DirectBurn::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    if (m_fireBall)
    {
        CCSetIterator iter = pTouches->begin();
        for (; iter != pTouches->end(); iter++)
        {
            CCTouch* pTouch = (CCTouch*)(*iter);
            CCPoint touchPos = pTouch->getLocation();

            m_fireBall->setPosition(touchPos);
            m_pStreak->setPosition(touchPos);
        }
    }
}

void DirectBurn::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    if (m_fireBall)
    {
        m_fireBall->SetAbort();
    }

    m_fireBall = NULL;
}

void DirectBurn::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    ccTouchesEnded(pTouches, pEvent);
}

void DirectBurn::Uninit()
{
    super::Uninit();
    
    if (m_fireBall)
    {
        m_fireBall->SetAbort();
    }

    m_fireBall = NULL;
}
