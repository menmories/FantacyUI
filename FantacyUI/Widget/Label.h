#ifndef __FANTACY_LABEL_H__
#define __FANTACY_LABEL_H__
#include "Types.h"
#include "Base/Geometry.h"
#include "Base/String.h"
#include "Render/Font.h"
#include "Base/Color.h"
#include "Text.h"

class FCanvas;
class FANTACY_API FLabel : public FWidget, public FText
{
public:
	FLabel();

	~FLabel();

	virtual void OnPaint(FCanvas* Canvas);
private:
	FString mText;
	FFont* mTextFont;
	FColor mTextColor;
};




#endif // !__FANTACY_WIDGET_H__

