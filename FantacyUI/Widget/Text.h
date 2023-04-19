#ifndef __FANTACY_TEXT_H__
#define __FANTACY_TEXT_H__
#include "Types.h"
#include "Base/Geometry.h"
#include "Base/String.h"
#include "Render/Font.h"
#include "Base/Color.h"

class FCanvas;
class FANTACY_API FText
{
public:
	FText();

	~FText();

	//设置文本对齐
	void SetTextAlignment(const DWRITE_TEXT_ALIGNMENT& alignment);

	//设置段落对齐
	void SetParagraphAlignment(const DWRITE_PARAGRAPH_ALIGNMENT& alignment);

	virtual void SetText(const FString& InText);

	virtual FString GetText()const;

	virtual u32 GetTextLength()const;

	FFont* GetTextFont();

	FColor GetTextColor()const;

	void SetTextColor(const FColor& Color);

	void PaintText(const FRectU& Rect, FCanvas* Canvas);
private:
	FString mText;
	FFont* mTextFont;
	FColor mTextColor;
};




#endif // !__FANTACY_WIDGET_H__

