#include "CommonHeaders.h"

#include "GameLogic/GeneralGroupLogic.h"
#include "GameObject/Generals/GeneralFactory/GeneralFactory.h"

#include "Ui/UiManager.h"

static const float g_generalCdTime = 5.0f;

const char* NormalPng[] =
{
    "G_DiaoChan.png",
    "G_MaChao.png"
};

const char* SelectedPng[] =
{
    "G_DiaoChanSelect.png",
    "G_MachaoSelect.png"
};

const char* DisablePng[] =
{
    "G_DiaoChanDisable.png",
    "G_MachaoDisable.png"
};

GeneralGroupLogic::GeneralGroupLogic()
{
}

GeneralGroupLogic::GeneralGroupLogic( const TGeneralDataVec& generalData)
    : m_generalData(generalData)
{
}

GeneralGroupLogic::~GeneralGroupLogic()
{
    m_generalData.clear();
    m_buttonCdMap.clear();
}

void GeneralGroupLogic::onEnter()
{
    CCNode::onEnter();

    // Create general buttons in game.
    for (UINT i = 0; i < m_generalData.size(); ++i)
    {
        CocoButton* pButton = CocoButton::create();
        pButton->setWidgetTag(static_cast<int>(i));
        pButton->setPosition(ccp(VisibleRect::left().x + 10, 30 * (1 + i)));
        pButton->setBeTouchAble(true);
        // Set relationship between these picture with generalType.
        EGeneralType type = m_generalData[i];
        pButton->setTextures(NormalPng[type], SelectedPng[type], DisablePng[type]);

        pButton->addReleaseEvent(this, coco_releaseselector(GeneralGroupLogic::GeneralBottonClicked));
        pButton->setScale(0.5f);

        UiManager::Singleton().AddChildWidget(pButton);
    }
}

void GeneralGroupLogic::onExit()
{
    CCNode::onExit();
}

void GeneralGroupLogic::GeneralBottonClicked( CCObject* pSender )
{
    cs::CocoButton* pButton = DynamicCast<cs::CocoButton*>(pSender);
    int widgetTag = pButton->getWidgetTag();
    EGeneralType type = m_generalData[widgetTag];

    GeneralFactory::Get().CreateGeneral(this, type, ccp(240,200));

    pButton->setBeTouchAble(false);
    pButton->setPressState(2);

    if (m_buttonCdMap.find(pButton) == m_buttonCdMap.end())
        m_buttonCdMap.insert(std::pair<cs::CocoButton*, float>(pButton, 0.0f));
}

void GeneralGroupLogic::Update( float dt )
{
    for (TButtonCdMap::iterator iter = m_buttonCdMap.begin(); iter != m_buttonCdMap.end(); ++iter)
    {
        iter->second += dt;

        if (iter->second > g_generalCdTime && iter->first)
        {
            iter->first->setBeTouchAble(true);
            iter->first->setPressState(0);

            m_buttonCdMap.erase(iter);
            break;
        }
    }
}