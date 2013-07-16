#ifndef  _APP_GoldPlate_H_
#define  _APP_GoldPlate_H_

#include "GameObject/Items/Item.h"

USING_NS_CC;

class GoldPlate : public Item
{
public:
    GoldPlate();
    virtual ~GoldPlate();

    virtual void onEnter();
    virtual void onExit();

    virtual void StateUpdate(float deltaTime);

    virtual int GetDetailTypeIndex();

    virtual void ItemTouchesEnded();

private:
    OVERLOAD_FSM(GoldPlate);

    unsigned int m_clickedTime;
};

#endif // _APP_GoldPlate_H_