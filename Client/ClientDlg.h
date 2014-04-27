
// ClientDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "Com_class.h"
#include "io.h"
#include "MySock.h"

// CClientDlg 对话框
class CClientDlg : public CDialogEx
{
// 构造
public:
	CClientDlg(CWnd* pParent = NULL);	// 标准构造函数
	LRESULT On_Receive(WPARAM wp, LPARAM lp); // 接收串口的消息，并处理

	void OnConnected(); // 连接Socket服务器
	void OnRvc(); // 接收 Socket 数据
	void OnClose(); // 关闭 Socket 连接
	CMySock m_Conn; // 

// 对话框数据
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	struct CONF{
		char title[32]; // 标题
		char ip[16]; // 地址
		short port; // 端口
		short com1_id; // 串口1的编号
		char com1_para[64]; // 串口1的参数
		short com2_id; // 串口2的编号
		char com2_para[64]; // 串口2的参数
		char cookie[256];
	};
	CONF conf;
	int len;
	int m_post_id; // 提交的编号，用于区分不同提交。
	char m_net_rvc_data[1025]; // 接收到的数据
	int m_net_rvc_len; // 接收到的数据长度

// 实现
protected:
	HICON m_hIcon;
	_thread_com com1; // 创建串口1
	_thread_com com2; // 创建串口2
	CString	m_e;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 车型
	CComboBox m_chexing;
	// 货物
	CComboBox m_huowu;
	// 规格
	CComboBox m_guige;
	// 流向
	CComboBox m_liuxiang;
	afx_msg void OnCbnSelchangeComboHuowu();
	afx_msg void OnBnClickedButtonCom();
	afx_msg void OnBnClickedButtonCom1Send();
	afx_msg void OnBnClickedButtonCom2Send();

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
	CEdit m_zhongliang;
	CButton m_btn_net;
	CButton m_btn_login;
	afx_msg void OnBnClickedButtonNetConn();
	afx_msg void OnBnClickedButtonComConn();
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedButtonLogout();
	void OnKeepalive(); // 保持连接
	void OnLogin(); // 用户登录
	void OnPost(); // 提交单据
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonTijiao();
	CButton m_dayin;
	afx_msg void OnBnClickedButtonDayin();
	CButton m_tijiao;
};
