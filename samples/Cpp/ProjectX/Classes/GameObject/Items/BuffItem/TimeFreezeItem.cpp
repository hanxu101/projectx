#include "CommonHeaders.h"

#include "GameObject/Items/BuffItem/TimeFreezeItem.h"
#include "Buff/TimeBuff/TimeBuff.h"

TimeFreezeItem::TimeFreezeItem()
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
    return static_cast<int>(eIT_TimeFreezeItem);
}

void TimeFreezeItem::ItemTouchesEnded()
{
    TimeBuff* pBuff = new TimeBuff(3.0f);
    getParent()->addChild(pBuff);

    Unspawn();
}