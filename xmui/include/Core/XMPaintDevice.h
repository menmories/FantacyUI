#ifndef XMUI_PAINT_DEVICE_H
#define XMUI_PAINT_DEVICE_H

#include "XMPlatformDef.h"
#include "XMPainter.h"
#include "Window/XMWindow.h"

class XMUI_API XMPaintDevice
{
public:
	static bool init();
	static void destroy();

	static void makeCurrent(XMPainter* painter);
	static XMPainter* current();

	static XMPainter* newPainter(XMWindow* owner);

private:
	static XMPainter* s_current;
};

#endif  // XMUI_PAINT_DEVICE_H
