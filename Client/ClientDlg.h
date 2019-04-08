
// ClientDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <memory>
#include "CnComm.h"
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
	void OnDiBang(int type); // �ذ����ݴ�����

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
		char path[256]; // ������·��
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
		char XianZhong[32]; // ���� v1.7.1
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
		char Type[16]; // ֧������
	}bill;

	int m_post_id; // �ύ�ı�ţ��������ֲ�ͬ�ύ��
	int m_isLogin; // �Ƿ��½
	int m_limit_flag; // �Ƿ�����/��������ģ�� ����v1.7.1

	unsigned char m_dibang_data[32]; // �ذ�����
	int m_dibang_data_pos; // �ذ����ݵ�λ��
	int m_Start; // �Ƿ�ʼ�ռ��ذ�����
	unsigned char str[1024]; // ���ڽ��ջ���

// ʵ��
protected:
	HICON m_hIcon;
	CnComm Comm_; // ����

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	unsigned char m_Weight[16]; // ������ȫ�ֱ���
	int iWeight1,iWeight2;

	CList<CString,CString> m_UserList; // �û����б�

	CONF conf;
	CComboBox m_chexing; // ����
	CComboBox m_huowu; // ����
	CComboBox m_guige; // ���

	afx_msg void OnBnClickedButtonCom1Send(); // ���ڰ�ť
	afx_msg void OnBnClickedButtonZhongliang(); // ȡ����

	CEdit m_ip; // IP��ַ
	CEdit m_port; // �˿�
	CEdit m_com1; // ����
	CComboBox m_type; // ��λ
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CComboBox m_user; // �û�
	CEdit m_pwd; // ����
	CEdit m_id; // ����
	CEdit m_chehao; // ����
	CEdit m_dianhua; // �绰
	CComboBox m_danwei; // ��λ
	CEdit m_pizhong; // Ƥ��
	CEdit m_maozhong; // ë��
	CEdit m_jingzhong; // ����
	CEdit m_danjia; // ����
	CEdit m_jine; // ���
	CEdit m_yue; // ���
	CButton m_shoudong; // �ֶ�
	CButton m_youhui; // �Ż�
	CEdit m_zhongliang; // ����
	CButton m_btn_login; // ��½��ť
	CButton m_gaidan; // �ĵ���ť
	CButton m_jiaojie; // ���Ӱ�ť
	CListCtrl m_list; // ������Ϣ�б�
	CEdit m_CheShu; // �ڳ�����
	afx_msg void OnBnClickedButtonComConn(); // �򿪴��ڰ�ť
	afx_msg void OnBnClickedButtonLogin(); // ��½��ť
	afx_msg void OnBnClickedButtonLogout(); // �ǳ���ť
	afx_msg void OnTimer(UINT_PTR nIDEvent); // ��ʱ��
	afx_msg void OnBnClickedButtonTijiao(); // �����ύ��ť
	CButton m_dayin; // ��ӡ��ť
	afx_msg void OnBnClickedButtonDayin(); // ������ӡ��ť
	CButton m_tijiao; // �ύ��ť
	afx_msg void OnBnClickedButtonGet(); // ������ȡ��ť
	afx_msg void OnBnClickedButtonEdit(); // �����༭��ť

	// ��ӡ���
	LRESULT OnBeginPrinting(WPARAM wParam,LPARAM lParam); // ��ӡ��ʼ
	LRESULT OnEndPrinting(WPARAM wParam,LPARAM lParam); // ��ӡ����
	LRESULT OnMyPrint(WPARAM wParam,LPARAM lParam);//������ӡ����
	void DoPrint(); // ִ�д�ӡ
	std::tr1::shared_ptr<CPrinter> m_printer; // ��ӡ����ָ��
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButtonJiaojie(); // �������Ӱ�ť

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
	static size_t limit_data(void *ptr, size_t size, size_t nmemb, void *userp); // ���ط�������
	static size_t getid_data(void *ptr, size_t size, size_t nmemb, void *userp); // ��õ��ŷ�������
	static size_t post_data(void *ptr, size_t size, size_t nmemb, void *userp); // �ύ���ݷ�������
	static size_t guige_data(void *ptr, size_t size, size_t nmemb, void *userp); // ��ù�񷵻�����
	static size_t cheliang_data(void *ptr, size_t size, size_t nmemb, void *userp); // ����ڳ�������������
	static size_t chehao_data(void *ptr, size_t size, size_t nmemb, void *userp); // ��ó��ŷ�������
	static size_t report_data(void *ptr, size_t size, size_t nmemb, void *userp); // ��ý��Ӱ౨��

	void OnCheLiang(); // �����ڳ����� 
	void ShowBill(); // ��ʾ���ݵ�����
	char *strCheLiang; // �ڳ�������Ϣ������(1MB)
	int  PosCheLiang; // �ڳ�������Ϣ���ݵ�λ��

	// Date Time Ctrl
	CDateTimeCtrl m_Date_Start;
	CDateTimeCtrl m_Date_End;
	
	afx_msg void OnBnClickedButton5(); // ����ڳ�������Ϣ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonGaidan();
	// ����
	CComboBox m_xianzhong;
	afx_msg void OnEnChangeEditChehao();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
};
