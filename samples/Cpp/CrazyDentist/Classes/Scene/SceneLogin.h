#ifndef _LOGIN_SCENE_H_
#define _LOGIN_SCENE_H_

#include "SceneBase.h"

USING_NS_CC;

class LoginLayer: public CCLayer
{
protected:

public:
    LoginLayer(void);
    ~LoginLayer(void);

    virtual std::string title();
    virtual void onEnter();

private:
    void menuCallback(CCObject * pSender);
};

class SceneLogin : public SceneBase
{
public:
    virtual void runThisTest();
};

#endif
