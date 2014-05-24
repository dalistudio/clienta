#pragma once
class CPrintFrame;
class CPreviewPrintView;
// CPrintView ��ͼ

class CPrintView : public CScrollView
{
public:
	CPrintView();
	virtual ~CPrintView();
	DECLARE_DYNCREATE(CPrintView)
public:
	void OnMyPrint();
	void OnMyPrintPreview(CPrintFrame* pf);
protected:
	CFrameWnd *m_pFrameWnd;
	
public:
	virtual void OnPrint(CDC* pDC, CPrintInfo* pinfo);
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);

	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewPrintView* pView);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);

protected:           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	
public:
	
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
	//��д:
	void OnFilePrintPreview(CFrameWnd *pFrame);
	BOOL DoPrintPreview(UINT nIDResource, CView* pPrintView, CRuntimeClass* pPreviewViewClass, CPrintPreviewState* pState);
};


