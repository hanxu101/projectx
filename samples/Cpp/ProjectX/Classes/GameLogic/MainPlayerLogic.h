#ifndef  _APP_MAINPLAYERLOGIC_H_
#define  _APP_MAINPLAYERLOGIC_H_

#include "cocos2d.h"
#include "CocoLoadingBar.h"

class MainPlayerLogic
{
public:
	static MainPlayerLogic& Get()
	{
		static MainPlayerLogic mainplayer;
		return mainplayer;
	}

	void Init(cs::CocoLoadingBar* pHpBar);
	void Uninit();

	void Reset();

	void ReduceHp(int reduceHp);
	void IncreaseHp(int increaseHp);

private:
	MainPlayerLogic();
	~MainPlayerLogic();

	void AdjustHpBar();

	cs::CocoLoadingBar* m_pHpBar;
	int m_originalHp;
	int m_currentHp;
};

#endif //_APP_GAMEOBJECTMANAGER_H_