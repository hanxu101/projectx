#ifndef  _APP_GENERAL_H_
#define  _APP_GENERAL_H_

#include "GameObject/GameObject.h"

namespace cs{class CocoImageView;}
class MagicCircle;

USING_NS_CC;

typedef std::vector<CCPoint> TPointVector;

class General : public GameObject 
{
public:
    General();
    virtual ~General();

    virtual void onEnter();
    virtual void onExit();

    virtual void StateUpdate(float deltaTime);

protected:
    DECLARE_FSM(General);
    DECLARE_VIRTUAL_STATE(Idle);
    DECLARE_VIRTUAL_STATE(ReadyToShowUp);
    DECLARE_VIRTUAL_STATE(ShowUp);
    DECLARE_VIRTUAL_STATE(CastSkill);
    DECLARE_VIRTUAL_STATE(Dead);

    CCSprite* m_pMainSprite;
    cs::CocoImageView* m_pProfileImage;

    float m_elapasedTime;

    MagicCircle* m_magicCircle;
    TPointVector m_magicPointVec;
};

#endif // _APP_GENERAL_H_