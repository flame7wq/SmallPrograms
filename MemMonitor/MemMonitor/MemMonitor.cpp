
// MemMonitor.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "MemMonitor.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMemMonitorApp

BEGIN_MESSAGE_MAP(CMemMonitorApp, CWinApp)
END_MESSAGE_MAP()


// CMemMonitorApp 构造

// 唯一的 CMemMonitorApp 对象

CMemMonitorApp theApp;


// CMemMonitorApp 初始化

BOOL CMemMonitorApp::InitInstance()
{
	CFrameWnd* pFrame = new CMainFrame;
	if (!pFrame)
	{
		delete pFrame;
		return FALSE;
	}
	m_pMainWnd = pFrame;
	// 创建并加载框架及其资源

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}