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

	bool AttachWindowsMessage(u32 uMsg, WPARAM wParam, LPARAM lParam);

private:
	std::vector<FWidget*> WidgetRenderQueue;
};

#endif // !__FANTACY_WINDOWATTACHER_H__

