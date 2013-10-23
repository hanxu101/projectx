#include "CommonHeaders.h"

#include "SceneTartar.h"
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

    UIImageView* pImage = DynamicCast<UIImageView*>(UiManager::Singleton().GetChildByName("ImageView2"));
    pImage->setVisible(false);
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
            UILabel* pUILabelDayDiff = DynamicCast<UILabel*>(UiManager::Singleton().GetChildByName("Label_DayDiff"));
            char str[10];
            sprintf(str,"%d",dayDiff);
            pUILabelDayDiff->setText(str);
            pUILabelDayDiff->setVisible(true);

            pUILabelDayDiff = DynamicCast<UILabel*>(UiManager::Singleton().GetChildByName("Label_PastDay"));
            pUILabelDayDiff->setVisible(true);

            // Set Image
            bool needCheck = dayDiff > 31;
            UIImageView* pImage = DynamicCast<UIImageView*>(UiManager::Singleton().GetChildByName("ImageView1"));
            pImage->setVisible(!needCheck);
            pImage = DynamicCast<UIImageView*>(UiManager::Singleton().GetChildByName("ImageView2"));
            pImage->setVisible(needCheck);
        }
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
