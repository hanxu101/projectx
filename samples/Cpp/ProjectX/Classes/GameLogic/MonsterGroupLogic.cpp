#include "GameLogic/MonsterGroupLogic.h"
#include "GameObject/Monster.h"
#include "GameObject/Monsters/EarthMonster/StoneMan.h"
#include "GameObject/Monsters/AirMonster/CrazyZombie.h"
#include "VisibleRect.h"
#include "GameObject/GameObjectManager/GameObjectManager.h"
#include "GameObject/Monsters/MonsterFactory/MonsterFactory.h"

MonsterGroupLogic::MonsterGroupLogic()
    : m_pTimer(NULL)
    , m_monsterLineWaveCount(0)
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

    m_pTimer = new CCTimer();
    m_pTimer->setInterval(1.0f);
    m_pTimer->autorelease();
    m_pTimer->retain();

    MMR_INIT_FSM(Idle);
}

void MonsterGroupLogic::InitMonsterData()
{
    for (UINT i = 0; i < 15; ++i)
    {
        AddOneLine(eMT_CrazyZombie,eMT_Invalid,eMT_Invalid,eMT_Invalid,eMT_Invalid);
        AddOneLine(eMT_Invalid,eMT_CrazyZombie,eMT_Invalid,eMT_Invalid,eMT_Invalid);
        AddOneLine(eMT_Invalid,eMT_Invalid,eMT_Invalid,eMT_Invalid,eMT_StoneMan);
        AddOneLine(eMT_Invalid,eMT_Invalid,eMT_Invalid,eMT_CrazyZombie,eMT_Invalid);
        AddOneLine(eMT_CrazyZombie,eMT_Invalid,eMT_StoneMan,eMT_Invalid,eMT_Invalid);
        AddOneLine(eMT_Invalid,eMT_StoneMan,eMT_Invalid,eMT_Invalid,eMT_Invalid);
        AddOneLine(eMT_Invalid,eMT_Invalid,eMT_CrazyZombie,eMT_Invalid,eMT_Invalid);
    }

    m_monsterLineWaveCount = m_monsterData.size();
}

void MonsterGroupLogic::onExit()
{
    m_pTimer->release();

    CCNode::onExit();
}

void MonsterGroupLogic::StateUpdate( float deltaTime )
{
    GetFsm().Update();
}


MMR_IMPLEMENT_STATE_BEGIN(MonsterGroupLogic, Idle)
{
    MMR_STATE_CONSTRUCTOR_BEGIN
    {
    }
    MMR_STATE_CONSTRUCTOR_END

        MMR_STATE_UPDATE_BEGIN
    {      
        MMR_SWITCH_TO_STATE(Activate);
    }
    MMR_STATE_UPDATE_END

        MMR_STATE_DESTRUCTOR_BEGIN
    {
    }
    MMR_STATE_DESTRUCTOR_END
}
MMR_IMPLEMENT_STATE_END

    MMR_IMPLEMENT_STATE_BEGIN(MonsterGroupLogic, Activate)
{
    MMR_STATE_CONSTRUCTOR_BEGIN
    {
        // TODO: Check the usage of timer.
        schedule(schedule_selector(MonsterGroupLogic::MonsterLineWave), 0.8f);
    }
    MMR_STATE_CONSTRUCTOR_END

        MMR_STATE_UPDATE_BEGIN
    {
    }
    MMR_STATE_UPDATE_END

        MMR_STATE_DESTRUCTOR_BEGIN
    {
    }
    MMR_STATE_DESTRUCTOR_END
}
MMR_IMPLEMENT_STATE_END


    void MonsterGroupLogic::MonsterLineWave( float /*dt*/ )
{
    // Temp. (Can cocos2dx stop this schedule?)
    if ( GetFsm().IsCurrentState( MMR_STATE(Activate) ) && !GameObjectManager::Get().CheckIsUnderPause(eGOT_Monster))
    {
        if (m_monsterLineWaveCount != 0)
        {
            const std::vector<EMonsterType>& monData = m_monsterData[--m_monsterLineWaveCount];

            if (monData.size() == 5)
            {
                SpawnMonster(48.0f, monData[0]);
                SpawnMonster(144.0f, monData[1]);
                SpawnMonster(240.0f, monData[2]);
                SpawnMonster(336.0f, monData[3]);
                SpawnMonster(432.0f, monData[4]);
            }
        }
    }
}

void MonsterGroupLogic::SpawnMonster( float positionX, EMonsterType type )
{
    if (type != eMT_Invalid)
        MonsterFactory::Get().CreateMonster(this, type, ccp(positionX, VisibleRect::top().y));
}

void MonsterGroupLogic::AddOneLine( EMonsterType line1, EMonsterType line2, EMonsterType line3, EMonsterType line4, EMonsterType line5 )
{
    std::vector<EMonsterType> monData;
    monData.push_back(line1);
    monData.push_back(line2);
    monData.push_back(line3);
    monData.push_back(line4);
    monData.push_back(line5);

    m_monsterData.push_back(monData);
}