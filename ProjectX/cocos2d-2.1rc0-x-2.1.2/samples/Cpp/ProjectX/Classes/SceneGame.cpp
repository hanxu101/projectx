#include "SceneGame.h"
#include "ResourceDefines.h"
#include "cocos2d.h"
#include "GameObject/MainCharacter.h"
#include "GameObject/FireBall.h"
#include "GameObject/Monster.h"

//------------------------------------------------------------------
//
// GameLayer
//
//------------------------------------------------------------------
GameLayer::GameLayer(void)
    : m_fireSlideThreshold(50.0f)
{
}

GameLayer::~GameLayer(void)
{
}

bool GameLayer::init()
{
    if (CCLayer::init())
    {
        setTouchEnabled(true);
        return true;
    }
    return false;
}

std::string GameLayer::title()
{
    return "GameScene";
}

void GameLayer::onEnter()
{
    CCLayer::onEnter();

    CCLabelTTF* label = CCLabelTTF::create(title().c_str(), "Arial", 32);
    addChild(label, 1);
    label->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y-50) );

    CCLabelTTF* infolabel = CCLabelTTF::create("Tap to Fire", "Arial", 10);
    addChild(infolabel , 1);
    infolabel ->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y-70) );

//  Test code...
//     m_pMainCharacter = new MainCharacter();
//     m_pMainCharacter->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y));
//     addChild(m_pMainCharacter);
//     m_pMainCharacter = new Monster();
//     m_pMainCharacter->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y));
//     addChild(m_pMainCharacter);
}


static CCDictionary s_dic;

void GameLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}

void GameLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator iter = pTouches->begin();
    for (; iter != pTouches->end(); iter++)
    {
        CCTouch* pTouch = (CCTouch*)(*iter);
        m_touchBeginLocation = pTouch->getLocation();

        if (m_touchBeginLocation.y > VisibleRect::top().y / 2)
        {
            Monster* pMonster = new Monster();
            pMonster->setPosition(m_touchBeginLocation.x, VisibleRect::top().y);
            addChild(pMonster);
        }
    }
}

void GameLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator iter = pTouches->begin();
    for (; iter != pTouches->end(); iter++)
    {
        CCTouch* pTouch = (CCTouch*)(*iter);
        CCPoint location = pTouch->getLocation();
        location.x += 1.0f;
    }
}

void GameLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator iter = pTouches->begin();
    for (; iter != pTouches->end(); iter++)
    {
        CCTouch* pTouch = (CCTouch*)(*iter);
        CCPoint location = pTouch->getLocation();
        if (ccpDistanceSQ(location, m_touchBeginLocation) > m_fireSlideThreshold)
        {
            FireBall* fireBall = new FireBall();
            fireBall->setPosition(location);
            fireBall->SetDirection(ccpNormalize(ccpSub(location, m_touchBeginLocation)));
            addChild(fireBall);
        }
    }
}

void GameLayer::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    ccTouchesEnded(pTouches, pEvent);
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
