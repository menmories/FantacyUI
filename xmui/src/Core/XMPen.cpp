#include "Core/XMPen.h"
#include "backend/XMDirect2D.h"

XMPen::XMPen()
	: m_width(1.0f)
	, m_type(XMPenType::PenType_Solid)
	, m_data(nullptr)
{
    //ID2D1StrokeStyle* pDashedStyle = nullptr;
    //ID2D1Factory* factory = GetDirectFactory();
    //float dashes[] = { 5.0f, 3.0f };  // 5像素实线，3像素空白
    //factory->CreateStrokeStyle(
    //    D2D1::StrokeStyleProperties(
    //        D2D1_CAP_STYLE_FLAT,
    //        D2D1_CAP_STYLE_FLAT,
    //        D2D1_CAP_STYLE_FLAT,
    //        D2D1_LINE_JOIN_MITER,
    //        10.0f,
    //        D2D1_DASH_STYLE_SOLID,
    //        0.0f
    //    ),
    //    dashes,
    //    2,
    //    &pDashedStyle
    //);
    //m_data = pDashedStyle;
}

XMPen::XMPen(float width, XMPenType type)
    : m_width(width)
    , m_type(type)
    , m_data(nullptr)
{
    //ID2D1StrokeStyle* pDashedStyle = nullptr;
    //ID2D1Factory* factory = GetDirectFactory();
    //float dashes[] = { 5.0f, 3.0f };  // 5像素实线，3像素空白
    //factory->CreateStrokeStyle(
    //    D2D1::StrokeStyleProperties(
    //        D2D1_CAP_STYLE_FLAT,
    //        D2D1_CAP_STYLE_FLAT,
    //        D2D1_CAP_STYLE_FLAT,
    //        D2D1_LINE_JOIN_MITER,
    //        10.0f,
    //        D2D1_DASH_STYLE_SOLID,
    //        0.0f
    //    ),
    //    dashes,
    //    2,
    //    &pDashedStyle
    //);
    //m_data = pDashedStyle;
}

XMPen::~XMPen()
{
    if (m_data)
    {
        ID2D1StrokeStyle* pStyle = (ID2D1StrokeStyle*)m_data;
        pStyle->Release();
        pStyle = nullptr;
    }
}



