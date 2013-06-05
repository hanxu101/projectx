#include "GameObject/Monsters/EarthMonster/StoneMan.h"
#include "VisibleRect.h"

StoneMan::StoneMan()
    : m_pMainSprite(NULL)
    , m_speed(100.0f)
    , m_deltaTime(0.0f)
{

}

StoneMan::~StoneMan()
{

}

void StoneMan::onEnter()
{
    Monster::onEnter();

    m_pMainSprite = CCSprite::create("Hero01_0.png");
    addChild(m_pMainSprite);

    MMR_INIT_FSM(Idle);
}

void StoneMan::onExit()
{
    Monster::onExit();
}

void StoneMan::StateUpdate(float deltaTime)
{
    m_deltaTime = deltaTime;
    GetFsm().Update();
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

MMR_IMPLEMENT_STATE_BEGIN(StoneMan, Idle)
{
    MMR_STATE_CONSTRUCTOR_BEGIN
    {
        // Set suitable position.
        const float monsterRoadSizeRate = 0.2f;
        const float offset = 0.5f;
        setPosition((int(getPosition().x / (VisibleRect::right().x * monsterRoadSizeRate)) + offset) * VisibleRect::right().x * monsterRoadSizeRate, getPosition().y);
        setScale(4.0f);
    }
    MMR_STATE_CONSTRUCTOR_END

        MMR_STATE_UPDATE_BEGIN
    {      
        MMR_SWITCH_TO_STATE(Move);
    }
    MMR_STATE_UPDATE_END

        MMR_STATE_DESTRUCTOR_BEGIN
    {
    }
    MMR_STATE_DESTRUCTOR_END
}
MMR_IMPLEMENT_STATE_END

    MMR_IMPLEMENT_STATE_BEGIN(StoneMan, Move)
{
    MMR_STATE_CONSTRUCTOR_BEGIN
    {
        PlayMonsterWalkAnimation();

        m_targetPos = CCPoint(getPosition().x, VisibleRect::bottom().y);
        m_direction = ccpSub(m_targetPos, getPosition());
        m_direction = ccpNormalize(m_direction);
    }
    MMR_STATE_CONSTRUCTOR_END

        MMR_STATE_UPDATE_BEGIN
    {      
        CCPoint newPos =  ccpAdd( getPosition(), ccpMult(ccpMult(m_direction, m_speed), m_deltaTime) );
        setPosition(newPos);

        MMR_TRANSIT_TO_STATE( !VisibleRect::getVisibleRect().containsPoint(newPos), NoTransitionAction, ArrivedBottomSafe );
    }
    MMR_STATE_UPDATE_END

        MMR_STATE_DESTRUCTOR_BEGIN
    {
    }
    MMR_STATE_DESTRUCTOR_END
}
MMR_IMPLEMENT_STATE_END

    MMR_IMPLEMENT_STATE_BEGIN(StoneMan, ArrivedBottomSafe)
{
    MMR_STATE_CONSTRUCTOR_BEGIN
    {
        Unspawn();
    }
    MMR_STATE_CONSTRUCTOR_END

        MMR_STATE_UPDATE_BEGIN
    {      
    }
    MMR_STATE_UPDATE_END

        MMR_STATE_DESTRUCTOR_BEGIN
    {
    }
    MMR_STATE_DESTRUCTOR_END
}
MMR_IMPLEMENT_STATE_END