#ifndef  _APP_MagicPoint_H_
#define  _APP_MagicPoint_H_

#include "GameObject/GameObject.h"

USING_NS_CC;

class MagicPoint : public GameObject, public CCStandardTouchDelegate
{
public:
    MagicPoint();
    virtual ~MagicPoint();

    virtual void onEnter();
    virtual void onExit();

protected:
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
};

#endif // _APP_MagicPoint_H_