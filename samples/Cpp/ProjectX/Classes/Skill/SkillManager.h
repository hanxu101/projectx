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
    void Init();
    void Update(float deltaTime);
    void Uninit();

    bool Execute(ESkillType type, float time);

    void AddSkillNum(ESkillType type, int num);

private:

    typedef std::vector<SkillBase*> TSkillVector;
    TSkillVector m_skillVec;

    int m_skillNum[eST_Count];
};

#endif // _APP_SkillManager_H_