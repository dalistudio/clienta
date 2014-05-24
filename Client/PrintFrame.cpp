// PrintFrame.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ClientDlg.h"
#include "PrintFrame.h"


// CPrintFrame

IMPLEMENT_DYNCREATE(CPrintFrame, CFrameWnd)

CPrintFrame::CPrintFrame()
{
	m_p_caller_dlg = NULL;
	m_p_wnd = AfxGetApp()->m_pMainWnd;
	AfxGetApp()->m_pMainWnd = this;
}

CPrintFrame::~CPrintFrame()
{
}


BEGIN_MESSAGE_MAP(CPrintFrame, CFrameWnd)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_WM_NCLBUTTONDBLCLK()
END_MESSAGE_MAP()


// CPrintFrame ��Ϣ�������

BOOL CPrintFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���
	m_p_view = new CPrintView();
	m_p_view->Create(NULL,NULL,WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,AFX_IDW_PANE_FIRST,pContext);
	return CFrameWnd::OnCreateClient(lpcs, pContext);
}

void CPrintFrame::OnDestroy()
{
	CFrameWnd::OnDestroy();
	AfxGetApp()->m_pMainWnd = m_p_wnd;
}


void CPrintFrame::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CPrintFrame::DestroyWindow();
}

BOOL CPrintFrame::Create( CString window_text, CDialog* callback_window,BOOL b_preview )
{
	ASSERT( callback_window );
	m_p_caller_dlg = callback_window;
	BOOL res = this->Create(NULL,window_text,WS_CAPTION|WS_SYSMENU|WS_THICKFRAME|WS_MINIMIZEBOX|WS_MAXIMIZEBOX,CRect(0,0,0,0));
	//���ô��ڵĴ�С
	CRect rect;
	this->GetDesktopWindow()->GetWindowRect(&rect);
	rect.DeflateRect(100,100);
	this->MoveWindow(&rect);

	if( b_preview )
	{
		this->m_p_view->OnMyPrintPreview(this);
	}
	else
	{
		//this->m_p_view->OnMyPrint();
	}
	return res;
}
void CPrintFrame::OnNcLButtonDblClk(UINT nHitTest, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CFrameWnd::OnNcLButtonDblClk(nHitTest, point);
}

LRESULT CPrintFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ����ר�ô����/����û���
	if( WM_MODAL_PRINT == message )
	{
		m_p_caller_dlg->PostMessage(WM_MODAL_PRINT,0,0);
	}
	return CFrameWnd::WindowProc(message, wParam, lParam);
}
