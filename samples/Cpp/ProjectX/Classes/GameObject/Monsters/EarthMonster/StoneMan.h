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

    virtual void StateUpdate(float deltaTime);

    virtual void Killed();

    virtual int GetDetailTypeIndex();

private:
    void PlayMonsterWalkAnimation();

    MMR_DECLARE_FSM(StoneMan);
    MMR_DECLARE_STATE(Idle);
    MMR_DECLARE_STATE(Move);
    MMR_DECLARE_STATE(ArrivedBottomSafe);

    CCSprite* m_pMainSprite;

    CCPoint m_targetPos;
    CCPoint m_direction;
    float m_speed;
    float m_deltaTime;
};

#endif // _APP_EarthMonster_H_