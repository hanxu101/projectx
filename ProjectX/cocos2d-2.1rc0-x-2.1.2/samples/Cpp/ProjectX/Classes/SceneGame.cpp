#include "SceneGame.h"
#include "ResourceDefines.h"
#include "cocos2d.h"
#include "GameObject/MainCharacter.h"

#define FIX_POS(_pos, _min, _max) \
	if (_pos < _min)        \
	_pos = _min;        \
else if (_pos > _max)   \
	_pos = _max;        \

//------------------------------------------------------------------
//
// GameLayer
//
//------------------------------------------------------------------
GameLayer::GameLayer(void)
	: m_fLastTime(0.0)
	, m_pBall(NULL)
	, m_pMainCharacter(NULL)
{
}

GameLayer::~GameLayer(void)
{
	//m_pBall->release();
}

std::string GameLayer::title()
{
	return "GameScene";
}

void GameLayer::onEnter()
{
	CCLayer::onEnter();

	setAccelerometerEnabled(true);


	CCLabelTTF* label = CCLabelTTF::create(title().c_str(), "Arial", 32);
	addChild(label, 1);
	label->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y-50) );

	//  m_pBall = CCSprite::create("ball.png");
	// 	m_pBall->retain();
	// 	m_pBall->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y));
	//  addChild(m_pBall);

	m_pMainCharacter = new MainCharacter();
	m_pMainCharacter->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y));
	addChild(m_pMainCharacter);
}

void GameLayer::didAccelerate(CCAcceleration* pAccelerationValue)
{
	//     double fNow = pAccelerationValue->timestamp;
	// 
	//     if (m_fLastTime > 0.0)
	//     {
	//         CCPoint ptNow = convertToUI
	//     }
	// 
	//     m_fLastTime = fNow;

	CCDirector* pDir = CCDirector::sharedDirector();

	/*FIXME: Testing on the Nexus S sometimes m_pBall is NULL */
	if ( m_pBall == NULL ) {
		return;
	}

	CCSize ballSize  = m_pBall->getContentSize();

	CCPoint ptNow  = m_pBall->getPosition();
	CCPoint ptTemp = pDir->convertToUI(ptNow);

	ptTemp.x += pAccelerationValue->x * 9.81f;
	ptTemp.y -= pAccelerationValue->y * 9.81f;

	CCPoint ptNext = pDir->convertToGL(ptTemp);
	FIX_POS(ptNext.x, (VisibleRect::left().x+ballSize.width / 2.0), (VisibleRect::right().x - ballSize.width / 2.0));
	FIX_POS(ptNext.y, (VisibleRect::bottom().y+ballSize.height / 2.0), (VisibleRect::top().y - ballSize.height / 2.0));
	m_pBall->setPosition(ptNext);
}

//------------------------------------------------------------------
//
// AccelerometerTestScene
//
//------------------------------------------------------------------
void SceneGame::runThisTest()
{
	CCLayer* pLayer = new GameLayer();
	addChild(pLayer);
	pLayer->release();

	CCDirector::sharedDirector()->replaceScene(this);
}
