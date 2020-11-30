#pragma once
#ifndef CMyButton_H
#define CMyButton_H


#include <afxwin.h>
class CMyButton :
    public CWnd
{
public:
	CMyButton(LPCTSTR lpszText, const RECT& rect, CWnd* pParentWnd, UINT nID);
protected:
	TCHAR m_szText[256];	// 按钮显示的文本
	BOOL m_bIsDown;		// 指示用户是否按下鼠标左键

	virtual void PostNcDestroy();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
};

#endif // !CMyButton_H

