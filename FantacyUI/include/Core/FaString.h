#ifndef __FASTRING_CLASS_H__
#define __FASTRING_CLASS_H__

#include "PlatformDef.h"



class FANTACY_API FaString
{
public:
    FaString();
    FaString(const wchar_t* src);
    FaString(const wchar_t* src, u32 len);
    FaString(const char* src);
    FaString(const char* src, u32 len);
    ~FaString();

    FaString& operator=(const FaString& other);
    FaString& operator=(const wchar_t* other);
    FaString& operator=(const char* other);

    FaString& operator+=(const FaString& other);
    FaString& operator+=(const wchar_t* other);

    bool operator==(const FaString& other)const;

    bool operator!=(const FaString& other)const;

    void FromUtf8(const char* other);

    FANTACY_INLINE const wchar_t* Str()const
    {
        return m_str;
    }

    FANTACY_INLINE u32 Length()const
    {
        return m_len;
    }
private:
    wchar_t* m_str;
    u32 m_len;
    u32 m_capacity;
};


FANTACY_API FaString operator+(const FaString& src1, const FaString& src2);
FANTACY_API FaString operator+(const char* src1, const FaString& src2);
FANTACY_API FaString operator+(const wchar_t* src1, const FaString& src2);
FANTACY_API const bool operator==(const wchar_t* src, const FaString& src2);
FANTACY_API const bool operator!=(const wchar_t* src, const FaString& src2);

#endif  //__FASTRING_CLASS_H__


