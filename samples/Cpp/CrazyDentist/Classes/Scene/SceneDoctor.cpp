#include "CommonHeaders.h"

#include "SceneDoctor.h"
#include "Ui/UiManager.h"
#include "GameData.h"

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
    pUILabel->setText(GameData::Singleton().GetClinicName().c_str());

    pUILabel = DynamicCast<UILabel*>(UiManager::Singleton().GetChildByName("Label_Doctor"));
    pUILabel->setText("Takashi");
    
    pUILabel = DynamicCast<UILabel*>(UiManager::Singleton().GetChildByName("Label_DoctorDesc"));
    pUILabel->setText("DoctorDesc");

    pUILabel = DynamicCast<UILabel*>(UiManager::Singleton().GetChildByName("Label_Phone"));
    pUILabel->setText("03-3333-3333");

    pUILabel = DynamicCast<UILabel*>(UiManager::Singleton().GetChildByName("Label_Website"));
    pUILabel->setText(GameData::Singleton().GetHomePageUrl().c_str());

    UIButton* pButton = DynamicCast<UIButton*>(UiManager::Singleton().GetChildByName("TextButton_Go"));
    pButton->addReleaseEvent(this, coco_releaseselector(DoctorLayer::BottonGoClicked));

    // Request Map file
    std::string mapPath = GameData::Singleton().GetMapPath();
    CCHttpRequest* request = new CCHttpRequest();
    std::string url = "http://localhost:8000/media/" + mapPath;
    request->setUrl(url.c_str());
    request->setRequestType(CCHttpRequest::kHttpGet);
    request->setResponseCallback(this, httpresponse_selector(DoctorLayer::onHttpRequestCompleted));
    request->setTag("GET IMAGE");
    CCHttpClient::getInstance()->send(request);
    request->release();

    int index = mapPath.find_last_of(".");
    if (index != -1)
    {
        m_mapTextureFormat = mapPath.substr(index);
    }
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

void DoctorLayer::onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response)
{
    if (!response)
    {
        return;
    }
    
    int statusCode = response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
    CCLog("response code: %d", statusCode);
    
    if (!response->isSucceed())
    {
        CCLog("response failed");
        CCLog("error buffer: %s", response->getErrorBuffer());
        return;
    }
    
    // dump data
    std::vector<char> *buffer = response->getResponseData();
    std::string bufferStr(buffer->begin(),buffer->end());

    std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();

    // Save it locally
    path += "map";
    path += m_mapTextureFormat;
        
    CCLOG("path: %s",path.c_str());
    FILE *fp = fopen(path.c_str(), "wb+");
    fwrite(bufferStr.c_str(), 1,buffer->size(), fp);
    fclose(fp);
    
    // Display
    UIImageView* pImage = DynamicCast<UIImageView*>(UiManager::Singleton().GetChildByName("ImageView"));
    pImage->setTexture(path.c_str());
    CCRect rect = pImage->getRect();
    float normalWidth = cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width - 10.0f;
    float normalHeight = normalWidth * 0.6f;
    pImage->setScaleX(normalWidth / rect.size.width * pImage->getScaleX());
    pImage->setScaleY(normalHeight / rect.size.height * pImage->getScaleY());    
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
