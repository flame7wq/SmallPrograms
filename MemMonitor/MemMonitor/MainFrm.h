
// MainFrm.h: CMainFrame 类的接口
//

#pragma once

class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame() noexcept;
protected: 
	DECLARE_DYNAMIC(CMainFrame)

protected:
	TCHAR m_szText[1024];
	RECT m_rcInfo;
	MEMORYSTATUSEX m_ms;
	// 生成的消息映射函数
protected:
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()

};


