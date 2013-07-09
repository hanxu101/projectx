#ifndef  _APP_SkillBase_H_
#define  _APP_SkillBase_H_

#include "Skill/SkillManager.h"

class SkillBase
{
public:
    SkillBase();
    virtual ~SkillBase();
    
    virtual void Init();
    bool Update(float deltaTime);

    virtual void Uninit();

    ESkillType GetType();

    void SetTime(float time);

protected:
    virtual void OnUpdate();

protected:
    ESkillType m_type;
    float m_lastTime;
};

#endif // _APP_SkillBase_H_
