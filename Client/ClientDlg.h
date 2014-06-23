
// ClientDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <memory>
#include "Com_class.h"
#include "io.h"
#include "MySock.h"
#include "printer.h"
#include "Resource.h"

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
		short com1_id; // ����1�ı��
		char com1_para[64]; // ����1�Ĳ���
		short com2_id; // ����2�ı��
		char com2_para[64]; // ����2�Ĳ���
		char cookie[256]; // Cookie
		char sid[256]; // �ỰID
		char aid[256]; // ���ID
	};

	struct DAYIN{
		CString m_title; // ����
		CString m_id; // ����
		CString m_CheHao; // ����
		CString m_CheXing; // ����
		CString m_DanWei; // �ջ���λ
		CString m_DianHua; // �绰
		CString m_HuoWu; // ��������
		CString m_GuiGe; // ������
		CString m_PiZhong; // Ƥ��
		CString m_MaoZhong; // ë��
		CString m_JingZhong; // ����
		CString m_DanJia; // ����
		CString m_JinE; // ���
		CString m_BeiZhu; // ��ע
		CString m_User; // ˾��Ա
	};
	DAYIN DaYin;
	
	int len;
	int m_post_id; // �ύ�ı�ţ��������ֲ�ͬ�ύ��
	char m_net_rvc_data[10240]; // ���յ�������
	int m_net_rvc_len; // ���յ������ݳ���

	unsigned char m_dibang_data[32]; // �ذ�����
	int m_dibang_data_pos; // �ذ����ݵ�λ��
	int m_Start; // �Ƿ�ʼ�ռ��ذ�����

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
	unsigned char m_Weight[16]; // ������ȫ�ֱ���
	int iWeight1,iWeight2;
	int m_type; // ��һ�λ�ڶ��ι��������� 1Ϊ��һ�� 2λ�ڶ���
	float m_midu; // �ܶ�
	CString m_danjiadanwei; // ���۵�λ

	CONF conf;
	// ����
	CComboBox m_chexing;
	// ����
	CComboBox m_huowu;
	// ���
	CComboBox m_guige;

	afx_msg void OnBnClickedButtonCom();
	afx_msg void OnBnClickedButtonCom1Send();
	//afx_msg void OnBnClickedButtonCom2Send();
	afx_msg void OnBnClickedButtonZhongliang(); // ȡ����

	void GetData(char *url, char *para);
	void PostData(char *url, char *para);
	CEdit m_ip;
	CEdit m_port;
	CEdit m_com1;
	CEdit m_com2;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_user;
	CEdit m_pwd;
	CEdit m_id;
	CEdit m_chehao;
	CEdit m_dianhua;
	CEdit m_shouhuo;
	CEdit m_pizhong;
	CEdit m_maozhong;
	CEdit m_jingzhong;
	CEdit m_danjia;
	CEdit m_jine;
	CEdit m_yue;
	CButton m_shoudong;
	CButton m_youhui;
	CEdit m_zhongliang;
	CButton m_btn_net;
	CButton m_btn_login;
	CListCtrl m_list; // ������Ϣ�б�
	afx_msg void OnBnClickedButtonNetConn();
	afx_msg void OnBnClickedButtonComConn();
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedButtonLogout();
	void OnKeepalive(); // ��������
	void OnLogin(); // �û���¼
	void OnGet1(); // ��һ�λ��ID
	void OnGet2(); // �ڶ��λ��ID
	void OnPost1(); // ��һ���ύ��
	void OnPost2(); // �ڶ����ύ��
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonTijiao();
	CButton m_dayin;
	afx_msg void OnBnClickedButtonDayin();
	CButton m_tijiao;
	void SetWindow();
	void GetWindow();
	afx_msg void OnBnClickedButtonGet();
	afx_msg void OnBnClickedButtonEdit();

	// ��ӡ���
	LRESULT OnBeginPrinting(WPARAM wParam,LPARAM lParam);
	LRESULT OnEndPrinting(WPARAM wParam,LPARAM lParam);
	LRESULT OnMyPrint(WPARAM wParam,LPARAM lParam);//������ӡ����
	void DoPrint();
	std::tr1::shared_ptr<CPrinter> m_printer;
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButtonFind();
	afx_msg void OnBnClickedButtonJiaojie();

	void CalcJinE(); // ������
	afx_msg void OnEnChangeEditDanjia();
	afx_msg void OnEnChangeEditJingzhong();
	afx_msg void OnCbnSelchangeComboHuowu();
	afx_msg void OnCbnSelchangeComboChexing();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonQuxiao();
};
