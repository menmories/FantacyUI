#ifndef CPAINTER_H
#define CPAINTER_H

#include "Painter/CPixmap.h"
#include "Window/CWindow.h"

class FANTACY_API CBrush
{
public:
	CBrush()
        : m_r(1.0f), m_g(1.0f), m_b(1.0f), m_a(1.0f)
	{

	}

    CBrush(u32 color)
    {
        m_r = ((color >> 16 & 0xff) / 255.0f);
        m_g = ((color >> 8 & 0xff) / 255.0f);
        m_b = ((color & 0xff) / 255.0f);
        m_a = ((color >> 24 & 0xff) / 255.0f);
    }

	CBrush(float r, float g, float b)
        : m_r(r), m_g(g), m_b(b), m_a(1.0f)
	{

	}
	CBrush(float r, float g, float b, float a)
		: m_r(r), m_g(g), m_b(b), m_a(a)
	{

	}

	float m_r;
    float m_g;
    float m_b;
    float m_a;
};

class FANTACY_API CFont
{
public:
    CFont();

    CFont(const FaString& fontName, int fontSize);

    FANTACY_INLINE FaString name() const
    {
        return m_fontName;
    }

    FANTACY_INLINE int size() const
    {
        return m_fontSize;
    }
private:
    FaString m_fontName;
    int m_fontSize;
};

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


class CWindow;
class FANTACY_API CPainter
{
public:
    CPainter();
	CPainter(CWindow* window);
	~CPainter();

	void clear(float r, float g, float b);

    static CPainter* fromPixmap(CPixmap* bitmap);

	FANTACY_INLINE void setBrush(const CBrush& brush)
	{
		m_brush = brush;
	}
	virtual void drawLine(int beginX, int beginY, int endX, int endY, float width);


    virtual void drawPixmap(CPixmap& pixmap, const CRect& rect);
	virtual void drawPixmap(CPixmap& pixmap, s32 x, s32 y, s32 width, s32 height);
    
	virtual void drawPixmapAlphaBlend(CPixmap& pixmap, s32 x, s32 y, s32 width, s32 height, u8 alpha);

	FANTACY_INLINE void setFont(const CFont& font)
	{
		m_font = font;
	}

	virtual void drawText(const FaString& text, int x, int y);
    virtual void drawText(const FaString& text, const CRect& rect);
    virtual void drawText(const FaString& text, const CRect& rect, const CBrush& brush);

    void fillRoundedRect(const CRect& rect, s32 radiusX, s32 radiusY);
	void fillRoundedRect(s32 x, s32 y, s32 width, s32 height, s32 radiusX, s32 radiusY);

    void drawRoundedRect(const CRect& rect, s32 radiusX, s32 radiusY, float lineWidth);
	void drawRoundedRect(s32 x, s32 y, s32 width, s32 height, s32 radiusX, s32 radiusY, float lineWidth);

    void fillRect(const CRect& rect);
	void fillRect(s32 x, s32 y, s32 width, s32 height);

	void drawRect(s32 x, s32 y, s32 width, s32 height, float lineWidth);
private:
	HDC m_hdc;
	CFont m_font;
	CBrush m_brush;
    HBITMAP m_bitmap;
};


#endif // !CPAINTER_H
