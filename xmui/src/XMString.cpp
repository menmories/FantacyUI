#include "XMString.h"
#include <assert.h>
#include <string>

//指定最低DEFAULT_ASSIGN_SIZE block的打小
#define DEFAULT_ASSIGN_SIZE 16

//根据DEFAULT_ASSIGN_SIZE块大小来计算需要分配的内存大小
XMUI_INLINE u32 AssignSize(u32 size)
{
	return size + (DEFAULT_ASSIGN_SIZE - (size % DEFAULT_ASSIGN_SIZE));
}

XMByteArray::XMByteArray()
	: m_data(nullptr)
	, m_length(0)
{
	
}

XMByteArray::XMByteArray(const char* in, s32 len)
{
	m_data = new char[len];
	m_length = len;
	memcpy(m_data, in, len);
}

XMByteArray::XMByteArray(XMByteArray&& other) noexcept
	: m_data(other.m_data)
	, m_length(other.m_length) 
{
	other.m_data = nullptr;  // 源对象放弃所有权
	other.m_length = 0;
}

XMByteArray::~XMByteArray()
{
	if (m_data)
	{
		delete[] m_data;
		m_data = nullptr;
	}
}

void XMByteArray::assign(char* in, s32 len)
{
	m_data = in;
	m_length = len;
}

XMByteArray::operator char* () const
{
	return m_data;
}

XMByteArray& XMByteArray::operator=(const XMByteArray& other)
{
	if (this != &other) {
		delete[] m_data;  // 释放旧数据
		m_length = other.m_length;
		m_data = new char[m_length + 1];
		if (other.m_data) {
			memcpy(m_data, other.m_data, m_length);
			m_data[m_length] = 0;
		}
	}
	return *this;
}



XMString::XMString()
	: m_capacity(DEFAULT_ASSIGN_SIZE)
	, m_len(0)
{
	m_str = new wchar_t[m_capacity];
	m_str[0] = 0;
}

XMString::XMString(const XMString& other)
	: m_len(other.m_len)
	, m_capacity(other.m_capacity)
{
	m_str = new wchar_t[m_capacity];
	wmemcpy(m_str, other.m_str, m_len);
	m_str[m_len] = 0;
}

XMString::XMString(const wchar_t* src)
{
	m_len = (u32)wcslen(src);
	m_capacity = AssignSize(m_len);
	m_str = new wchar_t[m_capacity];
	wmemcpy(m_str, src, m_len);
	m_str[m_len] = 0;
}

XMString::XMString(const wchar_t* src, u32 len)
{
	m_len = len;
	m_capacity = AssignSize(m_len);
	m_str = new wchar_t[m_capacity];
	wmemcpy(m_str, src, m_len);
	m_str[m_len] = 0;
}

XMString::XMString(const char* src)
{
	//int len = (int)strlen(src);
	u32 len = (u32)MultiByteToWideChar(CP_ACP, 0, src, -1, nullptr, 0);
	m_len = len - 1;
	m_capacity = AssignSize((u32)m_len);
	m_str = new wchar_t[m_capacity];
	MultiByteToWideChar(CP_ACP, 0, src, -1, m_str, len);
}

XMString::XMString(const char* src, u32 len)
{
	u32 length = (u32)MultiByteToWideChar(CP_ACP, 0, src, (int)len, nullptr, 0);
	m_len = length - 1;
	m_capacity = AssignSize((u32)m_len);
	m_str = new wchar_t[m_capacity];
	MultiByteToWideChar(CP_ACP, 0, src, (int)len, m_str, len);
}

XMString::~XMString()
{
	delete[] m_str;   
}
                                       
XMString& XMString::operator=(const XMString& other)
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

XMString& XMString::operator=(const wchar_t* other)
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

XMString& XMString::operator=(const char* other)
{
	int len = MultiByteToWideChar(CP_ACP, 0, other, -1, nullptr, 0);
	u32 newCapacity = AssignSize(len - 1);
	if (newCapacity > m_capacity)
	{
		m_capacity = newCapacity;
		delete[] m_str;
		m_str = new wchar_t[m_capacity];
	}
	
	MultiByteToWideChar(CP_ACP, 0, other, len, m_str, len);
	m_len = len - 1;
	return *this;
}

XMString& XMString::operator+=(const XMString& other)
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

XMString& XMString::operator+=(const wchar_t* other)
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

bool XMString::operator==(const XMString& other) const
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

bool XMString::operator!=(const XMString& other) const
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

void XMString::FromUtf8(const char* other)
{
	u32 length = (u32)MultiByteToWideChar(CP_UTF8, 0, other, -1, NULL, 0);
	u32 newCapacity = AssignSize((u32)length - 1);
	if (newCapacity > m_capacity)
	{
		delete[] m_str;
		m_str = new wchar_t[newCapacity];
		m_capacity = newCapacity;
	}
	wmemset(m_str, 0, m_capacity);
	MultiByteToWideChar(CP_UTF8, 0, other, -1, m_str, length);
	m_len = length - 1;
}

XMByteArray XMString::toByteArrary() const
{
	XMByteArray data;
	int len = WideCharToMultiByte(CP_ACP, 0, m_str, m_len, nullptr, 0, nullptr, nullptr);
	char* pData = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, m_str, m_len, pData, len, nullptr, nullptr);
	pData[len] = 0;
	data.assign(pData, len);
	return data;
}

XMUI_API XMString operator+(const XMString& src1, const XMString& src2)
{
	XMString str = src1;
	str += src2;
	return str;
}

XMUI_API XMString operator+(const char* src1, const XMString& src2)
{
	XMString str = src1;
	str += src2;
	return str;
}

XMUI_API XMString operator+(const wchar_t* src1, const XMString& src2)
{
	XMString str = src1;
	str += src2;
	return str;
}

XMUI_API const bool operator==(const wchar_t* src, const XMString& src2)
{
	return wcscmp(src, src2.Str()) == 0;
}

XMUI_API const bool operator!=(const wchar_t* src, const XMString& src2)
{
	return wcscmp(src, src2.Str());
}
