#ifndef __FANTACY_COLOR_H__
#define __FANTACY_COLOR_H__
#include "Types.h"
class FANTACY_API FColor
{
public:
	FColor();
	FColor(u32 color);
	FColor(u8 InR, u8 InG, u8 InB, u8 InA = 0xFF);
	union
	{
		u32 Color;
		struct
		{
			u8 A;
			u8 B;
			u8 G;
			u8 R;
		};
	};

	enum
	{
		COLOR_RED = 0xFFFF0000
	};
};

#endif // !__FANTACY_COLOR_H__

