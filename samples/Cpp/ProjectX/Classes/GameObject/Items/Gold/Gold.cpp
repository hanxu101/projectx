#include "CommonHeaders.h"

#include "GameObject/Items/Gold/Gold.h"
#include "Gamelogic/MainPlayerLogic.h"

Gold::Gold()
    : m_pMainSprite(NULL)
    , m_speed(20.0f)
    , m_deltaTime(0.0f)
{

}

Gold::~Gold()
{

}

void Gold::onEnter()
{
    Item::onEnter();

    m_pMainSprite = CCSprite::create("Coin.png");
    addChild(m_pMainSprite);

    INIT_FSM(Idle);
}

void Gold::onExit()
{
    Item::onExit();
}

void Gold::StateUpdate(float deltaTime)
{
    m_deltaTime = deltaTime;
    GetFsm().Update();
}

int Gold::GetDetailTypeIndex()
{
    return static_cast<int>(eMT_StoneMan);
}

void Gold::PlayMonsterWalkAnimation()
{
}

void Gold::ItemTouchesEnded()
{
    MainPlayerLogic::Singleton().IncreaseCoin(1);

    Unspawn();
}

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_STATE_BEGIN(Gold, Idle)
{
    STATE_CONSTRUCTOR_BEGIN
    {
    }
    STATE_CONSTRUCTOR_END

        STATE_UPDATE_BEGIN
    {      
        SWITCH_TO_STATE(Move);
    }
    STATE_UPDATE_END

        STATE_DESTRUCTOR_BEGIN
    {
    }
    STATE_DESTRUCTOR_END
}
IMPLEMENT_STATE_END

    IMPLEMENT_STATE_BEGIN(Gold, Move)
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

    IMPLEMENT_STATE_BEGIN(Gold, ArrivedBottomSafe)
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