#pragma once
#include "afxpriv.h"
class CPrintView;
// CPreviewPrintView ��ͼ

class CPreviewPrintView : public CPreviewView
{
	friend CPrintView;
	DECLARE_DYNCREATE(CPreviewPrintView)

protected:
	CPreviewPrintView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CPreviewPrintView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void OnPreviewClose();
	afx_msg void OnPreviewPrint();
};


