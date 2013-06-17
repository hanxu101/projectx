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
    GameObjectManager::Get().RegisterPauseUpdateGameObjectType(eGOT_Monster);
}

void TimeBuff::EndBuff()
{
    GameObjectManager::Get().UnregisterPauseUpdateGameObjectType(eGOT_Monster);
}
