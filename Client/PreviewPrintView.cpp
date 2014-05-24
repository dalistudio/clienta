// PreviewPrintView.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDlg.h"
#include "PreviewPrintView.h"
#include "PrintFrame.h"


// CPreviewPrintView

IMPLEMENT_DYNCREATE(CPreviewPrintView, CPreviewView)

CPreviewPrintView::CPreviewPrintView()
{

}

CPreviewPrintView::~CPreviewPrintView()
{
}

BEGIN_MESSAGE_MAP(CPreviewPrintView, CPreviewView)
	ON_COMMAND(AFX_ID_PREVIEW_CLOSE, &CPreviewPrintView::OnPreviewClose)
	ON_COMMAND(AFX_ID_PREVIEW_PRINT, &CPreviewPrintView::OnPreviewPrint)
END_MESSAGE_MAP()


// CPreviewPrintView 绘图

void CPreviewPrintView::OnDraw(CDC* pDC)
{
	CPreviewView::OnDraw(pDC);
	m_pToolBar->PostMessage(WM_IDLEUPDATECMDUI, (WPARAM)TRUE);
	// TODO: 在此添加绘制代码
}


// CPreviewPrintView 诊断

#ifdef _DEBUG
void CPreviewPrintView::AssertValid() const
{
	CPreviewView::AssertValid();
}

#ifndef _WIN32_WCE
void CPreviewPrintView::Dump(CDumpContext& dc) const
{
	CPreviewView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPreviewPrintView 消息处理程序

void CPreviewPrintView::OnPreviewClose()
{
	CPrintFrame* pf=(CPrintFrame*)::AfxGetMainWnd();
	pf->PostMessage(WM_CLOSE,0,0);
}
void CPreviewPrintView::OnPreviewPrint()
{
	CPrintFrame* pf=(CPrintFrame*)::AfxGetMainWnd();
	pf->PostMessage(WM_MODAL_PRINT,0,0);
	OnPreviewClose();               // force close of Preview
}