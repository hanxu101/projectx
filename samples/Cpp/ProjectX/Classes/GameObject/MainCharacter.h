#ifndef  _APP_MainCharacter_H_
#define  _APP_MainCharacter_H_

#include "GameObject/GameObject.h"

USING_NS_CC;

class MainCharacter : public GameObject, public CCTargetedTouchDelegate 
{
public:
    MainCharacter();
    virtual ~MainCharacter();

    virtual void onEnter();
    virtual void onExit();

    void StateUpdate(float deltaTime);

private:
    void PlayHeroTestAnimation();

    DECLARE_FSM(MainCharacter);
    DECLARE_STATE(Idle);

    CCSprite* m_pMainSprite;
};

#endif // _APP_MainCharacter_H_