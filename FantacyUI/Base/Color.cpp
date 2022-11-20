#include "pch.h"
#include "Color.h"

FColor::FColor()
	: Color(0xffffffff)
{
}

FColor::FColor(u32 color)
	: Color(color)
{
}

FColor::FColor(u8 InR, u8 InG, u8 InB, u8 InA)
	: R(InR)
	, G(InG)
	, B(InB)
	, A(InA)
{
}
