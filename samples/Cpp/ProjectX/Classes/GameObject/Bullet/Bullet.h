#ifndef  _APP_Bullet_H_
#define  _APP_Bullet_H_

#include "GameObject/GameObject.h"

USING_NS_CC;

class Bullet : public GameObject 
{
public:
    Bullet();
    virtual ~Bullet();

    virtual void onEnter();
    virtual void onExit();

    virtual void StateUpdate(float deltaTime);

protected:
    DECLARE_FSM(Bullet);
    DECLARE_VIRTUAL_STATE(Idle);
    DECLARE_VIRTUAL_STATE(Move);
    DECLARE_VIRTUAL_STATE(ArrivedBottomSafe);

    CCSprite* m_pMainSprite;
    CCParticleGalaxy* m_pParticle;

    CCPoint m_targetPos;
    CCPoint m_direction;

    float m_speed;
    float m_deltaTime;
};

#endif // _APP_Bullet_H_