#include "GameObject/Monsters/AirMonster/CrazyZombie.h"
#include "VisibleRect.h"
#include "GameObject/Items/BuffItem/TimeFreezeItem.h"
#include "utilities/Utilities.h"

CrazyZombie::CrazyZombie()
    : m_pMainSprite(NULL)
    , m_speed(30.0f)
    , m_deltaTime(0.0f)
    , m_timeElapsed(0.0f)
{

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

    MMR_INIT_FSM(Idle);
}

void CrazyZombie::onExit()
{
    Monster::onExit();
}

void CrazyZombie::StateUpdate(float deltaTime)
{
    m_deltaTime = deltaTime;
    GetFsm().Update();
}

void CrazyZombie::Killed()
{
    const float dropRate = 0.2f;

<<<<<<< .mine
	if (RandomFloat(0.0f, 1.0f) < dropRate)
	{
		TimeFreezeItem* pItem = new TimeFreezeItem();
		pItem->setPosition(getPosition());
		getParent()->addChild(pItem);
	}
=======
    if (RandomFloat(0.0f, 1.0f) < dropRate)
    {
        TimeFreezeItem* pItem = new TimeFreezeItem();
        pItem->setPosition(getPosition());
        getParent()->addChild(pItem);
    }
>>>>>>> .r33

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

MMR_IMPLEMENT_STATE_BEGIN(CrazyZombie, Idle)
{
    MMR_STATE_CONSTRUCTOR_BEGIN
    {
        // Set suitable position.
        const float monsterRoadSizeRate = 0.2f;
        const float offset = 0.5f;
        setPosition((int(getPosition().x / (VisibleRect::right().x * monsterRoadSizeRate)) + offset) * VisibleRect::right().x * monsterRoadSizeRate, getPosition().y);
        setScale(3.0f);
    }
    MMR_STATE_CONSTRUCTOR_END

        MMR_STATE_UPDATE_BEGIN
    {      
        MMR_SWITCH_TO_STATE(Move);
    }
    MMR_STATE_UPDATE_END

        MMR_STATE_DESTRUCTOR_BEGIN
    {
    }
    MMR_STATE_DESTRUCTOR_END
}
MMR_IMPLEMENT_STATE_END

    MMR_IMPLEMENT_STATE_BEGIN(CrazyZombie, Move)
{
    MMR_STATE_CONSTRUCTOR_BEGIN
    {
        PlayMonsterWalkAnimation();

        m_targetPos = CCPoint(getPosition().x, VisibleRect::bottom().y);
        m_direction = ccpSub(m_targetPos, getPosition());
        m_direction = ccpNormalize(m_direction);
    }
    MMR_STATE_CONSTRUCTOR_END

        MMR_STATE_UPDATE_BEGIN
    {
        m_timeElapsed += m_deltaTime;

        if (m_timeElapsed > 2.0f)
            m_speed = 150.0f + (m_timeElapsed - 2.0f) * 100.0f;

        CCPoint newPos =  ccpAdd( getPosition(), ccpMult(ccpMult(m_direction, m_speed), m_deltaTime) );
        setPosition(newPos);

        MMR_TRANSIT_TO_STATE( !VisibleRect::getVisibleRect().containsPoint(newPos), NoTransitionAction, ArrivedBottomSafe );
    }
    MMR_STATE_UPDATE_END

        MMR_STATE_DESTRUCTOR_BEGIN
    {
        m_timeElapsed = 0.0f;
    }
    MMR_STATE_DESTRUCTOR_END
}
MMR_IMPLEMENT_STATE_END

    MMR_IMPLEMENT_STATE_BEGIN(CrazyZombie, ArrivedBottomSafe)
{
    MMR_STATE_CONSTRUCTOR_BEGIN
    {
        Unspawn();
    }
    MMR_STATE_CONSTRUCTOR_END

        MMR_STATE_UPDATE_BEGIN
    {      
    }
    MMR_STATE_UPDATE_END

        MMR_STATE_DESTRUCTOR_BEGIN
    {
    }
    MMR_STATE_DESTRUCTOR_END
}
MMR_IMPLEMENT_STATE_END