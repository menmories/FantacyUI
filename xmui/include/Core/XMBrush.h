#ifndef XM_BRUSH_H
#define XM_BRUSH_H


#include "XMPlatformDef.h"
#include "XMColor.h"

enum class XMBrushType
{
	Brush_Solid,
	Brush_LinearGradient,
};

class XMUI_API XMGradientStop
{
public:
	float position;
	XMColor color;
};

class XMUI_API XMGradientStopCollection
{
public:

};

class XMUI_API XMBrush
{
public:
	XMBrush(const XMBrushType& type);
	XMBrush(const XMColor& color);

	~XMBrush();

	XMUI_INLINE void* data() const
	{
		return m_data;
	}
private:
	XMBrushType m_type;
	void* m_data;
};


#endif  // XM_BRUSH_H
