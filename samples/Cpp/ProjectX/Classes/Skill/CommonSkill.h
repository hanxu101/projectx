#ifndef PROJECTX_TRUNK_SAMPLES_CPP_PROJECTX_CLASSES_SKILL_COMMONSKILL_H__INCLUDED
#define PROJECTX_TRUNK_SAMPLES_CPP_PROJECTX_CLASSES_SKILL_COMMONSKILL_H__INCLUDED

class FireBall;

#include "Skill/SkillBase.h"

class CommonSkill : public SkillBase, public CCNode, public CCTargetedTouchDelegate
{
public:
    CommonSkill();
    virtual ~CommonSkill();

    virtual void Init();
    virtual void OnUpdate(float deltaTime);
    virtual void Uninit();

    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

private:
    void UpdateTouchInfo(float dt);
    UINT GetPreviousTouchPosIndex( UINT rollbackFrameNum, UINT maxCacheNumber );
    CCPoint CalculateDirection(int touchId);
    CCPoint CalculateSpinForce(int touchId);
    float CalculateSlideSpeedFactor(float slideDistance);
    void PrintMoveInfo();   // Debug
    void FakeInput();       // Debug


private:
    typedef std::map< int, CCPoint> TTouchPointMap;
    TTouchPointMap m_currentTouchPointMap;

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
};

#endif // PROJECTX_TRUNK_SAMPLES_CPP_PROJECTX_CLASSES_SKILL_COMMONSKILL_H__INCLUDED
