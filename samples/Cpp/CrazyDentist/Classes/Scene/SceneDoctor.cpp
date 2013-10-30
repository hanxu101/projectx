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
