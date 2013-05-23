#ifndef  _APP_MainCharacter_H_
#define  _APP_MainCharacter_H_

#include "cocos2d.h"
#include "FSM/FsmInclude.h"

USING_NS_CC;
 
class MainCharacter : public CCNode, public CCTargetedTouchDelegate 
{
public:
	MainCharacter();
	virtual ~MainCharacter();

	virtual void onEnter();
	virtual void onExit();

	void StateUpdate(float deltaTime);

private:
	void PlayHeroTestAnimation();

	MMR_DECLARE_FSM(MainCharacter);

	MMR_DECLARE_STATE(Idle);

	CCSprite* m_pMainSprite;
};

#endif // _APP_MainCharacter_H_