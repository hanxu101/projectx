#include "main.h"
#include "../Classes/AppDelegate.h"
#include "../Classes/AppMacros.h"
#include "CCEGLView.h"

USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
#ifdef DEBUG_NO_TITLE
    eglView->setViewName(" ");
#else
    eglView->setViewName("ProjectX");
#endif

    // Simply swap width and height for Win32. For other platform, see: http://www.cocos2d-x.org/boards/6/topics/14072
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    eglView->setFrameSize(1536, 2048);
#else
    eglView->setFrameSize(2048, 1536);
#endif

    // The resolution of ipad3 is very large. In general, PC's resolution is smaller than it.
    // So we need to invoke 'setFrameZoomFactor'(only valid on desktop(win32, mac, linux)) to make the window smaller.
    eglView->setFrameZoomFactor(0.4f);
    return CCApplication::sharedApplication()->run();
}
