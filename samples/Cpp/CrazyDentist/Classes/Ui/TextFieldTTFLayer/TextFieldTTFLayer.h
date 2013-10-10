#ifndef __KeyboardNotificationLayer_H__
#define __KeyboardNotificationLayer_H__


//////////////////////////////////////////////////////////////////////////
// KeyboardNotificationLayer for test IME keyboard notification.
//////////////////////////////////////////////////////////////////////////

class KeyboardNotificationLayer : public CCLayer, public CCIMEDelegate
{
public:
    KeyboardNotificationLayer();

    virtual void onClickTrackNode(bool bClicked) = 0;

    virtual void registerWithTouchDispatcher();
    virtual void keyboardWillShow(CCIMEKeyboardNotificationInfo& info);

    // CCLayer
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

protected:
    CCNode * m_pTrackNode;
    CCPoint  m_beginPos;
};


//////////////////////////////////////////////////////////////////////////
// TextFieldTTFLayer
//////////////////////////////////////////////////////////////////////////

class TextFieldTTFLayer : public KeyboardNotificationLayer, public CCTextFieldDelegate
{
public:
    void callbackRemoveNodeWhenDidAction(CCNode * pNode);

    // KeyboardNotificationLayer
    virtual void onClickTrackNode(bool bClicked);

    // CCLayer
    virtual void onEnter();
    virtual void onExit();

    // CCTextFieldDelegate
    virtual bool onTextFieldAttachWithIME(CCTextFieldTTF * pSender);
    virtual bool onTextFieldDetachWithIME(CCTextFieldTTF * pSender);
    virtual bool onTextFieldInsertText(CCTextFieldTTF * pSender, const char * text, int nLen);
    virtual bool onTextFieldDeleteBackward(CCTextFieldTTF * pSender, const char * delText, int nLen);
    virtual bool onDraw(CCTextFieldTTF * pSender);

    void EnableTextField(bool enable);

protected:
    CCTextFieldTTF *    m_pTextField;
    CCAction *          m_pTextFieldAction;
    bool                m_bAction;
    int                 m_nCharLimit;       // the textfield max char limit

};


#endif    // __KeyboardNotificationLayer_H__
