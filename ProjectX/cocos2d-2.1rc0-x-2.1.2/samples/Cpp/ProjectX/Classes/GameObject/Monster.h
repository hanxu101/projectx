#ifndef  _APP_Monster_H_
#define  _APP_Monster_H_

#include "GameObject/GameObject.h"

USING_NS_CC;

class Monster : public GameObject 
{
public:
    Monster();
    virtual ~Monster();

    virtual void onEnter();
    virtual void onExit();

    void StateUpdate(float deltaTime);

private:
    void PlayMonsterWalkAnimation();

    MMR_DECLARE_FSM(Monster);
    MMR_DECLARE_STATE(Idle);
    MMR_DECLARE_STATE(Move);
    MMR_DECLARE_STATE(Dead);

    CCSprite* m_pMainSprite;

    CCPoint m_targetPos;
    CCPoint m_direction;
    float m_speed;
    float m_deltaTime;
};

#endif // _APP_Monster_H_