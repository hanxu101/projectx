#ifndef  _APP_MonsterGroupLogic_H_
#define  _APP_MonsterGroupLogic_H_

#include "cocos2d.h"
#include "FSM/FsmInclude.h"

USING_NS_CC;

typedef std::vector< std::vector<bool> > TMonsterDataVec;

class MonsterGroupLogic : public CCNode
{
public:
    MonsterGroupLogic();
    virtual ~MonsterGroupLogic();

    virtual void onEnter();
    virtual void onExit();

    void StateUpdate(float deltaTime);

private:
    MMR_DECLARE_FSM(MonsterGroupLogic);
    MMR_DECLARE_STATE(Idle);
    MMR_DECLARE_STATE(Activate);

    void MonsterLineWave(float dt);
    void SpawnMonster(float positionX);

    void InitMonsterData();
    void AddOneLine(bool line1, bool line2, bool line3, bool line4, bool line5);

    CCTimer* m_pTimer;

    TMonsterDataVec m_monsterData;

    unsigned int m_monsterLineWaveCount;
};

#endif //_APP_MonsterGroupLogic_H_