#pragma once
#include "PrintView.h"

// CPrintFrame 框架

#define	WM_MY_PRINT				(WM_USER+1003)
#define	WM_BEGIN_PRINTING		(WM_USER+1004)
#define	WM_END_PRINTING			(WM_USER+1005)
#define WM_MODAL_PRINT			(WM_USER+1006)


class CPrintFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CPrintFrame)
public:
	CPrintFrame();           // 动态创建所使用的受保护的构造函数
	virtual ~CPrintFrame();
public:
	CPrintView	*m_p_view;
	CDialog		*m_p_caller_dlg;
	CWnd		*m_p_wnd;
protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	afx_msg void OnDestroy();
	afx_msg void OnClose();
public:
	BOOL Create( CString window_text, CDialog* callback_window,BOOL b_preview = FALSE );
private:
	virtual BOOL Create(
		LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName,
		DWORD dwStyle = WS_OVERLAPPEDWINDOW,
		const RECT& rect = rectDefault,
		CWnd* pParentWnd = NULL,
		LPCTSTR lpszMenuName = NULL,
		DWORD dwExStyle = 0,
		CCreateContext* pContext = NULL 
		)
	{
		return CFrameWnd::Create(lpszClassName,lpszWindowName,dwStyle,rect,pParentWnd,lpszMenuName,dwExStyle,pContext);
	}

public:
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};


