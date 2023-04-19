#include "pch.h"
#include "Render/Canvas.h"
#include "Render/Font.h"
#include "Widget.h"
#include "Label.h"
#include "Button.h"

FButton::FButton()
	: mBorderColor(0x00FFFFFF)
	, mEnteredColor(0x00FFFFFF)
	, mNormalColor(0x00ACFFFF)
	, mTouchedColor(0x40E0D0FF)
	, bPrevTouched(false)
{
	SetTextColor(0x000000ff);
	SetBackgroundColor(0x00ACFFFF);
}

FColor FButton::GetBorderColor() const
{
	return mBorderColor;
}

void FButton::OnPaint(FCanvas* Canvas)
{
	FBitmapCanvas BitmapCanvas;
	FRectU BaseRect = FPannel::GetRect();
	Canvas->CreateBitmapCanvas(FSize(BaseRect.GetWidth(), BaseRect.GetHeight()), &BitmapCanvas);
	BitmapCanvas.RenderTarget->BeginDraw();
	BitmapCanvas.Clear(GetBackgroundColor());
	//Paint childs.
	ID2D1SolidColorBrush* BorderBrush = BitmapCanvas.CreateSolidColorBrush(mBorderColor);
	assert(BorderBrush);
	/*if (!BorderBrush)
	{
		return;
	}*/

	BitmapCanvas.RenderTarget->DrawRectangle(D2D1::RectF(1,
		1,
		BaseRect.GetWidth() - 1,
		BaseRect.GetHeight() - 1),
		BorderBrush);

	ID2D1SolidColorBrush* TextBrush = BitmapCanvas.CreateSolidColorBrush(GetTextColor());
	assert(TextBrush);
	/*if (!TextBrush)
	{
		BorderBrush->Release();
		return;
	}*/

	FRectU TextRect(BaseRect.GetWidth(), BaseRect.GetHeight());
	PaintText(TextRect, &BitmapCanvas);

	/*IDWriteTextFormat* TextFormat = (IDWriteTextFormat*)GetTextFont()->GetObj();
	TextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_CENTER);
	TextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT::DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	D2D1_RECT_F TextRect = { (float)(BaseRect.Left + 0), (float)(BaseRect.Top),
		(float)(BaseRect.Right - 0), (float)(BaseRect.Bottom - 0) };

	BitmapCanvas.RenderTarget->DrawText(GetText().c_str(), GetTextLength(),
		TextFormat,
		TextRect,
		TextBrush);*/

	//End childs paint.
	ID2D1Bitmap* bitmap = nullptr;
	((ID2D1BitmapRenderTarget*)BitmapCanvas.RenderTarget)->GetBitmap(&bitmap);
	assert(bitmap);
	if (bitmap)
	{
		Canvas->RenderTarget->DrawBitmap(bitmap,
			D2D1::RectF(BaseRect.Left, BaseRect.Top, BaseRect.Right, BaseRect.Bottom),
			1.0,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
	}
	BitmapCanvas.RenderTarget->EndDraw();
	BorderBrush->Release();
	TextBrush->Release();
}

void FButton::OnMouseButtonDown(const FMouse& Mouse)
{
	if (Mouse.MouseButton == VK_LBUTTON)
	{
		bPrevTouched = true;
		SetBackgroundColor(mTouchedColor);
	}
	
}

void FButton::OnMouseButtonUp(const FMouse& Mouse)
{
	if (Mouse.MouseButton == VK_LBUTTON)
	{
		if (bPrevTouched)
		{
			if (OnClicked)
			{
				OnClicked();
			}
		}
		bPrevTouched = false;
		SetBackgroundColor(mEnteredColor);
	}
}

void FButton::OnMouseEnter()
{
	SetBackgroundColor(mEnteredColor);
}

void FButton::OnMouseLeave()
{
	SetBackgroundColor(mNormalColor);
}

FWidget* FButton::FindPointInWidget(const FPoint& InPoint)
{
	return FWidget::FindPointInWidget(InPoint);
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
