#include "pch.h"
#include "WindowAttacher.h"
#include <CommCtrl.h>
FWindowAttacher::FWindowAttacher(u64 uWindowId)
	: MouseEnterWidget(nullptr)
	, FocusWidget(nullptr)
	, bMouseTracking(false)
	, mHwnd((HWND)uWindowId)
{
}

void FWindowAttacher::AddWidget(FWidget* Widget)
{
	WidgetQueue.push_back(Widget);
}

void FWindowAttacher::OnPaint(FCanvas* Canvas)
{
	for (auto iter = WidgetQueue.begin(); iter != WidgetQueue.end(); iter++)
	{
		(*iter)->OnPaint(Canvas);
	}
}

void FWindowAttacher::OnMouseMove(const FPoint& MousePoint)
{
	if (!bMouseTracking)
	{
		TrackingMouse();
		bMouseTracking = true;
	}

	FWidget* Widget = FindEnterWidget(MousePoint);
	if (Widget)
	{
		if (MouseEnterWidget)
		{
			if (MouseEnterWidget != Widget)
			{
				MouseEnterWidget->OnMouseLeave();
				MouseEnterWidget = Widget;
				MouseEnterWidget->OnMouseEnter();
			}
		}
		else
		{
			MouseEnterWidget = Widget;
			MouseEnterWidget->OnMouseEnter();
		}
	}
	else
	{
		if (MouseEnterWidget)
		{
			MouseEnterWidget->OnMouseLeave();
			MouseEnterWidget = nullptr;
		}
	}
}

void FWindowAttacher::OnMouseEnter(const FPoint& MousePoint)
{
	bMouseTracking = false;
	MouseEnterWidget = FindEnterWidget(MousePoint);
	if (MouseEnterWidget)
	{
		MouseEnterWidget->OnMouseEnter();
		MouseEnterWidget->SetMouseEnter(true);
	}
}

void FWindowAttacher::OnMouseLeave()
{
	::SendMessage(mHwnd, WM_MOUSEMOVE, 0, (LPARAM)-1);
	bMouseTracking = false;
	if (MouseEnterWidget)
	{
		MouseEnterWidget->OnMouseLeave();
		MouseEnterWidget->SetMouseEnter(false);
		MouseEnterWidget = nullptr;
	}
}

void FWindowAttacher::OnMouseButtonDown(const FMouse& Mouse)
{
	if (MouseEnterWidget)
	{
		MouseEnterWidget->OnMouseButtonDown(Mouse);
	}
}

void FWindowAttacher::OnMouseButtonUp(const FMouse& Mouse)
{
	if (MouseEnterWidget)
	{

		/*FPoint pt(Mouse.X, Mouse.Y);
		MouseEnterWidget->ConvertMousePoint(pt, pt);
		if (MouseEnterWidget->PtInRegion(pt))
		{
			
		}*/
		MouseEnterWidget->OnMouseButtonUp(Mouse);
	}
}

bool FWindowAttacher::AttachWindowsMessage(u32 uMsg, WPARAM wParam, LPARAM lParam)
{
	return false;
}

FWidget* FWindowAttacher::FindEnterWidget(const FPoint& MousePoint)
{
	for (auto iter = WidgetQueue.rbegin(); iter != WidgetQueue.rend(); iter++)
	{
		if (!(*iter)->IsVisible())
		{
			continue;
		}
		FWidget* Widget = (*iter)->FindPointInWidget(MousePoint);
		if (Widget)
		{
			return Widget;
		}
	}
	return nullptr;
}

void FWindowAttacher::TrackingMouse()
{
	TRACKMOUSEEVENT tme = { 0 };
	tme.cbSize = sizeof(TRACKMOUSEEVENT);
	tme.dwFlags = TME_HOVER | TME_LEAVE;
	tme.hwndTrack = mHwnd;
	tme.dwHoverTime = 50; //= mHwnd == NULL ? 400UL : (DWORD) ::SendMessage(mHwnd, TTM_GETDELAYTIME, TTDT_INITIAL, 0L);
	TrackMouseEvent(&tme);
}


