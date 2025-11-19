#ifndef CPAINTER_H
#define CPAINTER_H

#include "Painter/CPixmap.h"
#include "Window/CWindow.h"

class CBrush
{
public:
	CBrush()
        : m_r(1.0f), m_g(1.0f), m_b(1.0f), m_a(1.0f)
	{

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

class CFont
{
public:
    CFont()
        : m_fontName(L"Arial"), m_fontSize(12)
    {

    }

    CFont(std::wstring fontName, int fontSize)
        : m_fontName(fontName), m_fontSize(fontSize)
    {

    }

	FANTACY_INLINE std::wstring name() const
    {
        return m_fontName;
    }

	FANTACY_INLINE int size() const
    {
        return m_fontSize;
    }
private:
    std::wstring m_fontName;
    int m_fontSize;
};

class CPoint
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

class CSize
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



class CRect
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
	CPainter(CWindow* window);
	~CPainter();

	void clear(float r, float g, float b);

    CPainter* createCompatiblePainter(int width, int height);

	FANTACY_INLINE void setBrush(const CBrush& brush)
	{
		m_brush = brush;
	}
	virtual void drawLine(int beginX, int beginY, int endX, int endY, float width);

	virtual void drawPixmap(CPixmap& pixmap, s32 x, s32 y, s32 width, s32 height);

	virtual void drawPixmapAlphaBlend(CPixmap& pixmap, s32 x, s32 y, s32 width, s32 height, u8 alpha);

	FANTACY_INLINE void setFont(const CFont& font)
	{
		m_font = font;
	}

	virtual void drawText(const std::wstring& text, int x, int y);

	void fillRoundedRect(s32 x, s32 y, s32 width, s32 height, s32 radiusX, s32 radiusY);

	void drawRoundedRect(s32 x, s32 y, s32 width, s32 height, s32 radiusX, s32 radiusY, float lineWidth);

	void fillRect(s32 x, s32 y, s32 width, s32 height);

	void drawRect(s32 x, s32 y, s32 width, s32 height, float lineWidth);
private:
	HDC m_hdc;
	CFont m_font;
	CBrush m_brush;
};


#endif // !CPAINTER_H
