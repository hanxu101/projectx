#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "cocos2d.h"

USING_NS_CC;

#define LINE_SPACE          40

enum
{
    MainMenu_Game = 0,
    MainMenu_Credits,
    MainMenu_Option,

	MainMenu_Count,
};

const std::string g_MainMenuNames[MainMenu_Count] = {
"Game",
"Credits",
"Option"
};

class SceneManager : public cocos2d::CCLayer
{

public:
	SceneManager();
    virtual void onEnter();

	void menuCallback(CCObject * pSender);
    void closeCallback(CCObject * pSender);

private:
    CCPoint m_tBeginPos;
    CCMenu* m_pItemMenu;
};

#endif // __SCENE_MANAGER_H__
