#include "CommonHeaders.h"

#include "GameObject/Generals/QX_DiaoChan/DiaoChan.h"
#include "Gamelogic/MainPlayerLogic.h"
#include "Ui/UiManager.h"

DiaoChan::DiaoChan()
{
}

DiaoChan::~DiaoChan()
{
}

void DiaoChan::onEnter()
{
    General::onEnter();
    
    m_type = eGT_DiaoChan;

    m_pMainSprite = CCSprite::create("Hero01_0.png");
    m_pMainSprite->setVisible(false);
    addChild(m_pMainSprite);

    m_pProfileImage = UIImageView::create();
    m_pProfileImage->setTexture("Eye_DiaoChan.png");
    m_pProfileImage->setVisible(false);

    const CCPoint& centerPoint = VisibleRect::center();
    m_magicPointVec.push_back(ccp(centerPoint.x - 50, centerPoint.y));
    m_magicPointVec.push_back(centerPoint);
    m_magicPointVec.push_back(ccp(centerPoint.x + 50, centerPoint.y));

     UiManager::Singleton().AddChildWidget(m_pProfileImage);
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