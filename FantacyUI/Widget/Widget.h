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
private:
	FRectU mRect;
	FWidget* mParent;
};




#endif // !__FANTACY_WIDGET_H__

