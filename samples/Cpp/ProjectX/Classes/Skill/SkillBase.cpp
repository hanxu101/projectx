#include "CommonHeaders.h"

#include "Skill/SkillBase.h"

SkillBase::SkillBase()
    : m_type(eST_Invalid)
    , m_lastTime(0.0f)
{

}

SkillBase::~SkillBase()
{

}

void SkillBase::Init()
{

}

bool SkillBase::Update( float deltaTime )
{
    m_lastTime -= deltaTime;
    if (m_lastTime < 0.0f)
        return false;
    
    OnUpdate();

    return true;
}

void SkillBase::OnUpdate()
{

}

void SkillBase::Uninit()
{

}

ESkillType SkillBase::GetType()
{
    return m_type;
}

void SkillBase::SetTime( float time )
{
    m_lastTime = time;
}
