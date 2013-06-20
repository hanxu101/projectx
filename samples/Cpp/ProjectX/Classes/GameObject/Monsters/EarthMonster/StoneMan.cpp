#include "CommonHeaders.h"

#include "GameObject/Monsters/EarthMonster/StoneMan.h"

StoneMan::StoneMan()
{
    m_speed = 28.0f;
}

StoneMan::~StoneMan()
{
}

void StoneMan::onEnter()
{
    Monster::onEnter();

    float scaleFactor = CCDirector::sharedDirector()->getContentScaleFactor();
    m_pMainSprite = CCSprite::create("StoneMan.png",CCRectMake(0, 0, 32 / scaleFactor, 48 / scaleFactor));
    addChild(m_pMainSprite);
}

void StoneMan::onExit()
{
    Monster::onExit();
}

void StoneMan::Killed()
{
    Unspawn();
}

int StoneMan::GetDetailTypeIndex()
{
    return static_cast<int>(eMT_StoneMan);
}

void StoneMan::PlayMonsterWalkAnimation()
{
    float scaleFactor = CCDirector::sharedDirector()->getContentScaleFactor();

    float x = 32 / scaleFactor;
    float y = 48 / scaleFactor;

    CCSpriteFrame *frame0=CCSpriteFrame::create("StoneMan.png",CCRectMake(0, 0, x, y)); 
    CCSpriteFrame *frame1=CCSpriteFrame::create("StoneMan.png",CCRectMake(x, 0, x, y)); 
    CCSpriteFrame *frame2=CCSpriteFrame::create("StoneMan.png",CCRectMake(x*2, 0, x, y)); 
    CCSpriteFrame *frame3=CCSpriteFrame::create("StoneMan.png",CCRectMake(x*3, 0, x, y)); 

    CCArray *animFrames = new CCArray; 
    animFrames->addObject(frame0); 
    animFrames->addObject(frame1); 
    animFrames->addObject(frame2); 
    animFrames->addObject(frame3); 

    CCAnimation *pAnim = CCAnimation::createWithSpriteFrames(animFrames, 0.1f); 
    animFrames->release();

    m_pMainSprite->runAction(CCRepeatForever::create(CCAnimate::create(pAnim)));
}

//////////////////////////////////////////////////////////////////////////

    IMPLEMENT_STATE_BEGIN(StoneMan, Move)
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
        CCPoint newPos =  ccpAdd( getPosition(), ccpMult(ccpMult(m_direction, m_speed), m_deltaTime) );
        setPosition(newPos);

        TRANSIT_TO_STATE( !VisibleRect::getVisibleRect().containsPoint(newPos), NoTransitionAction, ArrivedBottomSafe );
    }
    STATE_UPDATE_END

        STATE_DESTRUCTOR_BEGIN
    {
    }
    STATE_DESTRUCTOR_END
}
    IMPLEMENT_STATE_END