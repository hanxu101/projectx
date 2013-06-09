#ifndef  _APP_EarthMonster_H_
#define  _APP_EarthMonster_H_

#include "GameObject/Monster.h"

USING_NS_CC;

class StoneMan : public Monster 
{
public:
    StoneMan();
    virtual ~StoneMan();

    virtual void onEnter();
    virtual void onExit();

    virtual void Killed();

    virtual int GetDetailTypeIndex();

private:
    void PlayMonsterWalkAnimation();

    MMR_OVERLOAD_FSM(StoneMan);
    MMR_DECLARE_VIRTUAL_STATE(Move);
};

#endif // _APP_EarthMonster_H_