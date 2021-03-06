#include "CommonHeaders.h"

#include "GameObject/Generals/General.h"
#include "GameObject/GameObjectManager/GameObjectManager.h"
#include "GameObject/MagicMatrix/MagicCircle.h"

General::General()
    : GameObject(10.0f, eGOT_General,10.0f)
    , m_type(eGT_Invalid)
    , m_pMainSprite(NULL)
    , m_pProfileImage(NULL)
    , m_elapasedTime(0.0f)
    , m_deltaTime(0.0f)
    , m_magicCircle(NULL)
{
}

General::~General()
{
}

void General::onEnter()
{
    GameObject::onEnter();

    INIT_FSM(Idle);
}

void General::onExit()
{
    GameObject::onExit();
}

void General::StateUpdate( float deltaTime )
{
    m_deltaTime = deltaTime;
    m_elapasedTime += deltaTime;
    GetFsm().Update();
}

IMPLEMENT_STATE_BEGIN(General, Idle)
{
    STATE_CONSTRUCTOR_BEGIN
    {
    }
    STATE_CONSTRUCTOR_END

        STATE_UPDATE_BEGIN
    {      
        SWITCH_TO_STATE(ReadyToShowUp);
    }
    STATE_UPDATE_END

        STATE_DESTRUCTOR_BEGIN
    {
    }
    STATE_DESTRUCTOR_END
}
IMPLEMENT_STATE_END

    IMPLEMENT_STATE_BEGIN(General, ReadyToShowUp)
{
    STATE_CONSTRUCTOR_BEGIN
    {
        m_magicCircle = new MagicCircle(m_magicPointVec, 2.0f, m_type);
        m_magicCircle->setPosition(VisibleRect::center());
        getParent()->addChild(m_magicCircle);
    }
    STATE_CONSTRUCTOR_END

        STATE_UPDATE_BEGIN
    {      
        TRANSIT_TO_STATE( m_magicCircle->IsFailed(), NoTransitionAction, Dead );
        TRANSIT_TO_STATE( m_magicCircle->IsSucceed(), NoTransitionAction, ShowUp );
    }
    STATE_UPDATE_END

        STATE_DESTRUCTOR_BEGIN
    {
    }
    STATE_DESTRUCTOR_END
}
IMPLEMENT_STATE_END

    IMPLEMENT_STATE_BEGIN(General, ShowUp)
{
    STATE_CONSTRUCTOR_BEGIN
    {
        // Play show up animation...
        m_elapasedTime = 0.0f;

        if (m_pProfileImage)
        {
            m_pProfileImage->setVisible(true);

            CCRect rect = m_pProfileImage->getRect();
            float width = rect.getMaxX() - rect.getMinX();
            m_pProfileImage->setScale((VisibleRect::right().x - VisibleRect::left().x) / width);
            m_pProfileImage->setPosition(ccp(VisibleRect::left().x - width * 0.5f, VisibleRect::left().y));
            rect = m_pProfileImage->getRect();
            width = rect.getMaxX() - rect.getMinX();
            m_pProfileImage->runAction(CCMoveTo::create(0.3f, ccp(VisibleRect::right().x - width * 0.5f, VisibleRect::right().y)));

            GameObjectManager::Singleton().RegisterPauseUpdateGameObjectType(eGOT_Monster);
            GameObjectManager::Singleton().RegisterPauseUpdateGameObjectType(eGOT_Item);
        }
    }
    STATE_CONSTRUCTOR_END

        STATE_UPDATE_BEGIN
    {
        if (m_elapasedTime > 2.0f)
        {
            m_pProfileImage->removeFromParentAndCleanup(true);
            SWITCH_TO_STATE(CastSkill);
        }
    }
    STATE_UPDATE_END

        STATE_DESTRUCTOR_BEGIN
    {
        GameObjectManager::Singleton().UnregisterPauseUpdateGameObjectType(eGOT_Monster);
        GameObjectManager::Singleton().UnregisterPauseUpdateGameObjectType(eGOT_Item);
    }
    STATE_DESTRUCTOR_END
}
IMPLEMENT_STATE_END


    IMPLEMENT_STATE_BEGIN(General, CastSkill)
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


    IMPLEMENT_STATE_BEGIN(General, Dead)
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