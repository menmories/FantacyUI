#include "Core/XMPaintDevice.h"




#ifdef XMUI_USE_TGFX_BACKEND
#include "backend/tgfx/XMTgfx.h"
#elif defined XMUI_USE_BLEND2D_BACKEND
#include "backend/blend2d/XMBlend2d.h"
#elif defined XMUI_USE_DIRECT2D_BACKEND
#include "backend/direct2d/XMDirect2D.h"
#endif

XMPainter* XMPaintDevice::s_current = nullptr;


XMPainter* XMPaintDevice::newPainter(XMWindow* owner)
{
#ifdef XMUI_USE_TGFX_BACKEND
	XMTgfxPainter* painter = new XMTgfxPainter(owner);
#elif defined XMUI_USE_BLEND2D_BACKEND
	XMBlend2dPainter* painter = new XMBlend2dPainter(owner);
#elif defined XMUI_USE_DIRECT2D_BACKEND
	XMDirect2D* painter = new XMDirect2D(owner);
#endif
	return painter;
}




bool XMPaintDevice::init()
{
	return InitDirect2D();
}

void XMPaintDevice::destroy()
{
	DestroyDirect2D();
}

void XMPaintDevice::makeCurrent(XMPainter* painter)
{
	s_current = painter;
}

XMPainter* XMPaintDevice::current()
{
	return s_current;
}
