#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "SceneBase.h"

USING_NS_CC;

class MonsterGroupLogic;
class FireBall;

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

    float CalculateSlideSpeedFactor(float slideDistance); 
    void UpdateTouchInfo(float dt);
    CCPoint GetPreviousTouchPos( UINT rollbackFrameNum );

private:
    CCPoint m_currentTouchLocation;
    bool m_isTouching;
    UINT m_touchFrameCount;

    MonsterGroupLogic* m_pMonsterGroupLogic;

    std::vector<CCPoint> m_previousTouchPosVec;
    const static UINT8 PREVIOUS_TOUCHPOSITION_CACHE_NUM = 3;
    const static CCPoint INVALID_TOUCHPOSITION;
    const static float FIRE_SLIDE_DISTANCE_MAX;
    const static float FIRE_SLIDE_DISTANCE_MIN;
    const static float FIRE_TOUCH_TIME_THRESHOLD;
    float m_touchTimer;
    FireBall* m_fireBall;
};

class SceneGame : public SceneBase
{
public:
    virtual void runThisTest();
};

#endif
