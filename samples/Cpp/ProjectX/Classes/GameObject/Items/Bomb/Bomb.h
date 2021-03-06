#ifndef  _APP_Bomb_H_
#define  _APP_Bomb_H_

#include "GameObject/Items/Item.h"

USING_NS_CC;

class Bomb : public Item
{
public:
    Bomb();
    virtual ~Bomb();

    virtual void onEnter();
    virtual void onExit();

    virtual void StateUpdate(float deltaTime);

    virtual int GetDetailTypeIndex();

    virtual void ItemTouchesEnded();

private:
    OVERLOAD_FSM(Bomb);
    DECLARE_VIRTUAL_STATE(Move);

    void Attack();

    float m_lifeTime;
};

#endif // _APP_Bomb_H_