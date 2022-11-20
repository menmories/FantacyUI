#include "pch.h"
#include "Render/Canvas.h"
#include "Render/Font.h"
#include "Widget.h"
#include "Label.h"
#include "Button.h"

FButton::FButton()
	: mBorderColor(0x00FFFFFF)
{
}

void FButton::OnPaint(FCanvas* Canvas)
{
	FRectU BaseRect = GetRect();
	ID2D1SolidColorBrush* BorderBrush = Canvas->CreateSolidColorBrush(mBorderColor);
	if (!BorderBrush)
	{
		return;
	}

	D2D1_RECT_F TextRect = { 0.0f };


	Canvas->RenderTarget->DrawRectangle(D2D1::RectF(BaseRect.Left, 
		BaseRect.Top,
		BaseRect.Right,
		BaseRect.Bottom),
		BorderBrush);
	BorderBrush->Release();
}

FRoundedButton::FRoundedButton()
{
}

void FRoundedButton::OnPaint(FCanvas* Canvas)
{
}

FImageButton::FImageButton()
{
}
