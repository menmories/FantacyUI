#ifndef XM_PEN_H
#define XM_PEN_H

#include "XMPlatformDef.h"

enum class XMPenType
{
	PenType_Solid,
	PenType_dash,
};

class XMUI_API XMPen
{
public:
	XMPen();
	XMPen(float width, XMPenType type);
	~XMPen();

	XMUI_INLINE float width() const
	{
		return m_width;
	}

	XMUI_INLINE void* data() const
	{
		return m_data;
	}
private:
	float m_width;
	XMPenType m_type;
	void* m_data;
};


#endif	// XM_PEN_H

