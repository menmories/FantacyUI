#ifndef PLATFORMDEF_H
#define PLATFORMDEF_H

#ifndef PLATFORM_WINDOWS
#define PLATFORM_WINDOWS
#endif  // !PLATFORM_WINDOWS

//#define PLATFORM_LINUX


#ifdef PLATFORM_WINDOWS

#include <Windows.h>
#include <tchar.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;

typedef float f32;
typedef double f64;

typedef HWND WINID;

#include <string>
#ifdef _UNICODE
typedef std::wstring PaString;
#else
typedef std::string PaString;
#endif

#define FANTACY_INLINE __forceinline
#ifdef  FANTACY_EXPORT
#define FANTACY_API __declspec(dllexport)
#else 
#define FANTACY_API __declspec(dllimport)
#endif  // FANTACY_EXPORT


enum WindowStyle
{
	SimpleWindow,
	FramelessWindow,
	PopWindow
};


#endif  // !PLATFORM_WINDOWS




#ifdef PLATFORM_LINUX
#define PLATFORM_LINUX

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;

typedef float f32;
typedef double f64;

typedef int WINID;

#endif  // !PLATFORM_LINUX



#endif  // !PLATFORMDEF_H

