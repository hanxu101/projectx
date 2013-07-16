#ifndef  _APP_DirectBurn_H_
#define  _APP_DirectBurn_H_

#include "Skill/SkillBase.h"

class FireBall;

class DirectBurn : public SkillBase
{
    typedef SkillBase super;

public:
    DirectBurn();
    virtual ~DirectBurn();
    virtual void Uninit();
    
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

private:
    FireBall* m_fireBall;
    CCMotionStreak* m_pStreak;

};

#endif // _APP_DirectBurn_H_
