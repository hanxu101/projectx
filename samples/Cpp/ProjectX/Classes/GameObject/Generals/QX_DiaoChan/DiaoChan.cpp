#include "CommonHeaders.h"

#include "GameObject/Generals/QX_DiaoChan/DiaoChan.h"

DiaoChan::DiaoChan()
{
}

DiaoChan::~DiaoChan()
{
}

void DiaoChan::onEnter()
{
    General::onEnter();

    m_pMainSprite = CCSprite::create("Hero01_0.png");
    addChild(m_pMainSprite);
}

void DiaoChan::onExit()
{
    General::onExit();
}

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_STATE_BEGIN(DiaoChan, CastSkill)
{
    STATE_CONSTRUCTOR_BEGIN
    {
        setScale(5.0f);
        m_elapasedTime = 0.0f;
    }
    STATE_CONSTRUCTOR_END

        STATE_UPDATE_BEGIN
    {
        if (m_elapasedTime > 2.0f)
            SWITCH_TO_STATE(Dead);
    }
    STATE_UPDATE_END

        STATE_DESTRUCTOR_BEGIN
    {
    }
    STATE_DESTRUCTOR_END
}
IMPLEMENT_STATE_END