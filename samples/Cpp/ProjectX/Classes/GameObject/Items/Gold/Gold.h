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
    OVERLOAD_FSM(Gold);
};

#endif // _APP_Gold_H_