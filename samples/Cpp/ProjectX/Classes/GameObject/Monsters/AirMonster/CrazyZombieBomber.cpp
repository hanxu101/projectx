#include "CommonHeaders.h"

#include "GameObject/Monsters/AirMonster/CrazyZombieBomber.h"
#include "GameObject/Items/BuffItem/TimeFreezeItem.h"
#include "GameObject/Items/Gold/Gold.h"
#include "GameObject/Items/Bomb/Bomb.h"
#include "GameObject/GameObjectManager/GameObjectManager.h"


CrazyZombieBomber::CrazyZombieBomber()
    : m_timeElapsed(0.0f)
{
    m_speed = 20.0f;
}

CrazyZombieBomber::~CrazyZombieBomber()
{

}

void CrazyZombieBomber::onEnter()
{
    Monster::onEnter();

    float scaleFactor = CCDirector::sharedDirector()->getContentScaleFactor();
    m_pMainSprite = CCSprite::create("CrazyZombieBomber.png",CCRectMake(0, 0, 32 / scaleFactor, 48 / scaleFactor));
    addChild(m_pMainSprite);
}

void CrazyZombieBomber::onExit()
{
    Monster::onExit();
}

void CrazyZombieBomber::Killed()
{
    TGameObjectList objectList;
    if (GameObjectManager::IsSingletonCreated())
        GameObjectManager::Singleton().GetGameObjectList(eGOT_Monster, objectList);

    for (TGameObjectList::iterator iter = objectList.begin(); iter != objectList.end(); ++iter)
    {
        if (abs((*iter)->getPositionY() - getPositionY()) < 10.0f && (*iter) != this)
        {
            (*iter)->ReduceHp(10.0f);
        }
    }

    Unspawn();
}

int CrazyZombieBomber::GetDetailTypeIndex()
{
    return static_cast<int>(eMT_CrazyZombieBomber);
}

void CrazyZombieBomber::PlayMonsterWalkAnimation()
{
    float scaleFactor = CCDirector::sharedDirector()->getContentScaleFactor();

    float x = 32 / scaleFactor;
    float y = 48 / scaleFactor;

    CCSpriteFrame *frame0=CCSpriteFrame::create("CrazyZombieBomber.png",CCRectMake(0, 0, x, y)); 
    CCSpriteFrame *frame1=CCSpriteFrame::create("CrazyZombieBomber.png",CCRectMake(x, 0, x, y)); 
    CCSpriteFrame *frame2=CCSpriteFrame::create("CrazyZombieBomber.png",CCRectMake(x*2, 0, x, y)); 
    CCSpriteFrame *frame3=CCSpriteFrame::create("CrazyZombieBomber.png",CCRectMake(x*3, 0, x, y)); 

    CCArray *animFrames = new CCArray; 
    animFrames->addObject(frame0); 
    animFrames->addObject(frame1); 
    animFrames->addObject(frame2); 
    animFrames->addObject(frame3); 

    CCAnimation *pAnim = CCAnimation::createWithSpriteFrames(animFrames, 0.4f); 
    animFrames->release();

    m_pMainSprite->runAction(CCRepeatForever::create(CCAnimate::create(pAnim)));
}

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_STATE_BEGIN(CrazyZombieBomber, Move)
{
    STATE_CONSTRUCTOR_BEGIN
    {
        PlayMonsterWalkAnimation();

        m_targetPos = CCPoint(getPosition().x, VisibleRect::bottom().y);
        m_direction = ccpSub(m_targetPos, getPosition());
        m_direction = ccpNormalize(m_direction);
    }
    STATE_CONSTRUCTOR_END

        STATE_UPDATE_BEGIN
    {
        m_timeElapsed += m_deltaTime;

        if (m_timeElapsed > 2.0f)
            m_speed = 150.0f + (m_timeElapsed - 2.0f) * 100.0f;

        CCPoint newPos =  ccpAdd( getPosition(), ccpMult(ccpMult(m_direction, m_speed), m_deltaTime) );
        setPosition(newPos);

        TRANSIT_TO_STATE( !VisibleRect::getVisibleRect().containsPoint(newPos), NoTransitionAction, ArrivedBottomSafe );
    }
    STATE_UPDATE_END

        STATE_DESTRUCTOR_BEGIN
    {
        m_timeElapsed = 0.0f;
    }
    STATE_DESTRUCTOR_END
}
IMPLEMENT_STATE_END
