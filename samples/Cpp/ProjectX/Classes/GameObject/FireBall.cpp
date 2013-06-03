#include "GameObject/FireBall.h"
#include "Utilities/Utilities.h"
#include "VisibleRect.h"
#include "GameObject/GameObjectManager/GameObjectManager.h"
#include "GameObject/GameObject.h"

FireBall::FireBall()
	: GameObject(0.0f, eGOT_Bullet,10.0f)
	, m_pMainSprite(NULL)
	, m_speed(0.0f)
    , m_maxSpeed(400.0f)
{
}

FireBall::~FireBall()
{
}

void FireBall::onEnter()
{
	GameObject::onEnter();

	m_pMainSprite = CCSprite::create("ball.png");
	m_pMainSprite->setScale(4.0f);

	addChild(m_pMainSprite);

	MMR_INIT_FSM(Idle);
}

void FireBall::onExit()
{
	GameObject::onExit();
}

void FireBall::StateUpdate(float deltaTime)
{
	m_deltaTime = deltaTime;
	GetFsm().Update();
}

void FireBall::SetDirection(CCPoint direction)
{
	m_direction = direction;
}

void FireBall::SetSpeedFactor( float slideSpeed )
{
    m_speed = m_maxSpeed * slideSpeed;
}

void FireBall::SetAbort()
{
    GetFsm().SwitchState(MMR_STATE(Abort));
}

void FireBall::SetMove()
{
    GetFsm().SwitchState(MMR_STATE(Move));
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
		m_direction = ccpNormalize(m_direction);
	}
	MMR_STATE_CONSTRUCTOR_END

		MMR_STATE_UPDATE_BEGIN
	{      
		CCPoint newPos =  ccpAdd( getPosition(), ccpMult(ccpMult(m_direction, m_speed), m_deltaTime) );
		setPosition(newPos);

		//Temp. Check collision.
		TGameObjectList objectList;
		GameObjectManager::Get().GetGameObjectList(eGOT_Monster, objectList);
		for (TGameObjectList::iterator iter = objectList.begin(); iter != objectList.end(); ++iter)
		{
			float maxCollisionDis = (*iter)->GetCollisionRadius() + GetCollisionRadius();
			float distance = GetDistance((*iter)->getPositionX(), (*iter)->getPositionY(), getPositionX(), getPositionY());

			if (distance < maxCollisionDis)
			{
				(*iter)->Unspawn();
			}
		}

		MMR_TRANSIT_TO_STATE( !VisibleRect::getVisibleRect().containsPoint(newPos), NoTransitionAction, Dead );
	}
	MMR_STATE_UPDATE_END

		MMR_STATE_DESTRUCTOR_BEGIN
	{
	}
	MMR_STATE_DESTRUCTOR_END
}
MMR_IMPLEMENT_STATE_END

	MMR_IMPLEMENT_STATE_BEGIN(FireBall, Dead)
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

MMR_IMPLEMENT_STATE_BEGIN(FireBall, Abort)
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