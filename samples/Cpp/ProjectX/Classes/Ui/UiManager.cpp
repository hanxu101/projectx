#include "CommonHeaders.h"

#include "Ui/UiManager.h"

IMPLEMENT_SINGLETON(UiManager);

UiManager::UiManager()
    : m_pPanel(NULL)
    , m_pWidget(NULL)
{

}

UiManager::~UiManager()
{

}

void UiManager::Init( CCNode* pNode )
{
    COCOUISYSTEM->resetSystem(pNode);
    m_pPanel = CocoPanel::create();    
    COCOUISYSTEM->getCurScene()->addWidget(m_pPanel);

    m_pWidget = COCOUISYSTEM->createWidgetFromFile_json("../UI/Json/UIGame.json");
    m_pPanel->addChild(m_pWidget);
}

CocoWidget* UiManager::GetChildByName( const char* name )
{
    XAssert(m_pWidget, "m_pWidget is invalid.");

    return m_pWidget->getChildByName(name);
}

void UiManager::AddChildWidget( CocoWidget* child )
{
    m_pPanel->addChild(child);
}
