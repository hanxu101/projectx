#include "CommonHeaders.h"

#include "GameObject/MainCharacter.h"

MainCharacter::MainCharacter()
    : m_pMainSprite(NULL)
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

    //PlayHeroTestAnimation();

    addChild(m_pMainSprite);

    INIT_FSM(Idle);
}

void MainCharacter::onExit()
{
    GameObject::onExit();
}

void MainCharacter::StateUpdate(float deltaTime)
{
    GetFsm().Update();
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
    }
    STATE_UPDATE_END

        STATE_DESTRUCTOR_BEGIN
    {
    }
    STATE_DESTRUCTOR_END
}
IMPLEMENT_STATE_END