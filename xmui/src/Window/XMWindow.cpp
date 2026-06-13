#include "Window/XMWindow.h"
#include <Windows.h>
#include <windowsx.h>
#include <cstdio>
#include "XMApplication.h"
#include "Core/XMPainter.h"
#include "Core/XMPaintDevice.h"


#define WINDOW_CLASSNAME TEXT("MyWindow")

#define WMS_LBUTTONDOWN		0x01
#define WMS_EXITSIZEMOVE	0x02
#define WMS_WINDOWRESTORED	0x04

XMWindow::XMWindow()
	: m_winId(nullptr)
	, m_rXMWindow({ 200,150,200 + 800,150 + 600 })
	, m_rcCaption({ 0, 0, 0, 40 })
	, m_rcSizeBox({ 5,5,5,5 })
	, m_windowStyle(WindowStyle::SimpleWindow)
	, m_bTracking(false)
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
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);   // 默认光标
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // 背景颜色
	wcex.lpszMenuName = nullptr;               // 无菜单
	wcex.lpszClassName = WINDOW_CLASSNAME;  // 窗口类名
	wcex.hIconSm = nullptr; // LoadIcon(NULL, IDI_APPLICATION); // 小图标

	// 2. 注册窗口类
	if (!RegisterClassEx(&wcex))
	{
		//Has error
		return;
	}

	memset(&m_minMaxInfo, 0, sizeof(MINMAXINFO));
	m_minMaxInfo.ptMinTrackSize.x = 200;m_minMaxInfo.ptMinTrackSize.y = 300;
	m_minMaxInfo.ptMaxTrackSize.x = 65535; m_minMaxInfo.ptMaxTrackSize.y = 65535;
}

XMWindow::~XMWindow()
{
	UnregisterClass(WINDOW_CLASSNAME, (HINSTANCE)GetModuleHandleA(nullptr));
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

void XMWindow::setWindowStyle(WindowStyle style)
{
	m_windowStyle = style;
	if (m_winId)
	{
		SetWindowLongPtrW(m_winId, GWL_STYLE, ConvertToPlatformStyle(m_windowStyle));
	}
}

void XMWindow::getSize(s32& width, s32& height)
{
	RECT rXMWindow;
	GetClientRect(m_winId, &rXMWindow);
	width = rXMWindow.right - rXMWindow.left;
	height = rXMWindow.bottom - rXMWindow.top;
}

void XMWindow::resize(s32 width, s32 height)
{
	if (m_winId)
	{
		::SetWindowPos(m_winId, HWND_NOTOPMOST, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
	}
	else
	{
		m_rXMWindow.right = m_rXMWindow.left + width;
		m_rXMWindow.bottom = m_rXMWindow.top + height;
	}
	AdjustWindowRect(&m_rXMWindow, ConvertToPlatformStyle(m_windowStyle), FALSE);
}

void XMWindow::move(s32 x, s32 y)
{
	s32 width = m_rXMWindow.right - m_rXMWindow.left;
	s32 height = m_rXMWindow.bottom - m_rXMWindow.top;
	m_rXMWindow.left = x;
	m_rXMWindow.top = y;
	m_rXMWindow.right = x + width;
	m_rXMWindow.bottom = y + height;
	if (m_winId)
	{
		::SetWindowPos(m_winId, HWND_NOTOPMOST, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}
}

void XMWindow::setMaxSize(s32 width, s32 height)
{
	m_minMaxInfo.ptMaxTrackSize.x = width;
	m_minMaxInfo.ptMaxTrackSize.y = height;
}

void XMWindow::setMinSize(s32 width, s32 height)
{
	m_minMaxInfo.ptMinTrackSize.x = width;
	m_minMaxInfo.ptMinTrackSize.y = height;
}

void XMWindow::show()
{
	if (m_winId)
	{
		::ShowWindow(m_winId, SW_SHOW);
	}
	else
	{
		//wprintf(L"title=%s\n", m_title.Str());
		m_winId = CreateWindowEx(
			0,
			WINDOW_CLASSNAME,           // 窗口类名
			m_title.Str(),           // 窗口标题
			ConvertToPlatformStyle(m_windowStyle),        // 窗口样式
			m_rXMWindow.left, m_rXMWindow.top, // 位置
			m_rXMWindow.right - m_rXMWindow.left, m_rXMWindow.bottom - m_rXMWindow.top,                   // 大小
			nullptr,                       // 父窗口
			nullptr,                       // 菜单
			(HINSTANCE)GetModuleHandleA(nullptr),                  // 应用程序实例
			reinterpret_cast<void*>(this)                        // 附加数据
		);
		::ShowWindow(m_winId, SW_SHOW);
		::UpdateWindow(m_winId);
	}
}

void XMWindow::hide()
{
	if (!m_winId)
	{
		return;
	}
	::ShowWindow(m_winId, SW_HIDE);
}

void XMWindow::centerScreen()
{
	s32 screenWidth, screenHeight;
	XMApplication::getScreenSize(screenWidth, screenHeight);
	move((screenWidth - (m_rXMWindow.right - m_rXMWindow.left)) / 2, (screenHeight - (m_rXMWindow.bottom - m_rXMWindow.top)) / 2);
}

void XMWindow::showMinimized()
{
	if (!m_winId)
	{
		return;
	}
	::ShowWindow(m_winId, SW_SHOWMINIMIZED);
}

void XMWindow::showMaximized()
{
	if (!m_winId)
	{
		return;
	}
	::ShowWindow(m_winId, SW_SHOWMAXIMIZED);
}

void XMWindow::showNormal()
{
	if (!m_winId)
	{
		return;
	}
	::ShowWindow(m_winId, SW_SHOWNORMAL);
}

bool XMWindow::isMaximized() const
{
	return ::IsZoomed(m_winId);
}

bool XMWindow::isMinimized() const
{
	return ::IsIconic(m_winId);
}

void XMWindow::onPaint(XMPainter* painter)
{

}


void XMWindow::onCreate()
{
	
}

void XMWindow::onDestroy()
{
	
}

void XMWindow::onResize(s32 width, s32 height)
{

}

void XMWindow::onMouseMove(const XMPoint& pos)
{
	
}

void XMWindow::__init()
{
	m_painter = XMPaintDevice::newPainter(this);
	XMPaintDevice::makeCurrent(m_painter);
}

void XMWindow::__destroy()
{
	XMPaintDevice::makeCurrent(nullptr);
	m_painter->release();
	m_painter = nullptr;
	XMApplication::quit();
}

void XMWindow::update()
{
	InvalidateRect(winId(), &m_rXMWindow, FALSE);
}

LRESULT XMWindow::nativeMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_ERASEBKGND:
		{
			return TRUE;
		}
		//case WM_NCCALCSIZE:
		//{
		//	if (m_windowStyle != WindowStyle::FramelessWindow)
		//	{
		//		return ::DefWindowProc(winId(), uMsg, wParam, lParam);
		//	}
		//	LPRECT pRect = NULL;
		//	if (wParam == TRUE)
		//	{
		//		LPNCCALCSIZE_PARAMS pParam = (LPNCCALCSIZE_PARAMS)lParam;
		//		pRect = &pParam->rgrc[0];
		//	}
		//	else
		//	{
		//		pRect = (LPRECT)lParam;
		//	}

		//	if (isMaximized())
		//	{	// 最大化时，计算当前显示器最适合宽高度
		//		MONITORINFO oMonitor = {};
		//		oMonitor.cbSize = sizeof(oMonitor);
		//		::GetMonitorInfo(::MonitorFromWindow(winId(), MONITOR_DEFAULTTONEAREST), &oMonitor);
		//		CRect rcWork(oMonitor.rcWork.left, oMonitor.rcWork.top, oMonitor.rcWork.right - oMonitor.rcWork.left, oMonitor.rcWork.bottom - oMonitor.rcWork.top);
		//		CRect rcMonitor(oMonitor.rcWork.left, oMonitor.rcMonitor.top, oMonitor.rcMonitor.right - oMonitor.rcMonitor.left, oMonitor.rcMonitor.bottom - oMonitor.rcMonitor.top);

		//		rcWork.offset(-oMonitor.rcMonitor.left, -oMonitor.rcMonitor.top);

		//		pRect->top = pRect->left = 0;
		//		pRect->right = pRect->left + rcWork.width();
		//		pRect->bottom = pRect->top + rcWork.height();
		//		return WVR_REDRAW;
		//	}

		//	return 0;
		//	//return DefWindowProc(m_winId, uMsg, wParam, lParam);
		//}
		/*case WM_NCHITTEST:
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
		}*/
		case WM_CREATE:
		{
			__init();
			onCreate();
			if (!m_bTracking)
			{
				TRACKMOUSEEVENT tme = { 0 };
				tme.cbSize = sizeof(TRACKMOUSEEVENT);
				tme.dwFlags = TME_LEAVE | TME_HOVER;  // 监听离开+悬停
				tme.hwndTrack = this->winId();
				tme.dwHoverTime = HOVER_DEFAULT;     // 系统默认悬停时间

				TrackMouseEvent(&tme);
				m_bTracking = true;
			}
			break;
		}
		case WM_SIZE:
		{
			//param doc https://learn.microsoft.com/zh-cn/windows/win32/winmsg/wm-size
			int width = GET_X_LPARAM(lParam);
			int height = GET_Y_LPARAM(lParam);
			GetWindowRect(m_winId, &m_rXMWindow);
			m_painter->resize(width, height);
			onResize(width, height);
			if (wParam == SIZE_RESTORED)
			{
				m_nState |= WMS_WINDOWRESTORED;
				InvalidateRect(winId(), nullptr, TRUE);
			}
			break;
		}
		case WM_MOUSEHOVER:
		{
			break;
		}
		case WM_MOUSELEAVE:
		{
			m_bTracking = false;
			break;
		}
		case WM_GETMINMAXINFO:
		{
			MINMAXINFO* minMaxInfo = (MINMAXINFO*)lParam;
			minMaxInfo->ptMaxTrackSize.x = m_minMaxInfo.ptMaxTrackSize.x;
			minMaxInfo->ptMaxTrackSize.y = m_minMaxInfo.ptMaxTrackSize.y;
			minMaxInfo->ptMinTrackSize.x = m_minMaxInfo.ptMinTrackSize.x;
			minMaxInfo->ptMinTrackSize.y = m_minMaxInfo.ptMinTrackSize.y;
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
			m_painter->beginDraw();
			onPaint(m_painter);
			m_painter->endDraw();

			/*if (g_bInMoveOrSize)
			{
	            ValidateRect(m_winId, nullptr);
				return FALSE;
			}*/
			//if (m_nState & WMS_LBUTTONDOWN && !(m_nState & WMS_WINDOWRESTORED))
			//{
			//	/*if (m_nState & WMS_EXITSIZEMOVE)
			//	{
			//		m_painterDevice->beginPaint();
			//		paint();
			//		m_painterDevice->endPaint();
			//	}
			//	else
			//	{
			//		ValidateRect(m_winId, nullptr);
			//	}*/
			//	ValidateRect(m_winId, nullptr);
			//}
			//else
			//{
			//	onPaint(m_painter);
			//	m_nState &= ~WMS_WINDOWRESTORED;
			//}
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
		case WM_MOUSEMOVE:
		{
			XMPoint point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

			break;
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
			__destroy();
			break;
		}
		default:
		{
			return DefWindowProc(m_winId, uMsg, wParam, lParam);
		}
	}
	return FALSE;
}

LRESULT XMWindow::__WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	XMWindow* pThis = nullptr;
	if (uMsg == WM_NCCREATE)
	{
		LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
		pThis = reinterpret_cast<XMWindow*>(lpcs->lpCreateParams);
		pThis->m_winId = hWnd;
		SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
	}
	else
	{
		pThis = reinterpret_cast<XMWindow*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
	}
	if (pThis)
	{
		return pThis->nativeMessage(uMsg, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void XMWindow::setTitle(const XMString& title)
{
	if (m_winId)
	{
		SetWindowTextW(m_winId, title.Str());
	}
	m_title = title;
}

