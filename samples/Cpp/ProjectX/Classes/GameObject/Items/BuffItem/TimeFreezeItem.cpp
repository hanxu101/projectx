#include "GameObject/Items/BuffItem/TimeFreezeItem.h"
#include "VisibleRect.h"
#include "Buff/Buff.h"

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

    m_pMainSprite = CCSprite::create("Hero01_0.png");
    addChild(m_pMainSprite);

    MMR_INIT_FSM(Idle);
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
    CCAnimation* pAnim = CCAnimation::create();
    char str[20];

    for (UINT i = 0; i < 6; ++i)
    {
        sprintf(str,"Hero01_%d.png",i);
        pAnim->addSpriteFrameWithFileName(str);
    }

    pAnim->setDelayPerUnit(0.1f);
    pAnim->setRestoreOriginalFrame(true);

    m_pMainSprite->runAction(CCRepeatForever::create(CCAnimate::create(pAnim)));
}

void TimeFreezeItem::ItemTouchesEnded()
{
    GetFsm().SwitchState(MMR_STATE(Dead));
}

//////////////////////////////////////////////////////////////////////////

MMR_IMPLEMENT_STATE_BEGIN(TimeFreezeItem, Idle)
{
    MMR_STATE_CONSTRUCTOR_BEGIN
    {
        // Set suitable position.
        const float monsterRoadSizeRate = 0.2f;
        const float offset = 0.5f;
        setPosition((int(getPosition().x / (VisibleRect::right().x * monsterRoadSizeRate)) + offset) * VisibleRect::right().x * monsterRoadSizeRate + 10, getPosition().y);
        setScale(2.0f);
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

    MMR_IMPLEMENT_STATE_BEGIN(TimeFreezeItem, Move)
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
        CCPoint newPos =  ccpAdd( getPosition(), ccpMult(ccpMult(m_direction, m_speed), m_deltaTime) );
        setPosition(newPos);

        MMR_TRANSIT_TO_STATE( !VisibleRect::getVisibleRect().containsPoint(newPos), NoTransitionAction, Dead );
    }
    MMR_STATE_UPDATE_END

        MMR_STATE_DESTRUCTOR_BEGIN
    {
    }
    MMR_STATE_DESTRUCTOR_END
}
MMR_IMPLEMENT_STATE_END

    MMR_IMPLEMENT_STATE_BEGIN(TimeFreezeItem, Dead)
{
    MMR_STATE_CONSTRUCTOR_BEGIN
    {
        Buff* pBuff = new Buff(eBT_Good, 5.0f);
        getParent()->addChild(pBuff);

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