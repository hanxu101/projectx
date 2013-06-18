#ifndef  _APP_BUFFMANAGER_H_
#define  _APP_BUFFMANAGER_H_

#include "cocos2d.h"
#include "Buff/BuffEnum.h"
#include "utilities/Singleton.h"

class Buff;

typedef std::list<Buff*> TBuffList;
typedef std::vector<Buff*> TBuffVector;
typedef std::map< EBuffType, TBuffList > TBuffMap;

// Used for update Buff state. Manage buff map.
class BuffManager
{
    DECLARE_SINGLETON(BuffManager);

public:
    void Update(float dt);

    void RegisterBuff(Buff* pBuff);
    void UnregisterBuff(Buff* pBuff);

    void GetBuffList(EBuffType buffType, TBuffList& objectList);

private:
    void AddBuff(Buff* pBuff);
    void DelBuff(Buff* pBuff);

    void ClearPendingList();

    TBuffMap m_buffMap;
    TBuffVector m_addPendingList;
    TBuffVector m_delPendingList;
};

#endif //_APP_BUFFMANAGER_H_