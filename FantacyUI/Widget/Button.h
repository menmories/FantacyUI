#ifndef __FANTACY_BUTTON_H__
#define __FANTACY_BUTTON_H__
#include "Types.h"
#include "Base/Geometry.h"
#include "Base/String.h"
#include "Render/Font.h"
#include "Base/Color.h"
#include "Text.h"
#include "Pannel.h"
#include <functional>

class FCanvas;
class FANTACY_API FButton : public FText, public FPannel
{
public:
	FButton();

	FColor GetBorderColor()const;

	virtual void OnPaint(FCanvas* Canvas);

	virtual void OnMouseButtonDown(u32 MouseButton);

	virtual void OnMouseButtonUp(u32 MouseButton);

	virtual void OnMouseEnter();

	virtual void OnMouseLeave();

	virtual FWidget* FindPointInWidget(const FPoint& InPoint);

public:
	std::function<bool(void)> OnClicked;
	std::function<bool(void)> OnLButtonDown;
	std::function<bool(void)> OnRButtonDown;
	std::function<bool(void)> OnMButtonDown;
private:
	FColor mBorderColor;
	u32 bMouseEntered;
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

