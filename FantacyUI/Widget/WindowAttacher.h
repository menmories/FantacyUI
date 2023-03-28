#ifndef __FANTACY_WINDOWATTACHER_H__
#define __FANTACY_WINDOWATTACHER_H__

#include "Types.h"
#include "Render/Canvas.h"

#include "Widget.h"
#include <vector>

class FWindowAttacher
{
public:
	FWindowAttacher(u64 uWindowId);

	void AddWidget(FWidget* Widget);

	void OnPaint(FCanvas* Canvas);

	void OnMouseMove(const FPoint& MousePoint);

	void OnMouseEnter(const FPoint& MousePoint);

	void OnMouseLeave();

	virtual void OnMouseButtonDown(u32 MouseButton);

	virtual void OnMouseButtonUp(u32 MouseButton);

	bool AttachWindowsMessage(u32 uMsg, WPARAM wParam, LPARAM lParam);

	FWidget* FindEnterWidget(const FPoint& MousePoint);
	
	void TrackingMouse();
private:
	FWidget* FocusWidget;
	FWidget* MouseEnterWidget;
	std::vector<FWidget*> WidgetQueue;
	bool bMouseTracking;
	HWND mHwnd;
};

#endif // !__FANTACY_WINDOWATTACHER_H__

