#include "Gamelogic/MainPlayerLogic.h"

const int g_mainPlayerTotalHp = 10;

MainPlayerLogic::MainPlayerLogic()
    : m_pHpBar(NULL)
    , m_originalHp(0)
    , m_currentHp(0)
{
}

MainPlayerLogic::~MainPlayerLogic()
{
}

void MainPlayerLogic::Init( cs::CocoLoadingBar* pHpBar )
{
    CCAssert(pHpBar, "Cannot find hp bar resource");

    m_pHpBar = pHpBar;
    m_originalHp = g_mainPlayerTotalHp;
    m_currentHp = g_mainPlayerTotalHp;
}

void MainPlayerLogic::Uninit()
{
    Reset();
    m_pHpBar = NULL;
}

void MainPlayerLogic::Reset()
{
    m_currentHp = g_mainPlayerTotalHp;
}

void MainPlayerLogic::ReduceHp( int reduceHp )
{
    m_currentHp -= reduceHp;

    AdjustHpBar();
}

void MainPlayerLogic::IncreaseHp( int increaseHp )
{
    m_currentHp += increaseHp;

    AdjustHpBar();
}

void MainPlayerLogic::AdjustHpBar()
{
    if (m_pHpBar && m_originalHp != 0)
        m_pHpBar->setPercent(static_cast<float>(m_currentHp) / static_cast<float>(m_originalHp) * 100);
}