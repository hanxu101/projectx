#include "CommonHeaders.h"

#include "GameObject/Monsters/MonsterFactory/MonsterFactory.h"
#include "GameObject/Monsters/EarthMonster/StoneMan.h"
#include "GameObject/Monsters/AirMonster/CrazyZombie.h"
#include "GameObject/Monsters/AirMonster/CrazyZombieBomber.h"

MonsterFactory::MonsterFactory()
{
}

MonsterFactory::~MonsterFactory()
{
}

void MonsterFactory::CreateMonster( CCNode* parent, EMonsterType type, const CCPoint& position )
{
    switch (type)
    {
    case eMT_StoneMan:
        {
            StoneMan* pStoneMan = new StoneMan();
            pStoneMan->setPosition(position);
            parent->addChild(pStoneMan);
        }
        break;
    case eMT_CrazyZombie:
        {
            CrazyZombie* pCrazyZombie = new CrazyZombie();
            pCrazyZombie->setPosition(position);
            parent->addChild(pCrazyZombie);
        }
        break;
    case eMT_CrazyZombieBomber:
        {
            CrazyZombieBomber* pCrazyZombieBomber = new CrazyZombieBomber();
            pCrazyZombieBomber->setPosition(position);
            parent->addChild(pCrazyZombieBomber);
        }
    default:
        break;
    }
}