#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "SceneBase.h"

USING_NS_CC;

class MainCharacter;
class FireBall;

class GameLayer: public CCLayer
{
protected:
	MainCharacter* m_pMainCharacter;
	FireBall* m_pFireBall;

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
};

class SceneGame : public SceneBase
{
public:
	virtual void runThisTest();
};

#endif
