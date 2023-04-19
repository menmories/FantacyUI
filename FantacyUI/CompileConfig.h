
#ifndef __FANTACY_COMPILECONFIG_H__
#define __FANTACY_COMPILECONFIG_H__

#define PLATFORM_WINDOWS

#ifdef PLATFORM_WINDOWS
#define FANTACY_API __declspec(dllexport)

#else
#define FANTACY_API
#endif




#endif	//__FANTACY_COMPILECONFIG_H__

