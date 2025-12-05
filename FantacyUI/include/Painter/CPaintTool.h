#ifndef __CPAINTTOOL_H__
#define __CPAINTTOOL_H__

#include "PlatformDef.h"
#include "Core/FaString.h"

class FANTACY_API CColor
{
public:
    CColor();
    CColor(const CColor& color);
    CColor(u32 color);
    CColor(float r, float g, float b);
    CColor(float r, float g, float b, float a);
    ~CColor();

    FANTACY_INLINE float r() const
    {
        return m_r;
    }
    FANTACY_INLINE float g() const
    {
        return m_g;
    }
    FANTACY_INLINE float b() const
    {
        return m_b;
    }
    FANTACY_INLINE float a() const
    {
        return m_a;
    }
private:
    float m_r;
    float m_g;
    float m_b;
    float m_a;
};

enum class EBrushType
{
    BrushType_Solid,
    BrushType_Gradient,
};

class FANTACY_API CBrush
{
public:
    CBrush();
    CBrush(const CColor& color, EBrushType type = EBrushType::BrushType_Solid);

    FANTACY_INLINE EBrushType type() const
    {
        return m_type;
    }

    FANTACY_INLINE CColor color() const
    {
        return m_color;
    }

    FANTACY_INLINE void setColor(const CColor& color)
    {
        m_color = color;
    }
private:
    EBrushType m_type;
    CColor m_color;
};

class FANTACY_API CFont
{
public:
    CFont();
    CFont(const CFont& other);
    CFont(const FaString& fontName, int fontSize);

    FANTACY_INLINE FaString name() const
    {
        return m_fontName;
    }

    FANTACY_INLINE void setFontName(const FaString& fontName)
    {
        m_fontName = fontName;
    }

    FANTACY_INLINE int fontSize() const
    {
        return m_fontSize;
    }

    FANTACY_INLINE void setFontSize(int fontSize)
    {
        m_fontSize = fontSize;
    }
private:
    FaString m_fontName;
    int m_fontSize;
};


#endif // !__CPAINTTOOL_H__
