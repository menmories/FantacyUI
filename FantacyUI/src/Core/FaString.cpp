#include "Core/FaString.h"
#include <assert.h>
#include <string>

#define DEFAULT_ASSIGN_SIZE 16

//根据DEFAULT_ASSIGN_SIZE块大小来计算需要分配的内存大小
FANTACY_INLINE u32 AssignSize(u32 size)
{
	return size + (DEFAULT_ASSIGN_SIZE - (size % DEFAULT_ASSIGN_SIZE));
}

FaString::FaString()
	: m_capacity(DEFAULT_ASSIGN_SIZE)
	, m_len(0)
{
	m_str = new wchar_t[m_capacity];
	m_str[0] = 0;
}

FaString::FaString(const wchar_t* src)
{
	m_len = (u32)wcslen(src);
	m_capacity = AssignSize(m_len);
	m_str = new wchar_t[m_capacity];
	wmemcpy(m_str, src, m_len);
	m_str[m_len] = 0;
}

FaString::FaString(const wchar_t* src, u32 len)
{
	m_len = len;
	m_capacity = AssignSize(m_len);
	m_str = new wchar_t[m_capacity];
	wmemcpy(m_str, src, m_len);
	m_str[m_len] = 0;
}

FaString::FaString(const char* src)
{
	int len = (int)strlen(src);
	m_len = (u32)MultiByteToWideChar(CP_ACP, 0, src, len, nullptr, 0);
	m_capacity = AssignSize((u32)m_len);
	m_str = new wchar_t[m_capacity];
	MultiByteToWideChar(CP_ACP, 0, src, len, m_str, m_len);
	m_str[m_len] = 0;
}

FaString::FaString(const char* src, u32 len)
{
	m_len = (u32)MultiByteToWideChar(CP_ACP, 0, src, (int)len, nullptr, 0);
	m_capacity = AssignSize((u32)m_len);
	m_str = new wchar_t[m_capacity];
	MultiByteToWideChar(CP_ACP, 0, src, (int)len, m_str, m_len);
}

FaString::~FaString()
{
	delete[] m_str;
}

FaString& FaString::operator=(const FaString& other)
{
	m_len = other.m_len;
	if (m_capacity < other.m_capacity)
	{
		m_capacity = other.m_capacity;
		delete[] m_str;
		m_str = new wchar_t[m_capacity];
	}
	wmemcpy(m_str, other.m_str, m_len);
	m_str[m_len] = 0;
	return *this;
}

FaString& FaString::operator=(const wchar_t* other)
{
	m_len = (u32)wcslen(other);
	if (m_len >= m_capacity)
	{
		m_capacity = AssignSize(m_len);
		delete[] m_str;
		m_str = new wchar_t[m_capacity];
	}
	wmemcpy(m_str, other, m_len);
	m_str[m_len] = 0;
	return *this;
}

FaString& FaString::operator=(const char* other)
{
	int length = MultiByteToWideChar(CP_ACP, 0, other, -1, NULL, 0);
	u32 newCapacity = AssignSize((u32)length);
	if (newCapacity > m_capacity)
	{
		m_capacity = newCapacity;
		delete[] m_str;
		m_str = new wchar_t[m_capacity];
	}
	MultiByteToWideChar(CP_ACP, 0, other, -1, m_str, length);
	m_len = (u32)length;
	m_str[m_len - 1] = 0;
	return *this;
}

FaString& FaString::operator+=(const FaString& other)
{
	u32 newLength = m_len + other.m_len;
	u32 newCapacity = AssignSize(newLength);
	if (newCapacity > m_capacity)
	{
		wchar_t* newStr = new wchar_t[newCapacity];
		wmemcpy(newStr, m_str, m_len);
		wmemcpy(newStr + m_len, other.m_str, other.m_len);
		m_capacity = newCapacity;
		delete[] m_str;
		m_str = newStr;
	}
	else
	{
		wmemcpy(m_str + m_len, other.m_str, other.m_len);
	}
	m_len = newLength;
	m_str[m_len] = 0;
	return *this;
}

FaString& FaString::operator+=(const wchar_t* other)
{
	int length = (int)wcslen(other);
	u32 newLength = m_len + length;
	u32 newCapacity = AssignSize(newLength);
	if (newCapacity > m_capacity)
	{
		wchar_t* newStr = new wchar_t[newCapacity];
		wmemcpy(newStr, m_str, m_len);
		wmemcpy(newStr + m_len, other, length);
		m_capacity = newCapacity;
		delete[] m_str;
		m_str = newStr;
	}
	else
	{
		wmemcpy(m_str + m_len, other, length);
	}
	m_len = newLength;
	m_str[m_len] = 0;
	return *this;
}

bool FaString::operator==(const FaString& other) const
{
	if (m_capacity == other.m_capacity)
	{
		if (m_len == other.m_len)
		{
			return wcscmp(m_str, other.m_str) == 0;
		}
	}
	return false;
}

bool FaString::operator!=(const FaString& other) const
{
	if (m_capacity == other.m_capacity)
	{
		if (m_len == other.m_len)
		{
			return wcscmp(m_str, other.m_str);
		}
	}
	return true;
}

void FaString::FromUtf8(const char* other)
{
	int length = MultiByteToWideChar(CP_UTF8, 0, other, -1, NULL, 0);
	u32 newCapacity = AssignSize((u32)length);
	if (newCapacity > m_capacity)
	{
		delete[] m_str;
		m_str = new wchar_t[newCapacity];
		m_capacity = newCapacity;
	}
	wmemset(m_str, 0, m_capacity);
	MultiByteToWideChar(CP_UTF8, 0, other, -1, m_str, length);
	m_len = (u32)length;
	m_str[m_len - 1] = 0;
}

FANTACY_API FaString operator+(const FaString& src1, const FaString& src2)
{
	FaString str = src1;
	str += src2;
	return str;
}

FANTACY_API FaString operator+(const char* src1, const FaString& src2)
{
	FaString str = src1;
	str += src2;
	return str;
}

FANTACY_API FaString operator+(const wchar_t* src1, const FaString& src2)
{
	FaString str = src1;
	str += src2;
	return str;
}

FANTACY_API const bool operator==(const wchar_t* src, const FaString& src2)
{
	return wcscmp(src, src2.Str()) == 0;
}

FANTACY_API const bool operator!=(const wchar_t* src, const FaString& src2)
{
	return wcscmp(src, src2.Str());
}
