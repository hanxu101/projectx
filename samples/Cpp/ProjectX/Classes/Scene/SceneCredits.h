#ifndef _CREDITS_SCENE_H_
#define _CREDITS_SCENE_H_

#include "SceneBase.h"

USING_NS_CC;

class CreditsLayer: public CCLayer
{
protected:

public:
    CreditsLayer(void);
    ~CreditsLayer(void);

    virtual std::string title();
    virtual void onEnter();
};

class SceneCredits : public SceneBase
{
public:
    virtual void runThisTest();
};

#endif
