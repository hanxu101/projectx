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
    void Update(float dt);

    CocoWidget* GetChildByName(const char *name);
    void AddChildWidget(CocoWidget* child);
    bool IsInUi() const;
    void SetIsInUi(bool isInUi);

private:
    CocoPanel*  m_pPanel;
    CocoWidget* m_pWidget;
    bool m_isInUi;

};

#endif // _APP_UIManager_H_