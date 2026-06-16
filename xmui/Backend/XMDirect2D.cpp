#ifdef XMUI_USE_DIRECT2D_BACKEND

#include "XMDirect2D.h"

#include <complex>
#include <dwrite.h>

#include <cstdio>

ID2D1Factory* g_pFactory = nullptr;
IDWriteFactory* g_pDWriteFactory = nullptr;
IWICImagingFactory* m_wicFactory = nullptr;

template<class Interface>
inline void SafeRelease(Interface** ppInterfaceToRelease)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();
		(*ppInterfaceToRelease) = NULL;
	}
}

bool InitDirect2D()
{
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &g_pFactory);
	if (FAILED(hr))
	{
		return false;
	}
	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(g_pDWriteFactory),
		reinterpret_cast<IUnknown**>(&g_pDWriteFactory)
	);
	if (FAILED(hr))
	{
		SafeRelease(&g_pFactory);
		return false;
	}

	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&m_wicFactory)
	);
	if (FAILED(hr))
	{
		SafeRelease(&g_pFactory);
		SafeRelease(&g_pDWriteFactory);
		return false;
	}
	return true;
}

void DestroyDirect2D()
{
	SafeRelease(&g_pFactory);
	SafeRelease(&g_pDWriteFactory);
}

IDWriteFactory* GetDirectWriteFactory()
{
	return g_pDWriteFactory;
}

ID2D1Factory* GetDirectFactory()
{
	return g_pFactory;
}


XMDirect2D::XMDirect2D(XMWindow* owner)
	: m_window(owner)
{
	ID2D1HwndRenderTarget* renderTarget = nullptr;
	s32 width, height;
	m_window->getSize(width, height);

	/*HDC hdc = GetDC(m_window->winId());
	float dpiX = GetDeviceCaps(hdc, LOGPIXELSX);
	float dpiY = GetDeviceCaps(hdc, LOGPIXELSY);
	ReleaseDC(m_window->winId(), hdc);*/

	

	HRESULT hr = g_pFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_DEFAULT,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE),
			96.0f,  // 固定 96DPI
			96.0f   // 固定 96DPI
		),
		D2D1::HwndRenderTargetProperties(owner->winId(), D2D1::SizeU(width, height)),
		&renderTarget
	);

	/*HRESULT hr = g_pFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(owner->winId(), D2D1::SizeU(width, height)),
		&renderTarget
	);*/
	if (FAILED(hr))
	{
		fprintf(stderr, "AttachWindow error,CreateHwndRenderTarget failed.\n");
		return;
	}

	renderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f),
		&m_pBrush
	);
	if (FAILED(hr))
	{
		fprintf(stderr, "AttachWindow error,CreateHwndRenderTarget failed.\n");
		return;
	}
	/*float dpiX, dpiY;
	renderTarget->GetDpi(&dpiX, &dpiY);*/
	
	//renderTarget->SetTextRenderingParams(RenderParams);
	//renderTarget->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_DEFAULT);
	//renderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	m_renderTarget = renderTarget;
}

XMDirect2D::~XMDirect2D()
{
	SafeRelease(&m_pBrush);
	SafeRelease(&m_renderTarget);
}

void XMDirect2D::resize(int width, int height)
{
	float dpiX, dpiY;
	m_renderTarget->GetDpi(&dpiX, &dpiY);
	float scaleX = dpiX / 96.0f;  // 1.5
	float scaleY = dpiY / 96.0f;  // 1.5

	float logicWidth = width * scaleX;
	float logicHeight = height * scaleY;

	m_renderTarget->Resize(D2D1::SizeU(logicWidth, logicHeight));

	//m_renderTarget->Resize(D2D1::SizeU(width, height));
}

void XMDirect2D::beginDraw()
{
	m_renderTarget->BeginDraw();
	m_renderTarget->Clear(D2D1::ColorF(1.0f, 0.0f, 1.0f, 1.0f));
}


void XMDirect2D::endDraw()
{
	m_renderTarget->EndDraw();
	ValidateRect(m_window->winId(), nullptr);
}

void XMDirect2D::release()
{
	delete this;
}

void XMDirect2D::drawImage(const XMImage& image, int x, int y, int width, int height, float opcity)
{
	ID2D1Bitmap* pTempBitmap = (ID2D1Bitmap*)image.data();
	m_renderTarget->DrawBitmap(pTempBitmap, D2D1::RectF(x, y, x + width, y + height), 
		opcity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0, image.width(), image.height()));
}

void XMDirect2D::fillRect(const XMRect& rect, const XMBrush& brush)
{
	ID2D1Brush* pBrush = (ID2D1Brush*)brush.data();
	m_renderTarget->FillRectangle(D2D1::RectF(
		rect.Left(), rect.Top(), rect.Right(), rect.Bottom()
	), pBrush);
}

void XMDirect2D::drawRect(const XMRect& rect, const XMBrush& brush, const XMPen& pen)
{
	ID2D1Brush* pBrush = (ID2D1Brush*)brush.data();
	ID2D1StrokeStyle* pStyle = (ID2D1StrokeStyle*)pen.data();
	m_renderTarget->DrawRectangle(D2D1::RectF(rect.Left(), rect.Right(), rect.Top(), rect.Bottom()),
		pBrush, pen.width(), pStyle);
}

void XMDirect2D::drawText(const XMString& text, const XMRect& rect, const XMBrush& brush, const XMFont& font)
{
	int len = text.Length();
	IDWriteTextFormat* textFormat = (IDWriteTextFormat*)font.data();
	ID2D1Brush* pBrush = (ID2D1Brush*)brush.data();
	m_renderTarget->DrawTextW(text.Str(), len,
		textFormat, D2D1::RectF(rect.Left(),
			rect.Top(),
			rect.Right(),
			rect.Bottom()
		), pBrush, D2D1_DRAW_TEXT_OPTIONS_NONE,
		DWRITE_MEASURING_MODE_NATURAL);
}



#endif	//XMUI_USE_DIRECT2D_BACKEND
