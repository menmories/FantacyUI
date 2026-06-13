#ifndef XMUI_BLEND2D_H
#define XMUI_BLEND2D_H

#ifdef XMUI_USE_BLEND2D_BACKEND


#include <blend2d/blend2d.h>
#include <Core/XMPainter.h>
#include "Window/XMWindow.h"

class XMBlend2dPainter : public XMPainter
{
public:
	XMBlend2dPainter(XMWindow* window);
	virtual void beginDraw() override;
	virtual void endDraw() override;
	virtual void release() override;
	virtual void drawBitmap(XMBitmap* bitmap, int x, int y, int width, int height)override;

	XMUI_INLINE HDC getDC() const { return m_hdc; }

private:
	XMWindow* m_window;
	int m_width;
	int m_height;
	PAINTSTRUCT m_ps;
	HDC m_hdc;
	HDC m_hCompatibleDC;
	HDC m_oldDC;
	HBITMAP m_hCompatibleBitmap;
	HBITMAP m_hOldBitmap;
	void* m_pixelData;
	HBITMAP m_hPixelBitmap;
	BLContext m_blContext;

	BLImage m_testImage;
};

#endif	//XMUI_USE_BLEND2D_BACKEND


#endif	// XMUI_BLEND2D_H

