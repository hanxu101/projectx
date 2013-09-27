#ifndef _LOGIN_SCENE_H_
#define _LOGIN_SCENE_H_

#include "SceneBase.h"
#include "Ui/TextFieldTTFLayer/TextFieldTTFLayer.h"

USING_NS_CC;

class LoginLayer: public TextFieldTTFLayer
{
protected:

public:
    LoginLayer(void);
    ~LoginLayer(void);

    virtual std::string title();
    virtual void onEnter();

private:
    void BottonOKClicked( CCObject* pSender );
};

class SceneLogin : public SceneBase
{
public:
    virtual void runThisTest();
};

#endif
