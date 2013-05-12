#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "SceneBase.h"

USING_NS_CC;

class GameLayer: public CCLayer
{
protected:
    CCSprite* m_pBall;
    double    m_fLastTime;

public:
    GameLayer(void);
    ~GameLayer(void);

    virtual void didAccelerate(CCAcceleration* pAccelerationValue);

    virtual std::string title();
    virtual void onEnter();
};

class SceneGame : public SceneBase
{
public:
    virtual void runThisTest();
};

#endif
