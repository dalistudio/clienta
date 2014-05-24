// PrintView.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDlg.h"
#include "PrintView.h"
#include "PrintFrame.h"
#include "PreviewPrintView.h"
#include "PrintFrame.h"

BOOL CALLBACK _AfxMyPreviewCloseProc(CFrameWnd* pFrameWnd);
// CPrintView

IMPLEMENT_DYNCREATE(CPrintView, CScrollView)

CPrintView::CPrintView()
{

}

CPrintView::~CPrintView()
{
}

BEGIN_MESSAGE_MAP(CPrintView, CScrollView)
	ON_COMMAND(ID_FILE_PRINT,&CPrintView::OnMyPrint)
END_MESSAGE_MAP()


// CPrintView 绘图

void CPrintView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
}


// CPrintView 诊断

#ifdef _DEBUG
void CPrintView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CPrintView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPrintView 消息处理程序
void CPrintView::OnMyPrint()
{
	//GetParent()->ShowWindow(SW_SHOWMINIMIZED);
	//CScrollView::OnFilePrint();
	m_pFrameWnd->PostMessage(WM_MODAL_PRINT,0,0);

}
void CPrintView::OnMyPrintPreview(CPrintFrame* pf)
{
	GetParent()->ShowWindow(SW_SHOWMAXIMIZED);
	OnFilePrintPreview(pf);
}
BOOL CPrintView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	if(DoPreparePrinting(pInfo))
		return TRUE;
	else
	{
		GetParent()->DestroyWindow();
		return FALSE;
	}
}

BOOL CALLBACK _AfxMyPreviewCloseProc(CFrameWnd* pFrameWnd)
{
	ASSERT_VALID(pFrameWnd);

	CPreviewPrintView* pView = (CPreviewPrintView*) pFrameWnd->GetDlgItem(AFX_IDW_PANE_FIRST);
	ASSERT_KINDOF(CPreviewView, pView);

	pView->OnPreviewClose();
	return FALSE;
}

void CPrintView::OnFilePrintPreview(CFrameWnd *pFrame)
{
	m_pFrameWnd = pFrame;

	CPrintPreviewState* pState = new CPrintPreviewState;
	pState->lpfnCloseProc = _AfxMyPreviewCloseProc;

	if (!DoPrintPreview(AFX_IDD_PREVIEW_TOOLBAR, this,RUNTIME_CLASS(CPreviewPrintView), pState))
	{		

		TRACE0("Error: DoPrintPreview failed.\n");
		AfxMessageBox(AFX_IDP_COMMAND_FAILURE);
		delete pState;
	}
}

BOOL CPrintView::DoPrintPreview(UINT nIDResource, CView* pPrintView,
								  CRuntimeClass* pPreviewViewClass, CPrintPreviewState* pState)
{
	ASSERT_VALID_IDR(nIDResource);
	ASSERT_VALID(pPrintView);
	ASSERT(pPreviewViewClass != NULL);
	ASSERT(pPreviewViewClass->IsDerivedFrom(RUNTIME_CLASS(CPreviewView)));
	ASSERT(pState != NULL);

	ASSERT(m_pFrameWnd != NULL);
	CFrameWnd* pParent = m_pFrameWnd; //STATIC_DOWNCAST(CFrameWnd, AfxGetMainWnd()); //
	ASSERT_VALID(pParent);

	CCreateContext context;
	context.m_pCurrentFrame = pParent;
	context.m_pCurrentDoc = GetDocument();
	context.m_pLastView = this;

	// Create the preview view object
	CPreviewPrintView* pView = (CPreviewPrintView*)pPreviewViewClass->CreateObject();
	if (pView == NULL)
	{
		TRACE0("Error: Failed to create preview view.\n");
		return FALSE;
	}
	ASSERT_KINDOF(CPreviewView, pView);
	pView->m_pPreviewState = pState;        // save pointer

	pParent->OnSetPreviewMode(TRUE, pState);    // Take over Frame Window

	// Create the toolbar from the dialog resource
	pView->m_pToolBar = new CDialogBar;
	if (!pView->m_pToolBar->Create(pParent, MAKEINTRESOURCE(nIDResource),
		CBRS_TOP, AFX_IDW_PREVIEW_BAR))
	{
		TRACE0("Error: Preview could not create toolbar dialog.\n");
		pParent->OnSetPreviewMode(FALSE, pState);   // restore Frame Window
		delete pView->m_pToolBar;       // not autodestruct yet
		pView->m_pToolBar = NULL;
		pView->m_pPreviewState = NULL;  // do not delete state structure
		delete pView;
		return FALSE;
	}
	pView->m_pToolBar->m_bAutoDelete = TRUE;    // automatic cleanup

	if (!pView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0,0,0,0), pParent, AFX_IDW_PANE_FIRST, &context))
	{
		TRACE0("Error: couldn't create preview view for frame.\n");
		pParent->OnSetPreviewMode(FALSE, pState);   // restore Frame Window
		pView->m_pPreviewState = NULL;  // do not delete state structure
		delete pView;
		return FALSE;
	}

	pState->pViewActiveOld = pParent->GetActiveView();
	CPrintView* pActiveView = (CPrintView*)pParent->GetActiveFrame()->GetActiveView();
	if (pActiveView != NULL)
		pActiveView->OnActivateView(FALSE, pActiveView, pActiveView);

	if (!pView->SetPrintView(pPrintView))
	{
		pView->OnPreviewClose();
		return TRUE;            // signal that OnEndPrintPreview was called
	}

	pParent->SetActiveView(pView);  // set active view - even for MDI

	// update toolbar and redraw everything
	pView->m_pToolBar->SendMessage(WM_IDLEUPDATECMDUI, (WPARAM)TRUE);
	pParent->RecalcLayout();            // position and size everything
	pParent->UpdateWindow();

	return TRUE;
}

void CPrintView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	CScrollView::OnBeginPrinting(pDC, pInfo);
	CPrintFrame *pFrame =(CPrintFrame *)GetParent();
	pFrame->m_p_caller_dlg->SendMessage(WM_BEGIN_PRINTING,(WPARAM) pDC, (LPARAM) pInfo);
}
void CPrintView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	CScrollView::OnEndPrinting(pDC, pInfo);
	CPrintFrame *pFrame =(CPrintFrame *)GetParent();
	pFrame->m_p_caller_dlg->SendMessage(WM_END_PRINTING,(WPARAM) pDC, (LPARAM) pInfo);
	//if(m_b_print)		//直接打印，不是预览
	//	GetParent()->DestroyWindow();
}

void CPrintView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	if(pDC)
	{
		CPrintFrame* pf=(CPrintFrame*)::AfxGetMainWnd();		
//#ifdef _DEBUG
//
//		static int tt;
//		tt++;
//		CString ClipBoxstr;
//
//		CRect  client; 
//		pDC->GetClipBox(&client); 
//		ClipBoxstr.Format(_T(" 裁剪区 Top:%d Bottom:%d | Left:%d Right:%d"),client.top,client.bottom,client.left,client.right);
//		CString Repaintstr;
//		Repaintstr.Format(_T("第%d页 | 重绘%d次  "),pInfo->m_nCurPage,tt);
//		Repaintstr+=ClipBoxstr;
//		pf->SetWindowText(Repaintstr);
//#endif
	}
	CPrintFrame *pFrame =(CPrintFrame *)GetParent();
	pFrame->m_p_caller_dlg->SendMessage(WM_MY_PRINT,(WPARAM) pDC, (LPARAM) pInfo) ;
}
void CPrintView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewPrintView* pView) 
{
	// TODO: Add your specialized code here and/or call the base class
	ASSERT_VALID(pDC);
	ASSERT_VALID(pView);
	ASSERT(m_pFrameWnd != NULL);

	if (pView->m_pPrintView != NULL)
		OnEndPrinting(pDC, pInfo);

	CFrameWnd* pParent = m_pFrameWnd;
	ASSERT_VALID(pParent);

	// restore the old main window
	pParent->OnSetPreviewMode(FALSE, pView->m_pPreviewState);

	// Force active view back to old one
	pParent->SetActiveView(pView->m_pPreviewState->pViewActiveOld);
	if (pParent != GetParentFrame())
		OnActivateView(TRUE, this, this);   // re-activate view in real frame
	pView->DestroyWindow();     // destroy preview view
	// C++ object will be deleted in PostNcDestroy

	// restore main frame layout and idle message
	pParent->RecalcLayout();
	pParent->SendMessage(WM_SETMESSAGESTRING, (WPARAM)AFX_IDS_IDLEMESSAGE, 0L);
	pParent->UpdateWindow();
}

void CPrintView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	CView::OnPrepareDC(pDC, pInfo);
}
