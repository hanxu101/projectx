#include "CommonHeaders.h"

#include "GameObject/MagicMatrix/MagicPoint.h"

MagicPoint::MagicPoint()
    : GameObject(0.0f, eGOT_MagicMatrix,10.0f)
{
}

MagicPoint::~MagicPoint()
{
}

void MagicPoint::onEnter()
{
    GameObject::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}

void MagicPoint::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    GameObject::onExit();
}

void MagicPoint::ccTouchesMoved( CCSet *pTouches, CCEvent *pEvent )
{
    CCSetIterator iter = pTouches->begin();
    for (; iter != pTouches->end(); iter++)
    {
        CCTouch* pTouch = (CCTouch*)(*iter);
        CCPoint location = pTouch->getLocation();
        float dis = ccpDistance(location, getPosition());
        if ( dis < m_collisionRadius )
        {
            Unspawn();
        }
    }
}