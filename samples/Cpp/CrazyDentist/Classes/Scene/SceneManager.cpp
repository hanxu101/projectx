#include "CommonHeaders.h"

#include "SceneManager.h"

#include "SceneLogin.h"
#include "SceneCredits.h"
#include "SceneHome.h"
#include "SceneGame.h"
#include "SceneTartar.h"
#include "SceneDoctor.h"

#include "Ui/UiManager.h"
#include "GameData.h"

USING_NS_CC;

SceneManager::SceneManager()
{
    // UI Init
    if (!UiManager::IsSingletonCreated())
        UiManager::CreateSingleton();
    // GamdData Init
    if (!GameData::IsSingletonCreated())
        GameData::CreateSingleton();

     // add close menu
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(s_pPathClose, s_pPathCloseSelected, this, menu_selector(SceneManager::closeCallback) );
    CCMenu* pMenu =CCMenu::create(pCloseItem, NULL);

    pMenu->setPosition( CCPointZero );
    pCloseItem->setPosition(ccp( VisibleRect::right().x - 30, VisibleRect::top().y - 30));

    // add menu items for Main Menu
    m_pItemMenu = CCMenu::create();
    for (int i = 0; i < MainMenu_Home; ++i)
    {
        CCLabelTTF* label = CCLabelTTF::create(g_MainMenuNames[i].c_str(), COMMON_FONT_NAME, COMMON_FONT_SIZE);
        label->setColor(ccWHITE);
        CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(SceneManager::menuCallback));

        m_pItemMenu->addChild(pMenuItem, i + 10000);
        pMenuItem->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - (i + 2) * LINE_SPACE) ));
    }

    m_pItemMenu->setContentSize(CCSizeMake(VisibleRect::getVisibleRect().size.width, (MainMenu_Count + 1) * (LINE_SPACE)));
    m_pItemMenu->setPosition(CCPointZero);
    addChild(m_pItemMenu, 1);

    setTouchEnabled(true);

    addChild(pMenu, 1);

    CCLabelTTF* pLabel = CCLabelTTF::create("CrazyDentist", COMMON_FONT_NAME, COMMON_BIG_FONT_SIZE);
    pLabel->setColor(ccWHITE);

    // position the label on the center of the screen
    pLabel->setPosition(ccp(VisibleRect::center().x - 10,
                            (VisibleRect::top().y - LINE_SPACE)));

    // add the label as a child to this layer
    addChild(pLabel, 1);

    // add splash screen"
    CCSprite* pSprite = CCSprite::create("splashscreen.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);


    
    // Check if it's the 1st time to run the application. if it is. send the info.
    std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
    path += "installlogfile";
        
    FILE *fp = fopen(path.c_str(), "r");
    if (fp)
        fclose(fp);
    else
    {
        // send the info
        /*CCHttpRequest* request = new CCHttpRequest();
        std::string url = "http://127.0.0.1:8000/member/" + std::string(m_pTextField->getString());
        request->setUrl(url.c_str());
        request->setRequestType(CCHttpRequest::kHttpGet);
        request->setResponseCallback(this, httpresponse_selector(LoginLayer::onHttpRequestCompleted));
        request->setTag("GET test1");
        CCHttpClient::getInstance()->send(request);
        request->release();
        */

        fp = fopen(path.c_str(), "w");
        fclose(fp);
    }
        
}

void SceneManager::menuCallback(CCObject * pSender)
{
    // get the userdata, it's the index of the menu item clicked
    CCMenuItem* pMenuItem = (CCMenuItem *)(pSender);
    int nIdx = pMenuItem->getZOrder() - 10000;

    // create the test scene and run it
    CreateScene(nIdx);
}

void SceneManager::closeCallback(CCObject * pSender)
{
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void SceneManager::onEnter()
{
    CCLayer::onEnter();

#ifdef DEBUG_HIDE_TEXT
    // directly goto Game Scene
    CreateScene(MainMenu_Login);

#endif
}

SceneBase* SceneManager::CreateScene( int nIdx )
{
    CCDirector::sharedDirector()->purgeCachedData();

    SceneBase* pScene = NULL;

    switch (nIdx)
    {
    case MainMenu_Login:
        pScene = new SceneLogin(); break;
//     case MainMenu_Credits:
//         pScene = new SceneCredits(); break;
    case MainMenu_Home:
        pScene = new SceneHome(); break;
    case MainMenu_Game:
        pScene = new SceneGame(); break;
    case MainMenu_Tartar:
        pScene = new SceneTartar(); break;
    case MainMenu_Doctor:
        pScene = new SceneDoctor(); break;
    default:
        break;
    }

    if (pScene)
    {
        pScene->runThisTest();
        pScene->release();
    }

    return pScene;
}