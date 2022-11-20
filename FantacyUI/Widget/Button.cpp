#include "pch.h"
#include "Render/Canvas.h"
#include "Render/Font.h"
#include "Widget.h"
#include "Label.h"
#include "Button.h"

FButton::FButton()
	: mBorderColor(0x00FFFFFF)
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
	if (!BorderBrush)
	{
		return;
	}

	BitmapCanvas.RenderTarget->DrawRectangle(D2D1::RectF(BaseRect.Left,
		BaseRect.Top,
		BaseRect.Right,
		BaseRect.Bottom),
		BorderBrush);

	ID2D1SolidColorBrush* TextBrush = BitmapCanvas.CreateSolidColorBrush(GetTextColor());
	if (!TextBrush)
	{
		BorderBrush->Release();
		return;
	}
	/*D2D1_RECT_F TextRect = { 0.0f, 0.0f,
		(float)(BaseRect.GetWidth()), (float)(BaseRect.GetHeight()) };*/

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

	
	BorderBrush->Release();
	TextBrush->Release();
	//End childs paint.
	ID2D1Bitmap* bitmap = nullptr;
	((ID2D1BitmapRenderTarget*)BitmapCanvas.RenderTarget)->GetBitmap(&bitmap);
	if (bitmap)
	{
		Canvas->RenderTarget->DrawBitmap(bitmap,
			D2D1::RectF(BaseRect.Left, BaseRect.Top, BaseRect.Right, BaseRect.Bottom),
			1.0,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
	}
	BitmapCanvas.RenderTarget->EndDraw();
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
