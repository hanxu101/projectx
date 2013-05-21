#include "SceneCredits.h"
#include "ResourceDefines.h"
#include "cocos2d.h"


//------------------------------------------------------------------
//
// CreditsLayer
//
//------------------------------------------------------------------
CreditsLayer::CreditsLayer(void)
{
}

CreditsLayer::~CreditsLayer(void)
{
}

std::string CreditsLayer::title()
{
    return "CreditsScene";
}

void CreditsLayer::onEnter()
{
    CCLayer::onEnter();

    CCLabelTTF* label = CCLabelTTF::create(title().c_str(), "Arial", 32);
    addChild(label, 1);
    label->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y-50) );

	std::string content = "Made in China.";
    CCLabelTTF* labelContent = CCLabelTTF::create(content.c_str(), "Arial", 20);

    addChild(labelContent, 1);
    labelContent->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y-150) );
}

//------------------------------------------------------------------
//
// SceneCredits
//
//------------------------------------------------------------------
void SceneCredits::runThisTest()
{
    CCLayer* pLayer = new CreditsLayer();
    addChild(pLayer);
    pLayer->release();

    CCDirector::sharedDirector()->replaceScene(this);
}
