#ifndef  _APP_SkillBase_H_
#define  _APP_SkillBase_H_

#include "Skill/SkillManager.h"

class SkillBase : public CCNode, public CCTargetedTouchDelegate
{
public:
    SkillBase();
    virtual ~SkillBase();
    
    virtual void Init();
    bool Update(float deltaTime);
    virtual void Uninit();
    virtual void Reset();

    ESkillType GetType();

    void SetTime(float time);
    void SetHasTimeLimit(bool flag);

protected:
    virtual void OnUpdate(float deltaTime);

protected:
    ESkillType m_type;
    float m_lastTime;
    bool m_hasTimeLimit;
};

#endif // _APP_SkillBase_H_
