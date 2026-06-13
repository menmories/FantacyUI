#ifndef XMAPPLICATION_H
#define XMAPPLICATION_H

#include "XMPlatformDef.h"

class XMUI_API XMApplication final
{
public:
    XMApplication();
    XMApplication(int argc, char** argv);
    ~XMApplication();

    static int sendEvent(u32 uMsg, void* args);
    static int postEvent(u32 uMsg, void* args);

    static void quit(s32 code = 0);

    static void exit(s32 code = 0);

    static void enableHighDPIScaling();

    //获取主显示器的分辨率
    static void getFirstScreenSize(s32& width, s32& height);
    //获取当前显示器的分辨率
    static void getScreenSize(s32& width, s32& height);

    int run();

private:
    bool m_success;
};



#endif  // !XMAPPLICATION_H

