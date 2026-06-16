#ifdef XMUI_USE_BLEND2D_BACKEND

#include "backend/blend2d/XMBlend2d.h"

HBITMAP CreateARGBBitmap(HDC hdc, int width, int height, unsigned char* bits) {
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = width;
	bmi.bmiHeader.biHeight = -height;  // 负值表示自上而下的DIB
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = width * height * 4;

	// 准备位图文件头
	BITMAPFILEHEADER bmfHeader = { 0 };
	BITMAPINFOHEADER bi = { 0 };

	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = width;
	bi.biHeight = -height;
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = width * height * 4;

	int size1 = sizeof(BITMAPFILEHEADER);
	int size2 = sizeof(BITMAPINFOHEADER);
	bmfHeader.bfType = 0x4D42; // "BM"
	bmfHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bi.biSizeImage;
	bmfHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	unsigned char* pTemp = nullptr;
	HBITMAP bitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (void**)&pTemp, NULL, 0);
	int j = 0;
	for (int i = 0; i < width * height * 4; i += 4)
	{
		pTemp[i] = bits[j];
		pTemp[i + 1] = bits[j + 1];
		pTemp[i + 2] = bits[j + 2];
		pTemp[i + 3] = bits[j + 3];
		j += 4;
	}
	//return CreateBitmap(width, height, 1, 3, data);
	/*FILE* pFile = fopen("D:/test.bmp", "wb");
	fwrite(&bmfHeader, 1, sizeof(BITMAPFILEHEADER), pFile);
	fwrite(&bi, 1, sizeof(BITMAPINFOHEADER), pFile);
	fwrite(data, 1, bi.biSizeImage, pFile);
	fclose(pFile);*/
	return bitmap;
}

HBITMAP CreateARGBBitmapDIBSection(HDC hdc, int width, int height, void** ppData) {
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = width;
	bmi.bmiHeader.biHeight = -height;  // 负值表示自上而下的DIB
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = width * height * 4;
	return CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, ppData, NULL, 0);
}

XMBlend2dPainter::XMBlend2dPainter(XMWindow* window)
	: m_window(window)
	, m_ps({ 0 })
	, m_width(0)
	, m_height(0)
	, m_hdc(nullptr)
	, m_oldDC(nullptr)
	, m_hCompatibleDC(nullptr)
	, m_hCompatibleBitmap(nullptr)
	, m_hOldBitmap(nullptr)
{
	BLResult result = m_testImage.read_from_file("E:\\GitHub\\FantacyUI\\images\\12dd.jpg");
	//BL_SUCCESS == 0
}

void XMBlend2dPainter::beginDraw()
{
	RECT rcPaint;
	GetClientRect(m_window->winId(), &rcPaint);
	m_width = rcPaint.right - rcPaint.left;
	m_height = rcPaint.bottom - rcPaint.top;

	m_hdc = ::BeginPaint(m_window->winId(), &m_ps);
	m_hCompatibleDC = CreateCompatibleDC(m_hdc);
	//m_hCompatibleBitmap = CreateCompatibleBitmap(m_hdc, m_width, m_height);
	/*m_hOldBitmap = (HBITMAP)::SelectObject(m_hCompatibleDC, m_hCompatibleBitmap);*/


	m_hPixelBitmap = CreateARGBBitmapDIBSection(m_hdc, m_width, m_height, &m_pixelData);
	m_hOldBitmap = (HBITMAP)::SelectObject(m_hCompatibleDC, m_hPixelBitmap);
	/*m_hCompatibleBitmap = CreateCompatibleBitmap(m_hdc, m_width, m_height);
	m_hOldBitmap = (HBITMAP)::SelectObject(m_hCompatibleDC, m_hCompatibleBitmap);*/
	BLImage blImage;
	blImage.create_from_data(m_width, m_height, BLFormat::BL_FORMAT_PRGB32, m_pixelData, m_width * 4);
	m_blContext.begin(blImage);
	m_blContext.set_rendering_quality(BL_RENDERING_QUALITY_MAX_VALUE);
}

void XMBlend2dPainter::endDraw()
{
	RECT rcPaint;	// 绘制区域
	rcPaint.left = m_ps.rcPaint.left;
	rcPaint.top = m_ps.rcPaint.top;
	rcPaint.right = m_ps.rcPaint.right;
	rcPaint.bottom = m_ps.rcPaint.bottom;

	//m_blContext.scale(0.5, 0.5);
	//m_blContext.blit_image(BLRect(0, 0, m_testImage.width(), m_testImage.height()), m_testImage);
	m_blContext.blit_image(BLRect(0, 0, m_width, m_height), m_testImage);
	m_blContext.set_fill_style(BLRgba32(0xffff0000));
	m_blContext.fill_ellipse(50, 50, 50, 50);
	m_blContext.end();
	
	::BitBlt(m_hdc, rcPaint.left, rcPaint.top, rcPaint.right - rcPaint.left,
		rcPaint.bottom - rcPaint.top, m_hCompatibleDC, rcPaint.left, rcPaint.top, SRCCOPY);
	::SelectObject(m_hCompatibleDC, m_hOldBitmap);
	::DeleteObject(m_hPixelBitmap);
	::DeleteObject(m_hCompatibleBitmap);
	::DeleteDC(m_hCompatibleDC);
	::EndPaint(m_window->winId(), &m_ps);
}

void XMBlend2dPainter::release()
{
	delete this;
}

void XMBlend2dPainter::drawBitmap(XMBitmap* bitmap, int x, int y, int width, int height)
{
	
}





#endif	//XMUI_USE_BLEND2D_BACKEND
