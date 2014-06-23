
// ClientDlg.h : 头文件
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
		char cookie[256]; // Cookie
		char sid[256]; // 会话ID
		char aid[256]; // 身份ID
	};

	struct DAYIN{
		CString m_title; // 标题
		CString m_id; // 单号
		CString m_CheHao; // 车号
		CString m_CheXing; // 车型
		CString m_DanWei; // 收货单位
		CString m_DianHua; // 电话
		CString m_HuoWu; // 货物名称
		CString m_GuiGe; // 货物规格
		CString m_PiZhong; // 皮重
		CString m_MaoZhong; // 毛重
		CString m_JingZhong; // 净重
		CString m_DanJia; // 单价
		CString m_JinE; // 金额
		CString m_BeiZhu; // 备注
		CString m_User; // 司磅员
	};
	DAYIN DaYin;
	
	int len;
	int m_post_id; // 提交的编号，用于区分不同提交。
	char m_net_rvc_data[10240]; // 接收到的数据
	int m_net_rvc_len; // 接收到的数据长度

	unsigned char m_dibang_data[32]; // 地磅数据
	int m_dibang_data_pos; // 地磅数据的位置
	int m_Start; // 是否开始收集地磅数据

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
	unsigned char m_Weight[16]; // 重量的全局变量
	int iWeight1,iWeight2;
	int m_type; // 第一次或第二次过磅的类型 1为第一次 2位第二次
	float m_midu; // 密度
	CString m_danjiadanwei; // 单价单位

	CONF conf;
	// 车型
	CComboBox m_chexing;
	// 货物
	CComboBox m_huowu;
	// 规格
	CComboBox m_guige;

	afx_msg void OnBnClickedButtonCom();
	afx_msg void OnBnClickedButtonCom1Send();
	//afx_msg void OnBnClickedButtonCom2Send();
	afx_msg void OnBnClickedButtonZhongliang(); // 取重量

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
	CListCtrl m_list; // 车辆信息列表
	afx_msg void OnBnClickedButtonNetConn();
	afx_msg void OnBnClickedButtonComConn();
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedButtonLogout();
	void OnKeepalive(); // 保持连接
	void OnLogin(); // 用户登录
	void OnGet1(); // 第一次获得ID
	void OnGet2(); // 第二次获得ID
	void OnPost1(); // 第一次提交表单
	void OnPost2(); // 第二次提交表单
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonTijiao();
	CButton m_dayin;
	afx_msg void OnBnClickedButtonDayin();
	CButton m_tijiao;
	void SetWindow();
	void GetWindow();
	afx_msg void OnBnClickedButtonGet();
	afx_msg void OnBnClickedButtonEdit();

	// 打印相关
	LRESULT OnBeginPrinting(WPARAM wParam,LPARAM lParam);
	LRESULT OnEndPrinting(WPARAM wParam,LPARAM lParam);
	LRESULT OnMyPrint(WPARAM wParam,LPARAM lParam);//真正打印内容
	void DoPrint();
	std::tr1::shared_ptr<CPrinter> m_printer;
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButtonFind();
	afx_msg void OnBnClickedButtonJiaojie();

	void CalcJinE(); // 计算金额
	afx_msg void OnEnChangeEditDanjia();
	afx_msg void OnEnChangeEditJingzhong();
	afx_msg void OnCbnSelchangeComboHuowu();
	afx_msg void OnCbnSelchangeComboChexing();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonQuxiao();
};
