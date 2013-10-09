#include "CommonHeaders.h"

#include "SceneBase.h"
#include "SceneManager.h"

SceneBase::SceneBase(bool bPortrait)
{
    CCScene::init();
}

void SceneBase::onEnter()
{
    CCScene::onEnter();

#ifndef DEBUG_NO_BACK_TO_MAIN_MENU
    //add the menu item for back to main menu
    CCLabelTTF* label = CCLabelTTF::create("MainMenu", COMMON_FONT_NAME, COMMON_FONT_SIZE);

    CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(SceneBase::MainMenuCallback));

    CCMenu* pMenu =CCMenu::create(pMenuItem, NULL);

    pMenu->setPosition( CCPointZero );
    pMenuItem->setPosition( ccp( VisibleRect::right().x - 50, VisibleRect::bottom().y + 25) );

    addChild(pMenu, 1);
#endif
}

void SceneBase::MainMenuCallback(CCObject* pSender)
{
    CCScene* pScene = CCScene::create();
    CCLayer* pLayer = new SceneManager();
    pLayer->autorelease();

    pScene->addChild(pLayer);
    CCDirector::sharedDirector()->replaceScene(pScene);
}
