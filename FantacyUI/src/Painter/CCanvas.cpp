#include "Painter/CCanvas.h"
#include "Window/CWindow.h"
#include "Painter/CPainterDevice.h"

CCanvas::CCanvas()
	: m_hdc(nullptr)
	, m_hBitmap(nullptr)
	, m_gdiObj(nullptr)
	, m_width(0)
	, m_height(0)
{
}

CCanvas::CCanvas(HDC hdc, int width, int height)
{
	m_hdc = CreateCompatibleDC(hdc);
	m_hBitmap = CreateCompatibleBitmap(hdc, width, height);
	m_gdiObj = ::SelectObject(m_hdc, m_hBitmap);
	m_width = width;
	m_height = height;
}

CCanvas::CCanvas(CWindow* window)
{
	HDC hdc = window->painterDevice()->winDC();
	window->getSize(m_width, m_height);
	m_hdc = CreateCompatibleDC(hdc);
	m_hBitmap = CreateCompatibleBitmap(hdc, m_width, m_height);
	m_gdiObj = ::SelectObject(m_hdc, m_hBitmap);
}

CCanvas::CCanvas(CWindow* window, int width, int height)
{
	HDC hdc = window->painterDevice()->winDC();
	m_hdc = CreateCompatibleDC(hdc);
	m_hBitmap = CreateCompatibleBitmap(hdc, width, width);
	m_gdiObj = ::SelectObject(m_hdc, m_hBitmap);
	m_width = width;
	m_height = height;
}

CCanvas::~CCanvas()
{
	SelectObject(m_hdc, m_gdiObj);
	::DeleteObject(m_hdc);
	::DeleteObject(m_hBitmap);
}


