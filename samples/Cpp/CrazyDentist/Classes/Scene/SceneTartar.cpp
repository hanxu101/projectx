#include "CommonHeaders.h"

#include "SceneTartar.h"
#include "SceneManager.h"
#include "Ui/UiManager.h"

//------------------------------------------------------------------
//
// TartarLayer
//
//------------------------------------------------------------------
TartarLayer::TartarLayer(void)
{
}

TartarLayer::~TartarLayer(void)
{
}

std::string TartarLayer::title()
{
    return "CreditsScene";
}

void TartarLayer::onEnter()
{
    CCLayer::onEnter();

    UiManager::Singleton().Init(this);
    UiManager::Singleton().SetupWidget("../UIProject/Json/Tartar.json");

    UIWidget* pUIWidget = UiManager::Singleton().GetChildByName("Panel1");
    pUIWidget->setVisible(true);
    pUIWidget = UiManager::Singleton().GetChildByName("Panel2");
    pUIWidget->setVisible(false);

    UILabel* pUILabel = DynamicCast<UILabel*>(UiManager::Singleton().GetChildByName("Label_Warning"));
    pUILabel->setVisible(false);
    
    pUILabel = DynamicCast<UILabel*>(UiManager::Singleton().GetChildByName("Label_DayDiff"));
    pUILabel->setVisible(false);

    pUILabel = DynamicCast<UILabel*>(UiManager::Singleton().GetChildByName("Label_PastDay"));
    pUILabel->setVisible(false);

    UITextField* pUITextField = DynamicCast<UITextField*>(UiManager::Singleton().GetChildByName("TextField_Year"));
    pUITextField->setMaxLengthEnable(true);
    pUITextField->setMaxLength(4);
    pUITextField->addInsertTextEvent(this, coco_TextFieldInsertTextSelector(TartarLayer::TextFieldInserted));
    
    pUITextField = DynamicCast<UITextField*>(UiManager::Singleton().GetChildByName("TextField_Mon"));
    pUITextField->setMaxLengthEnable(true);
    pUITextField->setMaxLength(2);
    pUITextField->addInsertTextEvent(this, coco_TextFieldInsertTextSelector(TartarLayer::TextFieldInserted));

    pUITextField = DynamicCast<UITextField*>(UiManager::Singleton().GetChildByName("TextField_Day"));
    pUITextField->setMaxLengthEnable(true);
    pUITextField->setMaxLength(2);
    pUITextField->addInsertTextEvent(this, coco_TextFieldInsertTextSelector(TartarLayer::TextFieldInserted));

    UIButton* pButton = DynamicCast<UIButton*>(UiManager::Singleton().GetChildByName("TextButton_Start"));
    pButton->addReleaseEvent(this, coco_releaseselector(TartarLayer::BottonOKClicked));

    pButton = DynamicCast<UIButton*>(UiManager::Singleton().GetChildByName("TextButton_Finish"));
    pButton->addReleaseEvent(this, coco_releaseselector(TartarLayer::BottonFinishClicked));

    pButton = DynamicCast<UIButton*>(UiManager::Singleton().GetChildByName("TextButton_Order"));
    pButton->addReleaseEvent(this, coco_releaseselector(TartarLayer::BottonOrderClicked));

    UILabel* pUILabelWarning = DynamicCast<UILabel*>(UiManager::Singleton().GetChildByName("Label_NeedCheck"));
    pUILabelWarning->setVisible(false);

    UIImageView* pImage = DynamicCast<UIImageView*>(UiManager::Singleton().GetChildByName("ImageView"));
    CCRect rect = pImage->getRect();
    float normalWidth = cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width - 10.0f;
    float normalHeight = normalWidth * 0.6f;
    pImage->setScaleX(normalWidth / rect.size.width * pImage->getScaleX());
    pImage->setScaleY(normalHeight / rect.size.height * pImage->getScaleY());
}

void TartarLayer::TextFieldInserted( CCObject* pSender )
{
    UILabel* pUILabel = DynamicCast<UILabel*>(UiManager::Singleton().GetChildByName("Label_Warning"));
    pUILabel->setVisible(false);

    UITextField* pUITextField = DynamicCast<UITextField*>(pSender);
    std::string str = pUITextField->getStringValue();
    if (str.size() > 0)
    {
        char lastLetter = str[str.size()-1];
        if (lastLetter < '0' || lastLetter > '9')
        {
            str.pop_back();
            pUITextField->setText(str.c_str());
        }
    }
}

void TartarLayer::BottonOKClicked( CCObject* pSender )
{
    // Check date Format is correct or not
    bool dateFormatIsValid = true;
    UITextField* pUITextField = DynamicCast<UITextField*>(UiManager::Singleton().GetChildByName("TextField_Year"));
    int year = atoi(pUITextField->getStringValue());
    int mon = 0;
    int day = 0;
    if (year != 2013)
    {
        dateFormatIsValid = false;
    }
    if (dateFormatIsValid)
    {
        pUITextField = DynamicCast<UITextField*>(UiManager::Singleton().GetChildByName("TextField_Mon"));
        mon = atoi(pUITextField->getStringValue());
        if (mon < 1 || mon > 12)
        {
            dateFormatIsValid = false;
        }
    }
    if (dateFormatIsValid)
    {
        pUITextField = DynamicCast<UITextField*>(UiManager::Singleton().GetChildByName("TextField_Day"));
        day = atoi(pUITextField->getStringValue());
        if (day < 1 || day > 31)
        {
            dateFormatIsValid = false;
        }
    }
    
    if (!dateFormatIsValid)
    {
        UILabel* pUILabel = DynamicCast<UILabel*>(UiManager::Singleton().GetChildByName("Label_Warning"));
        pUILabel->setVisible(true);
    }
    else
    {
        // Get Current Date
        tm curTime = GetDate();
        curTime.tm_hour = 0;
        curTime.tm_min = 0;
        curTime.tm_sec = 0;

        tm inputTime;
        inputTime.tm_year = year;
        inputTime.tm_mon = mon;
        inputTime.tm_mday = day;

        int dayDiff = GetElapseDayNum(curTime, inputTime);
        if (dayDiff < 0)
        {
            UILabel* pUILabel = DynamicCast<UILabel*>(UiManager::Singleton().GetChildByName("Label_Warning"));
            pUILabel->setVisible(true);
        }
        else
        {
            UIWidget* pUIWidget = UiManager::Singleton().GetChildByName("Panel1");
            pUIWidget->setVisible(false);
            pUIWidget = UiManager::Singleton().GetChildByName("Panel2");
            pUIWidget->setVisible(true);

            UILabel* pUILabelDayDiff = DynamicCast<UILabel*>(UiManager::Singleton().GetChildByName("Label_DayDiff"));
            char str[10];
            sprintf(str,"%d",dayDiff);
            pUILabelDayDiff->setText(str);
            pUILabelDayDiff->setVisible(true);

            pUILabelDayDiff = DynamicCast<UILabel*>(UiManager::Singleton().GetChildByName("Label_PastDay"));
            pUILabelDayDiff->setVisible(true);

            // Request info according the diffDay.
            CCHttpRequest* request = new CCHttpRequest();
            std::string url = "http://localhost:8000/plaque/" + std::string(str);
            request->setUrl(url.c_str());
            request->setRequestType(CCHttpRequest::kHttpGet);
            request->setResponseCallback(this, httpresponse_selector(TartarLayer::onHttpRequestCompleted));
            request->setTag("GET INFO");
            CCHttpClient::getInstance()->send(request);
            request->release();
        }
    }
}

void TartarLayer::BottonFinishClicked( CCObject* pSender )
{
    SceneManager::CreateScene(MainMenu_Home);
}

void TartarLayer::BottonOrderClicked( CCObject* pSender )
{
    SceneManager::CreateScene(MainMenu_Doctor);
}

void TartarLayer::onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response)
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

    if (std::string(response->getHttpRequest()->getTag()) == std::string("GET INFO"))
    {
        // Display the memberId and name.
        cJSON* json;
        json = cJSON_Parse(bufferStr.c_str());
        if (json) 
        {
            cJSON* messageJSON = cJSON_GetObjectItem(json, "message");
            if (messageJSON)
            {
                // Set NeedCheck label
                UILabel* pUILabelWarning = DynamicCast<UILabel*>(UiManager::Singleton().GetChildByName("Label_NeedCheck"));
                pUILabelWarning->setVisible(true);
                pUILabelWarning->setText(messageJSON->valuestring);
            }

            cJSON* imageJSON = cJSON_GetObjectItem(json, "image");
            if (imageJSON)
            {
                std::string imagePath = imageJSON->valuestring;
                CCHttpRequest* request = new CCHttpRequest();
                std::string url = "http://localhost:8000/media/" + imagePath;
                request->setUrl(url.c_str());
                request->setRequestType(CCHttpRequest::kHttpGet);
                request->setResponseCallback(this, httpresponse_selector(TartarLayer::onHttpRequestCompleted));
                request->setTag("GET IMAGE");
                CCHttpClient::getInstance()->send(request);
                request->release();

                int index = imagePath.find_last_of(".");
                if (index != -1)
                {
                    m_textureFormat = imagePath.substr(index);
                }
            }
        }
    }
    else
    {
        std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();

        // Save it locally
        path += "currentTeeth";
        path += m_textureFormat;
        
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
    
}

//------------------------------------------------------------------
//
// SceneTartar
//
//------------------------------------------------------------------
void SceneTartar::runThisTest()
{
    CCLayer* pLayer = new TartarLayer();
    addChild(pLayer);
    pLayer->release();

    CCDirector::sharedDirector()->replaceScene(this);
}
