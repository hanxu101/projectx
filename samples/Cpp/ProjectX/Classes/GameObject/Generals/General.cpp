#include "CommonHeaders.h"

#include "GameObject/Generals/General.h"

General::General()
    : GameObject(10.0f, eGOT_General,10.0f)
    , m_pMainSprite(NULL)
    , m_elapasedTime(0.0f)
{
}

General::~General()
{
}

void General::onEnter()
{
    GameObject::onEnter();

    INIT_FSM(Idle);
}

void General::onExit()
{
    GameObject::onExit();
}

void General::StateUpdate( float deltaTime )
{
    m_elapasedTime += deltaTime;
    GetFsm().Update();
}

IMPLEMENT_STATE_BEGIN(General, Idle)
{
    STATE_CONSTRUCTOR_BEGIN
    {
    }
    STATE_CONSTRUCTOR_END

        STATE_UPDATE_BEGIN
    {      
        SWITCH_TO_STATE(ShowUp);
    }
    STATE_UPDATE_END

        STATE_DESTRUCTOR_BEGIN
    {
    }
    STATE_DESTRUCTOR_END
}
IMPLEMENT_STATE_END


    IMPLEMENT_STATE_BEGIN(General, ShowUp)
{
    STATE_CONSTRUCTOR_BEGIN
    {
        // Play show up animation...
    }
    STATE_CONSTRUCTOR_END

        STATE_UPDATE_BEGIN
    {
        SWITCH_TO_STATE(CastSkill);
    }
    STATE_UPDATE_END

        STATE_DESTRUCTOR_BEGIN
    {
    }
    STATE_DESTRUCTOR_END
}
IMPLEMENT_STATE_END


    IMPLEMENT_STATE_BEGIN(General, CastSkill)
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


    IMPLEMENT_STATE_BEGIN(General, Dead)
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