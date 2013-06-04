#ifndef  _APP_FireBall_H_
#define  _APP_FireBall_H_

#include "GameObject/GameObject.h"

USING_NS_CC;

class FireBall : public GameObject, public CCTargetedTouchDelegate 
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

    // State
    void SetAbort();
    void SetMove();

private:
    MMR_DECLARE_FSM(FireBall);
    MMR_DECLARE_STATE(Idle);
    MMR_DECLARE_STATE(Move);
    MMR_DECLARE_STATE(Dead);
    MMR_DECLARE_STATE(Abort);

    CCSprite* m_pMainSprite;
    CCPoint m_targetPos;
    CCPoint m_direction;
    float m_speed;
    float m_deltaTime;
    CCPoint m_force;

    // configurable variables
    float m_maxSpeed;
};

#endif // _APP_FireBall_H_