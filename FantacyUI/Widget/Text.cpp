#include "pch.h"
#include "Widget.h"
#include "Render/Canvas.h"
#include "Render/Font.h"
#include "Text.h"

FText::FText()
{
	mTextFont = FFontManager::Get()->GetFont(DEFAULT_FONT_ID); //FFontManager::Get()->CreateNewFont(TEXT("Î¢ÈíÑÅºÚ"), 14.0f);
	IDWriteTextFormat* TextFormat = (IDWriteTextFormat*)mTextFont->GetObj();

}

FText::~FText()
{
}

void FText::SetText(const FString& InText)
{
	mText = InText;
}


FString FText::GetText() const
{
	return mText;
}

u32 FText::GetTextLength() const
{
	return mText.length();
}

FFont* FText::GetTextFont()
{
	return mTextFont;
}

FColor FText::GetTextColor() const
{
	return mTextColor;
}

void FText::SetTextColor(const FColor& Color)
{
	mTextColor = Color;
}

void FText::PaintText(const FRectU& Rect, FCanvas* Canvas)
{
	D2D1_RECT_F textRect = { Rect.Left, Rect.Top, Rect.Right, Rect.Bottom };
	ID2D1SolidColorBrush* textBrush = nullptr;
	textBrush = Canvas->CreateSolidColorBrush(mTextColor);
	if (!textBrush)
	{
		return;
	}
	IDWriteTextFormat* TextFormat = (IDWriteTextFormat*)GetTextFont()->GetObj();
	TextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_CENTER);
	TextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT::DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	Canvas->RenderTarget->DrawText(mText.c_str(), mText.length(),
		(IDWriteTextFormat*)mTextFont->GetObj(),
		textRect,
		textBrush);
	textBrush->Release();
}
