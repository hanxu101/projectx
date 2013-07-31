#include "CommonHeaders.h"

#include "GameObject/Monsters/Boss/Shu/BossMaChao.h"
#include "GameObject/Bullet/Bullet.h"
#include "GameObject/Monsters/Boss/Defines/BossDefines.h"

BossMaChao::BossMaChao()
    : m_moveNode(0)
    , m_skillCastTimeElapsed(0.0f)
{
    m_speed = s_MaChao_MoveSpeed;
}

BossMaChao::~BossMaChao()
{
    m_moveAroundPos.clear();
}

void BossMaChao::onEnter()
{
    Monster::onEnter();

    SetMoveAroundPos();

    float scaleFactor = CCDirector::sharedDirector()->getContentScaleFactor();
    m_pMainSprite = CCSprite::create("Boss_MaChao.png",CCRectMake(0, 0, 32 / scaleFactor, 48 / scaleFactor));
    addChild(m_pMainSprite);
}

void BossMaChao::onExit()
{
    Monster::onExit();
}

void BossMaChao::Killed()
{
    Unspawn();
}

int BossMaChao::GetDetailTypeIndex()
{
    return static_cast<int>(eMT_MaChao);
}

void BossMaChao::SetMoveAroundPos()
{
    m_moveAroundPos.push_back(VisibleRect::right());
    m_moveAroundPos.push_back(VisibleRect::center());
    m_moveAroundPos.push_back(VisibleRect::left());
}

void BossMaChao::PlayMonsterWalkAnimation(EDirection direction)
{
    m_pMainSprite->stopAllActions();

    float scaleFactor = CCDirector::sharedDirector()->getContentScaleFactor();

    float x = 32 / scaleFactor;
    float y = 48 / scaleFactor;

    CCSpriteFrame *frame0=CCSpriteFrame::create("Boss_MaChao.png",CCRectMake(0, y * direction, x, y)); 
    CCSpriteFrame *frame1=CCSpriteFrame::create("Boss_MaChao.png",CCRectMake(x, y * direction, x, y)); 
    CCSpriteFrame *frame2=CCSpriteFrame::create("Boss_MaChao.png",CCRectMake(x*2, y * direction, x, y)); 
    CCSpriteFrame *frame3=CCSpriteFrame::create("Boss_MaChao.png",CCRectMake(x*3, y * direction, x, y)); 

    CCArray *animFrames = new CCArray; 
    animFrames->addObject(frame0); 
    animFrames->addObject(frame1); 
    animFrames->addObject(frame2); 
    animFrames->addObject(frame3); 

    CCAnimation *pAnim = CCAnimation::createWithSpriteFrames(animFrames, 0.1f); 
    animFrames->release();

    m_pMainSprite->runAction(CCRepeatForever::create(CCAnimate::create(pAnim)));
}

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_STATE_BEGIN(BossMaChao, Move)
{
    STATE_CONSTRUCTOR_BEGIN
    {
        PlayMonsterWalkAnimation(ED_Down);

        m_targetPos = VisibleRect::center();
        m_direction = ccpSub(m_targetPos, getPosition());
        m_direction = ccpNormalize(m_direction);
    }
    STATE_CONSTRUCTOR_END

        STATE_UPDATE_BEGIN
    {      
        CCPoint newPos =  ccpAdd( getPosition(), ccpMult(ccpMult(m_direction, m_speed), m_deltaTime) );
        setPosition(newPos);

        TRANSIT_TO_STATE( ccpDistanceSQ(newPos, m_targetPos) < s_Boss_TargetPos_Offset, NoTransitionAction, CastSkill );
    }
    STATE_UPDATE_END

        STATE_DESTRUCTOR_BEGIN
    {
    }
    STATE_DESTRUCTOR_END
}
IMPLEMENT_STATE_END


    IMPLEMENT_STATE_BEGIN(BossMaChao, CastSkill)
{
    STATE_CONSTRUCTOR_BEGIN
    {
        PlayMonsterWalkAnimation(ED_Down);

        Bullet* pBullet = new Bullet();
        pBullet->setPosition(getPosition());
        getParent()->addChild(pBullet);

        m_targetPos = CCPoint(getPosition().x, VisibleRect::bottom().y);
        m_direction = ccpSub(m_targetPos, getPosition());
        m_direction = ccpNormalize(m_direction);
    }
    STATE_CONSTRUCTOR_END

        STATE_UPDATE_BEGIN
    {
        m_skillCastTimeElapsed += m_deltaTime;
        TRANSIT_TO_STATE( m_skillCastTimeElapsed > s_MaChao_CastSkillTime, NoTransitionAction, MoveAround );
    }
    STATE_UPDATE_END

        STATE_DESTRUCTOR_BEGIN
    {
        m_skillCastTimeElapsed = 0.0f;
    }
    STATE_DESTRUCTOR_END
}
IMPLEMENT_STATE_END


    IMPLEMENT_STATE_BEGIN(BossMaChao, MoveAround)
{
    STATE_CONSTRUCTOR_BEGIN
    {
        m_targetPos = m_moveAroundPos[m_moveNode];
        ++m_moveNode;
        if (m_moveNode >= m_moveAroundPos.size())
            m_moveNode = 0;

        m_direction = ccpSub(m_targetPos, getPosition());
        m_direction = ccpNormalize(m_direction);

        EDirection direction = m_direction.x > 0 ? ED_Right : ED_Left;        
        PlayMonsterWalkAnimation(direction);
    }
    STATE_CONSTRUCTOR_END

        STATE_UPDATE_BEGIN
    {
        CCPoint newPos =  ccpAdd( getPosition(), ccpMult(ccpMult(m_direction, m_speed), m_deltaTime) );
        setPosition(newPos);

        TRANSIT_TO_STATE( ccpDistanceSQ(newPos, m_targetPos) < s_Boss_TargetPos_Offset, NoTransitionAction, CastSkill );
    }
    STATE_UPDATE_END

        STATE_DESTRUCTOR_BEGIN
    {
    }
    STATE_DESTRUCTOR_END
}
IMPLEMENT_STATE_END