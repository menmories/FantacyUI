#include "pch.h"
#include "Render/Canvas.h"
#include "Base/String.h"
#include "Render/Bitmap.h"
#include "Render/Canvas.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "Dwrite.lib")
#pragma comment(lib, "windowscodecs.lib")

template<class Interface>
inline void SafeRelease(
	Interface** ppInterfaceToRelease)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();
		(*ppInterfaceToRelease) = NULL;
	}
}

#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif


FCanvas::FCanvas()
	: RenderTarget(nullptr)
{
}

FCanvas::~FCanvas()
{
	SafeRelease(&RenderTarget);
}

bool FCanvas::Init(u64 WindowId)
{
	RenderTarget = FDirect2DContext::Get()->CreateRenderTarget(WindowId);
	if (!RenderTarget)
	{
		return false;
	}
	return true;
}

void FCanvas::Clear(const FColor& Color)
{
	D2D1_COLOR_F D2DColor;
	D2DColor.a = ((float)Color.A) / 255.0f;
	D2DColor.r = ((float)Color.R) / 255.0f;
	D2DColor.g = ((float)Color.G) / 255.0f;
	D2DColor.b = ((float)Color.B) / 255.0f;
	RenderTarget->Clear(D2DColor);
}

void FCanvas::Resize(const FSize& InSize)
{
	D2D1_SIZE_U PixelSize;
	PixelSize.width = InSize.Width;
	PixelSize.height = InSize.Height;
	RenderTarget->Resize(PixelSize);
}

void FCanvas::BeginDraw()
{
	RenderTarget->BeginDraw();
}

void FCanvas::EndDraw()
{
	RenderTarget->EndDraw();
}

bool FCanvas::CreateBitmapFromFileName(const FString& InFileName, FBitmap** bitmap)
{
	/*IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICStream* pStream = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICBitmapScaler* pScaler = NULL;
	ID2D1Bitmap* pBitmap = NULL;
	HRESULT hr = m_pWICFactory->CreateDecoderFromFilename(
		szFileName,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);
	if (FAILED(hr))
	{
		goto Last_Handle;
	}
	hr = pDecoder->GetFrame(0, &pSource);
	if (FAILED(hr))
	{
		SafeRelease(&pDecoder);
		goto Last_Handle;
	}
	hr = m_pWICFactory->CreateFormatConverter(&pConverter);
	if (FAILED(hr))
	{
		SafeRelease(&pDecoder);
		SafeRelease(&pSource);
		goto Last_Handle;
	}
	hr = pConverter->Initialize(
		pSource,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.f,
		WICBitmapPaletteTypeMedianCut
	);
	if (FAILED(hr))
	{
		SafeRelease(&pDecoder);
		SafeRelease(&pSource);
		SafeRelease(&pConverter);
		goto Last_Handle;
	}
	hr = m_pRenderTarget->CreateBitmapFromWicBitmap(
		pConverter,
		NULL,
		&pBitmap
	);
	if (FAILED(hr))
	{
		SafeRelease(&pDecoder);
		SafeRelease(&pSource);
		SafeRelease(&pConverter);
		goto Last_Handle;
	}
	m_pRenderTarget->CreateBitmapFromWicBitmap(pConverter, &pBitmap);
	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	SafeRelease(&pScaler);
Last_Handle:
	*bitmap = pBitmap;*/
	return true;
}

void FCanvas::CreateBitmapCanvas(const FSize& InSize, FBitmapCanvas* bitmapCanvas)
{
	RenderTarget->CreateCompatibleRenderTarget(D2D1::SizeF((float)InSize.Width, (float)InSize.Height), 
		(ID2D1BitmapRenderTarget**)&bitmapCanvas->RenderTarget);
}

ID2D1SolidColorBrush* FCanvas::CreateSolidColorBrush(const FColor& InColor)
{
	ID2D1SolidColorBrush* SolidColorBrush = nullptr;
	RenderTarget->CreateSolidColorBrush(D2D1::ColorF(
		((float)InColor.R) / 255.0f,
		((float)InColor.G) / 255.0f,
		((float)InColor.B) / 255.0f,
		((float)InColor.A) / 255.0f), &SolidColorBrush);
	return SolidColorBrush;
}

void FCanvas::DrawBitmap(const FRectU& InRect, FBitmap* bitmap)
{
	ID2D1Bitmap* D2DBitmap = nullptr;
	RenderTarget->DrawBitmap(D2DBitmap, D2D1::RectF(
		(float)InRect.Left,
		(float)InRect.Top,
		(float)InRect.Right,
		(float)InRect.Bottom
	));
}

FDirect2DContext* FDirect2DContext::Get()
{
	static FDirect2DContext Context;
	return &Context;
}

s32 FDirect2DContext::InitContext()
{
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &Direct2DFactory);
	if (FAILED(hr))
	{
		return 1;
	}

	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(DWriteFactory),
		reinterpret_cast<IUnknown**>(&DWriteFactory)
	);
	if (FAILED(hr))
	{
		return 2;
	}

	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		reinterpret_cast<void**>(&WicImagingFactory));
	if (FAILED(hr))
	{
		return 3;
	}
	return 0;
}

void FDirect2DContext::DestroyContext()
{
	SafeRelease(&Direct2DFactory);
	SafeRelease(&DWriteFactory);
	SafeRelease(&WicImagingFactory);
}

ID2D1HwndRenderTarget* FDirect2DContext::CreateRenderTarget(u64 WindowId)
{
	D2D1_SIZE_U size = D2D1::SizeU(
		100,
		100
	);
	ID2D1HwndRenderTarget* RenderTarget = nullptr;
	HRESULT hr = Direct2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties((HWND)WindowId, size),
		&RenderTarget
	);
	if (SUCCEEDED(hr))
	{
		return RenderTarget;
	}
	return nullptr;
}

FDirect2DContext::FDirect2DContext()
	: Direct2DFactory(nullptr)
	, DWriteFactory(nullptr)
	, WicImagingFactory(nullptr)
{
}

FDirect2DContext::~FDirect2DContext()
{
	
}

FBitmapCanvas::FBitmapCanvas()
{
}

FBitmapCanvas::~FBitmapCanvas()
{
}

ID2D1Bitmap* FBitmapCanvas::GetBitmap()
{
	ID2D1BitmapRenderTarget* BitmapRenderTarget = (ID2D1BitmapRenderTarget*)this->RenderTarget;
	ID2D1Bitmap* Bitmap = nullptr;
	if (BitmapRenderTarget)
	{
		HRESULT hr = BitmapRenderTarget->GetBitmap(&Bitmap);
		if (SUCCEEDED(hr))
		{
			return Bitmap;
		}
	}
	return nullptr;
}
