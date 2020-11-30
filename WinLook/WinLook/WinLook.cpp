
// WinLook.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "WinLook.h"
#include "MainFrm.h"
#include <tlhelp32.h>

BEGIN_MESSAGE_MAP(CWinLookApp, CWinApp)
END_MESSAGE_MAP()

CWinLookApp theApp;

BOOL CWinLookApp::InitInstance()
{
	m_pMainWnd = new CMainFrame;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}
CWindowInfo::CWindowInfo()
{
	m_hWnd = NULL;
}

void CWindowInfo::GetInfo(HWND hWnd)
{
	// 取得句柄、标题、类名
	m_hWnd = hWnd;
	::GetWindowText(m_hWnd, m_szWindowCaption, BUFFER_SIZE);
	::GetClassName(m_hWnd, m_szWindowClass, BUFFER_SIZE);

	// 取得磁盘上.exe文件的名称
	m_szExeFile[0] = '\0';
	DWORD nPID;
	// 取得包含窗口的进程的ID号
	::GetWindowThreadProcessId(m_hWnd, &nPID);
	// 给系统中的所有进程拍一个快照，查找ID号为nPID的进程的信息
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, nPID);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
		return;
	// 开始查找
	BOOL bFind = FALSE;
	PROCESSENTRY32 pe32 = { sizeof(pe32) };
	if (::Process32First(hProcessSnap, &pe32))
	{
		do
		{
			if (pe32.th32ProcessID == nPID)
			{
				bFind = TRUE;
				break;
			}
		} while (::Process32Next(hProcessSnap, &pe32));
	}
	::CloseHandle(hProcessSnap);
	// 只保存文件名结构中文件的名称（不包括目录）
	if (bFind)
	{
		TCHAR* pszExeFile = wcsrchr(pe32.szExeFile, TEXT('\\'));
		if (pszExeFile == NULL)
			pszExeFile = pe32.szExeFile;
		else
			pszExeFile++;
		wcscpy_s(m_szExeFile, pszExeFile);
	}
}

void CWindowInfo::DrawFrame()
{
	// 目标窗口的设备环境句柄
	HDC hdc = ::GetWindowDC(m_hWnd);
	// 目标窗口外框的大小
	RECT rcFrame;
	::GetWindowRect(m_hWnd, &rcFrame);
	int nWidth = rcFrame.right - rcFrame.left;
	int nHeight = rcFrame.bottom - rcFrame.top;

	// 用红色笔画沿外框四周画线
	HPEN hPen = ::CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	HPEN hOldPen = (HPEN)::SelectObject(hdc, hPen);

	::MoveToEx(hdc, 0, 0, NULL);
	::LineTo(hdc, nWidth, 0);
	::LineTo(hdc, nWidth, nHeight);
	::LineTo(hdc, 0, nHeight);
	::LineTo(hdc, 0, 0);

	::SelectObject(hdc, hOldPen);
	::DeleteObject(hPen);
	::ReleaseDC(m_hWnd, hdc);
}

void CWindowInfo::EraseFrame()
{
	// 重画本窗口的非客户区部分（RDW_FRAME、RDW_INVALIDATE标记），
	// 立即更新（RDW_UPDATENOW标记）
	::RedrawWindow(m_hWnd, NULL, NULL,
		RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW);

	HWND hWndParent = ::GetParent(m_hWnd);
	if (::IsWindow(hWndParent))
	{
		// 重画父窗口的整个客户区（RDW_ERASE、RDW_INVALIDATE标记），
		// 立即更新（RDW_UPDATENOW标记）， 包括所有子窗口（RDW_ALLCHILDREN标记）
		::RedrawWindow(hWndParent, NULL, NULL,
			RDW_ERASE | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);
	}
}


