#include "CommonHeaders.h"

#include "Ui/UiManager.h"

IMPLEMENT_SINGLETON(UiManager);

UiManager::UiManager()
    : m_pPanel(NULL)
    , m_pWidget(NULL)
    , m_isInUi(false)
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

void UiManager::Update( float dt )
{
    m_isInUi = false;
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

bool UiManager::IsInUi() const
{
    return m_isInUi;
}

void UiManager::SetIsInUi( bool isInUi )
{
    m_isInUi = isInUi;
}
