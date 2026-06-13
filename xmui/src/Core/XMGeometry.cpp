#include "Core/XMGeometry.h"

XMPoint::XMPoint()
    : m_x(0)
    , m_y(0)
{
}

XMPoint::XMPoint(int x, int y)
    : m_x(x)
    , m_y(y)
{

}

XMPoint::~XMPoint()
{
}







XMRect::XMRect()
	: m_left(0)
	, m_top(0)
	, m_right(0)
	, m_bottom(0)
{
}

XMRect::XMRect(int left, int top, int right, int bottom)
	: m_left(left)
	, m_top(top)
	, m_right(right)
	, m_bottom(bottom)
{
}

XMRect::~XMRect()
{
}

void XMRect::SetRect(int left, int top, int right, int bottom)
{
	m_left = left;
	m_top = top;
	m_right = right;
	m_bottom = bottom;
}

void XMRect::SetRect(const XMRect& rect)
{
	m_left = rect.m_left;
	m_top = rect.m_top;
	m_right = rect.m_right;
	m_bottom = rect.m_bottom;
}

void XMRect::OffsetRect(int dx, int dy)
{
	m_left += dx;
	m_top += dy;
	m_right += dx;
	m_bottom += dy;
}

void XMRect::Move(int x, int y)
{
	int width = m_right - m_left;
	int height = m_bottom - m_top;
	m_left = x;
	m_top = y;
	m_right = x + width;
	m_bottom = y + height;
}

void XMRect::Resize(int width, int height)
{
	m_right = m_left + width;
	m_bottom = m_top + height;
}

