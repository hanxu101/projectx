#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "SceneBase.h"

USING_NS_CC;

class MonsterGroupLogic;

class GameLayer: public CCLayer
{
public:
    GameLayer(void);
    ~GameLayer(void);
    bool init();

    virtual std::string title();
    virtual void onEnter();

    virtual void registerWithTouchDispatcher(void);
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

    CREATE_FUNC(GameLayer)

private:
    void Update(float dt);  

	float m_fireSlideThreshold;
    CCPoint m_touchBeginLocation;

    MonsterGroupLogic* m_pMonsterGroupLogic;
};

class SceneGame : public SceneBase
{
public:
    virtual void runThisTest();
};

#endif
