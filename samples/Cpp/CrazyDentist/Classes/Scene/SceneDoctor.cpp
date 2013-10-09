#include "CommonHeaders.h"

#include "SceneDoctor.h"

//------------------------------------------------------------------
//
// DoctorLayer
//
//------------------------------------------------------------------
DoctorLayer::DoctorLayer(void)
{
}

DoctorLayer::~DoctorLayer(void)
{
}

std::string DoctorLayer::title()
{
    return "CreditsScene";
}

void DoctorLayer::onEnter()
{
    CCLayer::onEnter();

    CCLabelTTF* label = CCLabelTTF::create(title().c_str(), COMMON_FONT_NAME, COMMON_BIG_FONT_SIZE);
    addChild(label, 1);
    label->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y-50) );

    std::string content = "DoctorLayer1.";
    CCLabelTTF* labelContent = CCLabelTTF::create(content.c_str(), COMMON_FONT_NAME, COMMON_FONT_SIZE);

    addChild(labelContent, 1);
    labelContent->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y-150) );
}

//------------------------------------------------------------------
//
// SceneDoctor
//
//------------------------------------------------------------------
void SceneDoctor::runThisTest()
{
    CCLayer* pLayer = new DoctorLayer();
    addChild(pLayer);
    pLayer->release();

    CCDirector::sharedDirector()->replaceScene(this);
}
