#include "CommonHeaders.h"

#include "GameLogic/MonsterGroupLogic.h"
#include "GameObject/Monsters/Monster.h"
#include "GameObject/Monsters/EarthMonster/StoneMan.h"
#include "GameObject/Monsters/AirMonster/CrazyZombie.h"
#include "GameObject/GameObjectManager/GameObjectManager.h"
#include "GameObject/Monsters/MonsterFactory/MonsterFactory.h"

MonsterGroupLogic::MonsterGroupLogic()
    : m_monsterLineWaveCount(0)
{
}

MonsterGroupLogic::~MonsterGroupLogic()
{
    m_monsterData.clear();
}

void MonsterGroupLogic::onEnter()
{
    CCNode::onEnter();

    InitMonsterData();

    INIT_FSM(Idle);
}

void MonsterGroupLogic::InitMonsterData()
{
    for (UINT i = 0; i < 15; ++i)
    {
        AddOneLine(eMT_Invalid,eMT_CrazyZombie,eMT_CrazyZombie,eMT_CrazyZombie,eMT_CrazyZombieBomber,eMT_CrazyZombie,eMT_CrazyZombie,eMT_CrazyZombie,eMT_CrazyZombie,eMT_Invalid);
        AddOneLine(eMT_Invalid,eMT_Invalid,eMT_Invalid,eMT_Invalid,eMT_CrazyZombie,eMT_CrazyZombie,eMT_Invalid,eMT_Invalid,eMT_Invalid,eMT_Invalid);
        AddOneLine(eMT_Invalid,eMT_Invalid,eMT_Invalid,eMT_Invalid,eMT_StoneMan,eMT_StoneMan,eMT_Invalid,eMT_Invalid,eMT_Invalid,eMT_Invalid);
        AddOneLine(eMT_Invalid,eMT_Invalid,eMT_Invalid,eMT_StoneMan,eMT_Invalid,eMT_Invalid,eMT_StoneMan,eMT_Invalid,eMT_Invalid,eMT_Invalid);
        AddOneLine(eMT_Invalid,eMT_Invalid,eMT_StoneMan,eMT_Invalid,eMT_Invalid,eMT_Invalid,eMT_Invalid,eMT_StoneMan,eMT_Invalid,eMT_Invalid);
        AddOneLine(eMT_Invalid,eMT_StoneMan,eMT_Invalid,eMT_Invalid,eMT_Invalid,eMT_Invalid,eMT_Invalid,eMT_Invalid,eMT_StoneMan,eMT_Invalid);
        AddOneLine(eMT_StoneMan,eMT_Invalid,eMT_Invalid,eMT_Invalid,eMT_MaChao,eMT_Invalid,eMT_Invalid,eMT_Invalid,eMT_Invalid,eMT_StoneMan);
    }

    m_monsterLineWaveCount = m_monsterData.size();
}

void MonsterGroupLogic::onExit()
{
    CCNode::onExit();
}

void MonsterGroupLogic::StateUpdate( float deltaTime )
{
    GetFsm().Update();
}


IMPLEMENT_STATE_BEGIN(MonsterGroupLogic, Idle)
{
    STATE_CONSTRUCTOR_BEGIN
    {
    }
    STATE_CONSTRUCTOR_END

        STATE_UPDATE_BEGIN
    {      
        SWITCH_TO_STATE(Activate);
    }
    STATE_UPDATE_END

        STATE_DESTRUCTOR_BEGIN
    {
    }
    STATE_DESTRUCTOR_END
}
IMPLEMENT_STATE_END

    IMPLEMENT_STATE_BEGIN(MonsterGroupLogic, Activate)
{
    STATE_CONSTRUCTOR_BEGIN
    {
        // TODO: Check the usage of timer.
        schedule(schedule_selector(MonsterGroupLogic::MonsterLineWave), 0.8f);
    }
    STATE_CONSTRUCTOR_END

        STATE_UPDATE_BEGIN
    {
    }
    STATE_UPDATE_END

        STATE_DESTRUCTOR_BEGIN
    {
    }
    STATE_DESTRUCTOR_END
}
IMPLEMENT_STATE_END


    void MonsterGroupLogic::MonsterLineWave( float /*dt*/ )
{
    const UINT roadNum = 10;

    float pathPosX[roadNum];
    float leftX = VisibleRect::left().x;
    float screenWidth = VisibleRect::right().x - leftX;

    for (UINT i = 0; i < roadNum; ++i)
    {
        pathPosX[i] = screenWidth / roadNum * (i + 0.5) + leftX;
    }

    // Temp. (Can cocos2dx stop this schedule?)
    if ( GetFsm().IsCurrentState( STATE(Activate) ) && GameObjectManager::IsSingletonCreated() &&!GameObjectManager::Singleton().CheckIsUnderPause(eGOT_Monster))
    {
        if (m_monsterLineWaveCount != 0)
        {
            const std::vector<EMonsterType>& monData = m_monsterData[--m_monsterLineWaveCount];

            if (monData.size() == roadNum)
            {
                for (UINT i = 0; i < roadNum; ++i)
                {
                    SpawnMonster(pathPosX[i], monData[i]);
                }
            }
        }
    }
}

void MonsterGroupLogic::SpawnMonster( float positionX, EMonsterType type )
{
    if (type != eMT_Invalid)
        MonsterFactory::Get().CreateMonster(this, type, ccp(positionX, VisibleRect::top().y));
}

void MonsterGroupLogic::AddOneLine( EMonsterType line1, EMonsterType line2, EMonsterType line3, EMonsterType line4, EMonsterType line5, EMonsterType line6, EMonsterType line7, EMonsterType line8, EMonsterType line9, EMonsterType line10)
{
    std::vector<EMonsterType> monData;
    monData.push_back(line1);
    monData.push_back(line2);
    monData.push_back(line3);
    monData.push_back(line4);
    monData.push_back(line5);
    monData.push_back(line6);
    monData.push_back(line7);
    monData.push_back(line8);
    monData.push_back(line9);
    monData.push_back(line10);

    m_monsterData.push_back(monData);
}