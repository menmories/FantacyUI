#ifndef __FABYTEARRAY_H__
#define __FABYTEARRAY_H__

#include "PlatformDef.h"

class FANTACY_API CFaByteArray
{
public:
	CFaByteArray();
	CFaByteArray(const char* src, int len);
	const char* data()const;
private:
	char m_small[23];
	union
	{
		char* m_data;
		int m_size;
	};
	bool m_bSmall;
};

#endif  //__FABYTEARRAY_H__
