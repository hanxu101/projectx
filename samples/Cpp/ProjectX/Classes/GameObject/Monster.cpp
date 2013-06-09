#include "GameObject/Monster.h"
#include "VisibleRect.h"

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

    MMR_INIT_FSM(Idle);
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

MMR_IMPLEMENT_STATE_BEGIN(Monster, Idle)
{
    MMR_STATE_CONSTRUCTOR_BEGIN
    {
        // Set suitable position.
        const float monsterRoadSizeRate = 0.2f;
        const float offset = 0.5f;
        setPosition((int(getPosition().x / (VisibleRect::right().x * monsterRoadSizeRate)) + offset) * VisibleRect::right().x * monsterRoadSizeRate, getPosition().y);
        setScale(4.0f);
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

    MMR_IMPLEMENT_STATE_BEGIN(Monster, Move)
{
    MMR_STATE_CONSTRUCTOR_BEGIN
    {
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

    MMR_IMPLEMENT_STATE_BEGIN(Monster, ArrivedBottomSafe)
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