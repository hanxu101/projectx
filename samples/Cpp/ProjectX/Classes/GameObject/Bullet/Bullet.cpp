#include "CommonHeaders.h"

#include "GameObject/Bullet/Bullet.h"
#include "Gamelogic/MainPlayerLogic.h"
#include "GameObject/GameObjectManager/GameObjectManager.h"

Bullet::Bullet()
    : GameObject(10.0f, eGOT_Bullet,10.0f)
    , m_pMainSprite(NULL)
    , m_pParticle(NULL)
    , m_targetPos(CCPointZero)
    , m_direction(CCPointZero)
    , m_speed(50.0f)
    , m_deltaTime(0.0f)
{
}

Bullet::~Bullet()
{
}

void Bullet::onEnter()
{
    GameObject::onEnter();

    INIT_FSM(Idle);
}

void Bullet::onExit()
{
    GameObject::onExit();
}

void Bullet::StateUpdate( float deltaTime )
{
    m_deltaTime = deltaTime;
    GetFsm().Update();
}

void Bullet::Attack()
{    
    TGameObjectList objectList;
    if (GameObjectManager::IsSingletonCreated())
        GameObjectManager::Singleton().GetGameObjectList(eGOT_MainCharacter, objectList);
    for (TGameObjectList::iterator iter = objectList.begin(); iter != objectList.end(); ++iter)
    {
        float maxCollisionDis = (*iter)->GetCollisionRadius() + GetCollisionRadius();
        float distanceSQ = ccpDistanceSQ((*iter)->getPosition(), getPosition());

        if (distanceSQ < maxCollisionDis * maxCollisionDis)
        {
            MainPlayerLogic::Singleton().ReduceHp(1);
            GetFsm().SwitchState(STATE(ArrivedBottomSafe));
        }
    }
}

IMPLEMENT_STATE_BEGIN(Bullet, Idle)
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

    IMPLEMENT_STATE_BEGIN(Bullet, Move)
{
    STATE_CONSTRUCTOR_BEGIN
    {
        m_pParticle = CCParticleGalaxy::create();
        CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage("stars.png");
        m_pParticle->setTexture(pTexture);
        m_pParticle->setLife(0.5f);
        m_pParticle->setScale(0.3f);
        m_pParticle->setPosition(getPosition());
        getParent()->addChild(m_pParticle, 10);

        m_targetPos = CCPoint(getPosition().x, VisibleRect::bottom().y);
        m_direction = ccpSub(m_targetPos, getPosition());
        m_direction = ccpNormalize(m_direction);
    }
    STATE_CONSTRUCTOR_END

        STATE_UPDATE_BEGIN
    {  
        CCPoint newPos =  ccpAdd( getPosition(), ccpMult(ccpMult(m_direction, m_speed), m_deltaTime) );
        setPosition(newPos);
        m_pParticle->setPosition(newPos);

        Attack();

        TRANSIT_TO_STATE( !VisibleRect::getVisibleRect().containsPoint(newPos), NoTransitionAction, ArrivedBottomSafe );
    }
    STATE_UPDATE_END

        STATE_DESTRUCTOR_BEGIN
    {
    }
    STATE_DESTRUCTOR_END
}
IMPLEMENT_STATE_END

    IMPLEMENT_STATE_BEGIN(Bullet, ArrivedBottomSafe)
{
    STATE_CONSTRUCTOR_BEGIN
    {
        m_pParticle->removeFromParentAndCleanup(true);
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