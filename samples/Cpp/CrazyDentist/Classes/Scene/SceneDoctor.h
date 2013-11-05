#ifndef _DOCTOR_SCENE_H_
#define _DOCTOR_SCENE_H_

#include "SceneBase.h"

USING_NS_CC;

class DoctorLayer: public CCLayer
{
public:
    DoctorLayer(void);
    ~DoctorLayer(void);

    virtual std::string title();
    virtual void onEnter();

private:
    void BottonGoClicked( CCObject* pSender );

};

class SceneDoctor : public SceneBase
{
public:
    virtual void runThisTest();
};

#endif
