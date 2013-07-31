#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "SceneBase.h"

USING_NS_CC;

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
};

class SceneGame : public SceneBase
{
public:
    virtual void runThisTest();
};

#endif
