#ifndef _LOGIN_SCENE_H_
#define _LOGIN_SCENE_H_

#include "SceneBase.h"
#include "Ui/TextFieldTTFLayer/TextFieldTTFLayer.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

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
    void BottonYesClicked( CCObject* pSender );
    void BottonNoClicked( CCObject* pSender );

    void onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response);

};

class SceneLogin : public SceneBase
{
public:
    virtual void runThisTest();
};

#endif
