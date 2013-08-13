#include "CommonHeaders.h"

#include "GameObject/MainCharacter.h"
#include "Ui/UiManager.h"

MainCharacter::MainCharacter()
    : GameObject(10.0f, eGOT_MainCharacter,10.0f)
    , m_pMainSprite(NULL)
    , m_speed(0.0f)
    , m_pLeftButton(false)
    , m_pRightButton(false)
{
}

MainCharacter::~MainCharacter()
{
}

void MainCharacter::onEnter()
{
    GameObject::onEnter();

    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false); 

    m_pMainSprite = CCSprite::create("Hero01_0.png");
    m_pMainSprite->setScale(4.0f);
    addChild(m_pMainSprite);

    m_pLeftButton = DynamicCast<UIButton*>(UiManager::Singleton().GetChildByName("ButtonLeft"));
    m_pRightButton = DynamicCast<UIButton*>(UiManager::Singleton().GetChildByName("ButtonRight"));

    m_pLeftButton->addPushDownEvent(this, coco_releaseselector(MainCharacter::BottonLeftPushDown));
    m_pLeftButton->addCancelEvent(this, coco_releaseselector(MainCharacter::BottonLeftCacel));
    m_pLeftButton->addReleaseEvent(this, coco_releaseselector(MainCharacter::BottonLeftRelease));
    m_pLeftButton->addMoveEvent(this, coco_releaseselector(MainCharacter::BottonLeftMove));

    m_pRightButton->addPushDownEvent(this, coco_releaseselector(MainCharacter::BottonRightPushDown));
    m_pRightButton->addCancelEvent(this, coco_releaseselector(MainCharacter::BottonRightCacel));
    m_pRightButton->addReleaseEvent(this, coco_releaseselector(MainCharacter::BottonRightRelease));
    m_pRightButton->addMoveEvent(this, coco_releaseselector(MainCharacter::BottonRightMove));
    
    INIT_FSM(Idle);
}

void MainCharacter::onExit()
{
    GameObject::onExit();

    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void MainCharacter::StateUpdate(float deltaTime)
{
    GetFsm().Update();
}

void MainCharacter::BottonLeftPushDown( CCObject* pSender )
{
    CCLOG("BottonLeftPushDown");
}

void MainCharacter::BottonLeftCacel( CCObject* pSender )
{
    CCLOG("BottonLeftCacel");
}

void MainCharacter::BottonLeftRelease( CCObject* pSender )
{
    CCLOG("BottonLeftRelease");
}

void MainCharacter::BottonLeftMove( CCObject* pSender )
{
    CCLOG("BottonLeftaddMove");
}

void MainCharacter::BottonRightPushDown( CCObject* pSender )
{
    CCLOG("BottonRightPushDown");
}

void MainCharacter::BottonRightCacel( CCObject* pSender )
{
    CCLOG("BottonRightCacel"); 
}

void MainCharacter::BottonRightRelease( CCObject* pSender )
{
    CCLOG("BottonRightRelease");
}

void MainCharacter::BottonRightMove( CCObject* pSender )
{
    CCLOG("BottonRightMovev");
}

bool MainCharacter::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
    CCPoint p = pTouch->getLocation();  
    if (m_pRightButton->getRect().containsPoint(p))
    {
        m_speed = 10.0f;
    }
    else if(m_pLeftButton->getRect().containsPoint(p))
    {        
        m_speed = -10.0f;
    }
    else
        m_speed = 0.0f;

    return true;
}

void MainCharacter::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
    CCPoint p = pTouch->getLocation();  
    if (m_pRightButton->getRect().containsPoint(p))
    {
        m_speed = 10.0f;
    }
    else if(m_pLeftButton->getRect().containsPoint(p))
    {        
        m_speed = -10.0f;
    }
    else
        m_speed = 0.0f;
}

void MainCharacter::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
    m_speed = 0.0f;
}

void MainCharacter::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
    m_speed = 0.0f;
}

void MainCharacter::PlayHeroTestAnimation()
{
    CCAnimation* pAnim = CCAnimation::create();
    char str[20];

    for (UINT i = 0; i < 6; ++i)
    {
        sprintf(str,"Hero01_%d.png",i);
        pAnim->addSpriteFrameWithFileName(str);
    }

    pAnim->setDelayPerUnit(0.1f);
    pAnim->setRestoreOriginalFrame(true);

    m_pMainSprite->runAction(CCRepeatForever::create(CCAnimate::create(pAnim)));


    //  Code using plist.

    // 	CCSpriteFrameCache* cache =CCSpriteFrameCache::sharedSpriteFrameCache();
    // 	cache->addSpriteFramesWithFile("attack.plist");
    // 	CCSprite *plistSprite=CCSprite::createWithSpriteFrameName("A1_0.png");
    // 	plistSprite->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width-plistSprite->getContentSize().width,CCDirector::sharedDirector()->getWinSize().height/2));
    // 	CCSpriteBatchNode* spritebatch =CCSpriteBatchNode::create("attack.png");
    // 	spritebatch->addChild(plistSprite);
    // 	addChild(spritebatch);
    // 
    // 	CCArray* plistArray=CCArray::createWithCapacity(4);
    // 	char name[20];
    // 	for(int i=0;i<4;i++){
    // 		sprintf(name,"A1_%d.png",i);
    // 		CCSpriteFrame* frame =cache->spriteFrameByName(name);
    // 		plistArray->addObject(frame);
    // 	}
    // 
    // 	CCAnimation *plitAnimation=CCAnimation::createWithSpriteFrames(plistArray,0.2f);
    // 	CCAnimate *plitAnimate=CCAnimate::create(plitAnimation);
    // 	CCActionInterval* plitSeq=(CCActionInterval*)(CCSequence::create(plitAnimate,
    // 		CCFlipX::create(true),
    // 		plitAnimate->copy()->autorelease(),
    // 		CCFlipX::create(false),
    // 		NULL
    // 		));
    // 
    // 	plistSprite->runAction(CCRepeatForever::create(plitSeq));
}

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_STATE_BEGIN(MainCharacter, Idle)
{
    STATE_CONSTRUCTOR_BEGIN
    {
        PlayHeroTestAnimation();
    }
    STATE_CONSTRUCTOR_END

        STATE_UPDATE_BEGIN
    {      
        if (getPositionX() + m_speed > VisibleRect::right().x)
            setPositionX(VisibleRect::right().x);
        else if (getPositionX() + m_speed < VisibleRect::left().x)
            setPositionX(VisibleRect::left().x);
        else
            setPositionX(getPositionX() + m_speed);
    }
    STATE_UPDATE_END

        STATE_DESTRUCTOR_BEGIN
    {
    }
    STATE_DESTRUCTOR_END
}
IMPLEMENT_STATE_END