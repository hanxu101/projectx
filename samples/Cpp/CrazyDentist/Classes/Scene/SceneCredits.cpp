#include "CommonHeaders.h"

#include "SceneCredits.h"

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

    CCLabelTTF* label = CCLabelTTF::create(title().c_str(), COMMON_FONT_NAME, COMMON_BIG_FONT_SIZE);
    addChild(label, 1);
    label->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y-50) );

	std::string content = "Made in China.";
    CCLabelTTF* labelContent = CCLabelTTF::create(content.c_str(), COMMON_FONT_NAME, COMMON_FONT_SIZE);

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
