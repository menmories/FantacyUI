
#ifndef __FANTACY_WINDOWBASE_H__
#define __FANTACY_WINDOWBASE_H__

#include "Base/String.h"


class FANTACY_API IWindow
{
public:
	virtual ~IWindow() {}

	virtual u64 GetWindowId()const = 0;

	virtual void SetText(const FString& Text) = 0;

	virtual void SetPos(s32 X, s32 Y) = 0;

	virtual void GetPos() = 0;

	virtual void GetSize() = 0;

	virtual void SetSize(s32 Width, s32 Height) = 0;

	virtual void Show() = 0;

	virtual void ShowHide() = 0;

	virtual void ShowMinimized() = 0;

	virtual void ShowMaximized() = 0;

	virtual s32 ShowModel() = 0;

	virtual void Destroy() = 0;
};


class FANTACY_API FWindowBase : public IWindow
{
public:
	FWindowBase();

	void CenterScreen();

	virtual u64 GetWindowId()const;

	virtual void SetText(const FString& Text);

	virtual void SetPos(s32 X, s32 Y);

	virtual void GetPos() {};

	virtual void GetSize() {};

	virtual void SetSize(s32 Width, s32 Height);

	virtual void Show();

	virtual void ShowHide();

	virtual void ShowMinimized();

	virtual void ShowMaximized();

	virtual s32 ShowModel();

	virtual void Destroy();
protected:
	virtual void SetupUI();

	virtual LPCTSTR GetClassName()const;

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	static LRESULT __WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	bool __RegisterWindowClass();
	bool Create(const LPCTSTR caption = TEXT(""), int x = 300, int y = 200, int width = 1024, int height = 768, IWindow* parent = nullptr);
private:
	u64 mWindowId;
};


#endif // !__FANTACY_WINDOWBASE_H__

