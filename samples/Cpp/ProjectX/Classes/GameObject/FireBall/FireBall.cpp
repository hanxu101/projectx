#include "GameObject/FireBall.h"
#include "Utilities/Utilities.h"
#include "VisibleRect.h"
#include "GameObject/GameObjectManager/GameObjectManager.h"
#include "GameObject/GameObject.h"

FireBall::FireBall()
    : GameObject(0.0f, eGOT_Bullet,10.0f)
    , m_pMainSprite(NULL)
    , m_targetPos(CCPoint(0.0f, 0.0f))
    , m_direction(CCPoint(0.0f, 0.0f))
    , m_speed(0.0f)
    , m_deltaTime(0.0f)
    , m_force(CCPoint(0.0f, 0.0f))
    , m_forceLength(0.0f)
    , m_forceDirection(CCPoint(0.0f, 0.0f))
    , m_maxSpeed(400.0f)
    , m_forceFactor(1.0f)
    , m_attackPoint(10.0f)
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

    MMR_INIT_FSM(Idle);
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
    GameObjectManager::Get().GetGameObjectList(eGOT_Monster, objectList);
    for (TGameObjectList::iterator iter = objectList.begin(); iter != objectList.end(); ++iter)
    {
        float maxCollisionDis = (*iter)->GetCollisionRadius() + GetCollisionRadius();
        float distanceSQ = ccpDistanceSQ((*iter)->getPosition(), getPosition());

        if (distanceSQ < maxCollisionDis * maxCollisionDis)
        {
            (*iter)->ReduceHp(m_attackPoint);
        }
    }
}

//////////////////////////////////////////////////////////////////////////
// Switch State
void FireBall::SetAbort()
{
    GetFsm().SwitchState(MMR_STATE(Abort));
}

void FireBall::SetMove()
{
    GetFsm().SwitchState(MMR_STATE(Move));
}

//////////////////////////////////////////////////////////////////////////
// States
MMR_IMPLEMENT_STATE_BEGIN(FireBall, Idle)
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

    MMR_IMPLEMENT_STATE_BEGIN(FireBall, Move)
{
    MMR_STATE_CONSTRUCTOR_BEGIN
    {
        m_moveForce = ccpNormalize(m_force);

        m_direction = ccpNormalize(m_direction);
        m_forceLength = ccpLength(m_force);
        m_forceDirection = ccpNormalize(m_force);
        m_forceDirectionSpeed = 0.0f;
    }
    MMR_STATE_CONSTRUCTOR_END

        MMR_STATE_UPDATE_BEGIN
    {
        m_forceDirectionSpeed += m_forceLength*m_forceFactor;
        CCPoint offset(ccpAdd(ccpMult(m_direction, m_speed), ccpMult(m_moveForce, m_forceDirectionSpeed)));
        offset = ccpMult(ccpNormalize(offset), m_speed * m_deltaTime); // make speed constant

        CCPoint newPos = ccpAdd(getPosition(), offset);
        setPosition(newPos);

        Attack();

        MMR_TRANSIT_TO_STATE( !VisibleRect::getVisibleRect().containsPoint(newPos), NoTransitionAction, Dead );
    }
    MMR_STATE_UPDATE_END

        MMR_STATE_DESTRUCTOR_BEGIN
    {
    }
    MMR_STATE_DESTRUCTOR_END
}
MMR_IMPLEMENT_STATE_END

    MMR_IMPLEMENT_STATE_BEGIN(FireBall, Dead)
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

    MMR_IMPLEMENT_STATE_BEGIN(FireBall, Abort)
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