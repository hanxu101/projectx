#ifndef _TEST_BASIC_H_
#define _TEST_BASIC_H_

USING_NS_CC;
using namespace std;

class SceneBase : public CCScene
{
public: 
    SceneBase(bool bPortrait = false);
    virtual void onEnter();

    virtual void runThisTest() = 0;

    // The CallBack for back to the main menu scene
    virtual void MainMenuCallback(CCObject* pSender);
};

typedef CCLayer* (*NEWTESTFUNC)();
#define TESTLAYER_CREATE_FUNC(className) \
static CCLayer* create##className() \
{ return new className(); }

#define CF(className) create##className

#endif
