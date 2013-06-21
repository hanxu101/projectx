#include "CommonHeaders.h"

#include "GameLogic/GpeLogic.h"

#include "GameObject/Gpe/Gpe.h"
#include "GameObject/Gpe/ReboundWall/ReboundWall.h"

GpeLogic::GpeLogic()
{
}

GpeLogic::~GpeLogic()
{
}

void GpeLogic::onEnter()
{
    CCNode::onEnter();

    InitGpe();
}

void GpeLogic::InitGpe()
{
    // Create 2 rebound wall on the right and left side of screen
    ReboundWall* preboundWall = new ReboundWall();
    preboundWall->SetSize(10, 10, 20, 20, CCPoint(0.0f, 0.0f));
    preboundWall->SetSpeed(10.0f);
    preboundWall->SetRange(10.0f, -10.0f);
    preboundWall->setPosition(CCPoint(VisibleRect::left().x + preboundWall->GetLeft(), VisibleRect::center().y));
    addChild(preboundWall);
    m_gpeVec.push_back(preboundWall);

    ReboundWall* preboundWall2 = new ReboundWall();
    preboundWall2->SetSize(10, 10, 20, 20, CCPoint(0.0f, 0.0f));
    preboundWall2->setPosition(CCPoint(VisibleRect::right().x - preboundWall2->GetRight(), VisibleRect::center().y));
    preboundWall2->SetSpeed(10.0f);
    preboundWall2->SetRange(10.0f, -10.0f);
    addChild(preboundWall2);
    m_gpeVec.push_back(preboundWall2);
}