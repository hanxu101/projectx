#ifndef  _APP_MagicPoint_H_
#define  _APP_MagicPoint_H_

#include "GameObject/GameObject.h"

namespace cs{class CocoImageView;}

USING_NS_CC;

class MagicPoint : public GameObject, public CCTargetedTouchDelegate
{
public:
    MagicPoint();
    virtual ~MagicPoint();

    virtual void onEnter();
    virtual void onExit();

protected:
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    
    cs::CocoImageView* m_pPointImage;
};

#endif // _APP_MagicPoint_H_