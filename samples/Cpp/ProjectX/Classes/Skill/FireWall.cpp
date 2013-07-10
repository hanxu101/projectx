#include "CommonHeaders.h"

#include "Skill/FireWall.h"
#include "GameObject/GameObjectManager/GameObjectManager.h"
#include "GameObject/GameObject.h"
#include "Gamelogic/MainPlayerLogic.h"

FireWall::FireWall()
    : m_collisionUnitRadius(5.0f)
    , m_unitDistance(5.0f)
    , m_comboAttackCount(0)
{
}

FireWall::~FireWall()
{

}

void FireWall::Init()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 2);
    m_collisionUnits.clear();
}

void FireWall::Uninit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void FireWall::OnUpdate( float deltaTime )
{
#ifdef DEBUG_DRAW_DEBUG_SHAPE
    glLineWidth( 2.0f );
    for (std::vector<CCPoint>::iterator unitIter = m_collisionUnits.begin(); unitIter != m_collisionUnits.end(); ++unitIter)
    {
        ccDrawCircle(*unitIter, m_collisionUnitRadius, (float)M_PI*2.0f, 50, false);
    }
#endif

    TGameObjectList objectList;
    if (GameObjectManager::IsSingletonCreated())
        GameObjectManager::Singleton().GetGameObjectList(eGOT_Monster, objectList);
    for (TGameObjectList::iterator iter = objectList.begin(); iter != objectList.end(); ++iter)
    {
        float maxCollisionDis = (*iter)->GetCollisionRadius() + m_collisionUnitRadius;
        
        for (std::vector<CCPoint>::iterator unitIter = m_collisionUnits.begin(); unitIter != m_collisionUnits.end(); ++unitIter)
        {
            float distanceSQ = ccpDistanceSQ((*iter)->getPosition(), *unitIter);

            if (distanceSQ < maxCollisionDis * maxCollisionDis)
            {
                (*iter)->ReduceHp(99999);
                ++m_comboAttackCount;
                MainPlayerLogic::Singleton().ComboIncreaseCoin(m_comboAttackCount);;
            }
        }
    }
}

void FireWall::ccTouchesBegan( cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent )
{

}

void FireWall::ccTouchesMoved( cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent )
{
    CCSetIterator iter = pTouches->begin();
    for (; iter != pTouches->end(); ++iter)
    {
        CCTouch* pTouch = (CCTouch*)(*iter);
        CCPoint touchPos = pTouch->getLocation();
        if (m_collisionUnits.size() == 0)
        {
             m_collisionUnits.push_back(touchPos);
 
            Unit* pUnit = Unit::create("ball_EnergyCharged.png");
            pUnit->setPosition(touchPos);
            CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
            pScene->addChild(pUnit);
        }
        else
        {
            bool collided = false;
            for (std::vector<CCPoint>::iterator unitIter = m_collisionUnits.begin(); unitIter != m_collisionUnits.end(); ++unitIter)
            {
                if (ccpDistanceSQ(*unitIter, touchPos) <= m_unitDistance*m_unitDistance)
                {
                    collided = true;   
                    break;
                }
            }
            if (!collided)
            {
                m_collisionUnits.push_back(touchPos);
                Unit* pUnit = Unit::create("ball_EnergyCharged.png");
                pUnit->setPosition(touchPos);
                CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();
                pScene->addChild(pUnit);
            }
        }
    }
}

void FireWall::ccTouchesEnded( cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent )
{

}

void FireWall::ccTouchesCancelled( cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent )
{

}

void FireWall::Unit::draw()
{
    CCSprite::draw();
#ifdef DEBUG_DRAW_DEBUG_SHAPE
    ccDrawCircle(CCPoint(0.0f, 0.0f), 5.0f, (float)M_PI*2.0f, 50, false);
#endif
}

FireWall::Unit::Unit()
{

}

FireWall::Unit* FireWall::Unit::create( const char *pszFileName )
{
    Unit *pobSprite = new Unit();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}
