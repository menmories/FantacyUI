#ifndef __FANTACY_WIDGET_H__
#define __FANTACY_WIDGET_H__
#include "Types.h"
#include "Base/Geometry.h"
#include "Base/Mouse.h"
class FCanvas;
class FANTACY_API FWidget
{
public:
	FWidget();

	FWidget* GetParent();

	void SetParent(FWidget* InParent);

	void SetRect(const FRectU& InRect);

	void SetPos(const FPoint& InPoint);

	void SetSize(const FSize& InSize);

	FRectU GetRect()const;

	virtual void OnPaint(FCanvas* Canvas);

	void SetMouseEnter(bool InEnter);

	bool GetMouseEnter()const;

	void SetFocus(bool InFocus);

	bool GetFocus()const;

	bool IsVisible()const;

	void SetVisible(bool InVisible);

	virtual void OnMouseButtonDown(const FMouse& MouseButton);

	virtual void OnMouseButtonUp(const FMouse& MouseButton);

	virtual void OnMouseEnter();

	virtual void OnMouseLeave();

	/*@brief 当父组件发生大小改变时,所有子控件将会收到来自父控件被改变后的大小,
	* 子控件可跟随父控件的大小来进行大小改变(如有需要)
	* @param InSize 参数一 父控件被改变后的大小
	* @return void
	*/
	virtual void OnResize(const FSize& InSize);

	virtual FWidget* FindPointInWidget(const FPoint& InPoint);

	virtual bool PtInRegion(const FPoint& InPoint);

	void ConvertMousePoint(const FPoint& MousePoint, FPoint& OutPoint);
protected:
	FRectU mRect;
	FWidget* mParent;
	u32 bMouseEnter : 1;
	u32 bFocus : 1;
	u32 bVisible : 1;		//可视/隐藏
};




#endif // !__FANTACY_WIDGET_H__

