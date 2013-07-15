#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "SceneBase.h"

USING_NS_CC;

class MonsterGroupLogic;
class GeneralGroupLogic;
class GpeLogic;

namespace cs{class CocoPanel;}

class GameLayer: public CCLayer
{
public:
    GameLayer(void);
    ~GameLayer(void);

    virtual std::string title();
    virtual void onEnter();
    virtual void onExit();

    CREATE_FUNC(GameLayer)

private:
    void Update(float dt);  

private:
    MonsterGroupLogic*  m_pMonsterGroupLogic;
    GeneralGroupLogic*  m_pGeneralGroupLogic;
    GpeLogic*           m_pGpeLogic;
};

class SceneGame : public SceneBase
{
public:
    virtual void runThisTest();
};

#endif
