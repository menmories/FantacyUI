#include "XMApplication.h"
#include <Gdiplus.h>
#include <Windows.h>
#include <windowsx.h>
#include <cstdio>

#include "Core/XMPaintDevice.h"
#include "Private/XMDelegateQueue.h"



#define XMUI_WM_UPDATE (WM_USER+20000)
#define XMUI_MSG_BLOCK		1
#define XMUI_MSG_UNBLOCK	2

u32 g_uiThreadId = 0;

XMDelegateQueue g_delegate_queue;

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
	g_uiThreadId = GetCurrentThreadId();
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

void threadEventHandle(int type, void* args)
{
	
}

int XMApplication::sendEvent(int type, void* args, XMEventCb cb)
{
	XMDelegateQueueData queueData;
	queueData.type = type;
	queueData.args = args;
	queueData.m_func = cb;
	g_delegate_queue.addToBegin(queueData);
	return PostThreadMessage(g_uiThreadId, XMUI_WM_UPDATE, XMUI_MSG_BLOCK, 0);
}

int XMApplication::postEvent(int type, void* args, XMEventCb cb)
{
	XMDelegateQueueData queueData;
	queueData.type = type;
	queueData.args = args;
	queueData.m_func = cb;
	g_delegate_queue.addFunc(queueData);
	return PostThreadMessage(g_uiThreadId, XMUI_WM_UPDATE, XMUI_MSG_UNBLOCK, 0);
}

void XMApplication::enableHighDPIScaling()
{
#if _MSC_VER <= 1900
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
		/*if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			printf("has message\n");
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (g_delegate_queue.hasEvent())
		{
			g_delegate_queue.callAndRemoveBlock();
		}*/

        if (!msg.hwnd && msg.message == XMUI_WM_UPDATE)
        {
            //printf("received a no window event.\n");
            while (g_delegate_queue.hasEvent())
            {
				switch (msg.wParam)
				{
				case XMUI_MSG_BLOCK:
				{
					g_delegate_queue.callAndRemoveBlock();
					break;
				}
				case XMUI_MSG_UNBLOCK:
				{
					g_delegate_queue.callAndRemove();
					break;
				}
				}
            }
            continue;
        }
		TranslateMessage(&msg);
		DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

