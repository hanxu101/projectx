#include "Buff/Buff.h"
#include "Buff/BuffManager/BuffManager.h"
#include "GameObject/GameObjectManager/GameObjectManager.h"

Buff::Buff()
    : m_type(eBT_Invalid)
    , m_lastTime(0.0f)
    , m_elapsedTime(0.0f)
{
}

Buff::Buff( EBuffType type, float lastTime )
    : m_type(type)
    , m_lastTime(lastTime)
    , m_elapsedTime(0.0f)
{
}

Buff::~Buff()
{
}

void Buff::onEnter()
{
    CCNode::onEnter();

    // Record in manager.
    BuffManager::Get().RegisterBuff(this);

    // Temp... Buff function.
    GameObjectManager::Get().RegisterPauseUpdateGameObjectType(eGOT_Monster);
}

void Buff::onExit()
{
    // Remove in manager.
    BuffManager::Get().UnregisterBuff(this);

    CCNode::onExit();
}

void Buff::Unspawn()
{
    removeFromParent();
}

void Buff::Update( float deltaTime )
{
    m_elapsedTime += deltaTime;

    if (m_elapsedTime > m_lastTime)
    {
        //Temp... Finish Logic here.
        GameObjectManager::Get().UnregisterPauseUpdateGameObjectType(eGOT_Monster);

        // Unspawn.
        Unspawn();
    }
}

EBuffType Buff::GetBuffType() const
{
    return m_type;
}