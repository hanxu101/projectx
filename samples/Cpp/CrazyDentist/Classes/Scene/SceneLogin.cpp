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
    UiManager::Singleton().Init(pUiNode);

    UIButton* pButtonOK = DynamicCast<UIButton*>(UiManager::Singleton().GetChildByName("TextButton_OK"));
    pButtonOK->addReleaseEvent(this, coco_releaseselector(LoginLayer::BottonOKClicked));
}

void LoginLayer::BottonOKClicked( CCObject* pSender )
{
    CCLOG("The Input is : %s.",  m_pTextField->getString());
    SceneManager::CreateScene(MainMenu_Home);
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
