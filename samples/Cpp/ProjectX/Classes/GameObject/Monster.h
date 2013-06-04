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
};

#endif // _APP_Monster_H_