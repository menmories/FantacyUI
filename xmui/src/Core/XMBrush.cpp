#include "Core/XMBrush.h"

#include <cassert>
#include <d2d1.h>

#include "Core/XMPaintDevice.h"


XMBrush::XMBrush(const XMBrushType& type)
	: m_type(type)
	, m_data(nullptr)
{
	if (m_type == XMBrushType::Brush_Solid)
	{
		ID2D1HwndRenderTarget* renderTarget = (ID2D1HwndRenderTarget*)XMPaintDevice::current()->renderData();
		assert(renderTarget);
		ID2D1SolidColorBrush* brush = nullptr;
		renderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f),
			&brush
		);
		m_data = brush;
	}
}

XMBrush::XMBrush(const XMColor& color)
	: m_type(XMBrushType::Brush_Solid)
{
	ID2D1HwndRenderTarget* renderTarget = (ID2D1HwndRenderTarget*)XMPaintDevice::current()->renderData();
	assert(renderTarget);
	ID2D1SolidColorBrush* brush = nullptr;
	renderTarget->CreateSolidColorBrush(D2D1::ColorF(color.RF(), color.GF(), color.BF(), color.AF()),
		&brush
	);
	m_data = brush;
}

XMBrush::~XMBrush()
{
	if (m_data)
	{
		ID2D1Brush* brush = (ID2D1Brush*)m_data;
		brush->Release();
		m_data = nullptr;
	}
}


