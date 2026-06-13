#include "Core/XMFont.h"

#include <cstdio>

#include "backend/direct2d/XMDirect2D.h"

XMFont::XMFont(const XMString& family, int pointSize)
	: m_family(family)
	, m_pointSize(pointSize)
{
	IDWriteFactory* factory = GetDirectWriteFactory();
	IDWriteTextFormat* pTextFormat = nullptr;

	HRESULT hr = factory->CreateTextFormat(
		m_family.Str(),    // 字体家族，这里是Arial字体，可替换为其他字体名称
		nullptr,     // 字体集合，这里使用系统默认字体集合
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		pointSize,       // 字体大小，单位是像素
		L"zh-cn",   // 区域设置，这里是美国英语，可根据需要修改
		&pTextFormat
	);
	if (FAILED(hr))
	{
		fprintf(stderr, "CreateTextFormat failed");
		return;
	}
	m_data = pTextFormat;
}


XMFont::~XMFont()
{
	IDWriteTextFormat* pTextFormat = (IDWriteTextFormat*)m_data;
	pTextFormat->Release();
	pTextFormat = nullptr;
}
