#ifndef  _APP_MAINPLAYERLOGIC_H_
#define  _APP_MAINPLAYERLOGIC_H_

namespace cs{class CocoLoadingBar; class CocoLabelAtlas;}

class MainPlayerLogic
{
    DECLARE_SINGLETON(MainPlayerLogic);

public:
    void Init(cs::CocoLoadingBar* pHpBar);
    void Uninit();

    void Reset();

    void ReduceHp(int reduceHp);
    void IncreaseHp(int increaseHp);

    void ReduceCoin(int reduceCoin);
    void IncreaseCoin(int increaseCoin);

private:
    void AdjustHpBar();
    void DrawCoinValue();

    cs::CocoLoadingBar* m_pHpBar;
    cs::CocoLabelAtlas* m_pCoinNumLableAtlas;

    int m_originalHp;
    int m_currentHp;

    int m_originalCoin;
    int m_currentCoin;
};

#endif //_APP_GAMEOBJECTMANAGER_H_