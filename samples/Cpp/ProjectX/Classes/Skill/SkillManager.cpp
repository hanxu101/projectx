#include "CommonHeaders.h"

#include "Skill/SkillManager.h"
#include "Skill/SkillBase.h"
#include "Skill/CommonSkill.h"
#include "Skill/DirectBurn.h"
#include "Skill/FireWall.h"
#include "Ui/UiManager.h"

IMPLEMENT_SINGLETON(SkillManager);

SkillManager::SkillManager()
    : m_layer(NULL)
    , m_commonSkill(NULL)
    , m_secondarySkill(NULL)
{
}

SkillManager::~SkillManager()
{

}

void SkillManager::Init(CCLayer* layer)
{
    m_layer = layer;

    for (int i = 0; i < eST_Count; ++i)
    {
        m_skillNum[i] = 3;
    }

    m_commonSkill = SetupSkill(eST_Common, false, 0.0f);

    UIButton* buttonSkill1 = DynamicCast<UIButton*>(UiManager::Singleton().GetChildByName("ButtonSkill1"));
    UIButton* buttonSkill2 = DynamicCast<UIButton*>(UiManager::Singleton().GetChildByName("ButtonSkill2"));

    buttonSkill1->addReleaseEvent(this, coco_releaseselector(SkillManager::Skill1BottonClicked));
    buttonSkill2->addReleaseEvent(this, coco_releaseselector(SkillManager::Skill2BottonClicked));
    buttonSkill1->addPushDownEvent(this, coco_releaseselector(SkillManager::SkillBottonPushDown));
    buttonSkill2->addPushDownEvent(this, coco_releaseselector(SkillManager::SkillBottonPushDown));
}

void SkillManager::Update(float deltaTime)
{
    // Update Secondary Skill.
    if (m_secondarySkill && !m_secondarySkill->Update(deltaTime))
    {
        m_secondarySkill->Uninit();
        m_layer->removeChild(m_secondarySkill);
        m_secondarySkill = NULL;
        m_commonSkill->Init();
    }

    // If there is no Secondary skill, update common skill.
    if (!m_secondarySkill)
        m_commonSkill->Update(deltaTime);
    
}

void SkillManager::Uninit()
{
    if (m_commonSkill)
    {
        m_commonSkill->Uninit();
        m_layer->removeChild(m_commonSkill);
        m_commonSkill = NULL;
    }

    if (m_secondarySkill)
    {
        m_secondarySkill->Uninit();
        m_layer->removeChild(m_secondarySkill);
        m_secondarySkill = NULL;
    }
}

SkillBase* SkillManager::SetupSkill( ESkillType type, bool hasTimeLimit, float time )
{
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
        pSkill->SetHasTimeLimit(hasTimeLimit);
        pSkill->SetTime(time);
        pSkill->autorelease();
        m_layer->addChild(pSkill);

        if (type != eST_Common)
            --m_skillNum[type];

        return pSkill;
    }

    return NULL;

}

void SkillManager::AddSkillNum( ESkillType type, int num )
{
    m_skillNum[type] += num;
}

bool SkillManager::LaunchSecondarySkill( ESkillType type, bool hasTimeLimit, float time )
{
    bool hadSecondarySkill = m_secondarySkill != NULL;
    if (hadSecondarySkill)
    {
        if (m_skillNum[type] > 0) // switch to a new skill
        {
            m_secondarySkill->Uninit();
            m_layer->removeChild(m_secondarySkill);
            m_secondarySkill = NULL;
        }
    }

    if (m_skillNum[type] > 0) // setup new skill
    {
        m_secondarySkill = SetupSkill(type, hasTimeLimit, time);
        if (!hadSecondarySkill && m_secondarySkill)
            m_commonSkill->Uninit();
    }
    
    return m_secondarySkill != NULL;
}

void SkillManager::Skill1BottonClicked( CCObject* pSender )
{
    LaunchSecondarySkill(eST_DirectBurn, true, 10.0f);
}

void SkillManager::Skill2BottonClicked( CCObject* pSender )
{
    LaunchSecondarySkill(eST_FireWall, true, 10.0f);
}

void SkillManager::SkillBottonPushDown( CCObject* pSender )
{
    UiManager::Singleton().SetIsInUi(true);
}
