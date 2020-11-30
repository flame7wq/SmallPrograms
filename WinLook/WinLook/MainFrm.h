
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
	int m_cxChar;	// 字符的平均宽度
	int m_cyChar;	// 字符的高
	int m_cyLine;	// 一行字符占用的空间的垂直长度

	HCURSOR m_hCursorArrow;		// 通常模式下使用的光标句柄（箭头光标）
	HCURSOR m_hCursorTarget;	// 用户选定窗口时使用的光标句柄（自定义光标）

	RECT m_rcMouseDown;		// 接受鼠标下按的方框的位置坐标
	RECT m_rcMsgBoxBorder;		// 消息框边框的位置坐标
	RECT m_rcMsgBox;		// 消息框的位置坐标
	CPoint m_ptHeaderOrigin;	// 绘制标题的起始位置

	BOOL m_bCatchMouseDown;		// 是否捕捉到鼠标下按事件
	CWindowInfo m_wndInfo;		// 一个目标窗口对象

// 生成的消息映射函数
protected:
	void DrawMouseInput(CDC* pDC);
	void DrawMsg(CDC* pDC);
	void DrawMsgHeader(CDC* pDC);
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void PostNcDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()

};


