#ifndef CPIXMAP_H
#define CPIXMAP_H


#include "PlatformDef.h"
#include <gdiplus.h>

class FANTACY_API CPixmap
{
public:
	CPixmap();
	~CPixmap();

	bool load_file(const char* fileName);

	FANTACY_INLINE int width()const
	{
		return m_width;
	}

	FANTACY_INLINE int height()const
	{
		return m_height;
	}

	FANTACY_INLINE void* data_const() const
	{
		return m_data;
	}

	FANTACY_INLINE void* data()
	{
		return m_data;
	}

	HBITMAP toBitmap()
	{
		//return CreateBitmap(m_width, m_height, 1, 32, m_data);
		return (HBITMAP)m_data;
	}

private:
	int m_width;
	int m_height;
	void* m_data;
	int m_comp;
};


#endif  // CPIXMAP_H

