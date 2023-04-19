#include "pch.h"
#include "Widget.h"
#include "Render/Canvas.h"
#include "Render/Font.h"
#include "Text.h"

FText::FText()
{
	//从FontManager获取默认字体
	mTextFont = FFontManager::Get()->GetFont(DEFAULT_FONT_ID); //FFontManager::Get()->CreateNewFont(TEXT("微软雅黑"), 14.0f);
	//IDWriteTextFormat* TextFormat = (IDWriteTextFormat*)mTextFont->GetObj();
	IDWriteTextFormat* TextFormat = (IDWriteTextFormat*)mTextFont->GetObj();
	TextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_CENTER);
	TextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT::DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
}

FText::~FText()
{
}

void FText::SetTextAlignment(const DWRITE_TEXT_ALIGNMENT& alignment)
{
	IDWriteTextFormat* TextFormat = (IDWriteTextFormat*)mTextFont->GetObj();
	TextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_CENTER);
	
}

void FText::SetParagraphAlignment(const DWRITE_PARAGRAPH_ALIGNMENT& alignment)
{
	IDWriteTextFormat* TextFormat = (IDWriteTextFormat*)mTextFont->GetObj();
	TextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT::DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
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
	return (u32)mText.length();
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
	D2D1_RECT_F textRect = { (FLOAT)Rect.Left, (FLOAT)Rect.Top, (FLOAT)Rect.Right, (FLOAT)Rect.Bottom };
	ID2D1SolidColorBrush* textBrush = nullptr;
	textBrush = Canvas->CreateSolidColorBrush(mTextColor);
	assert(textBrush);
	/*if (!textBrush)
	{
		return;
	}*/
	
	Canvas->RenderTarget->DrawText(mText.c_str(), (UINT32)mText.length(),
		(IDWriteTextFormat*)mTextFont->GetObj(),
		textRect,
		textBrush);
	textBrush->Release();
}
