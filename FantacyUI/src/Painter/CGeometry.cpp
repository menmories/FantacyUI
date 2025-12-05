#include "Painter/CGeometry.h"

bool CRect::ptInRect(int x, int y)
{
	if (x >= m_x && x <= width() &&
		y >= m_y && y <= height())
	{
		return true;
	}
    return false;
}

bool CRect::ptInRect(const CPoint& pt)
{
	if (pt.x() >= m_x && pt.x() <= width() &&
		pt.y() >= m_y && pt.y() <= height())
	{
		return true;
	}
	return false;
}
