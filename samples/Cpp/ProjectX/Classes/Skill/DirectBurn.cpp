#include "CommonHeaders.h"

#include "Skill/DirectBurn.h"
#include "GameObject/GameObjectManager/GameObjectManager.h"
#include "GameObject/FireBall/FireBall.h"

DirectBurn::DirectBurn()
{

}

DirectBurn::~DirectBurn()
{

}

void DirectBurn::OnUpdate(float deltaTime)
{
    TGameObjectList fireballList;
    GameObjectManager::Singleton().GetGameObjectList(eGOT_FireBall, fireballList);
    for(TGameObjectList::iterator iter = fireballList.begin(); iter != fireballList.end(); ++iter)
    {
        static_cast<FireBall*>(*iter)->SetCanDirectBurn(true);
    }
}

void DirectBurn::Uninit()
{
    super::Uninit();

    TGameObjectList fireballList;
    GameObjectManager::Singleton().GetGameObjectList(eGOT_FireBall, fireballList);
    for(TGameObjectList::iterator iter = fireballList.begin(); iter != fireballList.end(); ++iter)
    {
        static_cast<FireBall*>(*iter)->SetCanDirectBurn(false);
    }
}
