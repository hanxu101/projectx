#include "CommonHeaders.h"

#include "SceneManager.h"
#include "SceneGame.h"
#include "SceneCredits.h"
#include "UISystem.h"

USING_NS_CC;

static SceneBase* CreateScene(int nIdx)
{
    CCDirector::sharedDirector()->purgeCachedData();

    SceneBase* pScene = NULL;

    switch (nIdx)
    {
    case MainMenu_Game:
        pScene = new SceneGame(); break;
    case MainMenu_Credits:
        pScene = new SceneCredits(); break;
     case MainMenu_Option:
         pScene = new SceneGame(); break;
    default:
        break;
    }

    return pScene;
}

SceneManager::SceneManager()
{
    // UI Init
    COCOUISYSTEM->init();

     // add close menu
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(s_pPathClose, s_pPathCloseSelected, this, menu_selector(SceneManager::closeCallback) );
    CCMenu* pMenu =CCMenu::create(pCloseItem, NULL);

    pMenu->setPosition( CCPointZero );
    pCloseItem->setPosition(ccp( VisibleRect::right().x - 30, VisibleRect::top().y - 30));

    // add menu items for Main Menu
    m_pItemMenu = CCMenu::create();
    for (int i = 0; i < MainMenu_Count; ++i)
    {
        CCLabelTTF* label = CCLabelTTF::create(g_MainMenuNames[i].c_str(), "Arial", 20);
        label->setColor(ccMAGENTA);
        CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(SceneManager::menuCallback));

        m_pItemMenu->addChild(pMenuItem, i + 10000);
        pMenuItem->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - (i + 3) * LINE_SPACE) ));
    }

    m_pItemMenu->setContentSize(CCSizeMake(VisibleRect::getVisibleRect().size.width, (MainMenu_Count + 1) * (LINE_SPACE)));
    m_pItemMenu->setPosition(CCPointZero);
    addChild(m_pItemMenu, 1);

    setTouchEnabled(true);

    addChild(pMenu, 1);

    CCLabelTTF* pLabel = CCLabelTTF::create("Project", "Arial", TITLE_FONT_SIZE);
    pLabel->setColor(ccGRAY);

    // position the label on the center of the screen
    pLabel->setPosition(ccp(VisibleRect::center().x - 10,
                            (VisibleRect::top().y - 2*LINE_SPACE)));

    // add the label as a child to this layer
    addChild(pLabel, 1);

    // add splash screen"
    CCSprite* pSprite = CCSprite::create("projectx.png");

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
    SceneBase* pScene = CreateScene(nIdx);
    if (pScene)
    {
        pScene->runThisTest();
        pScene->release();
    }
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
    SceneBase* pScene = CreateScene(0);
    if (pScene)
    {
        pScene->runThisTest();
        pScene->release();
    }
#endif
}
