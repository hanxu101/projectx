#ifndef _HOME_SCENE_H_
#define _HOME_SCENE_H_

#include "SceneBase.h"

USING_NS_CC;

class HomeLayer: public CCLayer
{
protected:

public:
    HomeLayer(void);
    ~HomeLayer(void);

    virtual std::string title();
    virtual void onEnter();

private:
    void BottonGameClicked( CCObject* pSender );
    void BottonTartarClicked( CCObject* pSender );
    void BottonDoctorClicked( CCObject* pSender );

};

class SceneHome : public SceneBase
{
public:
    virtual void runThisTest();
};

#endif
