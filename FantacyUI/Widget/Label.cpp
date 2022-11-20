#include "pch.h"
#include "Widget.h"
#include "Label.h"
#include "Render/Canvas.h"
#include "Render/Font.h"
FLabel::FLabel()
{
	mTextFont = FFontManager::Get()->GetFont(DEFAULT_FONT_ID); //FFontManager::Get()->CreateNewFont(TEXT("Î¢ÈíÑÅºÚ"), 14.0f);
}

FLabel::~FLabel()
{
}

void FLabel::SetText(const FString& InText)
{
	mText = InText;
}


FString FLabel::GetText() const
{
	return mText;
}

u32 FLabel::GetTextLength() const
{
	return mText.length();
}

void FLabel::OnPaint(FCanvas* Canvas)
{
	FRectU rect = GetRect();
	D2D1_RECT_F textRect = { rect.Left, rect.Top, rect.Right, rect.Bottom };
	ID2D1SolidColorBrush* textBrush = nullptr;
	textBrush = Canvas->CreateSolidColorBrush(mTextColor);
	if (!textBrush)
	{
		return;
	}
	Canvas->RenderTarget->DrawText(mText.c_str(), mText.length(),
		(IDWriteTextFormat*)mTextFont->GetObj(),
		textRect,
		textBrush);
	textBrush->Release();

	//FBitmapCanvas BitmapCanvas;
	//Canvas->CreateBitmapCanvas(FSize(mRect.GetWidth(), mRect.GetHeight()), &BitmapCanvas);
	//
	//if (!mSolidColorBrush)
	//{
	//	Canvas->RenderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0, 0.6, 0.1), &mSolidColorBrush);
	//	BitmapCanvas.BitmapRenderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0, 0.0, 0.1), &mSolidColorBrush);
	//}
	//BitmapCanvas.BitmapRenderTarget->BeginDraw();
	//BitmapCanvas.BitmapRenderTarget->Clear(D2D1::ColorF(0.0f, 1.0f, 1.0f));
	//s32 width = BitmapCanvas.BitmapRenderTarget->GetPixelSize().width;
	//s32 height = BitmapCanvas.BitmapRenderTarget->GetPixelSize().height;
	//width = BitmapCanvas.BitmapRenderTarget->GetSize().width;
	//height = BitmapCanvas.BitmapRenderTarget->GetSize().height;
	///*BitmapCanvas.BitmapRenderTarget->FillRectangle(D2D1::RectF(0, 0, mRect.GetWidth(), mRect.GetHeight()),
	//	mSolidColorBrush);*/
	//BitmapCanvas.BitmapRenderTarget->FillRectangle(D2D1::RectF(0, 0, 20, 20),
	//	mSolidColorBrush);
	//BitmapCanvas.BitmapRenderTarget->FillRectangle(D2D1::RectF(mRect.GetWidth() / 2, 0, mRect.GetWidth(), mRect.GetHeight() / 2),
	//	mSolidColorBrush);

	//ID2D1Bitmap* bitmap = nullptr;
	//BitmapCanvas.BitmapRenderTarget->GetBitmap(&bitmap);
	//if (bitmap)
	//{
	//	Canvas->RenderTarget->DrawBitmap(bitmap, 
	//		D2D1::RectF(mRect.Left, mRect.Top, mRect.Right, mRect.Bottom),
	//		1.0,
	//		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
	//}
	//BitmapCanvas.BitmapRenderTarget->EndDraw();
	//mSolidColorBrush->Release();
	//mSolidColorBrush = nullptr;
}
