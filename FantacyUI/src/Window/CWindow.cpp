#include "Window/CWindow.h"
#include <Windows.h>
#include <windowsx.h>
#include <cstdio>
#include "CApplication.h"

#include "Painter/CPainterDevice.h"

#define WINDOW_CLASSNAME L"MyWindow"

#define WMS_LBUTTONDOWN		0x01
#define WMS_EXITSIZEMOVE	0x02

CWindow::CWindow()
	: m_winId(nullptr)
	, m_rcWindow({200,150,200 + 800,150 + 600})
	, m_rcCaption({ 0, 0, 0, 40 })
	, m_rcSizeBox({5,5,5,5})
	, m_painterDevice(nullptr)
	, m_windowStyle(WindowStyle::SimpleWindow)
	, m_rootWidget(nullptr)
{
	// 1. 定义窗口类
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = __WndProc;             // 窗口过程函数
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = (HINSTANCE)GetModuleHandle(nullptr);             // 应用程序实例句柄
	wcex.hIcon = nullptr; //LoadIcon(NULL, IDI_APPLICATION); // 默认图标
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);   // 默认光标
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // 背景颜色
	wcex.lpszMenuName = NULL;               // 无菜单
	wcex.lpszClassName = WINDOW_CLASSNAME;  // 窗口类名
	wcex.hIconSm = nullptr; // LoadIcon(NULL, IDI_APPLICATION); // 小图标

	// 2. 注册窗口类
	if (!RegisterClassExW(&wcex))
	{
		//Has error
		return;
	}
}

CWindow::~CWindow()
{
	UnregisterClassW(WINDOW_CLASSNAME, (HINSTANCE)GetModuleHandleA(nullptr));
}

u32 ConvertToPlatformStyle(WindowStyle style)
{
	u32 realStyle = WS_OVERLAPPEDWINDOW;
	if (style == WindowStyle::FramelessWindow)
	{
		realStyle = WS_OVERLAPPEDWINDOW;
	}
	else if (style == WindowStyle::PopWindow)
	{
		realStyle = WS_POPUPWINDOW;
	}
	return realStyle;
}

void CWindow::setWindowStyle(WindowStyle style)
{
	m_windowStyle = style;
	if (m_winId)
	{
		SetWindowLongPtr(m_winId, GWL_STYLE, ConvertToPlatformStyle(m_windowStyle));
	}
}

void CWindow::getSize(s32& width, s32& height)
{
	RECT rcWindow;
	GetClientRect(m_winId, &rcWindow);
	width = rcWindow.right - rcWindow.left;
	height = rcWindow.bottom - rcWindow.top;
}

void CWindow::resize(s32 width, s32 height)
{
	if (m_winId)
	{
		::SetWindowPos(m_winId, HWND_NOTOPMOST, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
	}
	else
	{
		m_rcWindow.right = m_rcWindow.left + width;
		m_rcWindow.bottom = m_rcWindow.top + height;
	}
	AdjustWindowRect(&m_rcWindow, ConvertToPlatformStyle(m_windowStyle), FALSE);
}

void CWindow::move(s32 x, s32 y)
{
	s32 width = m_rcWindow.right - m_rcWindow.left;
	s32 height = m_rcWindow.bottom - m_rcWindow.top;
	m_rcWindow.left = x;
	m_rcWindow.top = y;
	m_rcWindow.right = x + width;
	m_rcWindow.bottom = y + height;
	if (m_winId)
	{
		::SetWindowPos(m_winId, HWND_NOTOPMOST, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}
}

void CWindow::show()
{
	if (m_winId)
	{
		::ShowWindow(m_winId, SW_SHOW);
	}
	else
	{
		m_winId = CreateWindowExW(
			0,
			WINDOW_CLASSNAME,           // 窗口类名
			m_title.Str(),           // 窗口标题
			ConvertToPlatformStyle(m_windowStyle),        // 窗口样式
			m_rcWindow.left, m_rcWindow.top, // 位置
			m_rcWindow.right - m_rcWindow.left, m_rcWindow.bottom - m_rcWindow.top,                   // 大小
			NULL,                       // 父窗口
			NULL,                       // 菜单
			(HINSTANCE)GetModuleHandleA(nullptr),                  // 应用程序实例
			reinterpret_cast<void*>(this)                        // 附加数据
		);
		::ShowWindow(m_winId, SW_SHOW);
		::UpdateWindow(m_winId);
	}
}

void CWindow::hide()
{
	if (!m_winId)
	{
		return;
	}
	::ShowWindow(m_winId, SW_HIDE);
}

void CWindow::centerScreen()
{
	s32 screenWidth, screenHeight;
	CApplication::getScreenSize(screenWidth, screenHeight);
	move((screenWidth - (m_rcWindow.right - m_rcWindow.left)) / 2, (screenHeight - (m_rcWindow.bottom - m_rcWindow.top)) / 2);
}

void CWindow::showMinimized()
{
	if (!m_winId)
	{
		return;
	}
	::ShowWindow(m_winId, SW_SHOWMINIMIZED);
}

void CWindow::showMaximized()
{
	if (!m_winId)
	{
		return;
	}
	::ShowWindow(m_winId, SW_SHOWMAXIMIZED);
}

void CWindow::showNormal()
{
	if (!m_winId)
	{
		return;
	}
	::ShowWindow(m_winId, SW_SHOWNORMAL);
}

bool CWindow::isMaximized() const
{
	return ::IsZoomed(m_winId);
}

bool CWindow::isMinimized() const
{
	return ::IsIconic(m_winId);
}

void CWindow::paint()
{
	CPainter painter(this);
	m_rootWidget->prePaint(&painter);
}

void CWindow::onCreate()
{

}

void CWindow::onDestroy()
{
	CApplication::quit();
}

void CWindow::onResize(s32 width, s32 height)
{
	m_rootWidget->resize(width, height);
}

void CWindow::setRoot(CWidget* widget)
{
	m_rootWidget = widget;
	m_rootWidget->setOwner(this);
	m_rootWidget->resize(m_rcWindow.right - m_rcWindow.left, m_rcWindow.bottom - m_rcWindow.top);
}

void CWindow::update()
{
	InvalidateRect(winId(), &m_rcWindow, FALSE);
}

void CWindow::update(const CRect& rect)
{
	RECT reUpdate = { rect.x(), rect.y(), rect.right(), rect.bottom() };
	InvalidateRect(winId(), &reUpdate, FALSE);
}

LRESULT CWindow::nativeMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_ERASEBKGND:
	{
		return TRUE;
	}
	case WM_NCCALCSIZE:
	{
		if (m_windowStyle != WindowStyle::FramelessWindow)
		{
			return ::DefWindowProc(winId(), uMsg, wParam, lParam);
		}
		LPRECT pRect = NULL;
		if (wParam == TRUE)
		{
			LPNCCALCSIZE_PARAMS pParam = (LPNCCALCSIZE_PARAMS)lParam;
			pRect = &pParam->rgrc[0];
		}
		else
		{
			pRect = (LPRECT)lParam;
		}

		if (isMaximized())
		{	// 最大化时，计算当前显示器最适合宽高度
			MONITORINFO oMonitor = {};
			oMonitor.cbSize = sizeof(oMonitor);
			::GetMonitorInfo(::MonitorFromWindow(winId(), MONITOR_DEFAULTTONEAREST), &oMonitor);
			CRect rcWork(oMonitor.rcWork.left, oMonitor.rcWork.top, oMonitor.rcWork.right - oMonitor.rcWork.left, oMonitor.rcWork.bottom - oMonitor.rcWork.top);
			CRect rcMonitor(oMonitor.rcWork.left, oMonitor.rcMonitor.top, oMonitor.rcMonitor.right - oMonitor.rcMonitor.left, oMonitor.rcMonitor.bottom - oMonitor.rcMonitor.top);
			
			rcWork.offset(-oMonitor.rcMonitor.left, -oMonitor.rcMonitor.top);

			pRect->top = pRect->left = 0;
			pRect->right = pRect->left + rcWork.width();
			pRect->bottom = pRect->top + rcWork.height();
			return WVR_REDRAW;
		}

		return 0;
		//return DefWindowProc(m_winId, uMsg, wParam, lParam);
	}
	case WM_NCHITTEST:
	{
		if (m_windowStyle != WindowStyle::FramelessWindow)
		{
			return ::DefWindowProc(winId(), uMsg, wParam, lParam);
		}
		POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
		::ScreenToClient(winId(), &pt);

		RECT rcClient;
		::GetClientRect(winId(), &rcClient);

		if (!isMaximized())
		{
			if (pt.y < rcClient.top + m_rcSizeBox.top)
			{
				if (pt.x < rcClient.left + m_rcSizeBox.left) return HTTOPLEFT;
				if (pt.x > rcClient.right - m_rcSizeBox.right) return HTTOPRIGHT;
				return HTTOP;
			}
			else if (pt.y > rcClient.bottom - m_rcSizeBox.bottom)
			{
				if (pt.x < rcClient.left + m_rcSizeBox.left) return HTBOTTOMLEFT;
				if (pt.x > rcClient.right - m_rcSizeBox.right) return HTBOTTOMRIGHT;
				return HTBOTTOM;
			}

			if (pt.x < rcClient.left + m_rcSizeBox.left) return HTLEFT;
			if (pt.x > rcClient.right - m_rcSizeBox.right) return HTRIGHT;
		}

		if (pt.x >= rcClient.left + m_rcCaption.left && pt.x < rcClient.right - m_rcCaption.right \
			&& pt.y >= m_rcCaption.top && pt.y < m_rcCaption.bottom) {
				return HTCAPTION;
		}

		return HTCLIENT;
	}
	case WM_CREATE:
	{
		m_painterDevice = new CPainterDevice(this);
		onCreate();
		if (!m_rootWidget)
		{
			m_rootWidget = new CWidget();
		}
		break;
	}
	case WM_SIZE:
	{
		//param doc https://learn.microsoft.com/zh-cn/windows/win32/winmsg/wm-size
		m_rcWindow.right = m_rcWindow.left + LOWORD(lParam);
		m_rcWindow.bottom = m_rcWindow.top + HIWORD(lParam);
		onResize(LOWORD(lParam), HIWORD(lParam));
		break;
	}
	case WM_LBUTTONDOWN:
	{
		if (!PostThreadMessageA(GetCurrentThreadId(), (WM_USER + 1000), 0, 0))
		{
			printf("PostThreadMessageA(GetCurrentThreadId(), 100, 0, 0) failed!\n");
		}
		break;
	}
	/*case WM_SYSCOMMAND:
	{
		u32 uCommandType = (wParam & 0xFFF0);
		if (uCommandType == SC_CLOSE)
		{

		}
		return DefWindowProc(m_winId, uMsg, wParam, lParam);
	}*/
	/*case WM_WINDOWPOSCHANGED:
	{
		return DefWindowProc(m_winId, uMsg, wParam, lParam);
	}*/
	case WM_PAINT:
	{
		/*if (g_bInMoveOrSize)
		{
            ValidateRect(m_winId, nullptr);
			return FALSE;
		}*/
		if (m_nState & WMS_LBUTTONDOWN)
		{
			/*if (m_nState & WMS_EXITSIZEMOVE)
			{
				m_painterDevice->beginPaint();
				paint();
				m_painterDevice->endPaint();
			}
			else
			{
				ValidateRect(m_winId, nullptr);
			}*/
			ValidateRect(m_winId, nullptr);
		}
		else
		{
			m_painterDevice->beginPaint();
			paint();
			m_painterDevice->endPaint();
		}
		
		break;
	}
	case WM_NCLBUTTONDOWN:
	{
		if (wParam == HTCAPTION)
		{
			m_nState |= WMS_LBUTTONDOWN;
		}
		//break;
		return DefWindowProc(winId(), uMsg, wParam, lParam);
	}
	case WM_NCLBUTTONUP:
	{
		m_nState &= ~WMS_LBUTTONDOWN;
		InvalidateRect(m_winId, nullptr, TRUE);
		UpdateWindow(m_winId);
		return DefWindowProc(winId(), uMsg, wParam, lParam);
	}
	case WM_SYSCOMMAND:
	{
		LRESULT lr = DefWindowProc(winId(), uMsg, wParam, lParam);//采用默认处理
		u32 uCommandType = (wParam & 0xFFF0);
		if (uCommandType == SC_MOVE)
			PostMessage(winId(), WM_NCLBUTTONUP, HTCAPTION, lParam);   // 发送WM_NCLBUTTONUP消息
		return lr;
	}
	case WM_MOVING:
	{
		//g_bInMoveOrSize = true;
		//printf("WM_MOVE\n");
		return DefWindowProc(winId(), uMsg, wParam, lParam);
	}
	case WM_MOUSEWHEEL:
	{
		//printf("WM_MOUSEWHELL\n");
		return DefWindowProc(winId(), uMsg, wParam, lParam);
	}
	/*case WM_CANCELMODE:
	{
		g_bInMoveOrSize = false;
        InvalidateRect(m_winId, nullptr, TRUE);
        UpdateWindow(m_winId);
		return DefWindowProc(winId(), uMsg, wParam, lParam);
	}*/
	/*case WM_ENTERSIZEMOVE:
	{
		g_bInMoveOrSize = true;
		return DefWindowProc(m_winId, uMsg, wParam, lParam);
	}*/
	case WM_EXITSIZEMOVE:
	{
        m_nState &= ~WMS_LBUTTONDOWN;
		m_nState |= WMS_EXITSIZEMOVE;
		InvalidateRect(m_winId, nullptr, TRUE);
		UpdateWindow(m_winId);
		break;
	}
	case WM_DESTROY:
	{
		onDestroy();
		delete m_painterDevice;
		break;
	}
	default:
		return DefWindowProc(m_winId, uMsg, wParam, lParam);
	}
	return FALSE;
}

LRESULT CWindow::__WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CWindow* pThis = nullptr;
	if (uMsg == WM_NCCREATE)
	{
		LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
		pThis = reinterpret_cast<CWindow*>(lpcs->lpCreateParams);
		pThis->m_winId = hWnd;
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
	}
	else
	{
		pThis = reinterpret_cast<CWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	}
	if (pThis)
	{
		return pThis->nativeMessage(uMsg, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}

