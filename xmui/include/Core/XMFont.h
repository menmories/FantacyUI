#ifndef XM_FONT_H
#define XM_FONT_H


#include "XMPlatformDef.h"
#include "XMString.h"

class XMUI_API XMFont
{
public:
	XMFont(const XMString& family, int pointSize);
	~XMFont();

	XMUI_INLINE void* data() const
	{
		return m_data;
	}

	XMUI_INLINE int pointSize() const
	{
		return m_pointSize;
	}

	XMUI_INLINE XMString family() const
	{
		return m_family;
	}
private:
	XMString m_family;
	int m_pointSize;
	void* m_data;
};



#endif  // XM_FONT_H

