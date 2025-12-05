#include "Painter/CPaintTool.h"

CColor::CColor()
	: m_r(1.0f), m_g(1.0f), m_b(1.0f), m_a(1.0f)
{
}

CColor::CColor(const CColor& color)
    : m_r(color.m_r)
    , m_g(color.m_g)
    , m_b(color.m_b)
    , m_a(color.m_a)
{
}

CColor::CColor(u32 color)
{
    m_r = ((color >> 16 & 0xff) / 255.0f);
    m_g = ((color >> 8 & 0xff) / 255.0f);
    m_b = ((color & 0xff) / 255.0f);
    m_a = ((color >> 24 & 0xff) / 255.0f);
}

CColor::CColor(float r, float g, float b)
    : m_r(r), m_g(g), m_b(b), m_a(1.0f)
{

}
CColor::CColor(float r, float g, float b, float a)
    : m_r(r), m_g(g), m_b(b), m_a(a)
{
}

CColor::~CColor()
{
}

CBrush::CBrush()
    : m_type(EBrushType::BrushType_Solid)
{
}

CBrush::CBrush(const CColor& color, EBrushType type)
    : m_color(color)
    , m_type(type)
{

}


CFont::CFont()
    : m_fontName(L"Arial"), m_fontSize(12)
{

}

CFont::CFont(const CFont& other)
    : m_fontName(other.m_fontName)
    , m_fontSize(other.m_fontSize)
{
}

CFont::CFont(const FaString& fontName, int fontSize)
    : m_fontName(fontName), m_fontSize(fontSize)
{

}
