#ifndef FA_STRING_H
#define FA_STRING_H

//#ifdef __cplusplus
//extern "C" {
//#endif


#include "PlatformDef.h"


struct fa_string;

struct fa_string *fa_string_new(const char *str, u32 len);

struct fa_string *fa_string_new_from_utf8(const char *str);

void fa_string_set(struct fa_string *str, const wchar_t *s, u32 len);



void fa_string_set_utf8(struct fa_string* str, const char* s);

void fa_string_copy(struct fa_string *dst, struct fa_string *src);

void fa_string_copy_from_utf8(struct fa_string *dst, const char *s);

void fa_string_clear(struct fa_string *str);

void fa_string_append(struct fa_string *dst, struct fa_string *src);

void fa_string_append_char(struct fa_string *str, char c);

void fa_string_append_utf8(struct fa_string *str, const char *s);

void fa_string_append_int(struct fa_string *str, int i);

void fa_string_append_float(struct fa_string *str, float f, int pt);

wchar_t* fa_string_cstr(struct fa_string *str);

u32 fa_string_len(struct fa_string *str);

void fa_string_free(struct fa_string **str);

//#ifdef __cplusplus
//}
//#endif	//__cplusplus

#endif  // FA_STRING_H

