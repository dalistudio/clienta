
// ClientDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <memory>
#include "Com_class.h"
#include "io.h"
#include "printer.h"
#include "Resource.h"
#include "../curl/include/curl/curl.h"

// CClientDlg �Ի���
class CClientDlg : public CDialogEx
{
// ����
public:
	CClientDlg(CWnd* pParent = NULL);	// ��׼���캯��
	LRESULT On_Receive(WPARAM wp, LPARAM lp); // ���մ��ڵ���Ϣ��������

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
	};

	// �˵��ṹ
	struct BILL{
		char DanHao[16]; // ����
		char CheHao[16]; // ����
		char CheXing[16]; // ����
		char DanWei[64]; // �ջ���λ
		char DianHua[16]; // �绰
		char HuoWu[32]; // ��������
		char GuiGe[16]; // ������
		char PiZhong[16]; // Ƥ��
		char MaoZhong[16]; // ë��
		char JingZhong[16]; // ����
		char DanJia[16]; // ����
		char DanJiaDanWei[16]; // ���۵ĵ�λ
		char MiDu[16]; // �ܶ�
		char JinE[16]; // ���
		char YuE[16]; // ���
		char BeiZhu[64]; // ��ע
		char GuoBang1[32]; // ����1ʱ��
		char GuoBang2[32]; // ����2ʱ��
		char ChuChang[32]; // ����ʱ��
		char SiBangYuan[32]; // ˾��Ա
		char BaoAnYuan[32]; // ����Ա
		char ZhuangTai[16]; // ״̬
	}bill;

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

	int m_post_id; // �ύ�ı�ţ��������ֲ�ͬ�ύ��
	int m_isLogin; // �Ƿ��½

	unsigned char m_dibang_data[32]; // �ذ�����
	int m_dibang_data_pos; // �ذ����ݵ�λ��
	int m_Start; // �Ƿ�ʼ�ռ��ذ�����

// ʵ��
protected:
	HICON m_hIcon;
	_thread_com com1; // ��������1

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

	CONF conf;
	// ����
	CComboBox m_chexing;
	// ����
	CComboBox m_huowu;
	// ���
	CComboBox m_guige;

	afx_msg void OnBnClickedButtonCom();
	afx_msg void OnBnClickedButtonCom1Send();
	afx_msg void OnBnClickedButtonZhongliang(); // ȡ����

	CEdit m_ip;
	CEdit m_port;
	CEdit m_com1;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_user;
	CEdit m_pwd;
	CEdit m_id;
	CEdit m_chehao;
	CEdit m_dianhua;
	CComboBox m_shouhuo;
	CEdit m_pizhong;
	CEdit m_maozhong;
	CEdit m_jingzhong;
	CEdit m_danjia;
	CEdit m_jine;
	CEdit m_yue;
	CButton m_shoudong;
	CButton m_youhui;
	CEdit m_zhongliang;
	CButton m_btn_login;
	CListCtrl m_list; // ������Ϣ�б�
	CEdit m_CheShu; // �ڳ�����
	afx_msg void OnBnClickedButtonComConn();
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedButtonLogout();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonTijiao();
	CButton m_dayin;
	afx_msg void OnBnClickedButtonDayin();
	CButton m_tijiao;
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

	// CURL 
	CURL *curl;
	static size_t login_data(void *ptr, size_t size, size_t nmemb, void *userp); // ��½��������
	static size_t getid_data(void *ptr, size_t size, size_t nmemb, void *userp); // ��õ��ŷ�������
	static size_t post_data(void *ptr, size_t size, size_t nmemb, void *userp); // �ύ���ݷ�������
	static size_t guige_data(void *ptr, size_t size, size_t nmemb, void *userp); // ��ù�񷵻�����
	static size_t cheliang_data(void *ptr, size_t size, size_t nmemb, void *userp); // ����ڳ�������������
	static size_t chehao_data(void *ptr, size_t size, size_t nmemb, void *userp); // ��ó��ŷ�������
	void OnCheLiang(); // �����ڳ����� 
	void ShowBill(); // ��ʾ���ݵ�����
	char strCheLiang[16*1024]; // �ڳ�������Ϣ������
	int  PosCheLiang; // �ڳ�������Ϣ���ݵ�λ��
	
	afx_msg void OnBnClickedButton5(); // ����ڳ�������Ϣ
};
