#ifndef  _APP_AirMonster_H_
#define  _APP_AirMonster_H_

#include "GameObject/Monster.h"

USING_NS_CC;

class CrazyZombie : public Monster 
{
public:
    CrazyZombie();
    virtual ~CrazyZombie();

    virtual void onEnter();
    virtual void onExit();

    virtual void Killed();

    virtual int GetDetailTypeIndex();

private:
    void PlayMonsterWalkAnimation();

    MMR_OVERLOAD_FSM(CrazyZombie);
    MMR_DECLARE_VIRTUAL_STATE(Move);

    float m_timeElapsed;
};

#endif // _APP_AirMonster_H_