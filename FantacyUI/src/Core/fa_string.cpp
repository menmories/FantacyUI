
#include "Core/fa_string.h"
#include <string.h>

struct fa_string
{
	wchar_t* data;
    u32 length;
};

struct fa_string* fa_string_new(const char* str, u32 len)
{
	struct fa_string* self = (struct fa_string*)malloc(sizeof(struct fa_string));

	int length = MultiByteToWideChar(CP_ACP, 0, str, len, NULL, 0);

    self->data = (wchar_t*)malloc(sizeof(wchar_t) * length + sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, str, len, self->data, length);
	self->length = length;
	self->data[length] = L'\0';
	return self;
}

struct fa_string* fa_string_new_from_utf8(const char* str)
{
	struct fa_string* self = (struct fa_string*)malloc(sizeof(struct fa_string));

	int length = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);

	self->data = (wchar_t*)malloc(sizeof(wchar_t) * length + sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, str, -1, self->data, length);
	self->length = length;
	self->data[length] = L'\0';
	return self;
}

void fa_string_set(fa_string* str, const wchar_t* s, u32 len)
{
	if (str->length >= len)
	{
        memcpy(str->data, s, len * sizeof(wchar_t));
	}
	else
    {
        free(str->data);
        str->data = (wchar_t*)malloc(sizeof(wchar_t) * len + sizeof(wchar_t));
        memcpy(str->data, s, len * sizeof(wchar_t));
    }
    str->length = len;
    str->data[len] = L'\0';
}

void fa_string_set_utf8(fa_string* str, const char* s)
{
	
}

void fa_string_copy(fa_string* dst, fa_string* src)
{ 
	dst->data = (wchar_t*)malloc(src->length + sizeof(wchar_t));
	wmemcpy(dst->data, src->data, src->length);
	dst->data[src->length] = L'\0';
}

wchar_t* fa_string_cstr(fa_string* str)
{
	return str->data;
}

u32 fa_string_len(struct fa_string* str)
{
	return str->length;
}

void fa_string_free(struct fa_string** str)
{
	free((*str)->data);
    free(*str);
    *str = NULL;
}
