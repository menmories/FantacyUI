#include "pch.h"
#include "WindowAttacher.h"

FWindowAttacher::FWindowAttacher()
{
}

void FWindowAttacher::AddWidget(FWidget* Widget)
{
	WidgetRenderQueue.push_back(Widget);
}

void FWindowAttacher::OnPaint(FCanvas* Canvas)
{
	for (auto iter = WidgetRenderQueue.begin(); iter != WidgetRenderQueue.end(); iter++)
	{
		(*iter)->OnPaint(Canvas);
	}
}

bool FWindowAttacher::AttachWindowsMessage(u32 uMsg, WPARAM wParam, LPARAM lParam)
{
	return false;
}
