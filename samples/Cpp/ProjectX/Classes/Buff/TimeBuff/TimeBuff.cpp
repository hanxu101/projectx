#include "Buff/TimeBuff/TimeBuff.h"
#include "GameObject/GameObjectManager/GameObjectManager.h"

TimeBuff::TimeBuff()
{
}

TimeBuff::TimeBuff( float lastTime )
    : Buff(eBT_TimeBuff, lastTime, 0.0f)
{
}

TimeBuff::~TimeBuff()
{

}

void TimeBuff::ExcuteBuff()
{
    if (GameObjectManager::IsSingletonCreated())
        GameObjectManager::Singleton().RegisterPauseUpdateGameObjectType(eGOT_Monster);
}

void TimeBuff::EndBuff()
{
    if (GameObjectManager::IsSingletonCreated())
        GameObjectManager::Singleton().UnregisterPauseUpdateGameObjectType(eGOT_Monster);
}
