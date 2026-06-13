#ifndef XMUI_BITMAP_H
#define XMUI_BITMAP_H

#include "XMPlatformDef.h"
#include "XMString.h"

enum class XMBitmapFormat
{
	XMBF_ARGB32,
	XMBF_ARGB24,
	XMBF_RGB565,
	XMBF_ALPHA8,
};

//class XMUI_API XMBitmap
//{
//public:
//	XMBitmap(int width, int height, int stride, XMBitmapFormat format);
//
//	~XMBitmap();
//
//	void destroy();
//private:
//	u8* m_pixels;
//	int m_width;
//	int m_height;
//	int m_stride;
//	XMBitmapFormat m_format;
//	int m_refCount;
//};

class XMUI_API XMImage
{
public:
	XMImage();
	XMImage(const XMString& fileName);
	virtual ~XMImage();

	XMUI_INLINE bool isValid() const
	{
		return m_bValid;
	}

	bool loadFromFile(const XMString& fileName);


	XMUI_INLINE int width() const
	{
		return m_width;
	}

	XMUI_INLINE int height() const
	{
		return m_height;
	}

	XMUI_INLINE void* data() const
	{
		return m_data;
	}

private:
	bool __load_from_file(const XMString& fileName);
private:
	bool m_bValid;
	int m_width;
	int m_height;
	void* m_data;
};

#endif  // XMUI_BITMAP_H

