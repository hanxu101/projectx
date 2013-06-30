#ifndef  _APP_MagicCircle_H_
#define  _APP_MagicCircle_H_

#include "GameObject/GameObject.h"

USING_NS_CC;

class MagicCircle : public GameObject, public CCTargetedTouchDelegate
{
    typedef std::vector<CCPoint> TPointVector;

public:
    MagicCircle();
    MagicCircle(const TPointVector& magicPointVector, float durationTime, EGeneralType type);
    virtual ~MagicCircle();

    virtual void onEnter();
    virtual void onExit();

    virtual void StateUpdate(float deltaTime);

    bool IsSucceed();
    bool IsFailed();

protected:
    DECLARE_FSM(MagicCircle);
    DECLARE_STATE(Idle);
    DECLARE_STATE(Operating);
    DECLARE_STATE(Succeed);
    DECLARE_STATE(Failed);
    DECLARE_STATE(Dead);

    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouche, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouche, CCEvent *pEvent);

    void AddGraphics();
    void DelGraphics();

    EGeneralType m_associateGType;

    TPointVector m_magicPointVector;
    float m_elapsedTime;
    float m_durationTime;

    CCSprite* m_pMainSprite;
    CCMotionStreak* m_pStreak;
};

#endif // _APP_MagicCircle_H_