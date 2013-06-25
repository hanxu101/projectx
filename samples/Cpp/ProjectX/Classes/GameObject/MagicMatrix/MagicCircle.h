#ifndef  _APP_MagicCircle_H_
#define  _APP_MagicCircle_H_

#include "GameObject/GameObject.h"

USING_NS_CC;

class MagicCircle : public GameObject, public CCTargetedTouchDelegate
{
    typedef std::vector<CCPoint> TPointVector;

public:
    MagicCircle();
    MagicCircle(const TPointVector& magicPointVector, float durationTime);
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

    TPointVector m_magicPointVector;
    float m_elapsedTime;
    float m_durationTime;
};

#endif // _APP_MagicCircle_H_