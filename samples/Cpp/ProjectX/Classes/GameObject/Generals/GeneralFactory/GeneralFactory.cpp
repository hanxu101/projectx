#include "CommonHeaders.h"

#include "GameObject/Generals/GeneralFactory/GeneralFactory.h"
#include "GameObject/Generals/QX_DiaoChan/DiaoChan.h"
#include "GameObject/Generals/S_MaChao/MaChao.h"

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
    case eGT_MaChao:
        {
            MaChao* pMaChao = new MaChao();
            pMaChao->setPosition(position);
            parent->addChild(pMaChao);
        }
        break;
    default:
        break;
    }
}