#include "CommonHeaders.h"

#include "GameObject/Generals/QX_DiaoChan/DiaoChan.h"
#include "Gamelogic/MainPlayerLogic.h"
#include "CocoImageView.h"
#include "UISystem.h"

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
    m_pMainSprite->setVisible(false);
    addChild(m_pMainSprite);

    m_pProfileImage = cs::CocoImageView::create();
    m_pProfileImage->setTexture("DiaoChanEye.png");
    m_pProfileImage->setVisible(false);

    m_magicPointVec.push_back(ccp(240, 100));
    m_magicPointVec.push_back(ccp(240, 50));

    COCOUISYSTEM->getCurScene()->addWidget(m_pProfileImage);
}

void DiaoChan::onExit()
{
    m_magicPointVec.clear();
    General::onExit();
}

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_STATE_BEGIN(DiaoChan, CastSkill)
{
    STATE_CONSTRUCTOR_BEGIN
    {
        m_pMainSprite->setVisible(true);
        setScale(5.0f);
        m_elapasedTime = 0.0f;

        MainPlayerLogic::Singleton().IncreaseHp(1);
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