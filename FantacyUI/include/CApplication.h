#ifndef CAPPLICATION_H
#define CAPPLICATION_H

#include "PlatformDef.h"
#include <Utils/CEvent.h>

class FANTACY_API CApplication final
{
public:
    CApplication();
    CApplication(int argc, char** argv);
    ~CApplication();

    int sendEvent(CEvent* e);
    int postEvent(CEvent* e);

    static void quit(s32 code = 0);

    //获取主显示器的分辨率
    static void getFirstScreenSize(s32& width, s32& height);
    //获取当前显示器的分辨率
    static void getScreenSize(s32& width, s32& height);

    int run();
};



#endif  // !CAPPLICATION_H

