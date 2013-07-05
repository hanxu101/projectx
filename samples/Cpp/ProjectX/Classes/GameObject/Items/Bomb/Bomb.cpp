#include "CommonHeaders.h"

#include "GameObject/Items/Bomb/Bomb.h"
#include "GameObject/GameObjectManager/GameObjectManager.h"

Bomb::Bomb()
{

}

Bomb::~Bomb()
{

}

void Bomb::onEnter()
{
    Item::onEnter();

    m_pMainSprite = CCSprite::create("Bomb.png");
    addChild(m_pMainSprite);

    INIT_FSM(Idle);
}

void Bomb::onExit()
{
    Item::onExit();
}

void Bomb::StateUpdate(float deltaTime)
{
    m_deltaTime = deltaTime;
    GetFsm().Update();
}

int Bomb::GetDetailTypeIndex()
{
    return static_cast<int>(eIT_Bomb);
}

void Bomb::ItemTouchesEnded()
{
    Attack();

    Unspawn();
}

void Bomb::Attack()
{
    TGameObjectList objectList;
    if (GameObjectManager::IsSingletonCreated())
        GameObjectManager::Singleton().GetGameObjectList(eGOT_Monster, objectList);

    for (TGameObjectList::iterator iter = objectList.begin(); iter != objectList.end(); ++iter)
    {
        if ((*iter)->getPositionY() - getPositionY() < 6.0f)
        {
            (*iter)->ReduceHp(10.0f);
        }
    }
}