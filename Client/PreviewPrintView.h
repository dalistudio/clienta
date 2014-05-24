#pragma once
#include "afxpriv.h"
class CPrintView;
// CPreviewPrintView 视图

class CPreviewPrintView : public CPreviewView
{
	friend CPrintView;
	DECLARE_DYNCREATE(CPreviewPrintView)

protected:
	CPreviewPrintView();           // 动态创建所使用的受保护的构造函数
	virtual ~CPreviewPrintView();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
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


