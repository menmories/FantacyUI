#ifndef XM_GEOMETRY_H
#define XM_GEOMETRY_H

#include "XMPlatformDef.h"


class XMUI_API XMPoint
{
public:
	XMPoint();
	XMPoint(int x, int y);
	~XMPoint();

	XMUI_INLINE void SetPoint(int x, int y)
	{
		m_x = x;
		m_y = y;
	}

	XMUI_INLINE int X()const
	{
		return m_x;
	}

	XMUI_INLINE int Y()const
	{
		return m_y;
	}

	XMUI_INLINE void SetX(int x)
	{
		m_x = x;
	}

	XMUI_INLINE void SetY(int y)
	{
		m_y = y;
	}

	XMUI_INLINE void Offset(int dx, int dy)
	{
		m_x += dx;
		m_y += dy;
	}
private:
	int m_x;
	int m_y;
};




class XMUI_API XMRect
{
public:
	XMRect();
	XMRect(int left, int top, int right, int bottom);
	~XMRect();

	XMUI_INLINE int Left()const
	{
		return m_left;
	}
	
	XMUI_INLINE int Top()const
	{
		return m_top;
	}

	XMUI_INLINE int Right()const
	{
		return m_right;
	}

	XMUI_INLINE int Bottom()const
	{
		return m_bottom;
	}

	XMUI_INLINE int Width()const
	{
		return m_right - m_left;
	}

	XMUI_INLINE int Height()const
	{
		return m_bottom - m_top;
	}

	XMUI_INLINE void SetLeft(int left)
	{
		m_left = left;
	}

	XMUI_INLINE void SetTop(int top)
	{
		m_top = top;
	}

	XMUI_INLINE void SetRight(int right)
	{
		m_right = right;
	}

	XMUI_INLINE void SetBottom(int bottom)
	{
		m_bottom = bottom;
	}

	XMUI_INLINE void SetWidth(int width)
	{
		m_right = m_left + width;
	}

	XMUI_INLINE void SetHeight(int height)
	{
		m_bottom = m_top + height;
	}

	void SetRect(int left, int top, int right, int bottom);

	void SetRect(const XMRect& rect);

	void OffsetRect(int dx, int dy);

	void Move(int x, int y);

	void Resize(int width, int height);
private:
	int m_left;
	int m_top;
	int m_right;
	int m_bottom;
};



#endif  // XM_GEOMETRY_H
