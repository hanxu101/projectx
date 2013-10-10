#include "CommonHeaders.h"

#include "SceneLogin.h"
#include "SceneManager.h"
#include "Ui/UiManager.h"

//------------------------------------------------------------------
//
// LoginLayer
//
//------------------------------------------------------------------
LoginLayer::LoginLayer(void)
{
}

LoginLayer::~LoginLayer(void)
{
}

std::string LoginLayer::title()
{
    return "LoginLayer1";
}

void LoginLayer::onEnter()
{
    TextFieldTTFLayer::onEnter();

    CCNode* pUiNode = CCNode::create();
    addChild(pUiNode, 1);
    
    // UI setup
    UiManager::Singleton().Init(this);
    UiManager::Singleton().SetupWidget("../UIProject/Json/Login.json");

    UIButton* pButton = DynamicCast<UIButton*>(UiManager::Singleton().GetChildByName("TextButton_OK"));
    pButton->addReleaseEvent(this, coco_releaseselector(LoginLayer::BottonOKClicked));
    
    pButton = DynamicCast<UIButton*>(UiManager::Singleton().GetChildByName("TextButton_Yes"));
    pButton->addReleaseEvent(this, coco_releaseselector(LoginLayer::BottonYesClicked));
    
    pButton = DynamicCast<UIButton*>(UiManager::Singleton().GetChildByName("TextButton_No"));
    pButton->addReleaseEvent(this, coco_releaseselector(LoginLayer::BottonNoClicked));

    UIWidget* pUIWidget = UiManager::Singleton().GetChildByName("Panel_LoginConfirm");
    pUIWidget->setVisible(false);
}

void LoginLayer::BottonOKClicked( CCObject* pSender )
{
    UIWidget* pUIWidget = UiManager::Singleton().GetChildByName("Panel_Login");
    pUIWidget->setVisible(false);
    EnableTextField(false);

    pUIWidget = UiManager::Singleton().GetChildByName("Panel_LoginConfirm");
    pUIWidget->setVisible(true);

    CCLOG("The Input is : %s.",  m_pTextField->getString());
    //SceneManager::CreateScene(MainMenu_Home);
}

void LoginLayer::BottonYesClicked( CCObject* pSender )
{
    SceneManager::CreateScene(MainMenu_Home);
}

void LoginLayer::BottonNoClicked( CCObject* pSender )
{
    UIWidget* pUIWidget = UiManager::Singleton().GetChildByName("Panel_Login");
    pUIWidget->setVisible(true);
    EnableTextField(true);

    pUIWidget = UiManager::Singleton().GetChildByName("Panel_LoginConfirm");
    pUIWidget->setVisible(false);
}

//------------------------------------------------------------------
//
// SceneLogin
//
//------------------------------------------------------------------
void SceneLogin::runThisTest()
{
    CCLayer* pLayer = new LoginLayer();
    addChild(pLayer);
    pLayer->release();

    CCDirector::sharedDirector()->replaceScene(this);
}
