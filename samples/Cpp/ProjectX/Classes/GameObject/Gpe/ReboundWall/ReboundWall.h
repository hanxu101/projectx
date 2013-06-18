#ifndef  _APP_ReboundWall_H_
#define  _APP_ReboundWall_H_

#include "GameObject/GameObject.h"

USING_NS_CC;

class ReboundWall : public GameObject 
{
public:
    ReboundWall();
    virtual ~ReboundWall();

    virtual void onEnter();
    void StateUpdate(float deltaTime);

private:
    DECLARE_FSM(ReboundWall);
    DECLARE_VIRTUAL_STATE(Idle);

    CCSprite* m_pMainSprite;
    float m_deltaTime;

};

#endif // _APP_ReboundWall_H_
