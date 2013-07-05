#include "CommonHeaders.h"

#include "GameObject/Items/Item.h"

Item::Item()
    : GameObject(10.0f, eGOT_Item,10.0f)
    , m_pMainSprite(NULL)
    , m_targetPos(CCPointZero)
    , m_direction(CCPointZero)
    , m_speed(20.0f)
    , m_deltaTime(0.0f)
{
}

Item::~Item()
{
}

void Item::onEnter()
{
    GameObject::onEnter();
    registerWithTouchDispatcher();
}

void Item::onExit()
{
    unregisterWithTouchDispatcher();
    GameObject::onExit();
}

void Item::StateUpdate( float deltaTime )
{
}

void Item::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}

void Item::unregisterWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void Item::ccTouchesEnded( cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent )
{
    CCSetIterator iter = pTouches->begin();
    for (; iter != pTouches->end(); iter++)
    {
        CCTouch* pTouch = (CCTouch*)(*iter);
        CCPoint location = pTouch->getLocation();
        float dis = ccpDistance(location, getPosition());
        if ( dis < m_collisionRadius )
        {
            ItemTouchesEnded();
        }
    }
}


IMPLEMENT_STATE_BEGIN(Item, Idle)
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

    IMPLEMENT_STATE_BEGIN(Item, Move)
{
    STATE_CONSTRUCTOR_BEGIN
    {
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

    IMPLEMENT_STATE_BEGIN(Item, ArrivedBottomSafe)
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