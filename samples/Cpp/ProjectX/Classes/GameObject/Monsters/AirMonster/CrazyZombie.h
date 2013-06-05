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

    virtual void StateUpdate(float deltaTime);

    virtual void Killed();

    virtual int GetDetailTypeIndex();

private:
    void PlayMonsterWalkAnimation();

    MMR_DECLARE_FSM(CrazyZombie);
    MMR_DECLARE_STATE(Idle);
    MMR_DECLARE_STATE(Move);
    MMR_DECLARE_STATE(ArrivedBottomSafe);

    CCSprite* m_pMainSprite;

    CCPoint m_targetPos;
    CCPoint m_direction;
    float m_speed;
    float m_deltaTime;

    float m_timeElapsed;
};

#endif // _APP_AirMonster_H_