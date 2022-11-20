#ifndef __FANTACY_BUTTON_H__
#define __FANTACY_BUTTON_H__
#include "Types.h"
#include "Base/Geometry.h"
#include "Base/String.h"
#include "Render/Font.h"
#include "Base/Color.h"
#include "Text.h"
#include "Pannel.h"

class FCanvas;
class FANTACY_API FButton : public FText, public FPannel
{
public:
	FButton();

	FColor GetBorderColor()const;

	virtual void OnPaint(FCanvas* Canvas);

private:
	FColor mBorderColor;
};


class FANTACY_API FRoundedButton : public FButton
{
public:
	FRoundedButton();
	virtual void OnPaint(FCanvas* Canvas);
};

class FANTACY_API FImageButton : public FButton
{
public:
	FImageButton();
};

#endif // !__FANTACY_BUTTON_H__

