#ifndef XMUI_PAINTER_H
#define XMUI_PAINTER_H

#include "XMGeometry.h"
#include "XMBitmap.h"
#include "XMBrush.h"
#include "XMFont.h"
#include "XMPen.h"

class XMPainter
{
public:
	virtual void resize(int width, int height) = 0;
	virtual void beginDraw() = 0;
	virtual void endDraw() = 0;
	virtual void release() = 0;

	virtual void drawImage(const XMImage& image, int x, int y, int width, int height, float opcity = 1.0f) = 0;

	virtual void fillRect(const XMRect& rect, const XMBrush& brush) = 0;

	virtual void drawRect(const XMRect& rect, const XMBrush& brush, const XMPen& pen) = 0;

	virtual void drawText(const XMString& text, const XMRect& rect, const XMBrush& brush, const XMFont& font) = 0;

	virtual void* renderData() = 0;
};


#endif  // XMUI_PAINTER_H