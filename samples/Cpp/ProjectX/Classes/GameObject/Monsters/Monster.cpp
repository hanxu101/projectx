#include "CommonHeaders.h"

#include "GameObject/Monsters/Monster.h"
#include "Gamelogic/MainPlayerLogic.h"

Monster::Monster()
    : GameObject(10.0f, eGOT_Monster,10.0f)
    , m_pMainSprite(NULL)
    , m_targetPos(CCPointZero)
    , m_direction(CCPointZero)
    , m_speed(0.0f)
    , m_deltaTime(0.0f)
{
}

Monster::~Monster()
{
}

void Monster::onEnter()
{
    GameObject::onEnter();

    INIT_FSM(Idle);
}

void Monster::onExit()
{
    GameObject::onExit();
}

void Monster::StateUpdate( float deltaTime )
{
    m_deltaTime = deltaTime;
    GetFsm().Update();
}

IMPLEMENT_STATE_BEGIN(Monster, Idle)
{
    STATE_CONSTRUCTOR_BEGIN
    {
        // Set suitable size | postion.  TODO...
        setScale(2.0f);
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

    IMPLEMENT_STATE_BEGIN(Monster, Move)
{
    STATE_CONSTRUCTOR_BEGIN
    {
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

    IMPLEMENT_STATE_BEGIN(Monster, ArrivedBottomSafe)
{
    STATE_CONSTRUCTOR_BEGIN
    {
        MainPlayerLogic::Singleton().ReduceHp(1);
        MainPlayerLogic::Singleton().IncreaseCoin(1);
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