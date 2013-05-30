#ifndef  _APP_FireBall_H_
#define  _APP_FireBall_H_

#include "cocos2d.h"
#include "FSM/FsmInclude.h"

USING_NS_CC;

class FireBall : public CCNode, public CCTargetedTouchDelegate 
{
public:
    FireBall();
    virtual ~FireBall();

    virtual void onEnter();
    virtual void onExit();

    void StateUpdate(float deltaTime);

    void SetDirection(CCPoint direction);
private:
    MMR_DECLARE_FSM(FireBall);
    MMR_DECLARE_STATE(Idle);
    MMR_DECLARE_STATE(Move);
    MMR_DECLARE_STATE(Dead);

    CCSprite* m_pMainSprite;
    CCPoint m_targetPos;
    CCPoint m_direction;
    float m_speed;
    float m_deltaTime;
};

#endif // _APP_FireBall_H_