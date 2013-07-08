#ifndef  _APP_CRAZYZOMBIEBOMBER_H_
#define  _APP_CRAZYZOMBIEBOMBER_H_

#include "GameObject/Monsters/Monster.h"

USING_NS_CC;

class CrazyZombieBomber : public Monster 
{
public:
    CrazyZombieBomber();
    virtual ~CrazyZombieBomber();

    virtual void onEnter();
    virtual void onExit();

    virtual void Killed();

    virtual int GetDetailTypeIndex();

private:
    void PlayMonsterWalkAnimation();

    OVERLOAD_FSM(CrazyZombieBomber);
    DECLARE_VIRTUAL_STATE(Move);

    float m_timeElapsed;
};

#endif // _APP_CRAZYZOMBIEBOMBER_H_