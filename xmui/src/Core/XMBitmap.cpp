#include "Core/XMBitmap.h"


#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image.h"

#include <d2d1.h>
#include <string>

#include "backend/direct2d/XMDirect2D.h"
#include "Core/XMPaintDevice.h"

//
//XMBitmap::XMBitmap(int width, int height, int stride, XMBitmapFormat format)
//	: m_width(width)
//	, m_height(height)
//	, m_stride(stride)
//	, m_format(format)
//{
//	m_pixels = (u8*)malloc(m_width * m_height * stride);
//}
//
//XMBitmap::~XMBitmap()
//{
//
//}
//
//void XMBitmap::destroy()
//{
//	free(m_pixels);
//	m_pixels = nullptr;
//}









XMImage::XMImage()
	: m_width(0)
	, m_height(0)
	, m_data(nullptr)
	, m_bValid(false)
{
	
}

XMImage::XMImage(const XMString& fileName)
{
	m_bValid = loadFromFile(fileName);
}

XMImage::~XMImage()
{
	if (!m_data)
	{
		ID2D1Bitmap* bitmap = (ID2D1Bitmap*)m_data;
		bitmap->Release();
		m_bValid = false;
	}
}

bool XMImage::loadFromFile(const XMString& fileName)
{
	return m_bValid = __load_from_file(fileName);
}

bool XMImage::__load_from_file(const XMString& fileName)
{
	std::string tmpFileName = fileName.toByteArrary();

	FILE* pFile = fopen(tmpFileName.c_str(), "rb+");
	if (!pFile)
	{
		return false;
	}
	int width = 0;
	int height = 0;
	int comp = 0;
	stbi_uc* stbi_image = stbi_load_from_file(pFile, &width, &height, &comp, STBI_rgb_alpha);
	fclose(pFile);
	if (!stbi_image)
	{
		return false;
	}
	ID2D1Bitmap* bitmap = nullptr;
	ID2D1HwndRenderTarget* renderTarget = (ID2D1HwndRenderTarget*)XMPaintDevice::current()->renderData();
	D2D1_BITMAP_PROPERTIES properties = D2D1::BitmapProperties(
		D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED));
	HRESULT hr = renderTarget->CreateBitmap(D2D1::SizeU(width, height),
		stbi_image, width * 4, properties, &bitmap);
	free(stbi_image);
	if (FAILED(hr))
	{
		return false;
	}
	m_data = bitmap;
	m_width = width;
	m_height = height;
	return true;
}

