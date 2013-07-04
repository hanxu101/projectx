#ifndef  _APP_Gold_H_
#define  _APP_Gold_H_

#include "GameObject/Items/Item.h"

USING_NS_CC;

class Gold : public Item
{
public:
    Gold();
    virtual ~Gold();

    virtual void onEnter();
    virtual void onExit();

    virtual void StateUpdate(float deltaTime);

    virtual int GetDetailTypeIndex();

    virtual void ItemTouchesEnded();

private:
    void PlayMonsterWalkAnimation();

    DECLARE_FSM(Gold);
    DECLARE_STATE(Idle);
    DECLARE_STATE(Move);
    DECLARE_STATE(ArrivedBottomSafe);

    CCSprite* m_pMainSprite;

    CCPoint m_targetPos;
    CCPoint m_direction;
    float m_speed;
    float m_deltaTime;
};

#endif // _APP_Gold_H_