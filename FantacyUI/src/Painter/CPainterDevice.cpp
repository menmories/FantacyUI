#include "Painter/CPainterDevice.h"

CPainterDevice::CPainterDevice(CWindow* window)
	: m_window(window)
	, m_ps({0})
	, m_width(0)
	, m_height(0)
	, m_hdc(NULL)
	, m_hCompatibleDC(NULL)
	, m_hCompatibleBitmap(NULL)
	, m_hOldBitmap(NULL)
{
	window->getSize(m_width, m_height);
}


CPainterDevice::~CPainterDevice()
{
}

void CPainterDevice::beginPaint()
{
	RECT rcPaint;
	GetClientRect(m_window->winId(), &rcPaint);
	m_width = rcPaint.right - rcPaint.left;
	m_height = rcPaint.bottom - rcPaint.top;

	m_hdc = ::BeginPaint(m_window->winId(), &m_ps);
	m_hCompatibleDC = CreateCompatibleDC(m_hdc);
	m_hCompatibleBitmap = CreateCompatibleBitmap(m_hdc, m_width, m_height);
	m_hOldBitmap = (HBITMAP)::SelectObject(m_hCompatibleDC, m_hCompatibleBitmap);
	//Do paint use m_hCompatibleDC
	/*return m_hCompatibleDC;*/
}

void CPainterDevice::endPaint()
{
	RECT rcPaint;	// 绘制区域
	rcPaint.left = m_ps.rcPaint.left;
	rcPaint.top = m_ps.rcPaint.top;
	rcPaint.right = m_ps.rcPaint.right;
	rcPaint.bottom = m_ps.rcPaint.bottom;
	::BitBlt(m_hdc, rcPaint.left, rcPaint.top, rcPaint.right - rcPaint.left,
		rcPaint.bottom - rcPaint.top, m_hCompatibleDC, rcPaint.left, rcPaint.top, SRCCOPY);
	::SelectObject(m_hCompatibleDC, m_hOldBitmap);
	::DeleteObject(m_hCompatibleBitmap);
	::DeleteDC(m_hCompatibleDC);
	::EndPaint(m_window->winId(), &m_ps);
}

