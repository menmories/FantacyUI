#ifndef XMUI_STRING_H
#define XMUI_STRING_H

#include "XMPlatformDef.h"

class XMUI_API XMByteArray
{
public:
    XMByteArray();
    XMByteArray(const char* in, s32 len);
    XMByteArray(XMByteArray&& other) noexcept;
    ~XMByteArray();

    void assign(char* in, s32 len);

    char* data()
    {
        return m_data;
    }

    s32 length() const
    {
        return m_length;
    }

    operator char* ()const;

    XMByteArray& operator=(const XMByteArray& other);
private:
    char* m_data;
    s32 m_length;
};


class XMUI_API XMString
{
public:
    XMString();
    XMString(const XMString& other);
    XMString(const wchar_t* src);
    XMString(const wchar_t* src, u32 len);
    XMString(const char* src);
    XMString(const char* src, u32 len);
    ~XMString();

    XMString& operator=(const XMString& other);
    XMString& operator=(const wchar_t* other);
    XMString& operator=(const char* other);

    XMString& operator+=(const XMString& other);
    XMString& operator+=(const wchar_t* other);

    bool operator==(const XMString& other)const;

    bool operator!=(const XMString& other)const;

    void FromUtf8(const char* other);

    XMByteArray toByteArrary() const;

    XMUI_INLINE const wchar_t* Str()const
    {
        return m_str;
    }

    XMUI_INLINE u32 Length()const
    {
        return m_len;
    }
private:
    wchar_t* m_str;
    u32 m_len;
    u32 m_capacity;
};


XMUI_API XMString operator+(const XMString& src1, const XMString& src2);
XMUI_API XMString operator+(const char* src1, const XMString& src2);
XMUI_API XMString operator+(const wchar_t* src1, const XMString& src2);
XMUI_API const bool operator==(const wchar_t* src, const XMString& src2);
XMUI_API const bool operator!=(const wchar_t* src, const XMString& src2);

#endif  //XMUI_STRING_H


