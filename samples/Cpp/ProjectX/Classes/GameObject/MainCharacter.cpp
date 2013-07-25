#include "CommonHeaders.h"

#include "GameObject/MainCharacter.h"
#include "Ui/UiManager.h"

MainCharacter::MainCharacter()
    : m_pMainSprite(NULL)
    , m_speed(0.0f)
{
}

MainCharacter::~MainCharacter()
{
}

void MainCharacter::onEnter()
{
    GameObject::onEnter();

    m_pMainSprite = CCSprite::create("Hero01_0.png");
    m_pMainSprite->setScale(4.0f);
    addChild(m_pMainSprite);

    cs::CocoButton* buttonLeft = DynamicCast<cs::CocoButton*>(UiManager::Singleton().GetChildByName("ButtonLeft"));
    cs::CocoButton* buttonRight = DynamicCast<cs::CocoButton*>(UiManager::Singleton().GetChildByName("ButtonRight"));

    buttonLeft->addPushDownEvent(this, coco_releaseselector(MainCharacter::BottonLeftPushDown));
    buttonLeft->addCancelEvent(this, coco_releaseselector(MainCharacter::BottonLeftCacel));
    buttonLeft->addReleaseEvent(this, coco_releaseselector(MainCharacter::BottonLeftRelease));
    buttonLeft->addMoveEvent(this, coco_releaseselector(MainCharacter::BottonLeftMove));

    buttonRight->addPushDownEvent(this, coco_releaseselector(MainCharacter::BottonRightPushDown));
    buttonRight->addCancelEvent(this, coco_releaseselector(MainCharacter::BottonRightCacel));
    buttonRight->addReleaseEvent(this, coco_releaseselector(MainCharacter::BottonRightRelease));
    buttonRight->addMoveEvent(this, coco_releaseselector(MainCharacter::BottonRightMove));

    INIT_FSM(Idle);
}

void MainCharacter::onExit()
{
    GameObject::onExit();
}

void MainCharacter::StateUpdate(float deltaTime)
{
    GetFsm().Update();
    m_speed = 0.0f;
}

void MainCharacter::BottonLeftPushDown( CCObject* pSender )
{
    CCLOG("BottonLeftPushDown");

    m_speed = -10.0f;
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

    m_speed = 10.0f;
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
        setPositionX(getPositionX() + m_speed);
    }
    STATE_UPDATE_END

        STATE_DESTRUCTOR_BEGIN
    {
    }
    STATE_DESTRUCTOR_END
}
IMPLEMENT_STATE_END