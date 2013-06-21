#ifndef  _APP_GpeLogic_H_
#define  _APP_GpeLogic_H_

#include "utilities/FSM/FsmInclude.h"
#include "GameObject/GameObjectEnum.h"

class Gpe;

USING_NS_CC;

class GpeLogic : public CCNode
{
public:
    GpeLogic();
    virtual ~GpeLogic();
    virtual void onEnter();

private:
    void InitGpe();

private:
    typedef std::vector< Gpe* > TGpeVec;
    TGpeVec m_gpeVec;
};

#endif //_APP_GpeLogic_H_