#include "CommonHeaders.h"

#include "GameObject/Items/Bomb/Bomb.h"
#include "GameObject/GameObjectManager/GameObjectManager.h"

static const float g_bombExplosionRange = 30.0f;
static const float g_bombAttackDamage = 10.0f;

Bomb::Bomb()
    : m_lifeTime(2.0f)
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
        if (abs((*iter)->getPositionY() - getPositionY()) < g_bombExplosionRange)
        {
            (*iter)->ReduceHp(g_bombAttackDamage);
        }
    }
}

IMPLEMENT_STATE_BEGIN(Bomb, Move)
{
    STATE_CONSTRUCTOR_BEGIN
    {
    }
    STATE_CONSTRUCTOR_END

        STATE_UPDATE_BEGIN
    {      
        m_lifeTime -= m_deltaTime;
        TRANSIT_TO_STATE( m_lifeTime < 0.0f, NoTransitionAction, ArrivedBottomSafe );
    }
    STATE_UPDATE_END

        STATE_DESTRUCTOR_BEGIN
    {
    }
    STATE_DESTRUCTOR_END
}
IMPLEMENT_STATE_END