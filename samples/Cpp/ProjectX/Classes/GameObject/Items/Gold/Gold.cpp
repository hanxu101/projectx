#include "CommonHeaders.h"

#include "GameObject/Items/Gold/Gold.h"
#include "Gamelogic/MainPlayerLogic.h"

Gold::Gold()
{

}

Gold::~Gold()
{

}

void Gold::onEnter()
{
    Item::onEnter();

    m_pMainSprite = CCSprite::create("Coin.png");
    addChild(m_pMainSprite);

    INIT_FSM(Idle);
}

void Gold::onExit()
{
    Item::onExit();
}

void Gold::StateUpdate(float deltaTime)
{
    m_deltaTime = deltaTime;
    GetFsm().Update();
}

int Gold::GetDetailTypeIndex()
{
    return static_cast<int>(eIT_Gold);
}

void Gold::ItemTouchesEnded()
{
    MainPlayerLogic::Singleton().IncreaseCoin(1);

    Unspawn();
}