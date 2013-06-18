#include "GameObject/Gpe/ReboundWall/ReboundWall.h"
// #include "VisibleRect.h"
// #include "GameObject/Items/BuffItem/TimeFreezeItem.h"
//#include "utilities/Utilities.h"

ReboundWall::ReboundWall()
    : m_pMainSprite(NULL)
    , m_deltaTime(0.0f)
{
}

ReboundWall::~ReboundWall()
{

}

void ReboundWall::onEnter()
{
    m_pMainSprite = CCSprite::create("ball.png");
    m_pMainSprite->setScale(4.0f);

    addChild(m_pMainSprite);

    INIT_FSM(Idle);
}

void ReboundWall::StateUpdate(float deltaTime)
{
    m_deltaTime = deltaTime;
    GetFsm().Update();
}

//////////////////////////////////////////////////////////////////////////

    IMPLEMENT_STATE_BEGIN(ReboundWall, Idle)
{
    STATE_CONSTRUCTOR_BEGIN
    {
       
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
