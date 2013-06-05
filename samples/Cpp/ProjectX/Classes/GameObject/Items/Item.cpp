#include "GameObject/Items/Item.h"

Item::Item()
    : GameObject(10.0f, eGOT_Item,10.0f)
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