#ifndef CPAINTERDEVICE_H
#define CPAINTERDEVICE_H


#include "PlatformDef.h"
#include "Window/CWindow.h"

class CWindow;
class CPainterDevice
{
public:
	CPainterDevice(CWindow* window);
	~CPainterDevice();

	void beginPaint();

	void endPaint();

	FANTACY_INLINE HDC winDC()
	{
		return m_hCompatibleDC;
	}
private:
	int m_width;
	int m_height;
	CWindow* m_window;
	PAINTSTRUCT m_ps;
	HDC m_hdc;
	HDC m_hCompatibleDC;
	HDC m_oldDC;
	HBITMAP m_hCompatibleBitmap;
	HBITMAP m_hOldBitmap;
};


#endif // CPAINTERDEVICE_H


