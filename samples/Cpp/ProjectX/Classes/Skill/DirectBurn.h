#ifndef  _APP_DirectBurn_H_
#define  _APP_DirectBurn_H_

#include "Skill/SkillBase.h"

class DirectBurn : public SkillBase
{
public:
    DirectBurn();
    virtual ~DirectBurn();

    virtual void OnUpdate();
    virtual void Uninit();
};

#endif // _APP_DirectBurn_H_
