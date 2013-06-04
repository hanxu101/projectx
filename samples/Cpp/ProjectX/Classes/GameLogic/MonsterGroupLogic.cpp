#include "GameLogic/MonsterGroupLogic.h"
#include "GameObject/Monster.h"
#include "GameObject/Monsters/EarthMonster/StoneMan.h"
#include "GameObject/Monsters/AirMonster/CrazyZombie.h"
#include "VisibleRect.h"

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
        AddOneLine(true,false,false,false,false);
        AddOneLine(false,true,false,false,false);
        AddOneLine(false,false,false,false,true);
        AddOneLine(false,false,false,true,false);
        AddOneLine(true,false,true,false,false);
        AddOneLine(false,true,false,false,false);
        AddOneLine(false,false,true,false,false);
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
    if ( GetFsm().IsCurrentState( MMR_STATE(Activate) ))
    {
        if (m_monsterLineWaveCount != 0)
        {
            const std::vector<bool>& monData = m_monsterData[--m_monsterLineWaveCount];

            if (monData.size() == 5)
            {
                if (monData[0])
                    SpawnMonster(48.0f);
                if (monData[1])
                    SpawnMonster(144.0f);
                if (monData[2])
                    SpawnMonster(240.0f);
                if (monData[3])
                    SpawnMonster(336.0f);
                if (monData[4])
                    SpawnMonster(432.0f);
            }
        }
    }
}

void MonsterGroupLogic::SpawnMonster( float positionX )
{
    Monster* pMonster = new CrazyZombie();
    pMonster->setPosition(positionX, VisibleRect::top().y);
    addChild(pMonster);
}

void MonsterGroupLogic::AddOneLine( bool line1, bool line2, bool line3, bool line4, bool line5 )
{
    std::vector<bool> monData;
    monData.push_back(line1);
    monData.push_back(line2);
    monData.push_back(line3);
    monData.push_back(line4);
    monData.push_back(line5);

    m_monsterData.push_back(monData);
}