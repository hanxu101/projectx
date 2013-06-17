#include "Buff/Buff.h"
#include "Buff/BuffManager/BuffManager.h"

Buff::Buff()
    : m_type(eBT_Invalid)
    , m_lastTime(0.0f)
    , m_elapsedTime(0.0f)
{
}

Buff::Buff( EBuffType type, float lastTime, float elapsedTime )
    : m_type(type)
    , m_lastTime(lastTime)
    , m_elapsedTime(elapsedTime)
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

    ExcuteBuff();
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
        EndBuff();

        // Unspawn.
        Unspawn();
    }
}

EBuffType Buff::GetBuffType() const
{
    return m_type;
}