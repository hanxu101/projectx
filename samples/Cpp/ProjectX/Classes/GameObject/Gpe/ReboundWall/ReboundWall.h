#ifndef  _APP_ReboundWall_H_
#define  _APP_ReboundWall_H_

#include "GameObject/Gpe/Gpe.h"

class FireBall;

USING_NS_CC;

class ReboundWall : public Gpe 
{
public:
    ReboundWall();
    virtual ~ReboundWall();

    virtual void onEnter();
    void StateUpdate(float deltaTime);

    void SetSize(float right, float left, float bottom, float top, CCPoint center);
    float GetLeft() const;
    float GetRight() const;

    void SetRange(float upRange, float downRange);

    void SetSpeed(float speed);

    virtual void draw();

private:
    void CheckRedboud();
    void ReboundFireBall( FireBall* fireBall );

    DECLARE_FSM(ReboundWall);
    DECLARE_VIRTUAL_STATE(Idle);
    DECLARE_VIRTUAL_STATE(Move);

private:
    CCSprite* m_pMainSprite;
    float m_deltaTime;

    float m_right;
    float m_left;
    float m_bottom;
    float m_top;
    CCPoint m_center;

    float m_upRange;
    float m_downRange;

    float m_speed;
};

#endif // _APP_ReboundWall_H_
