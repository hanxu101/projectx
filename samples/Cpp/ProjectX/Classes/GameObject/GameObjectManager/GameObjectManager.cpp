#include "GameObject/GameObjectManager/GameObjectManager.h"
#include "GameObject/GameObject.h"
#include "utilities/Utilities.h"

GameObjectManager::GameObjectManager()
    : m_updateExceptionSign(0)
{

}

GameObjectManager::~GameObjectManager()
{
    m_gameObjMap.clear();
    m_addPendingList.clear();
    m_delPendingList.clear();
}

// Ensure safty while unregister.
void GameObjectManager::Update(float dt)
{
    for (unsigned int i = 0; i < m_addPendingList.size(); ++i)
    {
        AddGameObject(m_addPendingList[i]);
    }

    for (unsigned int i = 0; i < m_delPendingList.size(); ++i)
    {
        DelGameObject(m_delPendingList[i]);
    }

    m_addPendingList.clear();
    m_delPendingList.clear();

    for (TGameObjectMap::iterator iter = m_gameObjMap.begin(); iter != m_gameObjMap.end(); ++iter)
    {
        for (TGameObjectList::iterator listIter = iter->second.begin(); listIter != iter->second.end(); ++listIter)
        {
            if (!BIT_CHECK(m_updateExceptionSign, (*listIter)->GetGameObjectType()))
            {
                (*listIter)->StateUpdate(dt);
            }
        }
    }
}

void GameObjectManager::Reset()
{
	m_updateExceptionSign = 0;
}

void GameObjectManager::RegisterGameObject( GameObject* pObj )
{
    if (!pObj)
        return;

    m_addPendingList.push_back(pObj);
}

void GameObjectManager::UnregisterGameObject( GameObject* pObj )
{
    if (!pObj)
        return;

    m_delPendingList.push_back(pObj);
}

void GameObjectManager::GetGameObjectList( EGameObjectType objType, TGameObjectList& objectList )
{
    TGameObjectMap::iterator iter = m_gameObjMap.find(objType);

    if (iter != m_gameObjMap.end())
    {
        objectList = iter->second;
    }
}

void GameObjectManager::RegisterPauseUpdateGameObjectType( EGameObjectType type )
{
    BIT_SET(m_updateExceptionSign, type);
}

void GameObjectManager::UnregisterPauseUpdateGameObjectType( EGameObjectType type )
{
    BIT_CLEAR(m_updateExceptionSign, type);
}

bool GameObjectManager::CheckIsUnderPause( EGameObjectType type )
{
    return BIT_CHECK(m_updateExceptionSign, type) != 0;
}

//////////////////////////////////////////////////////////////////////////
// Private

void GameObjectManager::AddGameObject( GameObject* pObj )
{
    if (!pObj)
        return;

    EGameObjectType type = pObj->GetGameObjectType();
    TGameObjectMap::iterator iter = m_gameObjMap.find(type);

    if (iter != m_gameObjMap.end())
    {
        iter->second.push_back(pObj);
    }
    else
    {
        TGameObjectList list;
        list.push_back(pObj);
        m_gameObjMap.insert(std::pair<EGameObjectType, TGameObjectList>(type, list));
    }
}

void GameObjectManager::DelGameObject( GameObject* pObj )
{
    if (!pObj)
        return;

    EGameObjectType type = pObj->GetGameObjectType();
    TGameObjectMap::iterator iter = m_gameObjMap.find(type);

    if (iter != m_gameObjMap.end())
    {
        iter->second.remove(pObj);

        if (iter->second.empty())
            m_gameObjMap.erase(iter);
    }

    pObj->release();
}