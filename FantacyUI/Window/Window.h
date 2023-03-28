#ifndef __FANTACY_WINDOW_H__
#define __FANTACY_WINDOW_H__
#include "WindowBase.h"
#include "Widget/WindowAttacher.h"

class FCanvas;
class FANTACY_API FWindow : public FWindowBase
{
public:
	FWindow();

	void AddWidget(FWidget* Widget);
protected:
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)override;

	/*用于构建UI*/
	virtual void ConstructUI() {};

	virtual void OnPaint(FCanvas* Canvas);

	virtual void OnResize(s32 Width, s32 Height);

	virtual void OnMouseMove(const FPoint& MousePoint);

	virtual void OnMouseWheel(short zDelta);

	virtual void OnMouseEnter(const FPoint& MousePoint);

	virtual void OnMouseLeave();

	/*用于销毁各类资源*/
	virtual void OnDestroy();

private:
	FCanvas* mCanvas;
	FWindowAttacher* mWindowAttacher;
};

#endif	//__FANTACY_WINDOW_H__
