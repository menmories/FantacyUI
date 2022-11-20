#include "pch.h"
#include "Base/Application.h"
#include "Render/Canvas.h"
static bool s_bRealTimeDispatch = false;
bool FApplication::Init(bool bRealTimeDispatch)
{
    s_bRealTimeDispatch = bRealTimeDispatch;
    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
    if (FAILED(CoInitialize(NULL)))
    {
        return false;
    }

    FDirect2DContext* Context = FDirect2DContext::Get();
    if (Context->InitContext() != 0)
    {
        return false;
    }
    return true;
}

s32 FApplication::Exec()
{
    MSG msg = { 0 };
    if (s_bRealTimeDispatch)
    {
        while (true)
        {
            if (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }
    else
    {
        while (::GetMessage(&msg, nullptr, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    FDirect2DContext::Get()->DestroyContext();
    CoUninitialize();
    return (s32)msg.wParam;
}
