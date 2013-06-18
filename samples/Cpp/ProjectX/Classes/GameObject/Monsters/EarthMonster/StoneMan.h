#ifndef  _APP_EarthMonster_H_
#define  _APP_EarthMonster_H_

#include "GameObject/Monsters/Monster.h"

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

    OVERLOAD_FSM(StoneMan);
    DECLARE_VIRTUAL_STATE(Move);
};

#endif // _APP_EarthMonster_H_