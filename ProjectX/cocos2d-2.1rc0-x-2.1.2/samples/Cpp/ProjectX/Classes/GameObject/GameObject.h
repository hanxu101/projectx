#ifndef  _APP_GameObject_H_
#define  _APP_GameObject_H_

#include "cocos2d.h"
#include "FSM/FsmInclude.h"
#include "GameObject/GameObjectEnum.h"

USING_NS_CC;

class GameObject : public CCNode
{
public:
	GameObject();
	GameObject(float hp, EGameObjectType type, float collisonRadius);
	virtual ~GameObject();

	virtual void onEnter();
	virtual void onExit();

	void Unspawn();

	virtual void StateUpdate(float deltaTime);

	const EGameObjectType& GetGameObjectType();
	virtual int GetDetailTypeIndex();

	float GetCollisionRadius() const;

protected:
	float m_hp;
	EGameObjectType m_type;
	float m_collisionRadius;
};

#endif // _APP_MainCharacter_H_