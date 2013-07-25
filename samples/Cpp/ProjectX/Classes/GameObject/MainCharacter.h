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
    void BottonLeftPushDown( CCObject* pSender );
    void BottonLeftCacel( CCObject* pSender );
    void BottonLeftRelease( CCObject* pSender );
    void BottonLeftMove( CCObject* pSender );

    void BottonRightPushDown( CCObject* pSender );
    void BottonRightCacel( CCObject* pSender );
    void BottonRightRelease( CCObject* pSender );
    void BottonRightMove( CCObject* pSender );

    void PlayHeroTestAnimation();

    DECLARE_FSM(MainCharacter);
    DECLARE_STATE(Idle);
private:
    CCSprite* m_pMainSprite;
    float m_speed;
};

#endif // _APP_MainCharacter_H_