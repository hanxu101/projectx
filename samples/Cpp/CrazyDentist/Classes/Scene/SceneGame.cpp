#include "CommonHeaders.h"

#include "SceneGame.h"

#include "Ui/UiManager.h"

//------------------------------------------------------------------
//
// GameLayer
//
//------------------------------------------------------------------
const int g_uiZOrder = 3;
const int g_generalZOrder = 2;
const int g_monsterZOder = 1;
const int g_backGroundZOrder = -1;

GameLayer::GameLayer(void)
{
}

GameLayer::~GameLayer(void)
{
}

std::string GameLayer::title()
{
    return "GameScene";
}

void GameLayer::onEnter()
{
    CCLayer::onEnter();

    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(GameLayer::Update), this, 0, false);

    CCLabelTTF* label = CCLabelTTF::create(title().c_str(), "Arial", 32);
    addChild(label, 1);
    label->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y-50) );

    std::string content = "GameLayer1.";
    CCLabelTTF* labelContent = CCLabelTTF::create(content.c_str(), "Arial", 20);
    addChild(labelContent, 1);
    labelContent->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y-150) );

    // Back ground.
    CCSprite* pBackGround = CCSprite::create("splashscreen.png");

    CCRect rect = pBackGround->getTextureRect();
    float width = rect.getMaxX() - rect.getMinX();
    pBackGround->setScaleX((VisibleRect::right().x - VisibleRect::left().x) / width);
    float height = rect.getMaxY() - rect.getMinY();
    pBackGround->setScaleY((VisibleRect::top().y - VisibleRect::bottom().y) / height);

    pBackGround->setPosition(VisibleRect::center());
    addChild(pBackGround, g_backGroundZOrder);

    //setTouchEnabled(true);

    m_bTouchEnabled = true;
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 2);
}

void GameLayer::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);

    CCLayer::onExit();
}

void GameLayer::Update(float dt)
{
    UiManager::Singleton().Update(dt);
}

//------------------------------------------------------------------
//
// GameScene
//
//------------------------------------------------------------------
void SceneGame::runThisTest()
{
    GameLayer* pLayer = GameLayer::create();
    addChild(pLayer, 0);
    CCDirector::sharedDirector()->replaceScene(this);
}