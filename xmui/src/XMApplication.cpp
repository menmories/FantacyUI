#include "XMApplication.h"
#include <Gdiplus.h>
#include <Windows.h>
#include <windowsx.h>
#include <cstdio>

#include "Core/XMPaintDevice.h"


#define FANTACY_UPDATE_MSG (WM_USER+20000)

XMApplication::XMApplication()
{
    char* argv = new char[2048];
    GetModuleFileNameA(GetModuleHandle(nullptr), argv, 2048);
    XMApplication(1, &argv);
    delete[] argv;
}

XMApplication::XMApplication(int argc, char** argv)
	: m_success(false)
{
    if (FAILED(CoInitialize(nullptr)))
    {
        fprintf(stderr, "error:CoInitialize failed!\n");
        exit(-1);
    }
    if (!XMPaintDevice::init())
    {
        fprintf(stderr, "error:PaintDevice init failed!\n");
        exit(-1);
    }
}

XMApplication::~XMApplication()
{
    XMPaintDevice::destroy();
    CoUninitialize();
}

int XMApplication::sendEvent(u32 uMsg, void* args)
{
	//return PostThreadMessage(GetCurrentThread())
    return 0;
}

int XMApplication::postEvent(u32 uMsg, void* args)
{
    return 0;
}

void XMApplication::enableHighDPIScaling()
{
#if _MSC_VER < 1900
    SetProcessDPIAware();
#else
    SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
#endif
}

void XMApplication::quit(s32 code)
{
    ::PostQuitMessage(code);
}

void XMApplication::exit(s32 code)
{
    ::exit(code);
}

void XMApplication::getFirstScreenSize(s32& width, s32& height)
{
    HMONITOR hMonitor = MonitorFromWindow(nullptr, MONITOR_DEFAULTTOPRIMARY);
    MONITORINFO monitorInfo;
    monitorInfo.cbSize = sizeof(MONITORINFO);
    if (GetMonitorInfo(hMonitor, &monitorInfo))
    {
        width = monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left;
        height = monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top;
    }
}

void XMApplication::getScreenSize(s32& width, s32& height)
{
    width = GetSystemMetrics(SM_CXSCREEN);
    height = GetSystemMetrics(SM_CYSCREEN);
}

int XMApplication::run()
{
    MSG msg = { 0 };
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!msg.hwnd && msg.message == FANTACY_UPDATE_MSG)
        {
            printf("received a no window event.\n");
            continue;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

