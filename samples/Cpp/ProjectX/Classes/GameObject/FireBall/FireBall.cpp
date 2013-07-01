#include "CommonHeaders.h"

#include "GameObject/FireBall/FireBall.h"
#include "GameObject/GameObjectManager/GameObjectManager.h"
#include "GameObject/GameObject.h"
#include "Gamelogic/MainPlayerLogic.h"

FireBall::FireBall()
    : GameObject(0.0f, eGOT_FireBall,10.0f)
    , m_pMainSprite(NULL)
    , m_targetPos(CCPoint(0.0f, 0.0f))
    , m_direction(CCPoint(0.0f, 0.0f))
    , m_speed(0.0f)
    , m_deltaTime(0.0f)
    , m_force(CCPoint(0.0f, 0.0f))
    , m_forceLength(0.0f)
    , m_forceDirection(CCPoint(0.0f, 0.0f))
    , m_comboAttackCount(0)
    , m_maxSpeed(400.0f)
    , m_forceFactor(10.0f)
    , m_attackPoint(10.0f)
    , m_canRebound(true)
{
}

FireBall::~FireBall()
{
}

void FireBall::onEnter()
{
    GameObject::onEnter();

    m_pMainSprite = CCSprite::create("ball.png");
    m_pMainSprite->setScale(4.0f);

    addChild(m_pMainSprite);

    INIT_FSM(Idle);
}

void FireBall::onExit()
{
    GameObject::onExit();
}

void FireBall::StateUpdate(float deltaTime)
{
    m_deltaTime = deltaTime;
    GetFsm().Update();
}

void FireBall::SetDirection(CCPoint direction)
{
    m_direction = direction;
    m_forceDirectionSpeed = 0.0f;
}

const CCPoint& FireBall::GetDirection() const
{
    return m_direction;
}

void FireBall::SetSpeedFactor( float slideSpeed )
{
    m_speed = m_maxSpeed * slideSpeed;
}

void FireBall::SetForce(CCPoint force)
{
    m_force = force;
}

const CCPoint& FireBall::GetForce() const
{
    return m_force;
}

void FireBall::Attack()
{    
    TGameObjectList objectList;
    if (GameObjectManager::IsSingletonCreated())
        GameObjectManager::Singleton().GetGameObjectList(eGOT_Monster, objectList);
    for (TGameObjectList::iterator iter = objectList.begin(); iter != objectList.end(); ++iter)
    {
        float maxCollisionDis = (*iter)->GetCollisionRadius() + GetCollisionRadius();
        float distanceSQ = ccpDistanceSQ((*iter)->getPosition(), getPosition());

        if (distanceSQ < maxCollisionDis * maxCollisionDis)
        {
            (*iter)->ReduceHp(m_attackPoint);
            ++m_comboAttackCount;
            AddBonus();
        }
    }
}

void FireBall::AddBonus()
{
    // if the attacked 1-5, the bonus * 1
    // if the attacked > 5, the bouns * n
    if ( m_comboAttackCount < 5 )
        MainPlayerLogic::Singleton().IncreaseCoin(1);
    else
        MainPlayerLogic::Singleton().IncreaseCoin(m_comboAttackCount);
}

bool FireBall::CanRebound() const
{
    return m_canRebound;
}

void FireBall::SetCanRebound(bool canRebound)
{
    m_canRebound = canRebound;
}

//////////////////////////////////////////////////////////////////////////
// Switch State
void FireBall::SetAbort()
{
    GetFsm().SwitchState(STATE(Abort));
}

void FireBall::SetMove()
{
    GetFsm().SwitchState(STATE(Move));
}

//////////////////////////////////////////////////////////////////////////
// States
IMPLEMENT_STATE_BEGIN(FireBall, Idle)
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

    IMPLEMENT_STATE_BEGIN(FireBall, Move)
{
    STATE_CONSTRUCTOR_BEGIN
    {
        m_direction = ccpNormalize(m_direction);
        m_forceLength = ccpLength(m_force);
        m_forceDirection = ccpNormalize(m_force);
        m_forceDirectionSpeed = 0.0f;

		m_comboAttackCount = 0;
    }
    STATE_CONSTRUCTOR_END

        STATE_UPDATE_BEGIN
    {
        m_forceDirectionSpeed += m_forceLength*m_forceFactor;
        CCPoint offset(ccpAdd(ccpMult(m_direction, m_speed), ccpMult(ccpNormalize(m_force), m_forceDirectionSpeed)));
        offset = ccpMult(ccpNormalize(offset), m_speed * m_deltaTime); // make speed constant

        CCPoint newPos = ccpAdd(getPosition(), offset);
        setPosition(newPos);

        Attack();

        TRANSIT_TO_STATE( !VisibleRect::getVisibleRect().containsPoint(newPos), NoTransitionAction, Dead );
    }
    STATE_UPDATE_END

        STATE_DESTRUCTOR_BEGIN
    {
    }
    STATE_DESTRUCTOR_END
}
IMPLEMENT_STATE_END

    IMPLEMENT_STATE_BEGIN(FireBall, Dead)
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

    IMPLEMENT_STATE_BEGIN(FireBall, Abort)
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
