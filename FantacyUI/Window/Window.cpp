#include "pch.h"
#include "WindowBase.h"
#include "Window.h"
#include "Render/Canvas.h"
#include "Widget/WindowAttacher.h"
FWindow::FWindow()
	: mCanvas(nullptr)
	, mWindowAttacher(nullptr)
{
}

void FWindow::AddWidget(FWidget* Widget)
{
	mWindowAttacher->AddWidget(Widget);
}

LRESULT FWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_PAINT:
	{
		mCanvas->BeginDraw();
		mCanvas->Clear(FColor(0x0000ff));
		mWindowAttacher->OnPaint(mCanvas);
		OnPaint(mCanvas);
		mCanvas->EndDraw();
		break;
	}
	case WM_MOUSEMOVE:
	{
		FPoint MousePoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		OnMouseMove(MousePoint);
		break;
	}
	case WM_CHAR:
	{
		if (wParam > 0 && wParam < 0x10000)
		{
			//Add character
		}
		break;
	}
	case WM_SIZE:
	{
		FSize WindowSize(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		mCanvas->Resize(WindowSize);
		OnResize(WindowSize.Width, WindowSize.Height);
		break;
	}
	case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK:
	case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK:
	case WM_XBUTTONDOWN: case WM_XBUTTONDBLCLK:
	{
		break;
	}
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
	case WM_XBUTTONUP:
	{
		break;
	}
	case WM_CLOSE:
	{
		delete mWindowAttacher;
		delete mCanvas;
		Destroy();
		break;
	}
	case WM_DESTROY:
	{
		OnDestroy();
		break;
	}
	case WM_DEVICECHANGE:
	{
		break;
	}
	case WM_CREATE:
	{
		mCanvas = new FCanvas();
		mCanvas->Init(this->GetWindowId());
		mWindowAttacher = new FWindowAttacher();
		ConstructUI();
		break;
	}
	default:
	{
		return ::DefWindowProc((HWND)GetWindowId(), uMsg, wParam, lParam);
	}
	}
	return FALSE;
}

void FWindow::OnPaint(FCanvas* Canvas)
{
}

void FWindow::OnResize(s32 Width, s32 Height)
{

}

void FWindow::OnMouseMove(const FPoint& MousePoint)
{
}

void FWindow::OnDestroy()
{
	::PostQuitMessage(0);
}
