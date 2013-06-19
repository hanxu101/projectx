#include "CommonHeaders.h"

#include "GameObject/Generals/GeneralFactory/GeneralFactory.h"
#include "GameObject/Generals/QX_DiaoChan/DiaoChan.h"

GeneralFactory::GeneralFactory()
{

}

GeneralFactory::~GeneralFactory()
{

}

void GeneralFactory::CreateGeneral( CCNode* parent, EGeneralType type, const CCPoint& position )
{
    switch (type)
    {
    case eGT_DiaoChan:
        {
            DiaoChan* pDiaoChan = new DiaoChan();
            pDiaoChan->setPosition(position);
            parent->addChild(pDiaoChan);
        }
        break;
    default:
        break;
    }
}