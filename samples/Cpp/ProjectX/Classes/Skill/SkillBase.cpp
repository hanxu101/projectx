#include "CommonHeaders.h"

#include "Skill/SkillBase.h"

SkillBase::SkillBase()
    : m_type(eST_Invalid)
    , m_lastTime(0.0f)
    , m_hasTimeLimit(true)
{

}

SkillBase::~SkillBase()
{

}

void SkillBase::Init()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 2);
}

bool SkillBase::Update( float deltaTime )
{
    if (m_hasTimeLimit)
    {
        m_lastTime -= deltaTime;
        if (m_lastTime < 0.0f)
            return false;
    }
    
    OnUpdate(deltaTime);

    return true;
}

void SkillBase::OnUpdate(float deltaTime)
{

}

void SkillBase::Uninit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void SkillBase::Reset()
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

void SkillBase::SetHasTimeLimit( bool flag )
{
    m_hasTimeLimit = flag;
}
