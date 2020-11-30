
// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "MemMonitor.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()


CMainFrame::CMainFrame() noexcept
{
	m_ms.dwLength = sizeof(m_ms);
	::GlobalMemoryStatusEx(&m_ms);
	m_szText[0] = '\0';
	LPCTSTR lpszClassName = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW,
		// 图标加载
		::LoadCursor(NULL, IDC_ARROW), (HBRUSH)(COLOR_3DFACE + 1), AfxGetApp()->LoadIcon(IDI_ICON1));

	CreateEx(WS_EX_CLIENTEDGE, lpszClassName, TEXT("MemMonitor"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 320, 280, NULL, 0, NULL);
	

	::GetClientRect(m_hWnd, &m_rcInfo);
	m_rcInfo.left = 30;
	m_rcInfo.top = 20;
	m_rcInfo.right = m_rcInfo.right - 30;
	m_rcInfo.bottom = m_rcInfo.bottom - 30;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	::SetTimer(m_hWnd, IDT_TIMER, 1000, NULL);
	// 窗口提到顶层
	::SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOREDRAW | SWP_NOSIZE);

	return 0;
	// 安装定时器
}
void CMainFrame::OnPaint()
{
	// 宽字符处理 https://blog.csdn.net/jolin678/article/details/49364809
	// wcscat，wcslen
	TCHAR szBuff[128];
	m_szText[0] = '\0';

	wsprintf(szBuff, _T("\n  物理内存总量： %6I64d MB"), m_ms.ullTotalPhys / (1024 * 1024));
	wcscat_s(m_szText, szBuff);
	wsprintf(szBuff, _T("\n  可用物理内存：  %6I64d MB"), m_ms.ullAvailPhys / (1024 * 1024));
	wcscat_s(m_szText, szBuff);

	wsprintf(szBuff, _T("\n\n  虚拟内存总量：  %6I64d MB"), m_ms.ullTotalVirtual / (1024 * 1024));
	wcscat_s(m_szText, szBuff);
	wsprintf(szBuff, _T("\n  可用虚拟内存：  %6I64d MB"), m_ms.ullAvailVirtual / (1024 * 1024));
	wcscat_s(m_szText, szBuff);

	wsprintf(szBuff, _T("\n\n  内存使用率：     %d%%"), m_ms.dwMemoryLoad);
	wcscat_s(m_szText, szBuff);

	CPaintDC dc(this);
	dc.SetBkMode(TRANSPARENT);
	CFont font;
	CBrush brush(RGB(0xa0, 0xa0, 0xa0));
	font.CreateFontW(20, 0, 0, 0, FW_HEAVY, 0, 0, 0, ANSI_CHARSET, \
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, \
		VARIABLE_PITCH | FF_SWISS, TEXT("MS Sans Serif"));
	dc.SelectObject(font);
	dc.SelectObject(brush);
	dc.SetTextColor(RGB(0x32, 0x32, 0xfa));
	dc.RoundRect(m_rcInfo.left, m_rcInfo.top, m_rcInfo.right, m_rcInfo.bottom, 5, 5);
	dc.DrawText(m_szText, &m_rcInfo, 0);

}
void CMainFrame::OnTimer(UINT nIDEvent)
{
	if (nIDEvent == IDT_TIMER)
	{
		::GlobalMemoryStatusEx(&m_ms);
		// 无效显示文本的区域，迫使系统发送 WM_PAINT 消息，更新信息
		::InvalidateRect(m_hWnd, &m_rcInfo, TRUE);
	}
}

