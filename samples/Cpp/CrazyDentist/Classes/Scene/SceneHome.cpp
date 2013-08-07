#include "CommonHeaders.h"

#include "SceneHome.h"
#include "SceneManager.h"

//------------------------------------------------------------------
//
// HomeLayer
//
//------------------------------------------------------------------
HomeLayer::HomeLayer(void)
{
}

HomeLayer::~HomeLayer(void)
{
}

std::string HomeLayer::title()
{
    return "HomeScene";
}

void HomeLayer::onEnter()
{
    CCLayer::onEnter();

    CCLabelTTF* label = CCLabelTTF::create(title().c_str(), "Arial", 32);
    addChild(label, 1);
    label->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y-50) );

    std::string content = "HomeLayer1.";
    CCLabelTTF* labelContent = CCLabelTTF::create(content.c_str(), "Arial", 20);
    addChild(labelContent, 1);
    labelContent->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y-150) );
    
    CCMenu* pItemMenu = CCMenu::create();
    CCLabelTTF* nextLabel = CCLabelTTF::create("next", "Arial", 20);
    CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(nextLabel, this, menu_selector(HomeLayer::menuCallback));
    pItemMenu->addChild(pMenuItem);
    pMenuItem->setPosition( ccp( VisibleRect::center().x, VisibleRect::center().y ));
    pItemMenu->setPosition(CCPointZero);
    addChild(pItemMenu);
}

void HomeLayer::menuCallback(CCObject * pSender)
{ 
    SceneManager::CreateScene(MainMenu_Game);
}

//------------------------------------------------------------------
//
// SceneHome
//
//------------------------------------------------------------------
void SceneHome::runThisTest()
{
    CCLayer* pLayer = new HomeLayer();
    addChild(pLayer);
    pLayer->release();

    CCDirector::sharedDirector()->replaceScene(this);
}
