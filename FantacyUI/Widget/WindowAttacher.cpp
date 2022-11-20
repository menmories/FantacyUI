#include "pch.h"
#include "WindowAttacher.h"

FWindowAttacher::FWindowAttacher()
	: MouseEnterWidget(nullptr)
	, FocusWidget(nullptr)
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
	for (auto iter = WidgetQueue.rbegin(); iter != WidgetQueue.rend(); iter++)
	{
		FWidget* Widget = (*iter)->FindPointInWidget(MousePoint);
		if (Widget)
		{
			if (MouseEnterWidget)
			{
				MouseEnterWidget->OnMouseLeave();
			}
			MouseEnterWidget = Widget;
			MouseEnterWidget->OnMouseEnter();
		}
	}
}

void FWindowAttacher::OnMouseButtonDown(u32 MouseButton)
{
	if (MouseEnterWidget)
	{
		MouseEnterWidget->OnMouseButtonDown(MouseButton);
	}
}

void FWindowAttacher::OnMouseButtonUp(u32 MouseButton)
{
	if (MouseEnterWidget)
	{
		MouseEnterWidget->OnMouseButtonUp(MouseButton);
	}
}

bool FWindowAttacher::AttachWindowsMessage(u32 uMsg, WPARAM wParam, LPARAM lParam)
{
	return false;
}
