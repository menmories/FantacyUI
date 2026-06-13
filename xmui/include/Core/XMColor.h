#ifndef XM_COLOR_H
#define XM_COLOR_H

#include "XMPlatformDef.h"


class XMUI_API XMColor
{
public:
    XMColor();

    XMColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
    ~XMColor();

    XMUI_INLINE void SetColor(const XMColor& color)
    {
        m_r = color.m_r;
        m_g = color.m_g;
        m_b = color.m_b;
        m_a = color.m_a;
    }
    XMUI_INLINE void SetColor(int r, int g, int b, int a)
    {
        m_r = r;
        m_g = g;
        m_b = b;
        m_a = a;
    }

    XMUI_INLINE void SetColorF(float r, float g, float b, float a)
    {
        m_r = (unsigned char)(r * 255);
        m_g = (unsigned char)(g * 255);
        m_b = (unsigned char)(b * 255);
        m_a = (unsigned char)(a * 255);
    }

    XMUI_INLINE void SetR(unsigned char r)
    {
        m_r = r;
    }

    XMUI_INLINE void SetG(unsigned char g)
    {
        m_g = g;
    }

    XMUI_INLINE void SetB(unsigned char b)
    {
        m_b = b;
    }

    XMUI_INLINE void SetA(unsigned char a)
    {
        m_a = a;
    }

    XMUI_INLINE void SetColor(unsigned int color)
    {
        m_r = (color & 0xff000000) >> 24;
        m_g = (color & 0x00ff0000) >> 16;
        m_b = (color & 0x0000ff00) >> 8;
        m_a = (color & 0x000000ff);
    }

    XMUI_INLINE unsigned char R()const
    {
        return m_r;
    }

    XMUI_INLINE unsigned char G()const
    {
        return m_g;
    }

    XMUI_INLINE unsigned char B()const
    {
        return m_b;
    }

    XMUI_INLINE unsigned char A()const
    {
        return m_a;
    }

    XMUI_INLINE unsigned int Color()const
    {
        return (m_r << 24) | (m_g << 16) | (m_b << 8) | m_a;
    }

    XMUI_INLINE float RF()const
    {
        return m_r / 255.0f;
    }

    XMUI_INLINE float GF()const
    {
        return m_g / 255.0f;
    }

    XMUI_INLINE float BF()const
    {
        return m_b / 255.0f;
    }

    XMUI_INLINE float AF()const
    {
        return m_a / 255.0f;
    }

    XMUI_INLINE bool operator==(const XMColor& color)const
    {
        return m_r == color.m_r && m_g == color.m_g && m_b == color.m_b && m_a == color.m_a;
    }

    XMUI_INLINE bool operator!=(const XMColor& color)const
    {
        return m_r != color.m_r || m_g != color.m_g || m_b != color.m_b || m_a != color.m_a;
    }

    XMUI_INLINE XMColor operator+(const XMColor& color)const
    {
        return XMColor(m_r + color.m_r, m_g + color.m_g, m_b + color.m_b, m_a + color.m_a);
    }

    XMUI_INLINE XMColor operator-(const XMColor& color)const
    {
        return XMColor(m_r - color.m_r, m_g - color.m_g, m_b - color.m_b, m_a - color.m_a);
    }

    XMUI_INLINE XMColor operator*(const XMColor& color)const
    {
        return XMColor(m_r * color.m_r, m_g * color.m_g, m_b * color.m_b, m_a * color.m_a);
    }

    XMUI_INLINE XMColor operator/(const XMColor& color)const
    {
        return XMColor(m_r / color.m_r, m_g / color.m_g, m_b / color.m_b, m_a / color.m_a);
    }

    XMUI_INLINE XMColor operator+(int value)const
    {
        return XMColor(m_r + value, m_g + value, m_b + value, m_a + value);
    }

    XMUI_INLINE XMColor operator-(int value)const
    {
        return XMColor(m_r - value, m_g - value, m_b - value, m_a - value);
    }

    XMUI_INLINE XMColor operator*(int value)const
    {
        return XMColor(m_r * value, m_g * value, m_b * value, m_a * value);
    }

    XMUI_INLINE XMColor operator/(int value)const
    {
        return XMColor(m_r / value, m_g / value, m_b / value, m_a / value);
    }

    XMUI_INLINE XMColor operator+(float value)const
    {
        return XMColor(m_r + value, m_g + value, m_b + value, m_a + value);
    }

    XMUI_INLINE XMColor operator-(float value)const
    {
        return XMColor(m_r - value, m_g - value, m_b - value, m_a - value);
    }

    XMUI_INLINE XMColor operator*(float value)const
    {
        return XMColor(m_r * value, m_g * value, m_b * value, m_a * value);
    }

    XMUI_INLINE XMColor operator/(float value)const
    {
        return XMColor(m_r / value, m_g / value, m_b / value, m_a / value);
    }

    XMUI_INLINE XMColor& operator+=(const XMColor& color)
    {
        m_r += color.m_r;
        m_g += color.m_g;
        m_b += color.m_b;
        m_a += color.m_a;
        return *this;
    }

    XMUI_INLINE XMColor& operator-=(const XMColor& color)
    {
        m_r -= color.m_r;
        m_g -= color.m_g;
        m_b -= color.m_b;
        m_a -= color.m_a;
        return *this;
    }

    XMUI_INLINE XMColor& operator*=(const XMColor& color)
    {
        m_r *= color.m_r;
        m_g *= color.m_g;
        m_b *= color.m_b;
        m_a *= color.m_a;
        return *this;
    }

    XMUI_INLINE XMColor& operator/=(const XMColor& color)
    {
        m_r /= color.m_r;
        m_g /= color.m_g;
        m_b /= color.m_b;
        m_a /= color.m_a;
        return *this;
    }

    XMUI_INLINE XMColor& operator+=(int value)
    {
        m_r += (u8)value;
        m_g += (u8)value;
        m_b += (u8)value;
        m_a += (u8)value;
        return *this;
    }

    XMUI_INLINE XMColor& operator-=(int value)
    {
        m_r -= (u8)value;
        m_g -= (u8)value;
        m_b -= (u8)value;
        m_a -= (u8)value;
        return *this;
    }

    XMUI_INLINE XMColor& operator*=(int value)
    {
        m_r *= (u8)value;
        m_g *= (u8)value;
        m_b *= (u8)value;
        m_a *= (u8)value;
        return *this;
    }

    XMUI_INLINE XMColor& operator/=(int value)
    {
        m_r /= (u8)value;
        m_g /= (u8)value;
        m_b /= (u8)value;
        m_a /= (u8)value;
        return *this;
    }

    XMUI_INLINE XMColor& operator+=(float value)
    {
        m_r += (u8)value;
        m_g += (u8)value;
        m_b += (u8)value;
        m_a += (u8)value;
        return *this;
    }

    XMUI_INLINE XMColor& operator-=(float value)
    {
        m_r -= (u8)value;
        m_g -= (u8)value;
        m_b -= (u8)value;
        m_a -= (u8)value;
        return *this;
    }

    XMUI_INLINE XMColor& operator*=(float value)
    {
        m_r *= (u8)value;
        m_g *= (u8)value;
        m_b *= (u8)value;
        m_a *= (u8)value;
        return *this;
    }

    XMUI_INLINE XMColor& operator/=(float value)
    {
        m_r /= (u8)value;
        m_g /= (u8)value;
        m_b /= (u8)value;
        m_a /= (u8)value;
        return *this;
    }

    static const unsigned int Black = 0x000000ff;
    static const unsigned int White = 0xffffffff;
private:
    unsigned char m_r;
    unsigned char m_g;
    unsigned char m_b;
    unsigned char m_a;
};



#endif  // XM_COLOR_H

