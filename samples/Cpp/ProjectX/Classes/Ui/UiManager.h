#ifndef  _APP_UIManager_H_
#define  _APP_UIManager_H_

USING_NS_CC_EXT;

class UiManager
{
    DECLARE_SINGLETON(UiManager);

public:
    void Init(CCNode* pNode);
    void Update(float dt);

    UIWidget* GetChildByName(const char *name);
    void AddChildWidget(UIWidget* child);
    bool IsInUi() const;
    void SetIsInUi(bool isInUi);

private:
    UILayer* m_pUiLayer;

    bool m_isInUi;

};

#endif // _APP_UIManager_H_