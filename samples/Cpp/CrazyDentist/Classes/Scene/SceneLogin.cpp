#include "CommonHeaders.h"

#include "SceneLogin.h"
#include "SceneManager.h"
#include "Ui/UiManager.h"
#include "GameData.h"

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
    
    // UI setup
    UiManager::Singleton().Init(this);
    UiManager::Singleton().SetupWidget("../UIProject/Json/Login.json");

    UIButton* pButton = DynamicCast<UIButton*>(UiManager::Singleton().GetChildByName("TextButton_OK"));
    pButton->addReleaseEvent(this, coco_releaseselector(LoginLayer::BottonOKClicked));
    
    pButton = DynamicCast<UIButton*>(UiManager::Singleton().GetChildByName("TextButton_Yes"));
    pButton->addReleaseEvent(this, coco_releaseselector(LoginLayer::BottonYesClicked));
    
    pButton = DynamicCast<UIButton*>(UiManager::Singleton().GetChildByName("TextButton_No"));
    pButton->addReleaseEvent(this, coco_releaseselector(LoginLayer::BottonNoClicked));

    UILabel* pUILabel = DynamicCast<UILabel*>(UiManager::Singleton().GetChildByName("Label_Fail"));
    pUILabel->setVisible(false);
 
    UIWidget* pUIWidget = UiManager::Singleton().GetChildByName("Panel_LoginConfirm");
    pUIWidget->setVisible(false);
}

void LoginLayer::BottonOKClicked( CCObject* pSender )
{
    CCHttpRequest* request = new CCHttpRequest();
    std::string url = "http://127.0.0.1:8000/member/" + std::string(m_pTextField->getString());
    request->setUrl(url.c_str());
    request->setRequestType(CCHttpRequest::kHttpGet);
    request->setResponseCallback(this, httpresponse_selector(LoginLayer::onHttpRequestCompleted));
    request->setTag("GET test1");
    CCHttpClient::getInstance()->send(request);
    request->release();
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

void LoginLayer::onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response)
{
    if (!response)
    {
        UILabel* pUILabel = DynamicCast<UILabel*>(UiManager::Singleton().GetChildByName("Label_Fail"));
        pUILabel->setVisible(true);
 
        return;
    }

    int statusCode = response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
    CCLog("response code: %d", statusCode);
    
    if (!response->isSucceed()) 
    {
        UILabel* pUILabel = DynamicCast<UILabel*>(UiManager::Singleton().GetChildByName("Label_Fail"));
        pUILabel->setVisible(true);
 
        return;
    }
    
    // Success!

    // Enter next UI page
    UIWidget* pUIWidget = UiManager::Singleton().GetChildByName("Panel_Login");
    pUIWidget->setVisible(false);
    EnableTextField(false);
    pUIWidget = UiManager::Singleton().GetChildByName("Panel_LoginConfirm");
    pUIWidget->setVisible(true);
    UILabel* pUILabel = DynamicCast<UILabel*>(UiManager::Singleton().GetChildByName("Label_Fail"));
    pUILabel->setVisible(false);

    // Dump data
    std::vector<char> *buffer = response->getResponseData();
    std::string bufferStr(buffer->begin(),buffer->end());

    // Display the memberId and name.
    cJSON* json;
    json = cJSON_Parse(bufferStr.c_str());
    if (json) 
    {
        cJSON* memberIdJSON = cJSON_GetObjectItem(json, "member_id");
        if (memberIdJSON)
        {
            UILabel* pUILabel = DynamicCast<UILabel*>(UiManager::Singleton().GetChildByName("Label_NumberValue"));
            pUILabel->setText(memberIdJSON->valuestring);
        }
        cJSON* nameJSON = cJSON_GetObjectItem(json, "name");
        if (nameJSON)
        {
            UILabel* pUILabel = DynamicCast<UILabel*>(UiManager::Singleton().GetChildByName("Label_NameValue"));
            pUILabel->setText(nameJSON->valuestring);

            // Save clinic name
            GameData::Singleton().SetClinicName(std::string(nameJSON->valuestring));
        }
        cJSON* homePageJSON = cJSON_GetObjectItem(json, "homepage");
        if (homePageJSON)
        {
            // Save homepage Url
            GameData::Singleton().SetHomePageUrl(std::string(homePageJSON->valuestring));
        }
        cJSON* mapPathJSON = cJSON_GetObjectItem(json, "map");
        if (mapPathJSON)
        {
            // Save mapPath
            GameData::Singleton().SetMapPath(std::string(mapPathJSON->valuestring));
        }
    }

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
