#ifndef  _APP_BOOMERANG_H_
#define  _APP_BOOMERANG_H_

#include "GameObject/FireBall/FireBall.h"

USING_NS_CC;

class Boomerang : public FireBall
{
public:
    Boomerang();
    virtual ~Boomerang();

    virtual void onEnter();

private:
    MMR_OVERLOAD_FSM(Boomerang);
    MMR_DECLARE_VIRTUAL_STATE(Move);

private:
    float m_acceleration;
};

#endif // _APP_BOOMERANG_H_