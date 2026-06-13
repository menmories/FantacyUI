#ifndef XM_WINDOW_H
#define XM_WINDOW_H

#include "XMPlatformDef.h"
#include "XMString.h"
#include "Core/XMGeometry.h"

enum WindowStyle
{
	SimpleWindow,
	FramelessWindow,
	PopWindow,
	TransparentWindow,
};


class XMUI_API XMWindow
{
public:
	XMWindow();
	virtual ~XMWindow();

	XMUI_INLINE WINID winId() const
	{
		return m_winId;
	}

	void setTitle(const XMString& title);

	void setWindowStyle(WindowStyle style);

	void getSize(s32& width, s32& height);

	void resize(s32 width, s32 height);

	void move(s32 x, s32 y);

	void setMaxSize(s32 width, s32 height);
	void setMinSize(s32 width, s32 height);

	void show();

	void hide();

	void centerScreen();

	void showMinimized();

	void showMaximized();

	void showNormal();

	bool isMaximized()const;

	bool isMinimized()const;

	virtual void onPaint(class XMPainter* painter);

	virtual void onCreate();

	virtual void onDestroy();

	virtual void onResize(s32 width, s32 height);

	virtual void onMouseMove(const XMPoint& pos);

	void update();
protected:
	virtual LRESULT nativeMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
	void __init();
	void __destroy();
	static LRESULT CALLBACK __WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
	WINID m_winId;
	RECT m_rXMWindow;
	RECT m_rcCaption;
	RECT m_rcSizeBox;
	u8 m_nState = 0;
	WindowStyle m_windowStyle;
	MINMAXINFO m_minMaxInfo;
	bool m_bTracking;
	XMString m_title;


	class XMPainter* m_painter;
};



#endif // !XM_WINDOW_H
