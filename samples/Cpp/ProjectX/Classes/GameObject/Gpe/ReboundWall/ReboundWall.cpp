#include "CommonHeaders.h"

#include "GameObject/Gpe/ReboundWall/ReboundWall.h"
#include "GameObject/GameObjectManager/GameObjectManager.h"
#include "GameObject/FireBall/FireBall.h"

ReboundWall::ReboundWall()
    : m_pMainSprite(NULL)
    , m_deltaTime(0.0f)
    , m_right(0.0f)
    , m_left(0.0f)
    , m_bottom(0.0f)
    , m_top(0.0f)
    , m_center(CCPoint(0.0f, 0.0f))
    , m_upRange(0.0f)
    , m_downRange(0.0f)
    , m_speed(0.0f)
{
}

ReboundWall::~ReboundWall()
{

}

void ReboundWall::onEnter()
{
    Gpe::onEnter();

    m_pMainSprite = CCSprite::create("streak.png");
    m_pMainSprite->setScaleX(0.3f);

    addChild(m_pMainSprite);

    INIT_FSM(Idle);
}

void ReboundWall::StateUpdate(float deltaTime)
{
    m_deltaTime = deltaTime;
    GetFsm().Update();

    CheckRedboud();
}

void ReboundWall::SetSize(float right, float left, float bottom, float top, CCPoint center)
{
    m_right = right;
    m_left = left;
    m_bottom = bottom;
    m_top = top;
    m_center = center;
}

float ReboundWall::GetLeft() const
{
    return m_left;
}

float ReboundWall::GetRight() const
{
    return m_right;
}

void ReboundWall::SetRange(float upRange, float downRange)
{
    m_upRange = upRange;
    m_downRange = downRange;
}

void ReboundWall::SetSpeed(float speed)
{
    m_speed = speed;
}

void ReboundWall::draw()
{
#ifdef DEBUG_DRAW_DEBUG_SHAPE
	glLineWidth( 5.0f );
	ccDrawColor4B(ccRED.r, ccRED.g, ccRED.b, 255);
    CCPoint topLeft(ccpAdd(m_center, ccp(-m_left, m_top)));
    CCPoint topRight(ccpAdd(m_center, ccp(m_right, m_top)));
    CCPoint bottomRight(ccpAdd(m_center, ccp(m_right, -m_bottom)));
    CCPoint bottomLeft(ccpAdd(m_center, ccp(-m_left, -m_bottom)));

    ccDrawLine( topLeft, topRight);
    ccDrawLine( topRight, bottomRight);
    ccDrawLine( bottomRight, bottomLeft);
    ccDrawLine( bottomLeft, topLeft);
#endif
}

void ReboundWall::CheckRedboud()
{
    TGameObjectList objectList;
    if (GameObjectManager::IsSingletonCreated())
        GameObjectManager::Singleton().GetGameObjectList(eGOT_FireBall, objectList);

    for (TGameObjectList::iterator iter = objectList.begin(); iter != objectList.end(); ++iter)
    {
        float nearestDistance = FLT_MAX;

        CCPoint topLeft(ccpAdd( getPosition(), ccpAdd(m_center, ccp(-m_left, m_top))));
        CCPoint topRight(ccpAdd( getPosition(), ccpAdd(m_center, ccp(m_right, m_top))));
        CCPoint bottomRight(ccpAdd( getPosition(), ccpAdd(m_center, ccp(m_right, -m_bottom))));
        CCPoint bottomLeft(ccpAdd( getPosition(), ccpAdd(m_center, ccp(-m_left, -m_bottom))));

        float distanceSQ = ccpDistanceSQ(topLeft, (*iter)->getPosition());
        if (distanceSQ < nearestDistance)
        {
            nearestDistance = distanceSQ;
        }
        distanceSQ = ccpDistanceSQ(topRight, (*iter)->getPosition());
        if (distanceSQ < nearestDistance)
        {
            nearestDistance = distanceSQ;
        }
        distanceSQ = ccpDistanceSQ(bottomRight, (*iter)->getPosition());
        if (distanceSQ < nearestDistance)
        {
            nearestDistance = distanceSQ;
        }
        distanceSQ = ccpDistanceSQ(bottomLeft, (*iter)->getPosition());
        if (distanceSQ < nearestDistance)
        {
            nearestDistance = distanceSQ;
        }

        if (nearestDistance < (*iter)->GetCollisionRadius() * (*iter)->GetCollisionRadius())
        {
            ReboundFireBall(static_cast<FireBall*>(*iter));
        }
    }
}

void ReboundWall::ReboundFireBall( FireBall* fireBall )
{
    if (fireBall->CanRebound())
    {
        CCPoint direction = fireBall->GetDirection();
        direction.x = direction.x * -1.0f;
        fireBall->SetDirection(direction);
        fireBall->SetCanRebound(false);
    }
}

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_STATE_BEGIN(ReboundWall, Idle)
{
    STATE_CONSTRUCTOR_BEGIN
    {
       m_upRange += getPosition().y;
       m_downRange += getPosition().y;
    }
    STATE_CONSTRUCTOR_END

    STATE_UPDATE_BEGIN
    {
        TRANSIT_TO_STATE( true, NoTransitionAction, Move );
    }
    STATE_UPDATE_END

    STATE_DESTRUCTOR_BEGIN
    {

    }
    STATE_DESTRUCTOR_END
}
IMPLEMENT_STATE_END

IMPLEMENT_STATE_BEGIN(ReboundWall, Move)
{
    STATE_CONSTRUCTOR_BEGIN
    {
       
    }
    STATE_CONSTRUCTOR_END

    STATE_UPDATE_BEGIN
    {
        CCPoint newPos = ccpAdd(getPosition(), CCPoint(0.0f, m_speed * m_deltaTime));
        if (newPos.y > m_upRange)
        {
            m_speed = abs(m_speed) * -1.0f;
        }
        else if (newPos.y < m_downRange)
        {
            m_speed = abs(m_speed);
        }
        
        newPos = ccpAdd(getPosition(), CCPoint(0.0f, m_speed * m_deltaTime));
        setPosition(newPos);
    }
    STATE_UPDATE_END

    STATE_DESTRUCTOR_BEGIN
    {
    }
    STATE_DESTRUCTOR_END
}
IMPLEMENT_STATE_END
