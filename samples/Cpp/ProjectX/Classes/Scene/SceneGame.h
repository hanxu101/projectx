#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "SceneBase.h"

USING_NS_CC;

class MonsterGroupLogic;
class GeneralGroupLogic;
class GpeLogic;
class FireBall;

namespace cs{class CocoPanel;}

class GameLayer: public CCLayer
{
public:
    GameLayer(void);
    ~GameLayer(void);
    bool init();

    virtual std::string title();
    virtual void onEnter();
    virtual void onExit();

    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

    CREATE_FUNC(GameLayer)

private:
    void Update(float dt);  
    CCPoint CalculateDirection(int touchId);
    CCPoint CalculateSpinForce(int touchId);
    float CalculateSlideSpeedFactor(float slideDistance); 
    void UpdateTouchInfo(float dt);
    UINT GetPreviousTouchPosIndex( UINT rollbackFrameNum, UINT maxCacheNumber );

    void PrintMoveInfo();   // Debug
    void FakeInput();       // Debug

private:
    typedef std::map< int, CCPoint> TTouchPointMap;
    TTouchPointMap m_currentTouchPointMap;

    MonsterGroupLogic* m_pMonsterGroupLogic;
    GeneralGroupLogic* m_pGeneralGroupLogic;
    GpeLogic*          m_pGpeLogic;

    typedef std::map< int, std::vector<CCPoint> > TPreviousTouchPosVecMap;
    TPreviousTouchPosVecMap m_previousTouchPosVec;
    const static UINT8 PREVIOUS_TOUCHPOSITION_CACHE_NUM = 5;
    const static CCPoint INVALID_TOUCHPOSITION;
    const static float FIRE_SLIDE_DISTANCE_MAX;
    const static float FIRE_SLIDE_DISTANCE_MIN;
    const static float FIRE_TOUCH_TIME_THRESHOLD;
    const static UINT8 MULTI_TOUCH_SUPPORT_NUMBER = 3;

    typedef std::map< int, BOOL> TTouchIsTouchFlagMap;
    TTouchIsTouchFlagMap m_isTouching;

    typedef std::map< int, UINT> TTouchFrameCountMap;
    TTouchFrameCountMap m_touchFrameCount;
    
    typedef std::map< int, float > TTouchTimerMap;
    TTouchTimerMap m_touchTimer;
    
    FireBall* m_fireBall;
    CCMotionStreak* m_pStreak;

    cs::CocoPanel* m_pGameUI;
};

class SceneGame : public SceneBase
{
public:
    virtual void runThisTest();
};

#endif
