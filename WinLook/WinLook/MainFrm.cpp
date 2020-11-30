
// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "WinLook.h"
#include "MainFrm.h"
#include "CMyButton.h"

#define IDB_CLOSE 10
#define MAX_STRINGS 5

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	m_bCatchMouseDown = FALSE;

	// 加载两个光标
	m_hCursorArrow = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	m_hCursorTarget = AfxGetApp()->LoadCursor(IDC_CURSOR1);

	// 注册窗口类
	LPCTSTR lpszClassName = AfxRegisterWndClass(0, NULL,
		(HBRUSH)(COLOR_3DFACE + 1), AfxGetApp()->LoadIcon(IDI_ICON1));

	// 创建窗口
	CreateEx(0, lpszClassName, TEXT("Windows Looker"),
		WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, 0, NULL);

}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CClientDC dc(this);

	TEXTMETRIC tm;
	// GetTextMetrics函数取得指定设备环境中字符的大小属性 
	::GetTextMetrics(dc, &tm);
	m_cxChar = tm.tmAveCharWidth;
	m_cyChar = tm.tmHeight;
	m_cyLine = tm.tmHeight + tm.tmExternalLeading;

	// 设置窗口左上角正方形区域的位置坐标
	::SetRect(&m_rcMouseDown, 12, 12, 48, 48);

	// 设置标题的起始坐标
	m_ptHeaderOrigin.x = 48 + 6;
	m_ptHeaderOrigin.y = 12 + 4;

	// 设置消息框的位置坐标
	m_rcMsgBoxBorder.left = m_ptHeaderOrigin.x + 8 * m_cxChar;
	m_rcMsgBoxBorder.top = 12;
	m_rcMsgBoxBorder.right = m_rcMsgBoxBorder.left + m_cxChar * 32 + 8;
	m_rcMsgBoxBorder.bottom = m_rcMsgBoxBorder.top + m_cyLine * MAX_STRINGS + 8;
	m_rcMsgBox = m_rcMsgBoxBorder;
	// inflate是膨胀的意思，InflateRect函数使长方形的宽和高增大或缩小一定的数量
	::InflateRect(&m_rcMsgBox, -4, -4);

	// 创建按钮窗口对象
	RECT rcButton = { 12, m_rcMsgBoxBorder.bottom - 18, 64, m_rcMsgBoxBorder.bottom };
	new CMyButton(TEXT("Close"), rcButton, this, IDB_CLOSE);


	// 设置本窗口的大小
	RECT rect;
	::SetRect(&rect, 0, 0, m_rcMsgBoxBorder.right + 12, m_rcMsgBoxBorder.bottom + 12);
	// 上面得到的是窗口客户区的大小，AdjustWindowRect将客户区的大小转化成最终窗口的大小
	::AdjustWindowRect(&rect, GetStyle(), FALSE);
	// 重新设置窗口的大小
	::SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, rect.right - rect.left, rect.bottom - rect.top,
		SWP_NOMOVE | SWP_NOREDRAW);

	// 设置光标形状
	::SetCursor(m_hCursorArrow);
	return 0;
}
void CMainFrame::OnPaint()
{
	CPaintDC dc(this);

	// 画窗口左上角的正方形
	DrawMouseInput(&dc);
	// 画标题
	DrawMsgHeader(&dc);
	// 画消息框。DrawEdge函数绘制指定矩形的边框
	::DrawEdge(dc, &m_rcMsgBoxBorder, EDGE_SUNKEN, BF_RECT);
	DrawMsg(&dc);
}
void CMainFrame::DrawMouseInput(CDC* pDC)
{
	HBRUSH hBrush = ::CreateSolidBrush(::GetSysColor(COLOR_3DFACE));
	HBRUSH hOldBrush = (HBRUSH)pDC->SelectObject(hBrush);
	// 画矩形
	pDC->Rectangle(&m_rcMouseDown);
	pDC->SelectObject(hOldBrush);
	::DeleteObject(hBrush);
}

void CMainFrame::DrawMsgHeader(CDC* pDC)
{
	TCHAR* sz1 = TEXT("Caption:");
	TCHAR* sz2 = TEXT("Class:");
	TCHAR* sz3 = TEXT("Handle:");
	TCHAR* sz4 = TEXT("Name:");
	//  字符背景
	::SetBkColor(*pDC, ::GetSysColor(COLOR_3DFACE));

	pDC->TextOut(m_ptHeaderOrigin.x, m_ptHeaderOrigin.y, sz1, wcslen(sz1));
	pDC->TextOut(m_ptHeaderOrigin.x, m_ptHeaderOrigin.y + m_cyLine * 1, sz2, wcslen(sz2));
	pDC->TextOut(m_ptHeaderOrigin.x, m_ptHeaderOrigin.y + m_cyLine * 2, sz3, wcslen(sz3));
	pDC->TextOut(m_ptHeaderOrigin.x, m_ptHeaderOrigin.y + m_cyLine * 3, sz4, wcslen(sz4));
}

void CMainFrame::DrawMsg(CDC* pDC)
{
	int xPos = m_rcMsgBox.left;
	int yPos = m_rcMsgBox.top;
	TCHAR sz[32];
	wsprintf(sz, TEXT("0X%0X"), (int)m_wndInfo.m_hWnd);

	::SetBkColor(*pDC, ::GetSysColor(COLOR_3DFACE));

	pDC->TextOut(xPos, yPos, m_wndInfo.m_szWindowCaption, wcslen(m_wndInfo.m_szWindowCaption));
	pDC->TextOut(xPos, yPos + m_cyLine * 1, m_wndInfo.m_szWindowClass, wcslen(m_wndInfo.m_szWindowClass) < 33 ? wcslen(m_wndInfo.m_szWindowClass) : 30);
	pDC->TextOut(xPos, yPos + m_cyLine * 2, sz, wcslen(sz));
	pDC->TextOut(xPos, yPos + m_cyLine * 3, m_wndInfo.m_szExeFile, wcslen(m_wndInfo.m_szExeFile));
}
void CMainFrame::OnLButtonDown(UINT nFlags, CPoint point)
{
	// PtInRect函数用于判断point的位置是否在m_rcMouseDown指定的矩形区域中
	if (!m_bCatchMouseDown && ::PtInRect(&m_rcMouseDown, point))
	{
		// 在的话就更换光标形状，捕获鼠标输入，设置标志信息
		m_wndInfo.m_hWnd = NULL;
		::SetCursor(m_hCursorTarget);
		::SetCapture(m_hWnd);
		m_bCatchMouseDown = TRUE;
	}
}

void CMainFrame::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bCatchMouseDown)
	{
		// 恢复光标状态，释放捕获的鼠标输入，擦除目标窗口的矩形框架
		::SetCursor(m_hCursorArrow);
		::ReleaseCapture();
		m_bCatchMouseDown = FALSE;
		if (m_wndInfo.m_hWnd != NULL)
			m_wndInfo.EraseFrame();
	}
}

void CMainFrame::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bCatchMouseDown)
	{
		// 将客户区坐标转换为屏幕坐标
		::ClientToScreen(m_hWnd, &point);
		// 取得鼠标所在处的窗口的句柄
		HWND hWnd = ::WindowFromPoint(point);
		if (hWnd == m_wndInfo.m_hWnd)
			return;

		// 擦除前一个窗口上的红色框架，取得新的目标窗口的信息，绘制框架
		m_wndInfo.EraseFrame();
		m_wndInfo.GetInfo(hWnd);
		m_wndInfo.DrawFrame();

		// 通过无效显示区域，使窗口客户区重画
		::InvalidateRect(m_hWnd, &m_rcMsgBox, TRUE);
	}
}

void CMainFrame::PostNcDestroy()
{
	delete this;
}

BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (LOWORD(wParam) == IDB_CLOSE)
	{
		DestroyWindow();
		return TRUE;	// 返回TRUE说明此消息已经处理，阻止CWnd类继续处理
	}

	return FALSE;
}