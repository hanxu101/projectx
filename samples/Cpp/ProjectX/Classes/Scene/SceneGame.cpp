#include "CommonHeaders.h"

#include "SceneGame.h"
#include "GameObject/GameObjectManager/GameObjectManager.h"
#include "Buff/BuffManager/BuffManager.h"
#include "Skill/SkillManager.h"
#include "GameLogic/MonsterGroupLogic.h"
#include "GameLogic/GeneralGroupLogic.h"
#include "Gamelogic/MainPlayerLogic.h"
#include "GameLogic/GpeLogic.h"
#include "UISystem.h"
#include "CocoPanel.h"

//------------------------------------------------------------------
//
// GameLayer
//
//------------------------------------------------------------------
const int g_uiZOrder = 3;
const int g_generalZOrder = 2;
const int g_monsterZOder = 1;
const int g_backGroundZOrder = -1;

GameLayer::GameLayer(void)
    : m_pMonsterGroupLogic(NULL)
    , m_pGeneralGroupLogic(NULL)
    , m_pGpeLogic(NULL)
    , m_pGameUI(NULL)
{
}

GameLayer::~GameLayer(void)
{
}

std::string GameLayer::title()
{
    return "GameScene";
}

void GameLayer::onEnter()
{
    CCLayer::onEnter();

    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(GameLayer::Update), this, 0, false);

    GameObjectManager::CreateSingleton();
    BuffManager::CreateSingleton();
    SkillManager::CreateSingleton();
    SkillManager::Singleton().Init();

#ifndef DEBUG_HIDE_TEXT
    // Back ground.
    CCSprite* pBackGround = CCSprite::create("backGround.jpg");

    CCRect rect = pBackGround->getTextureRect();
    float width = rect.getMaxX() - rect.getMinX();
    pBackGround->setScaleX((VisibleRect::right().x - VisibleRect::left().x) / width);
    float height = rect.getMaxY() - rect.getMinY();
    pBackGround->setScaleY((VisibleRect::top().y - VisibleRect::bottom().y) / height);

    pBackGround->setPosition(VisibleRect::center());
    addChild(pBackGround, g_backGroundZOrder);
#endif

    cs::CocoWidget* pWidget = NULL;

#ifndef DEBUG_NO_UI
    // Init UI.
    CCNode* pUiNode = CCNode::create();
    addChild(pUiNode, g_uiZOrder);

    COCOUISYSTEM->resetSystem(pUiNode);
    m_pGameUI = cs::CocoPanel::create();
    COCOUISYSTEM->getCurScene()->addWidget(m_pGameUI);

    pWidget = COCOUISYSTEM->createWidgetFromFile_json("UIGame.json");
    m_pGameUI->addChild(pWidget);
#endif

    MainPlayerLogic::CreateSingleton();
    MainPlayerLogic::Singleton().Init(pWidget);

#ifndef DEBUG_NO_MONSTER
    // Init monster logic.
    m_pMonsterGroupLogic = new MonsterGroupLogic();
    m_pMonsterGroupLogic->autorelease();
    addChild(m_pMonsterGroupLogic, g_monsterZOder);
#endif

#ifndef DEBUG_NO_GENERAL
    // Init general logic.
    std::vector< EGeneralType > generalVec;
    generalVec.push_back(eGT_DiaoChan);
    generalVec.push_back(eGT_MaChao);
    m_pGeneralGroupLogic = new GeneralGroupLogic(generalVec, m_pGameUI);
    m_pGeneralGroupLogic->autorelease();
    addChild(m_pGeneralGroupLogic, g_generalZOrder);
#endif

#ifndef DEBUG_NO_GPE
    // Init Gpe logic.
    m_pGpeLogic = new GpeLogic();
    m_pGpeLogic->autorelease();
    addChild(m_pGpeLogic);
#endif

    //setTouchEnabled(true);

    m_bTouchEnabled = true;
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 2);
}

void GameLayer::onExit()
{
    COCOUISYSTEM->cleanUIScene();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);

    CCLayer::onExit();

    // Destroy singletons after base layer exit. (After all children exit)
    GameObjectManager::DestroySingleton();
    BuffManager::DestroySingleton();
    SkillManager::Singleton().Uninit();
    SkillManager::DestroySingleton();
    MainPlayerLogic::Singleton().Uninit();
    MainPlayerLogic::DestroySingleton();
}

void GameLayer::Update(float dt)
{
#ifndef DEBUG_NO_MONSTER
    m_pMonsterGroupLogic->StateUpdate(dt);
#endif

    m_pGeneralGroupLogic->Update(dt);

    GameObjectManager::Singleton().Update(dt);
    BuffManager::Singleton().Update(dt);
    SkillManager::Singleton().Update(dt);
}

//------------------------------------------------------------------
//
// GameScene
//
//------------------------------------------------------------------
void SceneGame::runThisTest()
{
    GameLayer* pLayer = GameLayer::create();
    addChild(pLayer, 0);
    CCDirector::sharedDirector()->replaceScene(this);
}