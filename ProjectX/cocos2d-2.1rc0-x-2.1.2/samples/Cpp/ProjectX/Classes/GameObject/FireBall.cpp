#include "GameObject/FireBall.h"
#include "Utilities/Utilities.h"
#include "VisibleRect.h"

FireBall::FireBall()
	: m_pMainSprite(NULL)
	, m_speed(100)
{
}

FireBall::~FireBall()
{
}

void FireBall::onEnter()
{
	CCNode::onEnter();
	m_pMainSprite = CCSprite::create("ball.png");
	m_pMainSprite->setScale(4.0f);

	addChild(m_pMainSprite);

	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(FireBall::StateUpdate), this, 0, false);
	MMR_INIT_FSM(Idle);
}

void FireBall::onExit()
{

}

void FireBall::StateUpdate(float deltaTime)
{
	m_deltaTime = deltaTime;
	GetFsm().Update();
}

//////////////////////////////////////////////////////////////////////////

MMR_IMPLEMENT_STATE_BEGIN(FireBall, Idle)
{
	MMR_STATE_CONSTRUCTOR_BEGIN
	{
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

MMR_IMPLEMENT_STATE_BEGIN(FireBall, Move)
{
	MMR_STATE_CONSTRUCTOR_BEGIN
	{
		m_targetPos = CCPoint(RandomFloat(VisibleRect::left().x, VisibleRect::right().x), RandomFloat(VisibleRect::bottom().y, VisibleRect::top().y));
		m_direction = ccpSub(m_targetPos, getPosition());
		m_direction = ccpNormalize(m_direction);
	}
	MMR_STATE_CONSTRUCTOR_END

		MMR_STATE_UPDATE_BEGIN
	{      
		CCPoint newPos =  ccpAdd( getPosition(), ccpMult(ccpMult(m_direction, m_speed), m_deltaTime) );
        setPosition(newPos);
	}
	MMR_STATE_UPDATE_END

		MMR_STATE_DESTRUCTOR_BEGIN
	{
	}
	MMR_STATE_DESTRUCTOR_END
}
MMR_IMPLEMENT_STATE_END