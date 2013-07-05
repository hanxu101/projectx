#ifndef  _APP_Item_H_
#define  _APP_Item_H_

#include "GameObject/GameObject.h"

USING_NS_CC;

class Item : public GameObject, public CCStandardTouchDelegate
{
public:
    Item();
    virtual ~Item();

    virtual void onEnter();
    virtual void onExit();

    virtual void StateUpdate(float deltaTime);

protected:
    void registerWithTouchDispatcher();
    void unregisterWithTouchDispatcher();

    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

    virtual void ItemTouchesEnded() = 0;

    DECLARE_FSM(Item);
    DECLARE_VIRTUAL_STATE(Idle);
    DECLARE_VIRTUAL_STATE(Move);
    DECLARE_VIRTUAL_STATE(ArrivedBottomSafe);

    CCSprite* m_pMainSprite;

    CCPoint m_targetPos;
    CCPoint m_direction;
    float m_speed;
    float m_deltaTime;
};

#endif // _APP_Monster_H_