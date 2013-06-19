#include "CommonHeaders.h"

#include "GameObject/Items/BuffItem/TimeFreezeItem.h"
#include "Buff/TimeBuff/TimeBuff.h"

TimeFreezeItem::TimeFreezeItem()
    : m_pMainSprite(NULL)
    , m_speed(20.0f)
    , m_deltaTime(0.0f)
{

}

TimeFreezeItem::~TimeFreezeItem()
{

}

void TimeFreezeItem::onEnter()
{
    Item::onEnter();

    m_pMainSprite = CCSprite::create("Clock.png");
    addChild(m_pMainSprite);

    INIT_FSM(Idle);
}

void TimeFreezeItem::onExit()
{
    Item::onExit();
}

void TimeFreezeItem::StateUpdate(float deltaTime)
{
    m_deltaTime = deltaTime;
    GetFsm().Update();
}

int TimeFreezeItem::GetDetailTypeIndex()
{
    return static_cast<int>(eMT_StoneMan);
}

void TimeFreezeItem::PlayMonsterWalkAnimation()
{
    //     CCAnimation* pAnim = CCAnimation::create();
    //     char str[20];
    // 
    //     for (UINT i = 0; i < 6; ++i)
    //     {
    //         sprintf(str,"Hero01_%d.png",i);
    //         pAnim->addSpriteFrameWithFileName(str);
    //     }
    // 
    //     pAnim->setDelayPerUnit(0.1f);
    //     pAnim->setRestoreOriginalFrame(true);
    // 
    //     m_pMainSprite->runAction(CCRepeatForever::create(CCAnimate::create(pAnim)));
}

void TimeFreezeItem::ItemTouchesEnded()
{
    TimeBuff* pBuff = new TimeBuff(3.0f);
    getParent()->addChild(pBuff);

    Unspawn();
}

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_STATE_BEGIN(TimeFreezeItem, Idle)
{
    STATE_CONSTRUCTOR_BEGIN
    {
    }
    STATE_CONSTRUCTOR_END

        STATE_UPDATE_BEGIN
    {      
        SWITCH_TO_STATE(Move);
    }
    STATE_UPDATE_END

        STATE_DESTRUCTOR_BEGIN
    {
    }
    STATE_DESTRUCTOR_END
}
IMPLEMENT_STATE_END

    IMPLEMENT_STATE_BEGIN(TimeFreezeItem, Move)
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

    IMPLEMENT_STATE_BEGIN(TimeFreezeItem, ArrivedBottomSafe)
{
    STATE_CONSTRUCTOR_BEGIN
    {
        Unspawn();
    }
    STATE_CONSTRUCTOR_END

        STATE_UPDATE_BEGIN
    {      
    }
    STATE_UPDATE_END

        STATE_DESTRUCTOR_BEGIN
    {
    }
    STATE_DESTRUCTOR_END
}
IMPLEMENT_STATE_END