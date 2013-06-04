#include "GameObject/Monster.h"

Monster::Monster()
    : GameObject(10.0f, eGOT_Monster,10.0f)
{
}

Monster::~Monster()
{
}

void Monster::onEnter()
{
    GameObject::onEnter();
}

void Monster::onExit()
{
    GameObject::onExit();
}

void Monster::StateUpdate( float deltaTime )
{
}