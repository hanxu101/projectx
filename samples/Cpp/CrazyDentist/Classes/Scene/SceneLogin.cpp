#include "CommonHeaders.h"

#include "SceneLogin.h"

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
    CCLayer::onEnter();

    CCLabelTTF* label = CCLabelTTF::create(title().c_str(), "Arial", 32);
    addChild(label, 1);
    label->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y-50) );

    std::string content = "LoginLayer1.";
    CCLabelTTF* labelContent = CCLabelTTF::create(content.c_str(), "Arial", 20);

    addChild(labelContent, 1);
    labelContent->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y-150) );

    CCMenu* pItemMenu = CCMenu::create();
    CCLabelTTF* nextLabel = CCLabelTTF::create("next", "Arial", 20);
    CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(nextLabel, this, menu_selector(LoginLayer::menuCallback));
    pItemMenu->addChild(pMenuItem);
    pMenuItem->setPosition( ccp( VisibleRect::center().x, VisibleRect::center().y ));
    pItemMenu->setPosition(CCPointZero);
    addChild(pItemMenu);
}
#include "SceneManager.h"

void LoginLayer::menuCallback(CCObject * pSender)
{ 
    SceneManager::CreateScene(MainMenu_Home);
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
