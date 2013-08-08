#include "CommonHeaders.h"

#include "Ui/UiManager.h"

IMPLEMENT_SINGLETON(UiManager);

UiManager::UiManager()
    : m_pUiLayer(NULL)
    , m_isInUi(false)
{

}

UiManager::~UiManager()
{

}

void UiManager::Init( CCNode* pNode )
{
    m_pUiLayer = UILayer::create();
    m_pUiLayer->scheduleUpdate();
    pNode->addChild(m_pUiLayer);
    m_pUiLayer->addWidget(CCUIHELPER->createWidgetFromJsonFile("../UI/Json/UIGame.json"));
}

void UiManager::Update( float dt )
{
    m_isInUi = false;
}

UIWidget* UiManager::GetChildByName( const char* name )
{
    XAssert(m_pUiLayer, "m_pUiLayer is invalid.");

    return m_pUiLayer->getWidgetByName(name);
}

void UiManager::AddChildWidget( UIWidget* child )
{
    XAssert(m_pUiLayer, "m_pUiLayer is invalid.");

    m_pUiLayer->addWidget(child);
}

bool UiManager::IsInUi() const
{
    return m_isInUi;
}

void UiManager::SetIsInUi( bool isInUi )
{
    m_isInUi = isInUi;
}
