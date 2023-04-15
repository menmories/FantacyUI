#ifndef __FANTACY_GEOMETRY_H__
#define __FANTACY_GEOMETRY_H__

#include <Types.h>

class FANTACY_API FSize
{
public:
	FSize();
	FSize(s32 InWidth, s32 InHeight);

	s32 Width;
	s32 Height;
};

class FANTACY_API FPoint
{
public:
	FPoint();
	FPoint(s32 InX, s32 InY);

	s32 X;
	s32 Y;
};

template <class TType>
class FRect
{
public:
	FRect()
		: Left(0)
		, Top(0)
		, Right(0)
		, Bottom(0)
	{
	}

	FRect(TType InWidth, TType InHeight)
		: Left(0)
		, Top(0)
		, Right(InWidth)
		, Bottom(InHeight)
	{
	}

	FRect(TType InLeft, TType InTop, TType InWidth, TType InHeight)
		: Left(InLeft)
		, Top(InTop)
		, Right(InLeft + InWidth)
		, Bottom(InTop + InHeight)
	{

	}

	bool PtInRect(TType AxisX, TType AxisY)const
	{
		if ((AxisX >= Left) && (AxisX <= Right))
		{
			if ((AxisY >= Top) && (AxisY <= Bottom))
			{
				return true;
			}
		}
		return false;
	}

	TType GetWidth()const
	{
		return Right - Left;
	}

	TType GetHeight()const
	{
		return Bottom - Top;
	}

	TType SetWidth(TType Width)
	{
		this->Right = this->Left + Width;
	}

	TType SetHeight(TType Height)
	{
		this->Bottom = this->Top + Height;
	}
public:
	TType Left;
	TType Top;
	TType Right;
	TType Bottom;
};


typedef FRect<s32> FRectU;
typedef FRect<float> FRectF;
typedef FRectU FMargin;

#endif // !__FANTACY_GEOMETRY_H__

