#ifndef  _APP_TimeFreezeItem_H_
#define  _APP_TimeFreezeItem_H_

#include "GameObject/Items/Item.h"

USING_NS_CC;

class TimeFreezeItem : public Item
{
public:
    TimeFreezeItem();
    virtual ~TimeFreezeItem();

    virtual void onEnter();
    virtual void onExit();

    virtual void StateUpdate(float deltaTime);

    virtual int GetDetailTypeIndex();

    virtual void ItemTouchesEnded();

private:
    OVERLOAD_FSM(TimeFreezeItem);
};

#endif // _APP_TimeFreezeItem_H_