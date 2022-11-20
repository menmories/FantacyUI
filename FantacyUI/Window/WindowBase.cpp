#include "pch.h"
#include "WindowBase.h"
#include "Base/Application.h"
#include "Base/Geometry.h"

FWindowBase::FWindowBase()
	: mWindowId(0)
{
}

void FWindowBase::CenterScreen()
{
	RECT rcWindow;
	RECT rcDesktop;
	FPoint Pos;
	::GetWindowRect((HWND)GetWindowId(), &rcWindow);
	::SystemParametersInfo(SPI_GETWORKAREA, NULL, &rcDesktop, NULL);
	int width = rcWindow.right - rcWindow.left;
	int height = rcWindow.bottom - rcWindow.top;

	int desktopWidth = rcDesktop.right - rcDesktop.left;
	int desktopHeight = rcDesktop.bottom - rcDesktop.top;
	Pos.X = (desktopWidth - width) / 2;
	Pos.Y = (desktopHeight - height) / 2;
	SetPos(Pos.X, Pos.Y);
}

u64 FWindowBase::GetWindowId() const
{
	return mWindowId;
}

void FWindowBase::SetPos(s32 X, s32 Y)
{
	::SetWindowPos((HWND)mWindowId, HWND_TOP, X, Y, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER);
}

void FWindowBase::SetSize(s32 Width, s32 Height)
{
	::SetWindowPos((HWND)mWindowId, HWND_TOP, 0, 0, Width, Height, SWP_NOMOVE | SWP_NOOWNERZORDER);
}

void FWindowBase::Show()
{
	::ShowWindow((HWND)mWindowId, SW_SHOWNORMAL);
}

void FWindowBase::ShowHide()
{
	::ShowWindow((HWND)mWindowId, SW_HIDE);
}

void FWindowBase::ShowMinimized()
{
	::ShowWindow((HWND)mWindowId, SW_MINIMIZE);
}

void FWindowBase::ShowMaximized()
{
	::ShowWindow((HWND)mWindowId, SW_MAXIMIZE);
}

s32 FWindowBase::ShowModel()
{
	HWND hParent = ::GetParent((HWND)mWindowId);
	s32 result = 0;
	if (hParent)
	{
		::EnableWindow(hParent, FALSE);
	}
	result = FApplication::Exec();
	return result;
}

void FWindowBase::Destroy()
{
	::DestroyWindow((HWND)mWindowId);
}

void FWindowBase::SetupUI()
{
	Create();
	CenterScreen();
}

LPCTSTR FWindowBase::GetClassName() const
{
    return TEXT("FANTACY_WINDOW");
}

LRESULT FWindowBase::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		return ::DefWindowProc((HWND)GetWindowId(), uMsg, wParam, lParam);
	}
	default:
	{
		return ::DefWindowProc((HWND)GetWindowId(), uMsg, wParam, lParam);
	}
	}
	return FALSE;
}

LRESULT FWindowBase::__WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lResult = 0;
	bool bHanded = true;
	FWindowBase* pThis = NULL;
	if (uMsg == WM_NCCREATE) {
		LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
		pThis = static_cast<FWindowBase*>(lpcs->lpCreateParams);
		pThis->mWindowId = (s64)hWnd;
		::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LPARAM>(pThis));
	}
	else {
		pThis = reinterpret_cast<FWindowBase*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
	}
	if (pThis)
	{
		return pThis->HandleMessage(uMsg, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}

bool FWindowBase::__RegisterWindowClass()
{
	WNDCLASS wc = { 0 };
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.lpfnWndProc = (WNDPROC)FWindowBase::__WndProc;
	wc.hInstance = (HINSTANCE)::GetModuleHandle(nullptr);
	wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = this->GetClassName();
	ATOM ret = ::RegisterClass(&wc);
	assert(ret != NULL || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS);
	return ret != NULL || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS;
}

bool FWindowBase::Create(const LPCTSTR caption, int x, int y, int width, int height, IWindow* parent)
{
	if (!__RegisterWindowClass())
	{
		return NULL;
	}
	HWND hParent = parent ? (HWND)parent->GetWindowId() : NULL;
	DWORD dwExStyle = WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_CLIENTEDGE | WS_EX_APPWINDOW;
	DWORD dwStyle = WS_OVERLAPPEDWINDOW;
	RECT rcWindow;
	rcWindow.left = x;
	rcWindow.top = y;
	rcWindow.right = x + width;
	rcWindow.bottom = y + height;
	::AdjustWindowRectEx(&rcWindow, dwStyle, FALSE, dwExStyle);
	mWindowId = (u64)::CreateWindowEx(dwExStyle, GetClassName(), caption,
		dwStyle, rcWindow.left, rcWindow.top, rcWindow.right - rcWindow.left, rcWindow.bottom - rcWindow.top,
		hParent, NULL, (HINSTANCE)::GetModuleHandle(nullptr), reinterpret_cast<void*>(this));
	return mWindowId ? true : false;
}
