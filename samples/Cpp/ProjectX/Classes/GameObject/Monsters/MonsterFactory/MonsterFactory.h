#ifndef  _APP_MONSTERFACTORY_H_
#define  _APP_MONSTERFACTORY_H_

#include "cocos2d.h"
#include "GameObject/GameObjectEnum.h"

USING_NS_CC;

class MonsterFactory
{
public:
    static MonsterFactory& Get()
    {
        static MonsterFactory factory;
        return factory;
    }

    void CreateMonster(CCNode* parent, EMonsterType type, const CCPoint& position);

private:
    MonsterFactory();
    ~MonsterFactory();
};

#endif //_APP_MONSTERFACTORY_H_