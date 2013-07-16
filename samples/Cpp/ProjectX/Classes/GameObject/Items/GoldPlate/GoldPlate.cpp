#include "CommonHeaders.h"

#include "GameObject/Items/GoldPlate/GoldPlate.h"
#include "Gamelogic/MainPlayerLogic.h"

GoldPlate::GoldPlate()
    : m_clickedTime(0)
{

}

GoldPlate::~GoldPlate()
{

}

void GoldPlate::onEnter()
{
    Item::onEnter();

    m_pMainSprite = CCSprite::create("Coin.png");
    addChild(m_pMainSprite);

    INIT_FSM(Idle);
}

void GoldPlate::onExit()
{
    Item::onExit();
}

void GoldPlate::StateUpdate(float deltaTime)
{
    m_deltaTime = deltaTime;
    GetFsm().Update();
}

int GoldPlate::GetDetailTypeIndex()
{
    return static_cast<int>(eIT_Gold);
}

void GoldPlate::ItemTouchesEnded()
{
    if (++m_clickedTime > 10)
    {
        MainPlayerLogic::Singleton().IncreaseCoin(1000);
        Unspawn();
    }
    else
    {
        MainPlayerLogic::Singleton().IncreaseCoin(1);
    }   
}