

#ifndef __FANTACY_STRING_H__
#define __FANTACY_STRING_H__

#include <string>

//typedef CString FString;
typedef std::string FStringA;
typedef std::wstring FStringW;

#ifdef _UNICODE
typedef FStringW FString;
#else
typedef FStringA FString;
#endif	//_UNICODE


#endif // !__FANTACY_STRING_H__




