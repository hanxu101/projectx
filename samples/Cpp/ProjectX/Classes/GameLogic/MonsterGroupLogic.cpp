#include "CommonHeaders.h"

#include "GameLogic/MonsterGroupLogic.h"
#include "GameObject/Monsters/Monster.h"
#include "GameObject/Monsters/EarthMonster/StoneMan.h"
#include "GameObject/Monsters/AirMonster/CrazyZombie.h"
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

    INIT_FSM(Idle);
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
    float pathPosX[5];
    float leftX = VisibleRect::left().x;
    float screenWidth = VisibleRect::right().x - leftX;

    for (UINT i = 0; i < 5; ++i)
    {
        pathPosX[i] = screenWidth * 0.2 * (i + 0.5) + leftX;
    }

    // Temp. (Can cocos2dx stop this schedule?)
    if ( GetFsm().IsCurrentState( STATE(Activate) ) && GameObjectManager::IsSingletonCreated() &&!GameObjectManager::Singleton().CheckIsUnderPause(eGOT_Monster))
    {
        if (m_monsterLineWaveCount != 0)
        {
            const std::vector<EMonsterType>& monData = m_monsterData[--m_monsterLineWaveCount];

            if (monData.size() == 5)
            {
                SpawnMonster(pathPosX[0], monData[0]);
                SpawnMonster(pathPosX[1], monData[1]);
                SpawnMonster(pathPosX[2], monData[2]);
                SpawnMonster(pathPosX[3], monData[3]);
                SpawnMonster(pathPosX[4], monData[4]);
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