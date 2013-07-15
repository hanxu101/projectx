#ifndef  _APP_GeneralGroupLogic_H_
#define  _APP_GeneralGroupLogic_H_

#include "GameObject/GameObjectEnum.h"

USING_NS_CC;

namespace cs{class CocoPanel; class CocoButton;}

typedef std::vector< EGeneralType > TGeneralDataVec;
typedef std::map< cs::CocoButton*, float > TButtonCdMap;

class GeneralGroupLogic : public CCNode
{
public:
    GeneralGroupLogic();
    GeneralGroupLogic(const TGeneralDataVec& generalData);
    virtual ~GeneralGroupLogic();

    virtual void onEnter();
    virtual void onExit();

    void Update(float dt);

private:
    void GeneralBottonClicked(CCObject* pSender);

    TGeneralDataVec m_generalData;

    TButtonCdMap m_buttonCdMap;
};

#endif //_APP_GeneralGroupLogic_H_