#ifndef __CCANVAS_H__
#define __CCANVAS_H__


#include "PlatformDef.h"
#include "Window/CWindow.h"
#include "CPixmap.h"

class CWindow;
class CCanvas
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

	CCanvas operator=(const CCanvas& other) = delete;
private:
	HDC m_hdc;
	HBITMAP m_hBitmap;
	HGDIOBJ m_gdiObj;
	s32 m_width, m_height;
};




#endif  //__CCANVAS_H__
