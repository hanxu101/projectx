#ifndef  _APP_GENERALFACTORY_H_
#define  _APP_GENERALFACTORY_H_

#include "GameObject/GameObjectEnum.h"

USING_NS_CC;

class GeneralFactory
{
public:
    static GeneralFactory& Get()
    {
        static GeneralFactory factory;
        return factory;
    }

    void CreateGeneral(CCNode* parent, EGeneralType type, const CCPoint& position);

private:
    GeneralFactory();
    ~GeneralFactory();
};

#endif //_APP_GENERALFACTORY_H_