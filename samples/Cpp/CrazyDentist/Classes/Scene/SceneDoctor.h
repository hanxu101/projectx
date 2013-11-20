#ifndef _DOCTOR_SCENE_H_
#define _DOCTOR_SCENE_H_

#include "SceneBase.h"

USING_NS_CC;
USING_NS_CC_EXT;

class DoctorLayer: public CCLayer
{
public:
    DoctorLayer(void);
    ~DoctorLayer(void);

    virtual std::string title();
    virtual void onEnter();

private:
    void BottonGoClicked( CCObject* pSender );
    void onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response);

private:
    std::string m_mapTextureFormat;
};

class SceneDoctor : public SceneBase
{
public:
    virtual void runThisTest();
};

#endif
