#ifndef  _APP_GAMEOBJECTCATALOG_H_
#define  _APP_GAMEOBJECTCATALOG_H_

#include "cocos2d.h"
#include "GameObject/GameObjectEnum.h"

class GameObject;

typedef std::list<GameObject*> TGameObjectList;
typedef std::vector<GameObject*> TGameObjectVector;
typedef std::map< EGameObjectType, TGameObjectList > TGameObjectMap;

// Used for update gameObject state. Manage obj map.
class GameObjectManager
{
public:
	static GameObjectManager& Get()
	{
		static GameObjectManager catalog;
		return catalog;
	}

	void Update(float dt);

	void RegisterGameObject(GameObject* pObj);
	void UnregisterGameObject(GameObject* pObj);

	void GetGameObjectList(EGameObjectType objType, TGameObjectList& objectList);

private:
	GameObjectManager();
	~GameObjectManager();

	void AddGameObject(GameObject* pObj);
	void DelGameObject(GameObject* pObj);

	TGameObjectMap m_gameObjMap;
	TGameObjectVector m_addPendingList;
	TGameObjectVector m_delPendingList;    
};

#endif //_APP_GAMEOBJECTCATALOG_H_