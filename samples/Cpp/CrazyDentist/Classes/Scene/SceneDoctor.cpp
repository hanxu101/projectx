#include "CommonHeaders.h"

#include "SceneDoctor.h"
#include "Ui/UiManager.h"

//------------------------------------------------------------------
//
// DoctorLayer
//
//------------------------------------------------------------------
DoctorLayer::DoctorLayer(void)
{
}

DoctorLayer::~DoctorLayer(void)
{
}

std::string DoctorLayer::title()
{
    return "CreditsScene";
}

void DoctorLayer::onEnter()
{
    CCLayer::onEnter();

    UiManager::Singleton().Init(this);
    UiManager::Singleton().SetupWidget("../UIProject/Json/Doctor.json");

    UILabel* pUILabel = DynamicCast<UILabel*>(UiManager::Singleton().GetChildByName("Label_Hospital"));
    pUILabel->setText("Tokyo Hospital");
    
    pUILabel = DynamicCast<UILabel*>(UiManager::Singleton().GetChildByName("Label_Doctor"));
    pUILabel->setText("Takashi");
    
    pUILabel = DynamicCast<UILabel*>(UiManager::Singleton().GetChildByName("Label_DoctorDesc"));
    pUILabel->setText("DoctorDesc");

    pUILabel = DynamicCast<UILabel*>(UiManager::Singleton().GetChildByName("Label_Phone"));
    pUILabel->setText("03-3333-3333");

    pUILabel = DynamicCast<UILabel*>(UiManager::Singleton().GetChildByName("Label_Website"));
    pUILabel->setText("www.google.com");

    UIButton* pButton = DynamicCast<UIButton*>(UiManager::Singleton().GetChildByName("TextButton_Go"));
    pButton->addReleaseEvent(this, coco_releaseselector(DoctorLayer::BottonGoClicked));
}

void DoctorLayer::BottonGoClicked( CCObject* pSender )
{
    UILabel* pUILabel = DynamicCast<UILabel*>(UiManager::Singleton().GetChildByName("Label_Website"));
    const char* url = pUILabel->getStringValue();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    // Please Refer to: http://www.cocos2d-x.org/forums/6/topics/11290
    //void CCApplication::openURL(const char* pszUrl)
    //{
    //    [[UIApplication sharedApplication] openURL:pszUrl];
    //}
    XAssert(false, "Function is not added yet. Please refer to http://www.cocos2d-x.org/forums/6/topics/11290");
#else
    ShellExecuteA(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
#endif
}

//------------------------------------------------------------------
//
// SceneDoctor
//
//------------------------------------------------------------------
void SceneDoctor::runThisTest()
{
    CCLayer* pLayer = new DoctorLayer();
    addChild(pLayer);
    pLayer->release();

    CCDirector::sharedDirector()->replaceScene(this);
}
