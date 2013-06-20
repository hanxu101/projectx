#include "CommonHeaders.h"

#include "GameLogic/GeneralGroupLogic.h"
#include "GameObject/Generals/GeneralFactory/GeneralFactory.h"
#include "CocoButton.h"
#include "CocoPanel.h"

#include "UISystem.h"

const char* NormalPng[] =
{
    "DiaoChan.png"
};

const char* SelectedPng[] =
{
    "DiaoChanSelect.png"
};

GeneralGroupLogic::GeneralGroupLogic()
    : m_pGameUI(NULL)
{
}

GeneralGroupLogic::GeneralGroupLogic( const TGeneralDataVec& generalData, cs::CocoPanel* pGameUI )
    : m_generalData(generalData)
    , m_pGameUI(pGameUI)
{
}

GeneralGroupLogic::~GeneralGroupLogic()
{
    m_generalData.clear();
}

void GeneralGroupLogic::onEnter()
{
    CCNode::onEnter();

    if (m_pGameUI)
    {
        // Create general buttons in game.
        for (UINT i = 0; i < m_generalData.size(); ++i)
        {
            cs::CocoButton* pButton = cs::CocoButton::create();
            pButton->setWidgetTag(static_cast<int>(i));
            pButton->setWidgetZOrder(10);
            pButton->setPosition(ccp(130, 30 * (1 + i)));
            pButton->setBeTouchAble(true);
            // Set relationship between these picture with generalType.
            EGeneralType type = m_generalData[i];
            pButton->setTextures(NormalPng[type], SelectedPng[type], "");

            pButton->addReleaseEvent(this, coco_releaseselector(GeneralGroupLogic::GeneralBottonClicked));
            pButton->setScale(0.5f);

            m_pGameUI->addChild(pButton);
        }
    }
}

void GeneralGroupLogic::onExit()
{
    CCNode::onExit();
}

void GeneralGroupLogic::GeneralBottonClicked( CCObject* pSender )
{
    cs::CocoButton* pButton = dynamic_cast<cs::CocoButton*>(pSender);
    int widgetTag = pButton->getWidgetTag();
    EGeneralType type = m_generalData[widgetTag];

    GeneralFactory::Get().CreateGeneral(this, type, ccp(240,200));
}