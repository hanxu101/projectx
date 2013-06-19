#ifndef  _APP_GeneralGroupLogic_H_
#define  _APP_GeneralGroupLogic_H_

#include "GameObject/GameObjectEnum.h"

USING_NS_CC;

namespace cs{class CocoPanel;}

typedef std::vector< EGeneralType > TGeneralDataVec;

class GeneralGroupLogic : public CCNode
{
public:
    GeneralGroupLogic();
    GeneralGroupLogic(const TGeneralDataVec& generalData, cs::CocoPanel* pGameUI);
    virtual ~GeneralGroupLogic();

    virtual void onEnter();
    virtual void onExit();

private:
    void GeneralBottonClicked(CCObject* pSender);

    TGeneralDataVec m_generalData;

    cs::CocoPanel* m_pGameUI;
};

#endif //_APP_GeneralGroupLogic_H_