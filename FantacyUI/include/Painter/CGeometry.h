#ifndef __CGEOMETRY_H__
#define __CGEOMETRY_H__

#include "PlatformDef.h"

class FANTACY_API CPoint
{
public:
    CPoint()
        : m_x(0), m_y(0)
    {
    }
    CPoint(const CPoint& point)
        : m_x(point.m_x), m_y(point.m_y)
    {
    }
    CPoint(int x, int y)
        : m_x(x), m_y(y)
    {
    }
    ~CPoint()
    {
    }

    FANTACY_INLINE int x() const
    {
        return m_x;
    }
    FANTACY_INLINE int y() const
    {
        return m_y;
    }

    FANTACY_INLINE void setX(int x)
    {
        m_x = x;
    }

    FANTACY_INLINE void setY(int y)
    {
        m_y = y;
    }

    CPoint& operator=(const CPoint& point)
    {
        m_x = point.m_x;
        m_y = point.m_y;
        return *this;
    }
private:
    int m_x;
    int m_y;
};

class FANTACY_API CSize
{
public:
    CSize::CSize()
        : m_width(0), m_height(0)
    {
    }
    CSize::CSize(const CSize& size)
        : m_width(size.m_width), m_height(size.m_height)
    {
    }
    CSize::CSize(int width, int height)
        : m_width(width), m_height(height)
    {
    }
    CSize::~CSize()
    {
    }
    CSize& operator=(const CSize& size)
    {
        m_width = size.m_width;
        m_height = size.m_height;
        return *this;
    }
    FANTACY_INLINE int width() const
    {
        return m_width;
    }
    FANTACY_INLINE int height() const
    {
        return m_height;
    }
    FANTACY_INLINE void setWidth(int width)
    {
        m_width = width;
    }
    FANTACY_INLINE void setHeight(int height)
    {
        m_height = height;
    }
private:
    int m_width;
    int m_height;
};



class FANTACY_API CRect
{
public:
    CRect()
        : m_x(0), m_y(0), m_width(0), m_height(0)
    {
    }
    CRect(const CRect& rect)
        : m_x(rect.m_x), m_y(rect.m_y), m_width(rect.m_width), m_height(rect.m_height)
    {
    }
    CRect(int x, int y, int width, int height)
        : m_x(x), m_y(y), m_width(width), m_height(height)
    {
    }
    ~CRect()
    {
    }

    bool ptInRect(int x, int y);
    bool ptInRect(const CPoint& pt);

    void offset(int x, int y)
    {
        m_x += x;
        m_y += y;
    }

    FANTACY_INLINE int x() const
    {
        return m_x;
    }
    FANTACY_INLINE int y() const
    {
        return m_y;
    }
    FANTACY_INLINE int width() const
    {
        return m_width;
    }
    FANTACY_INLINE int height() const
    {
        return m_height;
    }
    FANTACY_INLINE CRect rect() const
    {
        return CRect(m_x, m_y, m_width, m_height);
    }
    FANTACY_INLINE void setRect(int x, int y, int width, int height)
    {
        m_x = x;
        m_y = y;
        m_width = width;
        m_height = height;
    }
    FANTACY_INLINE void setX(int x)
    {
        m_x = x;
    }
    FANTACY_INLINE void setY(int y)
    {
        m_y = y;
    }

    void move(int x, int y)
    {
        m_x = x;
        m_y = y;
    }

    void resize(int width, int height)
    {
        m_width = width;
        m_height = height;
    }

    FANTACY_INLINE void setWidth(int width)
    {
        m_width = width;
    }
    FANTACY_INLINE void setHeight(int height)
    {
        m_height = height;
    }

    CRect& operator=(const CRect& rect)
    {
        m_x = rect.m_x;
        m_y = rect.m_y;
        m_width = rect.m_width;
        m_height = rect.m_height;
        return *this;
    }

    int bottom() const
    {
        return m_x + m_width;
    }

    int right() const
    {
        return m_y + m_height;
    }

    CRect center(const CRect& rect) const
    {
        return CRect(rect.m_x + (rect.m_width - width()) / 2, rect.m_y + (rect.m_height - height()) / 2, width(), height());
    }
private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
};




#endif // !__CGEOMETRY_H__
