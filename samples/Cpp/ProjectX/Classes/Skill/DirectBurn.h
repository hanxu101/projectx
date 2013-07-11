#ifndef  _APP_DirectBurn_H_
#define  _APP_DirectBurn_H_

#include "Skill/SkillBase.h"

class DirectBurn : public SkillBase
{
    typedef SkillBase super;

public:
    DirectBurn();
    virtual ~DirectBurn();

    virtual void OnUpdate(float deltaTime);
    virtual void Uninit();

};

#endif // _APP_DirectBurn_H_
