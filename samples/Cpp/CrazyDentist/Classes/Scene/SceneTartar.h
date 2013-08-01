#ifndef _TARTAR_SCENE_H_
#define _TARTAR_SCENE_H_

#include "SceneBase.h"

USING_NS_CC;

class TartarLayer: public CCLayer
{
protected:

public:
    TartarLayer(void);
    ~TartarLayer(void);

    virtual std::string title();
    virtual void onEnter();
};

class SceneTartar : public SceneBase
{
public:
    virtual void runThisTest();
};

#endif
