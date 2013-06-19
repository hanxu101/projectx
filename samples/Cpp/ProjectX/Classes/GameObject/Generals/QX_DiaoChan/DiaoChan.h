#ifndef  _APP_DIAOCHAN_H_
#define  _APP_DIAOCHAN_H_

#include "GameObject/Generals/General.h"

USING_NS_CC;

class DiaoChan : public General 
{
public:
    DiaoChan();
    virtual ~DiaoChan();

    virtual void onEnter();
    virtual void onExit();

private:
    OVERLOAD_FSM(DiaoChan);
    DECLARE_VIRTUAL_STATE(CastSkill);
};

#endif // _APP_DIAOCHAN_H_