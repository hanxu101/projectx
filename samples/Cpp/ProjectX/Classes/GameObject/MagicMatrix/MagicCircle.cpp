#include "CommonHeaders.h"

#include "GameObject/MagicMatrix/MagicCircle.h"
#include "GameObject/MagicMatrix/MagicPoint.h"

MagicCircle::MagicCircle()
    : m_elapsedTime(0.0f)
    , m_durationTime(0.0f)
{
}

MagicCircle::MagicCircle( const TPointVector& magicPointVector, float durationTime )
    : m_magicPointVector(magicPointVector)
    , m_elapsedTime(0.0f)
    , m_durationTime(durationTime)
{
}

MagicCircle::~MagicCircle()
{
    m_magicPointVector.clear();
}

void MagicCircle::onEnter()
{
    GameObject::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);

    INIT_FSM(Idle);
}

void MagicCircle::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    GameObject::onExit();
}

void MagicCircle::StateUpdate( float deltaTime )
{
    m_elapsedTime += deltaTime;
    GetFsm().Update();
}

bool MagicCircle::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
    return true;
}

void MagicCircle::ccTouchEnded( CCTouch* /*pTouche*/, CCEvent* /*pEvent*/ )
{
    if (GetFsm().IsCurrentState(STATE(Operating)) && m_elapsedTime <= 2.0f && getChildrenCount() > 0)
    {
        GetFsm().SwitchState(STATE(Failed));
    }
}

bool MagicCircle::IsSucceed()
{
    return GetFsm().IsCurrentState(STATE(Succeed));
}

bool MagicCircle::IsFailed()
{
    return GetFsm().IsCurrentState(STATE(Failed));
}

IMPLEMENT_STATE_BEGIN(MagicCircle, Idle)
{
    STATE_CONSTRUCTOR_BEGIN
    {
    }
    STATE_CONSTRUCTOR_END

        STATE_UPDATE_BEGIN
    {      
        SWITCH_TO_STATE(Operating);
    }
    STATE_UPDATE_END

        STATE_DESTRUCTOR_BEGIN
    {
    }
    STATE_DESTRUCTOR_END
}
IMPLEMENT_STATE_END


    IMPLEMENT_STATE_BEGIN(MagicCircle, Operating)
{
    STATE_CONSTRUCTOR_BEGIN
    {
        for (UINT i = 0; i < m_magicPointVector.size(); ++i)
        {
            MagicPoint* pPoint = new MagicPoint();
            pPoint->setPosition(m_magicPointVector[i]);
            addChild(pPoint);            
        }

        m_elapsedTime = 0.0f;
    }
    STATE_CONSTRUCTOR_END

        STATE_UPDATE_BEGIN
    {      
        if (m_elapsedTime > 2.0f)
        {
            SWITCH_TO_STATE(Failed);
        }
        else if (getChildrenCount() == 0)
        {
            SWITCH_TO_STATE(Succeed);
        }
    }
    STATE_UPDATE_END

        STATE_DESTRUCTOR_BEGIN
    {
    }
    STATE_DESTRUCTOR_END
}
IMPLEMENT_STATE_END


    IMPLEMENT_STATE_BEGIN(MagicCircle, Succeed)
{
    STATE_CONSTRUCTOR_BEGIN
    {
    }
    STATE_CONSTRUCTOR_END

        STATE_UPDATE_BEGIN
    {      
        SWITCH_TO_STATE(Dead);
    }
    STATE_UPDATE_END

        STATE_DESTRUCTOR_BEGIN
    {
    }
    STATE_DESTRUCTOR_END
}
IMPLEMENT_STATE_END


    IMPLEMENT_STATE_BEGIN(MagicCircle, Failed)
{
    STATE_CONSTRUCTOR_BEGIN
    {
    }
    STATE_CONSTRUCTOR_END

        STATE_UPDATE_BEGIN
    {      
        SWITCH_TO_STATE(Dead);
    }
    STATE_UPDATE_END

        STATE_DESTRUCTOR_BEGIN
    {
    }
    STATE_DESTRUCTOR_END
}
IMPLEMENT_STATE_END

    IMPLEMENT_STATE_BEGIN(MagicCircle, Dead)
{
    STATE_CONSTRUCTOR_BEGIN
    {
        Unspawn();
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