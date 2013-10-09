#include "CommonHeaders.h"

#include "SceneTartar.h"

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

    CCLabelTTF* label = CCLabelTTF::create(title().c_str(), COMMON_FONT_NAME, COMMON_BIG_FONT_SIZE);
    addChild(label, 1);
    label->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y-50) );

    std::string content = "TartarLayer1.";
    CCLabelTTF* labelContent = CCLabelTTF::create(content.c_str(), COMMON_FONT_NAME, COMMON_FONT_SIZE);

    addChild(labelContent, 1);
    labelContent->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y-150) );
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
