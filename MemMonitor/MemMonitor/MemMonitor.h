
// MemMonitor.h: MemMonitor 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"       // 主符号


// CMemMonitorApp:
// 有关此类的实现，请参阅 MemMonitor.cpp
//

class CMemMonitorApp : public CWinApp
{
public:
	virtual BOOL InitInstance();

public:
	DECLARE_MESSAGE_MAP()
};

extern CMemMonitorApp theApp;
