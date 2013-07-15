#ifndef  _APP_UIManager_H_
#define  _APP_UIManager_H_

#include "CocoPanel.h"
#include "CocoWidget.h"
#include "UISystem.h"
#include "CocoLabelAtlas.h"
#include "CocoLoadingBar.h"
#include "CocoButton.h"

using namespace cs;

class UiManager
{
    DECLARE_SINGLETON(UiManager);

public:
    void Init(CCNode* pNode);
    CocoWidget* GetChildByName(const char *name);
    void AddChildWidget(CocoWidget* child);

private:
    CocoPanel*  m_pPanel;
    CocoWidget* m_pWidget;

};

#endif // _APP_UIManager_H_