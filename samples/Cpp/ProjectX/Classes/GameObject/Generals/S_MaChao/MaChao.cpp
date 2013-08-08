#include "CommonHeaders.h"

#include "GameObject/GameObjectManager/GameObjectManager.h"
#include "GameObject/Generals/S_MaChao/MaChao.h"
#include "Ui/UiManager.h"

MaChao::MaChao()
{
}

MaChao::~MaChao()
{
}

void MaChao::onEnter()
{
    General::onEnter();

    m_type = eGT_MaChao;

    m_pMainSprite = CCSprite::create("Hero01_2.png");
    m_pMainSprite->setVisible(false);
    addChild(m_pMainSprite);

    m_pProfileImage = UIImageView::create();
    m_pProfileImage->setTexture("Eye_MaChao.png");
    m_pProfileImage->setVisible(false);

    const CCPoint& centerPoint = VisibleRect::center();
    m_magicPointVec.push_back(ccp(centerPoint.x - 50, centerPoint.y));
    m_magicPointVec.push_back(centerPoint);
    m_magicPointVec.push_back(ccp(centerPoint.x + 50, centerPoint.y));
    m_magicPointVec.push_back(ccp(centerPoint.x, centerPoint.y + 50));
    m_magicPointVec.push_back(ccp(centerPoint.x, centerPoint.y - 50));

    UiManager::Singleton().AddChildWidget(m_pProfileImage);
}

void MaChao::onExit()
{
    m_magicPointVec.clear();
    General::onExit();
}

void MaChao::Attack()
{    
    TGameObjectList objectList;
    if (GameObjectManager::IsSingletonCreated())
        GameObjectManager::Singleton().GetGameObjectList(eGOT_Monster, objectList);
    for (TGameObjectList::iterator iter = objectList.begin(); iter != objectList.end(); ++iter)
    {
        if ((*iter)->getPositionY() - getPositionY() < 2.0f)
        {
            (*iter)->ReduceHp(10.0f);
        }
    }
}

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_STATE_BEGIN(MaChao, CastSkill)
{
    STATE_CONSTRUCTOR_BEGIN
    {
        m_pMainSprite->setVisible(true);
        setScale(5.0f);
        m_elapasedTime = 0.0f;

        setPosition(VisibleRect::bottom());
    }
    STATE_CONSTRUCTOR_END

        STATE_UPDATE_BEGIN
    {
        CCPoint newPos =  ccpAdd( getPosition(), ccpMult(ccpMult(ccp(0,1), 200.0f), m_deltaTime) );
        setPosition(newPos);

        Attack();

        TRANSIT_TO_STATE( !VisibleRect::getVisibleRect().containsPoint(newPos), NoTransitionAction, Dead );
    }
    STATE_UPDATE_END

        STATE_DESTRUCTOR_BEGIN
    {
    }
    STATE_DESTRUCTOR_END
}
IMPLEMENT_STATE_END