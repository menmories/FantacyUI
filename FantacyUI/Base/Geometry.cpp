#include "pch.h"
#include "Base/Thread.h"
#include "Geometry.h"

FSize::FSize()
	: Width(0)
	, Height(0)
{
}

FSize::FSize(s32 InWidth, s32 InHeight)
	: Width(InWidth)
	, Height(InHeight)
{
}

FPoint::FPoint()
	: X(0)
	, Y(0)
{
}

FPoint::FPoint(s32 InX, s32 InY)
	: X(InX)
	, Y(InY)
{
}
