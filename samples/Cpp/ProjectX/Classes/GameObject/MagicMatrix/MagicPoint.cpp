#include "CommonHeaders.h"

#include "GameObject/MagicMatrix/MagicPoint.h"
#include "CocoImageView.h"
#include "UISystem.h"

MagicPoint::MagicPoint()
    : GameObject(0.0f, eGOT_MagicMatrix,10.0f)
    , m_pPointImage(NULL)
{
}

MagicPoint::~MagicPoint()
{
}

void MagicPoint::onEnter()
{
    GameObject::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);

#ifdef TestPoint
    m_pPointImage = cs::CocoImageView::create();
    m_pPointImage->setTexture("ball.png");
    m_pPointImage->setScale(3.0f);
    m_pPointImage->setPosition(getPosition());
#endif

    COCOUISYSTEM->getCurScene()->addWidget(m_pPointImage);
}

void MagicPoint::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);

#ifdef TestPoint
    m_pPointImage->removeFromParentAndCleanup(true);
#endif
    GameObject::onExit();
}

void MagicPoint::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
    CCPoint location = pTouch->getLocation();
    float dis = ccpDistance(location, getPosition());
    if ( dis < m_collisionRadius )
    {
        Unspawn();
    }
}

bool MagicPoint::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
    return true;
}
