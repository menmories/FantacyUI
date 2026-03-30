#include "Core/FaByteArray.h"

CFaByteArray::CFaByteArray()
	: m_small{ 0 }
	, m_bSmall(true)
{
}

CFaByteArray::CFaByteArray(const char* src, int len)
	: m_small{ 0 }
	, m_bSmall(true)
{
	if (len >= 23)
	{
		m_bSmall = false;
		m_data = new char[len + 1];
		memcpy(m_data, src, len);
		m_data[len] = 0;
	}
	else
	{
		memcpy(m_small, src, len);
		m_small[len] = 0;
	}
	m_size = len;
}

const char* CFaByteArray::data() const
{
	if (m_bSmall)
	{
		const char* pdata = m_small;
		return pdata;
	}
	return m_data;
}
