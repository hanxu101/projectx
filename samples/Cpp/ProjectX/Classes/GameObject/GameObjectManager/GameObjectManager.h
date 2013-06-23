#ifndef  _APP_GAMEOBJECTMANAGER_H_
#define  _APP_GAMEOBJECTMANAGER_H_

#include "GameObject/GameObjectEnum.h"
#include "utilities/Singleton.h"

class GameObject;

typedef std::list<GameObject*> TGameObjectList;
typedef std::vector<GameObject*> TGameObjectVector;
typedef std::map< EGameObjectType, TGameObjectList > TGameObjectMap;

// Used for update gameObject state. Manage obj map.
class GameObjectManager
{
    DECLARE_SINGLETON(GameObjectManager);

public:
    void Update(float dt);

    void Reset();

    void RegisterGameObject(GameObject* pObj);
    void UnregisterGameObject(GameObject* pObj);

    void GetGameObjectList(EGameObjectType objType, TGameObjectList& objectList);

    void RegisterPauseUpdateGameObjectType(EGameObjectType type);
    void UnregisterPauseUpdateGameObjectType(EGameObjectType type);

    bool CheckIsUnderPause(EGameObjectType type);

private:
    void AddGameObject(GameObject* pObj);
    void DelGameObject(GameObject* pObj);

    void ClearPendingList();

    TGameObjectMap m_gameObjMap;
    TGameObjectVector m_addPendingList;
    TGameObjectVector m_delPendingList;

    int m_updateExceptionSign;

    int m_exceptionSignCount[eGOT_Count];
};

#endif //_APP_GAMEOBJECTMANAGER_H_