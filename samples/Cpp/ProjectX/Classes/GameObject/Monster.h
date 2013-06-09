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

    virtual void StateUpdate(float deltaTime);

protected:
    MMR_DECLARE_FSM(Monster);
    MMR_DECLARE_VIRTUAL_STATE(Idle);
    MMR_DECLARE_VIRTUAL_STATE(Move);
    MMR_DECLARE_VIRTUAL_STATE(ArrivedBottomSafe);

    CCSprite* m_pMainSprite;

    CCPoint m_targetPos;
    CCPoint m_direction;

    float m_speed;
    float m_deltaTime;
};

#endif // _APP_Monster_H_