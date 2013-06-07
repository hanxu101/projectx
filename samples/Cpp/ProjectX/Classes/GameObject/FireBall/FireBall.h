#ifndef  _APP_FireBall_H_
#define  _APP_FireBall_H_

#include "GameObject/GameObject.h"

USING_NS_CC;

class FireBall : public GameObject
{
public:
    FireBall();
    virtual ~FireBall();

    virtual void onEnter();
    virtual void onExit();

    void StateUpdate(float deltaTime);

    void SetDirection(CCPoint direction);
    void SetSpeedFactor(float slideSpeed);
    void SetForce(CCPoint force);
    const CCPoint& GetDirection() const;
    const CCPoint& GetForce() const;

    // State
    void SetAbort();
    void SetMove();

protected:
    void Attack();

    MMR_DECLARE_FSM(FireBall);
    MMR_DECLARE_VIRTUAL_STATE(Idle);
    MMR_DECLARE_VIRTUAL_STATE(Move);
    MMR_DECLARE_VIRTUAL_STATE(Dead);
    MMR_DECLARE_VIRTUAL_STATE(Abort);

    CCSprite* m_pMainSprite;
    CCPoint m_targetPos;
    CCPoint m_direction;
    float m_speed;
    float m_deltaTime;
    CCPoint m_force;
    float m_forceLength;
    CCPoint m_forceDirection;
    float m_forceDirectionSpeed;

    CCPoint m_moveForce;

    // configurable variables
    float m_maxSpeed;
    float m_forceFactor;
    float m_attackPoint;
};

#endif // _APP_FireBall_H_