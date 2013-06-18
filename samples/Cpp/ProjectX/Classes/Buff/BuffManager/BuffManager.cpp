#include "Buff/BuffManager/BuffManager.h"
#include "Buff/Buff.h"

IMPLEMENT_SINGLETON(BuffManager);

BuffManager::BuffManager()
{

}

BuffManager::~BuffManager()
{
    m_buffMap.clear();
    ClearPendingList();
}

void BuffManager::Update(float dt)
{
    ClearPendingList();

    for (TBuffMap::iterator iter = m_buffMap.begin(); iter != m_buffMap.end(); ++iter)
    {
        for (TBuffList::iterator listIter = iter->second.begin(); listIter != iter->second.end(); ++listIter)
        {
            (*listIter)->Update(dt);
        }
    }
}

void BuffManager::RegisterBuff( Buff* pBuff )
{
    if (!pBuff)
        return;

    m_addPendingList.push_back(pBuff);
}

void BuffManager::UnregisterBuff( Buff* pBuff )
{
    if (!pBuff)
        return;

    m_delPendingList.push_back(pBuff);
}

void BuffManager::GetBuffList( EBuffType buffType, TBuffList& objectList )
{
    TBuffMap::iterator iter = m_buffMap.find(buffType);

    if (iter != m_buffMap.end())
    {
        objectList = iter->second;
    }
}

//////////////////////////////////////////////////////////////////////////
// Private

void BuffManager::AddBuff( Buff* pBuff )
{
    if (!pBuff)
        return;

    EBuffType type = pBuff->GetBuffType();
    TBuffMap::iterator iter = m_buffMap.find(type);

    if (iter != m_buffMap.end())
    {
        iter->second.push_back(pBuff);
    }
    else
    {
        TBuffList list;
        list.push_back(pBuff);
        m_buffMap.insert(std::pair<EBuffType, TBuffList>(type, list));
    }
}

void BuffManager::DelBuff( Buff* pBuff )
{
    if (!pBuff)
        return;

    EBuffType type = pBuff->GetBuffType();
    TBuffMap::iterator iter = m_buffMap.find(type);

    if (iter != m_buffMap.end())
    {
        iter->second.remove(pBuff);

        if (iter->second.empty())
            m_buffMap.erase(iter);
    }

    pBuff->release();
}

void BuffManager::ClearPendingList()
{
    for (unsigned int i = 0; i < m_addPendingList.size(); ++i)
    {
        AddBuff(m_addPendingList[i]);
    }

    for (unsigned int i = 0; i < m_delPendingList.size(); ++i)
    {
        DelBuff(m_delPendingList[i]);
    }

    m_addPendingList.clear();
    m_delPendingList.clear();
}