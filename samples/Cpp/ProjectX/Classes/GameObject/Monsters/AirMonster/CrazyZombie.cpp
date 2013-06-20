#include "CommonHeaders.h"

#include "GameObject/Monsters/AirMonster/CrazyZombie.h"
#include "GameObject/Items/BuffItem/TimeFreezeItem.h"

CrazyZombie::CrazyZombie()
    : m_timeElapsed(0.0f)
{
    m_speed = 20.0f;
}

CrazyZombie::~CrazyZombie()
{

}

void CrazyZombie::onEnter()
{
    Monster::onEnter();

    float scaleFactor = CCDirector::sharedDirector()->getContentScaleFactor();
    m_pMainSprite = CCSprite::create("CrazyZombie.png",CCRectMake(0, 0, 32 / scaleFactor, 48 / scaleFactor));
    addChild(m_pMainSprite);
}

void CrazyZombie::onExit()
{
    Monster::onExit();
}


void CrazyZombie::Killed()
{
    const float dropRate = 0.2f;

    if (RandomFloat(0.0f, 1.0f) < dropRate)
    {
        TimeFreezeItem* pItem = new TimeFreezeItem();
        pItem->setPosition(getPosition());
        getParent()->addChild(pItem);
    }

    Unspawn();
}

int CrazyZombie::GetDetailTypeIndex()
{
    return static_cast<int>(eMT_CrazyZombie);
}

void CrazyZombie::PlayMonsterWalkAnimation()
{
    float scaleFactor = CCDirector::sharedDirector()->getContentScaleFactor();

    float x = 32 / scaleFactor;
    float y = 48 / scaleFactor;

    CCSpriteFrame *frame0=CCSpriteFrame::create("CrazyZombie.png",CCRectMake(0, 0, x, y)); 
    CCSpriteFrame *frame1=CCSpriteFrame::create("CrazyZombie.png",CCRectMake(x, 0, x, y)); 
    CCSpriteFrame *frame2=CCSpriteFrame::create("CrazyZombie.png",CCRectMake(x*2, 0, x, y)); 
    CCSpriteFrame *frame3=CCSpriteFrame::create("CrazyZombie.png",CCRectMake(x*3, 0, x, y)); 

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

    IMPLEMENT_STATE_BEGIN(CrazyZombie, Move)
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
