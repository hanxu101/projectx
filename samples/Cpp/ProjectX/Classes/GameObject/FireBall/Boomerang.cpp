#include "GameObject/FireBall/Boomerang.h"
#include "Utilities/Utilities.h"
#include "VisibleRect.h"
#include "GameObject/GameObjectManager/GameObjectManager.h"
#include "GameObject/GameObject.h"

Boomerang::Boomerang()
    : m_acceleration(-400.0f)
{
}

Boomerang::~Boomerang()
{
}

void Boomerang::onEnter()
{
    FireBall::onEnter();
}

MMR_IMPLEMENT_STATE_BEGIN(Boomerang, Move)
{
    MMR_STATE_CONSTRUCTOR_BEGIN
    {
        m_direction = ccpNormalize(m_direction);
    }
    MMR_STATE_CONSTRUCTOR_END

        MMR_STATE_UPDATE_BEGIN
    {
        m_speed += m_acceleration * m_deltaTime;
        CCPoint offset(ccpMult(m_direction, m_speed * m_deltaTime));

        CCPoint newPos = ccpAdd(getPosition(), offset);
        setPosition(newPos);

        Attack();

        MMR_TRANSIT_TO_STATE( !VisibleRect::getVisibleRect().containsPoint(newPos), NoTransitionAction, Dead );
    }
    MMR_STATE_UPDATE_END

        MMR_STATE_DESTRUCTOR_BEGIN
    {
    }
    MMR_STATE_DESTRUCTOR_END
}
MMR_IMPLEMENT_STATE_END
