#include "CApplication.h"
#include <Gdiplus.h>
#include <Windows.h>
#include <windowsx.h>
#include <cstdio>

#define COSTOM_MSG (WM_USER+20000)

Gdiplus::GdiplusStartupInput gdiplusStartupInput = 0;
ULONG_PTR m_gdiplusToken = 0;

CApplication::CApplication()
{
    char* argv = new char[2048];
    GetModuleFileNameA(GetModuleHandle(nullptr), argv, 2048);
    CApplication(1, &argv);
    delete[] argv;
}

CApplication::CApplication(int argc, char** argv)
{
    Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, nullptr);
}

CApplication::~CApplication()
{
    Gdiplus::GdiplusShutdown(m_gdiplusToken);
}

int CApplication::sendEvent(CEvent* e)
{
    return 0;
}

int CApplication::postEvent(CEvent* e)
{
    return 0;
}

void CApplication::quit(s32 code)
{
    ::PostQuitMessage(code);
}

void CApplication::getFirstScreenSize(s32& width, s32& height)
{
    HMONITOR hMonitor = MonitorFromWindow(NULL, MONITOR_DEFAULTTOPRIMARY);
    MONITORINFO monitorInfo;
    monitorInfo.cbSize = sizeof(MONITORINFO);
    if (GetMonitorInfo(hMonitor, &monitorInfo))
    {
        width = monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left;
        height = monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top;
    }
}

void CApplication::getScreenSize(s32& width, s32& height)
{
    width = GetSystemMetrics(SM_CXSCREEN);
    height = GetSystemMetrics(SM_CYSCREEN);
}

int CApplication::run()
{
    MSG msg = { 0 };
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!msg.hwnd && msg.message == COSTOM_MSG)
        {
            printf("received a no window event.\n");
            continue;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

