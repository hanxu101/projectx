#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "cocos2d.h"

USING_NS_CC;

#define LINE_SPACE          40

enum
{
    MainMenu_A = 0,
    MainMenu_B,
    MainMenu_C,
	MainMenu_D,

	MainMenu_Count,
};

const std::string g_MainMenuNames[MainMenu_Count] = {
"A",
"B",
"C",
"D"
};

class StartLayer : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(StartLayer);
};

class SceneManager : public cocos2d::CCLayer
{

public:
	SceneManager();

	void menuCallback(CCObject * pSender);
    void closeCallback(CCObject * pSender);

private:
    CCPoint m_tBeginPos;
    CCMenu* m_pItemMenu;
};

#endif // __StartLayer_SCENE_H__
