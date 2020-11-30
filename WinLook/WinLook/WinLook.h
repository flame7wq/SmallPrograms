
// WinLook.h: WinLook 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"
#define BUFFER_SIZE 256

class CWinLookApp : public CWinApp
{
// 重写
public:
	virtual BOOL InitInstance();

// 实现
public:
	DECLARE_MESSAGE_MAP()
};

extern CWinLookApp theApp;

class CWindowInfo
{
public:
	CWindowInfo();
	// 更新数据
	void GetInfo(HWND hWnd);
	// 绘制矩形外框
	void DrawFrame();
	// 擦除矩形外框
	void EraseFrame();

	HWND m_hWnd;
	TCHAR m_szWindowCaption[BUFFER_SIZE];
	TCHAR m_szWindowClass[BUFFER_SIZE];
	TCHAR m_szExeFile[MAX_PATH];
};
