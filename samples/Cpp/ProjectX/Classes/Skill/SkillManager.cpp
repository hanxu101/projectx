#include "CommonHeaders.h"

#include "Skill/SkillManager.h"
#include "Skill/SkillBase.h"
#include "Skill/CommonSkill.h"
#include "Skill/DirectBurn.h"
#include "Skill/FireWall.h"

IMPLEMENT_SINGLETON(SkillManager);

SkillManager::SkillManager()
{
}

SkillManager::~SkillManager()
{

}

void SkillManager::Init()
{
    for (int i = 0; i < eST_Count; ++i)
    {
        m_skillNum[i] = 3;
    }

    Execute(eST_Common, 0.0f);
}

void SkillManager::Update(float deltaTime)
{
    TSkillVector::iterator iter = m_skillVec.begin();
    for (; iter != m_skillVec.end();)
    {
        if ((*iter)->Update(deltaTime))
        {
            ++iter;
        }
        else
        {
            (*iter)->Uninit();
            CC_SAFE_DELETE(*iter);
            iter = m_skillVec.erase(iter);
        }
    }
}

void SkillManager::Uninit()
{

}

bool SkillManager::Execute( ESkillType type, float time )
{
    bool result = false;

    if (m_skillNum[type] > 0)
    {
        SkillBase* pSkill = NULL;
        switch(type)
        {
        case eST_Common:
            pSkill = new CommonSkill();
            break;
        case eST_FireWall:
            pSkill = new FireWall();
            break;
        case eST_DirectBurn:
            pSkill = new DirectBurn();
            break;
        default:
            XAssert(false, "Invalid Skill Type.");
            break;
        }

        pSkill->Init();
        pSkill->SetTime(time);
        m_skillVec.push_back(pSkill);

        if (type != eST_Common)
            --m_skillNum[type];

        result = true;
    }

    return result;

}

void SkillManager::AddSkillNum( ESkillType type, int num )
{
    m_skillNum[type] += num;
}

void SkillManager::GetSkill( ESkillType type, SkillManager::TSkillVector& skillVec)
{
    skillVec.clear();

    for (TSkillVector::iterator iter = m_skillVec.begin(); iter != m_skillVec.end(); ++iter)
    {
        if ((*iter)->GetType() == type)
            skillVec.push_back(*iter);
    }
}
