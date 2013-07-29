#ifndef  _APP_SkillManager_H_
#define  _APP_SkillManager_H_

class SkillBase;

enum ESkillType
{
    eST_Common,
    eST_FireWall,
    eST_DirectBurn,

    eST_Count,
    eST_Invalid
};


class SkillManager : public CCNode
{
    DECLARE_SINGLETON(SkillManager);

public:
    void Init(CCLayer* layer);
    void Update(float deltaTime);
    void Uninit();

    bool LaunchSecondarySkill(ESkillType type, bool hasTimeLimit, float time);
    void AddSkillNum(ESkillType type, int num);

private:
    SkillBase* SetupSkill(ESkillType type, bool hasTimeLimit, float time);
    void Skill1BottonClicked( CCObject* pSender );
    void Skill2BottonClicked( CCObject* pSender );
    void SkillBottonPushDown( CCObject* pSender );

private:
    CCLayer* m_layer;
    SkillBase* m_commonSkill;
    SkillBase* m_secondarySkill;
    int m_skillNum[eST_Count];
};

#endif // _APP_SkillManager_H_