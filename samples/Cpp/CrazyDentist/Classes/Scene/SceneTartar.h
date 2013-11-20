#ifndef _TARTAR_SCENE_H_
#define _TARTAR_SCENE_H_

#include "SceneBase.h"

USING_NS_CC;
USING_NS_CC_EXT;

class TartarLayer: public CCLayer
{
public:
    TartarLayer(void);
    ~TartarLayer(void);

    virtual std::string title();
    virtual void onEnter();

private:
    void TextFieldInserted( CCObject* pSender );
    void BottonOKClicked( CCObject* pSender );
    void BottonFinishClicked( CCObject* pSender );    
    void BottonOrderClicked( CCObject* pSender );

    void onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response);

private:
    std::string m_textureFormat;
};

class SceneTartar : public SceneBase
{
public:
    virtual void runThisTest();
};

#endif
