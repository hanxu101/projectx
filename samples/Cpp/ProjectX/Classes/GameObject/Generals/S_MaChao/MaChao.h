#ifndef  _APP_MACHAO_H_
#define  _APP_MACHAO_H_

#include "GameObject/Generals/General.h"

USING_NS_CC;

class MaChao : public General 
{
public:
    MaChao();
    virtual ~MaChao();

    virtual void onEnter();
    virtual void onExit();

private:
    void Attack();

    OVERLOAD_FSM(MaChao);
    DECLARE_VIRTUAL_STATE(CastSkill);
};

#endif // _APP_MACHAO_H_