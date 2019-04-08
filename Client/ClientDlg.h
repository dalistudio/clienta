
// ClientDlg.h : 头文件
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

// CClientDlg 对话框
class CClientDlg : public CDialogEx
{
// 构造
public:
	CClientDlg(CWnd* pParent = NULL);	// 标准构造函数
	LRESULT On_Receive(WPARAM wp, LPARAM lp); // 接收串口的消息，并处理
	void OnDiBang(int type); // 地磅数据处理函数

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
		char path[256]; // 报表保存路径
	};

	// 账单结构
	struct BILL{
		char DanHao[16]; // 单号
		char CheHao[16]; // 车号
		char CheXing[16]; // 车型
		char DanWei[64]; // 收货单位
		char DianHua[16]; // 电话
		char HuoWu[32]; // 货物名称
		char GuiGe[16]; // 货物规格
		char XianZhong[32]; // 限重 v1.7.1
		char PiZhong[16]; // 皮重
		char MaoZhong[16]; // 毛重
		char JingZhong[16]; // 净重
		char DanJia[16]; // 单价
		char DanJiaDanWei[16]; // 单价的单位
		char MiDu[16]; // 密度
		char JinE[16]; // 金额
		char YuE[16]; // 余额
		char BeiZhu[64]; // 备注
		char GuoBang1[32]; // 过磅1时间
		char GuoBang2[32]; // 过磅2时间
		char ChuChang[32]; // 出场时间
		char SiBangYuan[32]; // 司磅员
		char BaoAnYuan[32]; // 保安员
		char ZhuangTai[16]; // 状态
		char Type[16]; // 支付类型
	}bill;

	int m_post_id; // 提交的编号，用于区分不同提交。
	int m_isLogin; // 是否登陆
	int m_limit_flag; // 是否启用/禁用限重模块 限重v1.7.1

	unsigned char m_dibang_data[32]; // 地磅数据
	int m_dibang_data_pos; // 地磅数据的位置
	int m_Start; // 是否开始收集地磅数据
	unsigned char str[1024]; // 串口接收缓冲

// 实现
protected:
	HICON m_hIcon;
	CnComm Comm_; // 串口

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	unsigned char m_Weight[16]; // 重量的全局变量
	int iWeight1,iWeight2;

	CList<CString,CString> m_UserList; // 用户名列表

	CONF conf;
	CComboBox m_chexing; // 车型
	CComboBox m_huowu; // 货物
	CComboBox m_guige; // 规格

	afx_msg void OnBnClickedButtonCom1Send(); // 串口按钮
	afx_msg void OnBnClickedButtonZhongliang(); // 取重量

	CEdit m_ip; // IP地址
	CEdit m_port; // 端口
	CEdit m_com1; // 串口
	CComboBox m_type; // 单位
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CComboBox m_user; // 用户
	CEdit m_pwd; // 密码
	CEdit m_id; // 单号
	CEdit m_chehao; // 车号
	CEdit m_dianhua; // 电话
	CComboBox m_danwei; // 单位
	CEdit m_pizhong; // 皮重
	CEdit m_maozhong; // 毛重
	CEdit m_jingzhong; // 净重
	CEdit m_danjia; // 单价
	CEdit m_jine; // 金额
	CEdit m_yue; // 余额
	CButton m_shoudong; // 手动
	CButton m_youhui; // 优惠
	CEdit m_zhongliang; // 重量
	CButton m_btn_login; // 登陆按钮
	CButton m_gaidan; // 改单按钮
	CButton m_jiaojie; // 交接按钮
	CListCtrl m_list; // 车辆信息列表
	CEdit m_CheShu; // 在场车数
	afx_msg void OnBnClickedButtonComConn(); // 打开串口按钮
	afx_msg void OnBnClickedButtonLogin(); // 登陆按钮
	afx_msg void OnBnClickedButtonLogout(); // 登出按钮
	afx_msg void OnTimer(UINT_PTR nIDEvent); // 定时器
	afx_msg void OnBnClickedButtonTijiao(); // 单击提交按钮
	CButton m_dayin; // 打印按钮
	afx_msg void OnBnClickedButtonDayin(); // 单击打印按钮
	CButton m_tijiao; // 提交按钮
	afx_msg void OnBnClickedButtonGet(); // 单击获取按钮
	afx_msg void OnBnClickedButtonEdit(); // 单击编辑按钮

	// 打印相关
	LRESULT OnBeginPrinting(WPARAM wParam,LPARAM lParam); // 打印开始
	LRESULT OnEndPrinting(WPARAM wParam,LPARAM lParam); // 打印结束
	LRESULT OnMyPrint(WPARAM wParam,LPARAM lParam);//真正打印内容
	void DoPrint(); // 执行打印
	std::tr1::shared_ptr<CPrinter> m_printer; // 打印共享指针
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButtonJiaojie(); // 单击交接按钮

	void CalcJinE(); // 计算金额
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
	static size_t login_data(void *ptr, size_t size, size_t nmemb, void *userp); // 登陆返回数据
	static size_t limit_data(void *ptr, size_t size, size_t nmemb, void *userp); // 限重返回数据
	static size_t getid_data(void *ptr, size_t size, size_t nmemb, void *userp); // 获得单号返回数据
	static size_t post_data(void *ptr, size_t size, size_t nmemb, void *userp); // 提交数据返回数据
	static size_t guige_data(void *ptr, size_t size, size_t nmemb, void *userp); // 获得规格返回数据
	static size_t cheliang_data(void *ptr, size_t size, size_t nmemb, void *userp); // 获得在场车辆返回数据
	static size_t chehao_data(void *ptr, size_t size, size_t nmemb, void *userp); // 获得车号返回数据
	static size_t report_data(void *ptr, size_t size, size_t nmemb, void *userp); // 获得交接班报表

	void OnCheLiang(); // 车辆在场请求 
	void ShowBill(); // 显示单据的数据
	char *strCheLiang; // 在场车辆信息的数据(1MB)
	int  PosCheLiang; // 在场车辆信息数据的位置

	// Date Time Ctrl
	CDateTimeCtrl m_Date_Start;
	CDateTimeCtrl m_Date_End;
	
	afx_msg void OnBnClickedButton5(); // 获得在场车辆信息
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonGaidan();
	// 限重
	CComboBox m_xianzhong;
	afx_msg void OnEnChangeEditChehao();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
};
