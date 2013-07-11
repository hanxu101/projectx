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


class SkillManager
{
    DECLARE_SINGLETON(SkillManager);

public:
    void Init(CCLayer* layer);
    void Update(float deltaTime);
    void Uninit();

    bool Execute(ESkillType type, bool hasTimeLimit, float time);

    void AddSkillNum(ESkillType type, int num);

    typedef std::vector<SkillBase*> TSkillVector;
    void GetSkill(ESkillType type, SkillManager::TSkillVector& skillVec);

private:
    CCLayer* m_layer;
    TSkillVector m_skillVec;

    int m_skillNum[eST_Count];
};

#endif // _APP_SkillManager_H_