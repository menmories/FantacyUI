#ifndef __FANTACY_WINDOWATTACHER_H__
#define __FANTACY_WINDOWATTACHER_H__

#include "Types.h"
#include "Render/Canvas.h"

#include "Widget.h"
#include <vector>

class FWindowAttacher
{
public:
	FWindowAttacher();

	void AddWidget(FWidget* Widget);

	void OnPaint(FCanvas* Canvas);

	void OnMouseMove(const FPoint& MousePoint);

	virtual void OnMouseButtonDown(u32 MouseButton);

	virtual void OnMouseButtonUp(u32 MouseButton);

	bool AttachWindowsMessage(u32 uMsg, WPARAM wParam, LPARAM lParam);

private:
	FWidget* FocusWidget;
	FWidget* MouseEnterWidget;
	std::vector<FWidget*> WidgetQueue;
};

#endif // !__FANTACY_WINDOWATTACHER_H__

