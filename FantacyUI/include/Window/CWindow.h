#ifndef CWINDOW_H
#define CWINDOW_H


#include "PlatformDef.h"
#include "Core/FaString.h"
#include "Painter/CPainter.h"
#include "Widgets/CWidget.h"

enum WindowStyle
{
	SimpleWindow,
	FramelessWindow,
	PopWindow,
	TransparentWindow,
};

class CRect;
class CWidget;
class CPainter;
class CPainterDevice;
class FANTACY_API CWindow
{
public:
	CWindow();
	~CWindow();

	FANTACY_INLINE WINID winId() const
	{
		return m_winId;
	}

	FANTACY_INLINE void setTitle(const FaString& title)
	{
		m_title = title;
	}

	void setWindowStyle(WindowStyle style);

	void getSize(s32& width, s32& height);

	void resize(s32 width, s32 height);

	void move(s32 x, s32 y);

	void show();

	void hide();

	void centerScreen();

	void showMinimized();

	void showMaximized();

	void showNormal();

	bool isMaximized()const;

	bool isMinimized()const;

	__forceinline CPainterDevice* painterDevice(){return m_painterDevice;}

	virtual void paint();

	virtual void onCreate();

	virtual void onDestroy();

	virtual void onResize(s32 width, s32 height);

	void setRoot(CWidget* widget);

	void update();
	void update(const CRect& rect);
protected:
	virtual LRESULT nativeMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
	static LRESULT CALLBACK __WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
	WINID m_winId;
	FaString m_title;
	RECT m_rcWindow;
	RECT m_rcCaption;
	RECT m_rcSizeBox;
	CPainterDevice* m_painterDevice;
	u8 m_nState = 0;
	WindowStyle m_windowStyle;
	CWidget* m_rootWidget;
};



#endif // !CWINDOW_H
