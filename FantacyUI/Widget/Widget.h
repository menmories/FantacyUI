#ifndef __FANTACY_WIDGET_H__
#define __FANTACY_WIDGET_H__
#include "Types.h"
#include "Base/Geometry.h"

class FCanvas;
class FANTACY_API FWidget
{
public:
	FWidget();

	FWidget* GetParent();

	void SetParent(FWidget* InParent);

	void SetRect(const FRectU& InRect);

	FRectU GetRect()const;

	virtual void OnPaint(FCanvas* Canvas);

	void SetMouseEnter(bool InEnter);

	bool GetMouseEnter()const;

	void SetFocus(bool InFocus);

	bool GetFocus()const;

	virtual void OnMouseButtonDown(u32 MouseButton);

	virtual void OnMouseButtonUp(u32 MouseButton);

	virtual void OnMouseEnter();

	virtual void OnMouseLeave();

	virtual FWidget* FindPointInWidget(const FPoint& InPoint);

	virtual bool PtInRegion(const FPoint& InPoint);

	void ConvertMousePoint(const FPoint& MousePoint, FPoint& OutPoint);
private:
	FRectU mRect;
	FWidget* mParent;
	u32 bMouseEnter : 1;
	u32 bFocus : 1;
};




#endif // !__FANTACY_WIDGET_H__

