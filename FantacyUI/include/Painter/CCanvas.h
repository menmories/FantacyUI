#ifndef __CCANVAS_H__
#define __CCANVAS_H__


#include "PlatformDef.h"
#include "CPixmap.h"

class CWindow;
class CPainter;
class FANTACY_API CCanvas
{
public:
	CCanvas();
	CCanvas(HDC hdc, int width, int height);
	CCanvas(CWindow* window);
	CCanvas(CWindow* window, int width, int height);
	~CCanvas();

	FANTACY_INLINE HDC getPaintDC()
	{
		return m_hdc;
	}

	void getBitmap(CPixmap* pixmap)
	{
		pixmap->setBitmap(m_hBitmap);
	}

	FANTACY_INLINE s32 width()const
	{
		return m_width;
	}

	FANTACY_INLINE s32 height()const
	{
		return m_height;
	}

	CCanvas operator=(const CCanvas& other) = delete;
private:
	HDC m_hdc;
	HBITMAP m_hBitmap;
	HGDIOBJ m_gdiObj;
	s32 m_width, m_height;
};




#endif  //__CCANVAS_H__
