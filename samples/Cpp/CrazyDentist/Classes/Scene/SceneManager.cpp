#include "CommonHeaders.h"

#include "SceneManager.h"

#include "SceneLogin.h"
#include "SceneCredits.h"
#include "SceneHome.h"
#include "SceneGame.h"
#include "SceneTartar.h"
#include "SceneDoctor.h"

#include "Ui/UiManager.h"

USING_NS_CC;

SceneManager::SceneManager()
{
    // UI Init
    COCOUISYSTEM->init();
    if (!UiManager::IsSingletonCreated())
        UiManager::CreateSingleton();

     // add close menu
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(s_pPathClose, s_pPathCloseSelected, this, menu_selector(SceneManager::closeCallback) );
    CCMenu* pMenu =CCMenu::create(pCloseItem, NULL);

    pMenu->setPosition( CCPointZero );
    pCloseItem->setPosition(ccp( VisibleRect::right().x - 30, VisibleRect::top().y - 30));

    // add menu items for Main Menu
    m_pItemMenu = CCMenu::create();
    for (int i = 0; i <= MainMenu_Credits; ++i)
    {
        CCLabelTTF* label = CCLabelTTF::create(g_MainMenuNames[i].c_str(), "Arial", 20);
        label->setColor(ccBLACK);
        CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(SceneManager::menuCallback));

        m_pItemMenu->addChild(pMenuItem, i + 10000);
        pMenuItem->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - (i + 3) * LINE_SPACE) ));
    }

    m_pItemMenu->setContentSize(CCSizeMake(VisibleRect::getVisibleRect().size.width, (MainMenu_Count + 1) * (LINE_SPACE)));
    m_pItemMenu->setPosition(CCPointZero);
    addChild(m_pItemMenu, 1);

    setTouchEnabled(true);

    addChild(pMenu, 1);

    CCLabelTTF* pLabel = CCLabelTTF::create("CrazyDentist", "Arial", TITLE_FONT_SIZE);
    pLabel->setColor(ccBLACK);

    // position the label on the center of the screen
    pLabel->setPosition(ccp(VisibleRect::center().x - 10,
                            (VisibleRect::top().y - 2*LINE_SPACE)));

    // add the label as a child to this layer
    addChild(pLabel, 1);

    // add splash screen"
    CCSprite* pSprite = CCSprite::create("splashscreen.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);

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
    case MainMenu_Credits:
        pScene = new SceneCredits(); break;
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