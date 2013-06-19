#ifndef  _APP_MonsterGroupLogic_H_
#define  _APP_MonsterGroupLogic_H_

#include "utilities/FSM/FsmInclude.h"
#include "GameObject/GameObjectEnum.h"

USING_NS_CC;

typedef std::vector< std::vector<EMonsterType> > TMonsterDataVec;

class MonsterGroupLogic : public CCNode
{
public:
    MonsterGroupLogic();
    virtual ~MonsterGroupLogic();

    virtual void onEnter();
    virtual void onExit();

    void StateUpdate(float deltaTime);

private:
    DECLARE_FSM(MonsterGroupLogic);
    DECLARE_STATE(Idle);
    DECLARE_STATE(Activate);

    void MonsterLineWave(float dt);
    void SpawnMonster(float positionX, EMonsterType type);

    void InitMonsterData();
    void AddOneLine(EMonsterType line1, EMonsterType line2, EMonsterType line3, EMonsterType line4, EMonsterType line5);

    CCTimer* m_pTimer;

    TMonsterDataVec m_monsterData;

    unsigned int m_monsterLineWaveCount;
};

#endif //_APP_MonsterGroupLogic_H_