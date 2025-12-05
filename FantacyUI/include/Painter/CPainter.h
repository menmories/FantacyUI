#ifndef CPAINTER_H
#define CPAINTER_H

#include "Painter/CPixmap.h"
#include "Window/CWindow.h"
#include "CGeometry.h"
#include "CPaintTool.h"
#include "CCanvas.h"

class CWindow;
class CCanvas;

struct CPainterData
{
public:
	CBrush brush;
	CFont font;
};

class FANTACY_API CPainter
{
public:
    CPainter();
	CPainter(CWindow* window);
	~CPainter();

	void clear(float r, float g, float b);

    static CPainter* fromPixmap(CPixmap* bitmap);

	FANTACY_INLINE void setBrush(const CBrush& brush)
	{
		m_brush = brush;
	}
	virtual void drawLine(int beginX, int beginY, int endX, int endY, float width);


    virtual void drawPixmap(CPixmap& pixmap, const CRect& rect);
	virtual void drawPixmap(CPixmap& pixmap, s32 x, s32 y, s32 width, s32 height);
    
	virtual void drawPixmapAlphaBlend(CPixmap& pixmap, s32 x, s32 y, s32 width, s32 height, u8 alpha);

	FANTACY_INLINE void setFont(const CFont& font)
	{
		m_font = font;
	}

	virtual void drawText(const FaString& text, int x, int y);
    virtual void drawText(const FaString& text, const CRect& rect);
    virtual void drawText(const FaString& text, const CRect& rect, const CBrush& brush);

    void fillRoundedRect(const CRect& rect, s32 radiusX, s32 radiusY);
	void fillRoundedRect(s32 x, s32 y, s32 width, s32 height, s32 radiusX, s32 radiusY);

    void drawRoundedRect(const CRect& rect, s32 radiusX, s32 radiusY, float lineWidth);
	void drawRoundedRect(s32 x, s32 y, s32 width, s32 height, s32 radiusX, s32 radiusY, float lineWidth);

    void fillRect(const CRect& rect);
	void fillRect(s32 x, s32 y, s32 width, s32 height);

	void drawRect(s32 x, s32 y, s32 width, s32 height, float lineWidth);
private:
	CCanvas m_canvas;
	CPainterData* m_painterData;
	CPainterData* m_painterDataBuf;
	HDC m_hdc;
	CFont m_font;
	CBrush m_brush;
    HBITMAP m_bitmap;
};


#endif // !CPAINTER_H
