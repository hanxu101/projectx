#include "CommonHeaders.h"

#include "GameLogic/GpeLogic.h"
#include "GameObject/Monsters/Monster.h"
#include "GameObject/Monsters/EarthMonster/StoneMan.h"
#include "GameObject/Monsters/AirMonster/CrazyZombie.h"
#include "GameObject/GameObjectManager/GameObjectManager.h"
#include "GameObject/Monsters/MonsterFactory/MonsterFactory.h"

GpeLogic::GpeLogic()
    : m_pTimer(NULL)
    , m_monsterLineWaveCount(0)
{
}

GpeLogic::~GpeLogic()
{
    m_monsterData.clear();
}

void GpeLogic::onEnter()
{
    CCNode::onEnter();

    InitMonsterData();

    m_pTimer = new CCTimer();
    m_pTimer->setInterval(1.0f);
    m_pTimer->autorelease();
    m_pTimer->retain();

    INIT_FSM(Idle);
}

void GpeLogic::InitMonsterData()
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

void GpeLogic::onExit()
{
    m_pTimer->release();

    CCNode::onExit();
}

void GpeLogic::StateUpdate( float deltaTime )
{
    GetFsm().Update();
}


IMPLEMENT_STATE_BEGIN(GpeLogic, Idle)
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

    IMPLEMENT_STATE_BEGIN(GpeLogic, Activate)
{
    STATE_CONSTRUCTOR_BEGIN
    {
        // TODO: Check the usage of timer.
        schedule(schedule_selector(GpeLogic::MonsterLineWave), 0.8f);
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


    void GpeLogic::MonsterLineWave( float /*dt*/ )
{
    // Temp. (Can cocos2dx stop this schedule?)
    if ( GetFsm().IsCurrentState( STATE(Activate) ) && GameObjectManager::IsSingletonCreated() && !GameObjectManager::Singleton().CheckIsUnderPause(eGOT_Monster))
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

void GpeLogic::SpawnMonster( float positionX, EMonsterType type )
{
    if (type != eMT_Invalid)
        MonsterFactory::Get().CreateMonster(this, type, ccp(positionX, VisibleRect::top().y));
}

void GpeLogic::AddOneLine( EMonsterType line1, EMonsterType line2, EMonsterType line3, EMonsterType line4, EMonsterType line5 )
{
    std::vector<EMonsterType> monData;
    monData.push_back(line1);
    monData.push_back(line2);
    monData.push_back(line3);
    monData.push_back(line4);
    monData.push_back(line5);

    m_monsterData.push_back(monData);
}