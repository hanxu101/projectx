#include "CommonHeaders.h"

#include "SceneHome.h"
#include "SceneManager.h"
#include "Ui/UiManager.h"
#include "GameData.h"

//------------------------------------------------------------------
//
// HomeLayer
//
//------------------------------------------------------------------
HomeLayer::HomeLayer(void)
{
}

HomeLayer::~HomeLayer(void)
{
}

std::string HomeLayer::title()
{
    return "HomeScene";
}

void HomeLayer::onEnter()
{
    CCLayer::onEnter();

    // UI setup
    UiManager::Singleton().Init(this);
    UiManager::Singleton().SetupWidget("../UIProject/Json/Home.json");

    UITextButton* pButton = DynamicCast<UITextButton*>(UiManager::Singleton().GetChildByName("TextButton_Game"));
    pButton->addReleaseEvent(this, coco_releaseselector(HomeLayer::BottonGameClicked));

    pButton = DynamicCast<UITextButton*>(UiManager::Singleton().GetChildByName("TextButton_Tartar"));
    pButton->addReleaseEvent(this, coco_releaseselector(HomeLayer::BottonTartarClicked));

    pButton = DynamicCast<UITextButton*>(UiManager::Singleton().GetChildByName("TextButton_Doctor"));
    pButton->addReleaseEvent(this, coco_releaseselector(HomeLayer::BottonDoctorClicked));
    pButton->setText(GameData::Singleton().GetClinicName().c_str());
}

void HomeLayer::BottonGameClicked( CCObject* pSender )
{
    SceneManager::CreateScene(MainMenu_Game);
}

void HomeLayer::BottonTartarClicked( CCObject* pSender )
{
    SceneManager::CreateScene(MainMenu_Tartar);
}

void HomeLayer::BottonDoctorClicked( CCObject* pSender )
{
    SceneManager::CreateScene(MainMenu_Doctor);
}

//------------------------------------------------------------------
//
// SceneHome
//
//------------------------------------------------------------------
void SceneHome::runThisTest()
{
    CCLayer* pLayer = new HomeLayer();
    addChild(pLayer);
    pLayer->release();

    CCDirector::sharedDirector()->replaceScene(this);
}
