#include "Painter/CPainterDevice.h"
#include "Painter/CPainter.h"
#include "CApplication.h"
#include <gdiplus.h>

CPainter::CPainter()
{
}

CPainter::CPainter(CWindow* window)
	: m_hdc(window->painterDevice()->winDC())
	, m_brush(CColor(0.0f, 0.0f, 0.0f, 1.0f))
{
}

CPainter::~CPainter()
{
}

// 创建兼容的DIB位图（使用32位ARGB格式）
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
	for (int i = 0; i < width * height * 4; i+=4)
	{
		pTemp[i] = bits[j];
		pTemp[i+1] = bits[j+1];
		pTemp[i+2] = bits[j+2];
		pTemp[i+3] = bits[j+3];
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

void CPainter::clear(float r, float g, float b)
{
    Gdiplus::Graphics graphics(m_hdc);
    graphics.Clear(Gdiplus::Color((BYTE)(255*r), (BYTE)(255*g), (BYTE)(255*b)));

	/*RECT rcPaint = {0, 0, m_width, m_height};
	HBRUSH hBrush = CreateSolidBrush(RGB((BYTE)(255*r), (BYTE)(255*g), (BYTE)(255*b)));
	FillRect(m_hCompatibleDC, &rcPaint, hBrush);*/

}

CPainter* CPainter::fromPixmap(CPixmap* bitmap)
{
	CPainter* painter = new CPainter();
	HDC hdc = GetDC(nullptr);
	
	painter->m_hdc = CreateCompatibleDC(hdc);
	painter->m_bitmap = CreateCompatibleBitmap(painter->m_hdc, bitmap->width(), bitmap->height());
	SelectObject(painter->m_hdc, painter->m_bitmap);
	return painter;
}

void CPainter::drawLine(int beginX, int beginY, int endX, int endY, float width)
{
	Gdiplus::Graphics graphics(m_hdc);
	if (m_brush.type() == EBrushType::BrushType_Solid)
	{
		CColor color = m_brush.color();
		Gdiplus::SolidBrush brush(Gdiplus::Color((BYTE)(color.r() * 255), 
			(BYTE)(color.g() * 255), (BYTE)(color.b() * 255)));
		Gdiplus::Pen pen(&brush, width);
		graphics.DrawLine(&pen, beginX, beginY, endX, endY);
	}
}

void CPainter::drawPixmap(CPixmap& pixmap, const CRect& rect)
{
	HDC hCompatibleDC = CreateCompatibleDC(m_hdc);
	HBITMAP hBitmapSrc = pixmap.toBitmap();
	HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hCompatibleDC, hBitmapSrc);
	::SetStretchBltMode(m_hdc, HALFTONE);
	::StretchBlt(m_hdc, rect.x(), rect.y(), rect.width(), rect.height(), hCompatibleDC, 0, 0, pixmap.width(), pixmap.height(), SRCCOPY);

	::SelectObject(hCompatibleDC, hOldBitmap);
	::DeleteDC(hCompatibleDC);
}

void CPainter::drawPixmap(CPixmap& pixmap, s32 x, s32 y, s32 width, s32 height)
{
	HDC hCompatibleDC = CreateCompatibleDC(m_hdc);
	HBITMAP hBitmapSrc = pixmap.toBitmap();
	HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hCompatibleDC, hBitmapSrc);
	::SetStretchBltMode(m_hdc, HALFTONE);
	::StretchBlt(m_hdc, x, y, width, height, hCompatibleDC, 0, 0, pixmap.width(), pixmap.height(), SRCCOPY);

	::SelectObject(hCompatibleDC, hOldBitmap);
	::DeleteDC(hCompatibleDC);
}

void CPainter::drawPixmapAlphaBlend(CPixmap& pixmap, s32 x, s32 y, s32 width, s32 height, u8 alpha)
{
	HDC hCompatibleDC = CreateCompatibleDC(m_hdc);
	HBITMAP hBitmapSrc = pixmap.toBitmap();
	HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hCompatibleDC, hBitmapSrc);

	BLENDFUNCTION blend = { 0 };
	blend.BlendOp = AC_SRC_OVER;        // 源图像覆盖在目标上
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = alpha;    // 使用像素自身的alpha通道（不额外叠加透明度）
	blend.AlphaFormat = AC_SRC_ALPHA;   // 启用源图像的alpha通道
	BOOL bRet = AlphaBlend(m_hdc, 0, 0, width, height, hCompatibleDC, 0, 0, pixmap.width(), pixmap.height(), blend);

	::SelectObject(hCompatibleDC, hOldBitmap);
	DeleteDC(hCompatibleDC);
}

void CPainter::drawText(const FaString& text, int x, int y)
{
	Gdiplus::Graphics graphics(m_hdc);
	//Gdiplus::Font font(m_font.name().c_str(), m_font.size());
	Gdiplus::Font font(m_font.name().Str(), (Gdiplus::REAL)m_font.fontSize(), Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);

	if (m_brush.type() == EBrushType::BrushType_Solid)
	{
		CColor color = m_brush.color();
		Gdiplus::SolidBrush brush(Gdiplus::Color((BYTE)(color.a() * 255), (BYTE)(color.r() * 255),
			(BYTE)(color.g() * 255),
			(BYTE)(color.b() * 255)));
		graphics.DrawString(text.Str(), (INT)text.Length(), &font, Gdiplus::PointF((Gdiplus::REAL)x, (Gdiplus::REAL)y), &brush);
	}

	
}

void CPainter::drawText(const FaString& text, const CRect& rect)
{
	Gdiplus::Graphics graphics(m_hdc);
	Gdiplus::Font font(m_font.name().Str(), (Gdiplus::REAL)m_font.fontSize(), Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	Gdiplus::StringFormat sf = new Gdiplus::StringFormat();
	sf.SetAlignment(Gdiplus::StringAlignmentCenter);
	sf.SetLineAlignment(Gdiplus::StringAlignmentCenter);
	Gdiplus::RectF rcLayout((Gdiplus::REAL)rect.x(), (Gdiplus::REAL)rect.y(), (Gdiplus::REAL)rect.width(), (Gdiplus::REAL)rect.height());

	if (m_brush.type() == EBrushType::BrushType_Solid)
	{
		CColor color = m_brush.color();
		Gdiplus::SolidBrush brush(Gdiplus::Color((BYTE)(color.a() * 255), (BYTE)(color.r() * 255),
			(BYTE)(color.g() * 255),
			(BYTE)(color.b() * 255)));
		graphics.DrawString(text.Str(), (INT)text.Length(), &font, rcLayout, &sf, &brush);
	}
}

void CPainter::drawText(const FaString& text, const CRect& rect, const CBrush& brush)
{
	Gdiplus::Graphics graphics(m_hdc);
	Gdiplus::Font font(m_font.name().Str(), (Gdiplus::REAL)m_font.fontSize(), Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	Gdiplus::RectF rcLayout((Gdiplus::REAL)rect.x(), (Gdiplus::REAL)rect.y(), (Gdiplus::REAL)rect.width(), (Gdiplus::REAL)rect.height());
	Gdiplus::StringFormat sf = new Gdiplus::StringFormat();
	sf.SetAlignment(Gdiplus::StringAlignmentCenter);
	sf.SetLineAlignment(Gdiplus::StringAlignmentCenter);

	if (brush.type() == EBrushType::BrushType_Solid)
	{
		CColor color = brush.color();
		Gdiplus::SolidBrush gdiBrush(Gdiplus::Color((BYTE)(color.a() * 255), (BYTE)(color.r() * 255),
			(BYTE)(color.g() * 255),
			(BYTE)(color.b() * 255)));
		graphics.DrawString(text.Str(), (INT)text.Length(), &font, rcLayout, &sf, &gdiBrush);
	}
	
}

void CPainter::fillRoundedRect(const CRect& rect, s32 radiusX, s32 radiusY)
{
	fillRoundedRect(rect.x(), rect.y(), rect.width(), rect.height(), radiusX, radiusY);
}

void CPainter::fillRoundedRect(s32 x, s32 y, s32 width, s32 height, s32 radiusX, s32 radiusY)
{
	Gdiplus::Graphics graphics(m_hdc);
	graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
	// 创建路径用于绘制圆角矩形
	Gdiplus::GraphicsPath path;
	radiusX *= 2;
	radiusY *= 2;

	// 左上角圆弧
	path.AddArc(x, y, radiusX, radiusY, 180, 90);
	// 右上角圆弧
	path.AddArc(x + width - radiusX, y, radiusX, radiusY, 270, 90);
	// 右下角圆弧
	path.AddArc(x + width - radiusX, y + height - radiusY, radiusX, radiusY, 0, 90);
	// 左下角圆弧
	path.AddArc(x, y + height - radiusY, radiusX, radiusY, 90, 90);

	// 闭合路径
	path.CloseAllFigures();

	if (m_brush.type() == EBrushType::BrushType_Solid)
	{
		CColor color = m_brush.color();
		Gdiplus::SolidBrush brush(Gdiplus::Color((BYTE)(color.a() * 255), (BYTE)(color.r() * 255),
			(BYTE)(color.g() * 255),
			(BYTE)(color.b() * 255)));
		graphics.FillPath(&brush, &path);
	}
	

	// 如果提供了画刷，则填充路径
	//if (brush != NULL)
	//	graphics.FillPath(brush, &path);

	// 如果提供了画笔，则绘制路径轮廓
	/*if (pen != NULL)
		graphics.DrawPath(pen, &path);*/
}

void CPainter::drawRoundedRect(const CRect& rect, s32 radiusX, s32 radiusY, float lineWidth)
{
	drawRoundedRect(rect.x(), rect.y(), rect.width(), rect.height(), radiusX, radiusY, lineWidth);
}

void CPainter::drawRoundedRect(s32 x, s32 y, s32 width, s32 height, s32 radiusX, s32 radiusY, float lineWidth)
{
	Gdiplus::Graphics graphics(m_hdc);
    graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
	// 创建路径用于绘制圆角矩形
	Gdiplus::GraphicsPath path;

	// 左上角圆弧
	path.AddArc(x, y, radiusX, radiusY, 180, 90);
	// 右上角圆弧
	path.AddArc(x + width - radiusX, y, radiusX, radiusY, 270, 90);
	// 右下角圆弧
	path.AddArc(x + width - radiusX, y + height - radiusY, radiusX, radiusY, 0, 90);
	// 左下角圆弧
	path.AddArc(x, y + height - radiusY, radiusX, radiusY, 90, 90);

	// 闭合路径
	path.CloseAllFigures();

	if (m_brush.type() == EBrushType::BrushType_Solid)
	{
		CColor color = m_brush.color();
		Gdiplus::SolidBrush brush(Gdiplus::Color((BYTE)(color.a() * 255), (BYTE)(color.r() * 255),
			(BYTE)(color.g() * 255),
			(BYTE)(color.b() * 255)));
		Gdiplus::Pen pen(&brush, lineWidth);
		graphics.DrawPath(&pen, &path);
	}
}

void CPainter::fillRect(const CRect& rect)
{
	fillRect(rect.x(), rect.y(), rect.width(), rect.height());
}

void CPainter::fillRect(s32 x, s32 y, s32 width, s32 height)
{
    Gdiplus::Graphics graphics(m_hdc);
	if (m_brush.type() == EBrushType::BrushType_Solid)
	{
		CColor color = m_brush.color();
		Gdiplus::SolidBrush brush(Gdiplus::Color((BYTE)(color.a() * 255), (BYTE)(color.r() * 255),
			(BYTE)(color.g() * 255),
			(BYTE)(color.b() * 255)));
		graphics.FillRectangle(&brush, x, y, width, height);
	}
}

void CPainter::drawRect(s32 x, s32 y, s32 width, s32 height, float lineWidth)
{
    Gdiplus::Graphics graphics(m_hdc);
	//graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
	if (m_brush.type() == EBrushType::BrushType_Solid)
	{
		CColor color = m_brush.color();
		Gdiplus::SolidBrush brush(Gdiplus::Color((BYTE)(color.a() * 255), (BYTE)(color.r() * 255),
			(BYTE)(color.g() * 255),
			(BYTE)(color.b() * 255)));
		Gdiplus::Pen pen(&brush, lineWidth);
		graphics.DrawRectangle(&pen, x, y, width, height);
	}
}

