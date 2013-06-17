#include "GameObject/Monsters/EarthMonster/StoneMan.h"
#include "VisibleRect.h"

StoneMan::StoneMan()
{
    m_speed = 100.0f;
}

StoneMan::~StoneMan()
{
}

void StoneMan::onEnter()
{
    Monster::onEnter();

    m_pMainSprite = CCSprite::create("Hero01_0.png");
    addChild(m_pMainSprite);
}

void StoneMan::onExit()
{
    Monster::onExit();
}

void StoneMan::Killed()
{
    Unspawn();
}

int StoneMan::GetDetailTypeIndex()
{
    return static_cast<int>(eMT_StoneMan);
}

void StoneMan::PlayMonsterWalkAnimation()
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
}

//////////////////////////////////////////////////////////////////////////

    IMPLEMENT_STATE_BEGIN(StoneMan, Move)
{
    STATE_CONSTRUCTOR_BEGIN
    {
        PlayMonsterWalkAnimation();

        m_targetPos = CCPoint(getPosition().x, VisibleRect::bottom().y);
        m_direction = ccpSub(m_targetPos, getPosition());
        m_direction = ccpNormalize(m_direction);
    }
    STATE_CONSTRUCTOR_END

        STATE_UPDATE_BEGIN
    {      
        CCPoint newPos =  ccpAdd( getPosition(), ccpMult(ccpMult(m_direction, m_speed), m_deltaTime) );
        setPosition(newPos);

        TRANSIT_TO_STATE( !VisibleRect::getVisibleRect().containsPoint(newPos), NoTransitionAction, ArrivedBottomSafe );
    }
    STATE_UPDATE_END

        STATE_DESTRUCTOR_BEGIN
    {
    }
    STATE_DESTRUCTOR_END
}
    IMPLEMENT_STATE_END