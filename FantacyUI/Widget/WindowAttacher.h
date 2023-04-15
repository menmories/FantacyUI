#ifndef __FANTACY_WINDOWATTACHER_H__
#define __FANTACY_WINDOWATTACHER_H__

#include "Types.h"
#include "Render/Canvas.h"

#include "Widget.h"
#include <vector>
#include "Base/Mouse.h"

class FWindowAttacher
{
public:
	FWindowAttacher(u64 uWindowId);

	void AddWidget(FWidget* Widget);

	void OnPaint(FCanvas* Canvas);

	void OnMouseMove(const FPoint& MousePoint);

	void OnMouseEnter(const FPoint& MousePoint);

	void OnMouseLeave();

	virtual void OnMouseButtonDown(const FMouse& Mouse);

	virtual void OnMouseButtonUp(const FMouse& Mouse);

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

