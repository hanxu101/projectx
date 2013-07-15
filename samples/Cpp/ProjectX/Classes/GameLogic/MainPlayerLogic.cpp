#include "CommonHeaders.h"

#include "Gamelogic/MainPlayerLogic.h"
#include "Ui/UiManager.h"

static const int g_mainPlayerTotalHp = 10;
static const int g_originalCoinNum = 0;

IMPLEMENT_SINGLETON(MainPlayerLogic);

MainPlayerLogic::MainPlayerLogic()
    : m_pHpBar(NULL)
    , m_pCoinNumLableAtlas(NULL)
    , m_originalHp(0)
    , m_currentHp(0)
    , m_originalCoin(0)
    , m_currentCoin(0)
{
}

MainPlayerLogic::~MainPlayerLogic()
{
}

void MainPlayerLogic::Init()
{
    m_currentHp = g_mainPlayerTotalHp;
    m_originalCoin = g_originalCoinNum;
    m_currentCoin = g_originalCoinNum;

    m_pHpBar = DynamicCast<cs::CocoLoadingBar*>(UiManager::Singleton().GetChildByName("HpBar"));
    m_pCoinNumLableAtlas = DynamicCast<cs::CocoLabelAtlas*>(UiManager::Singleton().GetChildByName("Gold"));
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
    if (m_currentHp > 0)
        m_currentHp -= reduceHp;

    AdjustHpBar();
}

void MainPlayerLogic::IncreaseHp( int increaseHp )
{
    m_currentHp += increaseHp;

    AdjustHpBar();
}

void MainPlayerLogic::ReduceCoin( int reduceCoin )
{
    if (m_currentCoin > 0)
    {
        m_currentCoin -= reduceCoin;

        DrawCoinValue();
    }
}

void MainPlayerLogic::IncreaseCoin( int increaseCoin )
{
    m_currentCoin += increaseCoin;

    DrawCoinValue();
}

void MainPlayerLogic::ComboIncreaseCoin( int comboNum )
{
    // if the attacked 1-5, the bonus * 1
    // if the attacked > 5, the bouns * n
    if ( comboNum < 5 )
        IncreaseCoin(1);
    else
        IncreaseCoin(comboNum);
}

void MainPlayerLogic::AdjustHpBar()
{
    if (m_pHpBar && m_originalHp != 0)
        m_pHpBar->setPercent(static_cast<float>(m_currentHp) / static_cast<float>(m_originalHp) * 100);
}

void MainPlayerLogic::DrawCoinValue()
{
    char stringValue[20];
    _itoa(m_currentCoin, stringValue, 10);

    if (m_pCoinNumLableAtlas)
        m_pCoinNumLableAtlas->setStringValue(stringValue);
}
