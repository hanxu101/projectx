#ifndef  _APP_MainCharacter_H_
#define  _APP_MainCharacter_H_

#include "GameObject/GameObject.h"

USING_NS_CC_EXT;

class MainCharacter : public GameObject, public CCTargetedTouchDelegate 
{
public:
    MainCharacter();
    virtual ~MainCharacter();

    virtual void onEnter();
    virtual void onExit();

    void StateUpdate(float deltaTime);

    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouche, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouche, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouche, CCEvent *pEvent);

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
    
    UIButton* m_pLeftButton;
    UIButton* m_pRightButton;
};

#endif // _APP_MainCharacter_H_