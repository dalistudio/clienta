
// ClientDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "Com_class.h"
#include "io.h"
#include "MySock.h"

// CClientDlg �Ի���
class CClientDlg : public CDialogEx
{
// ����
public:
	CClientDlg(CWnd* pParent = NULL);	// ��׼���캯��
	LRESULT On_Receive(WPARAM wp, LPARAM lp); // ���մ��ڵ���Ϣ��������

	void OnConnected(); // ����Socket������
	void OnRvc(); // ���� Socket ����
	void OnClose(); // �ر� Socket ����
	CMySock m_Conn; // 

// �Ի�������
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	struct CONF{
		char title[32]; // ����
		char ip[16]; // ��ַ
		short port; // �˿�
		short com1_name; // ����1�ı��
		char com1_parm[16]; // ����1�Ĳ���
		short com2_name; // ����2�ı��
		char com2_parm[16]; // ����2�Ĳ���
	};
	CONF conf;
	int len;
// ʵ��
protected:
	HICON m_hIcon;
	_thread_com com1; // ��������1
	_thread_com com2; // ��������2
	CString	m_e;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// ����
	CComboBox m_cbCheXing;
	// ����
	CComboBox m_cbHuoWu;
	// ���
	CComboBox m_cbGuiGe;
	// ����
	CComboBox m_cbLiuXiang;
	afx_msg void OnCbnSelchangeComboHuowu();
	afx_msg void OnBnClickedButtonCom();
	afx_msg void OnBnClickedButtonCom1Send();
	afx_msg void OnBnClickedButtonCom2Send();

	void GetData(char *url, char *parm);
	void PostData(char *url, char *parm);
	CEdit m_ip;
	CEdit m_port;
	CEdit m_com1;
	CEdit m_com2;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
