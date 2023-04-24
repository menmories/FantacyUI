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

	/*@brief �������������С�ı�ʱ,�����ӿؼ������յ����Ը��ؼ����ı��Ĵ�С,
	* �ӿؼ��ɸ��游�ؼ��Ĵ�С�����д�С�ı�(������Ҫ)
	* @param InSize ����һ ���ؼ����ı��Ĵ�С
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
	u32 bVisible : 1;		//����/����
};




#endif // !__FANTACY_WIDGET_H__

