#include "CommonHeaders.h"

#include "GameLogic/GeneralGroupLogic.h"
#include "GameObject/Generals/GeneralFactory/GeneralFactory.h"
#include "CocoButton.h"
#include "CocoPanel.h"

#include "UISystem.h"

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
            pButton->setPosition(ccp(140, 60 * (1 + i)));
            pButton->setBeTouchAble(true);
            // Set relation ship between these picture with generalType.
            pButton->setTextures("DiaoChan.png", "DiaoChanSelect.png", "DiaoChan.png");
            pButton->addReleaseEvent(this, coco_releaseselector(GeneralGroupLogic::GeneralBottonClicked));

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