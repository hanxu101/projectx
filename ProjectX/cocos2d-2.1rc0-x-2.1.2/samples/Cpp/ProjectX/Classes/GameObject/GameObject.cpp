#include "GameObject/GameObject.h"
#include "GameObject/GameObjectManager/GameObjectManager.h"

GameObject::GameObject()
    : m_hp(0.0f)
    , m_type(eGOT_Invalid)
{
}

GameObject::GameObject( float hp, EGameObjectType type )
    : m_hp(hp)
    , m_type(type)
{
}

GameObject::~GameObject()
{
}

void GameObject::onEnter()
{
    CCNode::onEnter();

    GameObjectManager::Get().RegisterGameObject(this);
}

void GameObject::onExit()
{
    GameObjectManager::Get().UnregisterGameObject(this);

    CCNode::onExit();
}

void GameObject::Unspawn()
{
    removeFromParent();
}

void GameObject::StateUpdate(float deltaTime)
{
}

const EGameObjectType& GameObject::GetGameObjectType()
{
    return m_type;
}

int GameObject::GetDetailTypeIndex()
{
    return static_cast<int>(m_type);
}
