
// ClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"
#include "uni2utf8.h"
#include "../cjson/cJSON.h"
#include "PrintFrame.h"
#include "PrintView.h"
#include "printer.h"
#include <memory>
#include <Afxtempl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// 左键点击关于对话框时执行
void CAboutDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//MessageBox(L"关于");
	SendMessage(WM_CLOSE); // 关闭关于对话框
	CDialogEx::OnLButtonDown(nFlags, point);
}

// CClientDlg 对话框

CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CHEXING, m_chexing); // 车型
	DDX_Control(pDX, IDC_COMBO_HUOWU, m_huowu); // 货物
	DDX_Control(pDX, IDC_COMBO_GUIGE, m_guige); // 规格
	DDX_Control(pDX, IDC_EDIT_IP, m_ip); // IP地址
	DDX_Control(pDX, IDC_EDIT_PORT, m_port); // 端口
	DDX_Control(pDX, IDC_EDIT_COM1, m_com1); // 串口
	DDX_Control(pDX, IDC_COMBO_TYPE, m_type); // 客户类型
	DDX_Control(pDX, IDC_EDIT_USER, m_user); // 用户
	DDX_Control(pDX, IDC_EDIT_PWD, m_pwd); // 密码
	DDX_Control(pDX, IDC_EDIT_DANHAO, m_id); // 单号
	DDX_Control(pDX, IDC_EDIT_CHEHAO, m_chehao); // 车号
	DDX_Control(pDX, IDC_EDIT_DIANHUA, m_dianhua); // 电话
	DDX_Control(pDX, IDC_EDIT_DANWEI, m_danwei); // 单位
	DDX_Control(pDX, IDC_EDIT_PIZHONG, m_pizhong); // 皮重
	DDX_Control(pDX, IDC_EDIT_MAOZHONG, m_maozhong); // 毛重
	DDX_Control(pDX, IDC_EDIT_JINGZHONG, m_jingzhong); // 净重
	DDX_Control(pDX, IDC_EDIT_DANJIA, m_danjia); // 单价
	DDX_Control(pDX, IDC_EDIT_JINE, m_jine); // 金额
	DDX_Control(pDX, IDC_EDIT_YUE, m_yue); // 余额
	DDX_Control(pDX, IDC_CHECK1, m_shoudong); // 手动皮重
	DDX_Control(pDX, IDC_CHECK2, m_youhui); // 优惠金额
	DDX_Control(pDX, IDC_EDIT_ZHONGLIANG, m_zhongliang); // 重量
	DDX_Control(pDX, IDC_BUTTON_LOGIN, m_btn_login); // 登陆按钮
	DDX_Control(pDX, IDC_BUTTON_GAIDAN, m_gaidan); // 改单按钮
	DDX_Control(pDX, IDC_BUTTON_JIAOJIE, m_jiaojie); // 交接按钮
	DDX_Control(pDX, IDC_BUTTON_DAYIN, m_dayin); // 打印按钮
	DDX_Control(pDX, IDC_BUTTON_TIJIAO, m_tijiao); // 提交按钮
	DDX_Control(pDX, IDC_LIST1, m_list); // 车辆信息列表
	DDX_Control(pDX, IDC_CHESHU, m_CheShu); // 在场车数
	DDX_Control(pDX, IDC_DATE_START, m_Date_Start); // 开始时间
	DDX_Control(pDX, IDC_DATE_END, m_Date_End); // 结束时间
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_MESSAGE(ON_COM_RECEIVE, On_Receive) // 如果收到 ON_COM_RECEIVE 消息，调用接收函数
	ON_BN_CLICKED(IDC_BUTTON_COM1_SEND, &CClientDlg::OnBnClickedButtonCom1Send)
	ON_BN_CLICKED(IDC_BUTTON_ZHONGLIANG, &CClientDlg::OnBnClickedButtonZhongliang)
	ON_BN_CLICKED(IDC_BUTTON_COM_CONN, &CClientDlg::OnBnClickedButtonComConn)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CClientDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_LOGOUT, &CClientDlg::OnBnClickedButtonLogout)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_TIJIAO, &CClientDlg::OnBnClickedButtonTijiao)
	ON_BN_CLICKED(IDC_BUTTON_DAYIN, &CClientDlg::OnBnClickedButtonDayin)
	ON_BN_CLICKED(IDC_BUTTON_GET, &CClientDlg::OnBnClickedButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &CClientDlg::OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_JIAOJIE, &CClientDlg::OnBnClickedButtonJiaojie)
	ON_EN_CHANGE(IDC_EDIT_DANJIA, &CClientDlg::OnEnChangeEditDanjia)
	ON_EN_CHANGE(IDC_EDIT_JINGZHONG, &CClientDlg::OnEnChangeEditJingzhong)
	ON_CBN_SELCHANGE(IDC_COMBO_HUOWU, &CClientDlg::OnCbnSelchangeComboHuowu)
	ON_CBN_SELCHANGE(IDC_COMBO_CHEXING, &CClientDlg::OnCbnSelchangeComboChexing)
	ON_BN_CLICKED(IDC_CHECK1, &CClientDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CClientDlg::OnBnClickedCheck2)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CClientDlg::OnNMDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON_QUXIAO, &CClientDlg::OnBnClickedButtonQuxiao)
	ON_BN_CLICKED(IDC_BUTTON5, &CClientDlg::OnBnClickedButton5)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_GAIDAN, &CClientDlg::OnBnClickedButtonGaidan)
END_MESSAGE_MAP()


// CClientDlg 消息处理程序

BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	Comm_.SetOption(Comm_.GetOption() | CnComm::EN_RX_BUFFER); // 设置串口使用读缓冲
	memset(&bill,0,sizeof(BILL)); // 初始化单据

	//
	// CURL 初始化
	// 
	CURLcode code = curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	memset(strCheLiang,0,16*1024);
	PosCheLiang=0;

	// Date Time Ctrl 报表时间控件
	m_Date_Start.SetFormat(L"yyyy-MM-dd HH:mm:ss");
	m_Date_End.SetFormat(L"yyyy-MM-dd HH:mm:ss");

	memset(m_Weight,0,16); // 清空重量的全局变量
	memset(m_dibang_data,0,32); // 清空地磅数据
	m_dibang_data_pos = 0; // 地磅数据的位置
	m_Start = 0; // 是否开始收集地磅数据
	iWeight1 = 0;
	iWeight2 = 0;

#ifdef _DEBUG // 调试版开启
	// 开启命令行窗口 
	int hCrt;
	FILE *hf;
	AllocConsole();
	hCrt = _open_osfhandle(
		(long) GetStdHandle(STD_OUTPUT_HANDLE),
		0x4000
	);
	hf = _fdopen( hCrt, "w" );
	*stdout = *hf;
	int i = setvbuf( stdout, NULL, _IONBF, 0 );
#endif

	// 默认配置
	m_tijiao.EnableWindow(FALSE); // 禁用“提交”按钮
	m_dayin.EnableWindow(FALSE); // 禁用“打印”按钮

	memset(&conf,0,sizeof(CONF));
	strcpy_s(conf.title,"海南港口文峰石场");
	strcpy_s(conf.ip,"192.168.1.5");
	conf.port = 80;
	conf.com1_id=1;
	strcpy_s(conf.com1_para,"9600,N,8,1");

	// 打开配置文件 JSON 格式
	FILE *f;
	fopen_s(&f,"config","rb"); // 配置文件 config
	if(f==NULL)
	{
		MessageBox(_T("打开配置文件失败！"), _T("config"), MB_ICONHAND);
	}
	else
	{
		fseek(f,0,SEEK_END); // 跳到文件尾
		long len=ftell(f); // 获得文件长度
		fseek(f,0,SEEK_SET); // 跳到文件头
		char *data=(char*)malloc(len+1); // 分配文件空间
		fread(data,1,len,f); // 读取文件数据
		fclose(f); // 关闭文件
		cJSON *jsonroot = cJSON_Parse(data); //json根
		if(jsonroot)
		{
			strcpy_s(conf.title,cJSON_GetObjectItem(jsonroot,"title")->valuestring); // 获得标题
			strcpy_s(conf.path,cJSON_GetObjectItem(jsonroot,"path")->valuestring); // 获得报表保存的路径

			cJSON *jsonServer=cJSON_GetObjectItem(jsonroot,"server");//取 Server
			strcpy_s(conf.ip,cJSON_GetObjectItem(jsonServer,"ip")->valuestring); // 获得IP地址
			conf.port = cJSON_GetObjectItem(jsonServer,"port")->valueint; // 获得端口

			cJSON *jsonCOM=cJSON_GetObjectItem(jsonroot,"com");//取 COM
			conf.com1_id = cJSON_GetObjectItem(jsonCOM,"port")->valueint; // 获得COM端口
			strcpy_s(conf.com1_para,cJSON_GetObjectItem(jsonCOM,"para")->valuestring); // 获得COM的属性
		}
		else
		{
			MessageBox(_T("配置文件错误！"),_T("config"),MB_ICONHAND);
		}
		cJSON_Delete(jsonroot);
	}

	USES_CONVERSION;
	// 打开用户名文件
	fopen_s(&f,"user.dat","rt"); // 只读
	if(f!=NULL)
	{
		m_user.ResetContent();
		while(!feof(f)) // 是否到文件尾
		{
			char user[32] = {0};
			fgets(user,16,f); // 按行读取用户名
			for (int i = 0; user[i]; i++) // 消除字符串后面的回车换行符号
			{
				if (user[i] == '\n' || user[i] == '\r') 
				{
					user[i] = 0;
					break;
				}
			}
			m_user.AddString(A2W(user)); // 将用户名加入用户列表
			m_UserList.AddTail(A2W(user)); // 添加用户名的链表中
		}
		m_user.SetCurSel(0); // 选择第一项作为默认选择
		fclose(f); // 关闭文件
	} // 剩下的处理在登陆成功后
	

	
	// 显示网络服务器的IP地址和端口
	m_ip.SetWindowText(A2CW(conf.ip));
	char port[8] = {0};
	_ltoa_s(conf.port,port,6,10);
	m_port.SetWindowText(A2CW(port));

	// 设置定时器
	SetTimer(1,60000,0); // 60秒

	// 初始化串口
	OnBnClickedButtonComConn();

	///////////////////////

	CFont *m_Font;
	m_Font = new CFont; 
	m_Font->CreateFont(
		32, // 字体高度
		13,	// 字体宽度
		0,	// 文本行的倾斜度
		0,	// 字符基线的倾斜度
		100,	// 字体的粗细
		FALSE,	// 是否斜体
		FALSE,	// 是否下划线
		0,		// 是否删除线
		ANSI_CHARSET,			// 字体的字符集
		OUT_DEFAULT_PRECIS,		// 字符的输出精度
		CLIP_DEFAULT_PRECIS,	// 字符的裁剪精度
		DEFAULT_QUALITY,		// 字符的输出质量
		FF_SWISS,				// 字符间距和字体族
		_T("隶书"));				// 字体名称

		// 实时重量的字体
		CFont *m_Font2;
		m_Font2 = new CFont; 
		m_Font2->CreateFont(
		60, // 字体高度
		25,	// 字体宽度
		0,	// 文本行的倾斜度
		0,	// 字符基线的倾斜度
		200,	// 字体的粗细
		FALSE,	// 是否斜体
		FALSE,	// 是否下划线
		0,		// 是否删除线
		ANSI_CHARSET,			// 字体的字符集
		OUT_DEFAULT_PRECIS,		// 字符的输出精度
		CLIP_DEFAULT_PRECIS,	// 字符的裁剪精度
		DEFAULT_QUALITY,		// 字符的输出质量
		FF_SWISS,				// 字符间距和字体族
		_T("Arial Black"));		// 字体名称

	// 重量
	GetDlgItem(IDC_EDIT_ZHONGLIANG)->SetFont(m_Font2);

	// 标题
	GetDlgItem(IDC_EDIT_TITLE)->SetWindowText(A2CW(conf.title));
	GetDlgItem(IDC_EDIT_TITLE)->SetFont(m_Font);
	//////////////////////////////////////

	// 单号
	GetDlgItem(IDC_STATIC_DANHAO)->SetFont(m_Font);
	GetDlgItem(IDC_EDIT_DANHAO)->SetFont(m_Font);
	
	// 车号
	GetDlgItem(IDC_STATIC_CHEHAO)->SetFont(m_Font);
	GetDlgItem(IDC_EDIT_CHEHAO)->SetFont(m_Font);

	// 电话
	GetDlgItem(IDC_STATIC_DIANHUA)->SetFont(m_Font);
	GetDlgItem(IDC_EDIT_DIANHUA)->SetFont(m_Font);

	// 货物名称
	GetDlgItem(IDC_STATIC_HUOWU)->SetFont(m_Font);
	GetDlgItem(IDC_COMBO_HUOWU)->SetFont(m_Font);

	// 货物规格
	GetDlgItem(IDC_STATIC_GUIGE)->SetFont(m_Font);
	GetDlgItem(IDC_COMBO_GUIGE)->SetFont(m_Font);

	// 收货单位
	GetDlgItem(IDC_STATIC_DANWEI)->SetFont(m_Font);
	GetDlgItem(IDC_EDIT_DANWEI)->SetFont(m_Font);

	// 余额
	GetDlgItem(IDC_STATIC_YUE)->SetFont(m_Font);
	GetDlgItem(IDC_STATIC_YEY)->SetFont(m_Font);

	// 皮重单位
	GetDlgItem(IDC_STATIC_PZKG)->SetFont(m_Font);

	// 毛重单位
	GetDlgItem(IDC_STATIC_MZKG)->SetFont(m_Font);

	// 净重单位
	GetDlgItem(IDC_STATIC_JZKG)->SetFont(m_Font);

	// 金额单位
	GetDlgItem(IDC_STATIC_JE)->SetFont(m_Font);

	////////////////////////////////

	// 车型
	GetDlgItem(IDC_STATIC_CHEXING)->SetFont(m_Font);
	GetDlgItem(IDC_COMBO_CHEXING)->SetFont(m_Font);

	// 皮重
	GetDlgItem(IDC_STATIC_PIZHONG)->SetFont(m_Font);
	GetDlgItem(IDC_EDIT_PIZHONG)->SetFont(m_Font);

	// 毛重
	GetDlgItem(IDC_STATIC_MAOZHONG)->SetFont(m_Font);
	GetDlgItem(IDC_EDIT_MAOZHONG)->SetFont(m_Font);

	// 净重
	GetDlgItem(IDC_STATIC_JINGZHONG)->SetFont(m_Font);
	GetDlgItem(IDC_EDIT_JINGZHONG)->SetFont(m_Font);

	// 单价
	GetDlgItem(IDC_STATIC_DANJIA)->SetFont(m_Font);
	GetDlgItem(IDC_EDIT_DANJIA)->SetFont(m_Font);

	// 金额
	GetDlgItem(IDC_STATIC_JINE)->SetFont(m_Font);
	GetDlgItem(IDC_EDIT_JINE)->SetFont(m_Font);

	// 余额
	GetDlgItem(IDC_STATIC_YUE)->SetFont(m_Font);
	GetDlgItem(IDC_EDIT_YUE)->SetFont(m_Font);

	/////////////////////////////////

	// 取重量按钮
	GetDlgItem(IDC_BUTTON_ZHONGLIANG)->SetFont(m_Font);

	// 提交按钮
	GetDlgItem(IDC_BUTTON_TIJIAO)->SetFont(m_Font);

	// 打印按钮
	GetDlgItem(IDC_BUTTON_DAYIN)->SetFont(m_Font);

	/////////////////////////////////

	// 车型
	m_chexing.AddString(_T("大车"));
	m_chexing.AddString(_T("小车"));
	m_chexing.SetCurSel(0); // 选择第一项“大车”

	// 客户类型
	m_type.AddString(_T("全部"));
	m_type.AddString(_T("零售"));
	m_type.AddString(_T("预付款"));
	m_type.AddString(_T("月结"));
	m_type.SetCurSel(1);

	///////////////////////////////
	// 车辆信息列表设置
	LONG lStyle; 
	lStyle = GetWindowLong(m_list.m_hWnd, GWL_STYLE);// 获取当前窗口style 
	lStyle &= ~LVS_TYPEMASK; // 清除显示方式位 
	lStyle |= LVS_REPORT; // 设置style 
	SetWindowLong(m_list.m_hWnd, GWL_STYLE, lStyle);// 设置style 
	DWORD dwStyle = m_list.GetExtendedStyle(); 
	dwStyle |= LVS_EX_FULLROWSELECT;// 选中某行使整行高亮（只适用与report 风格的listctrl ） 
	dwStyle |= LVS_EX_GRIDLINES;// 网格线（只适用与report 风格的listctrl ） 
//	dwStyle |= LVS_EX_CHECKBOXES;//item 前生成checkbox 控件 
	m_list.SetExtendedStyle(dwStyle); // 设置扩展风格 

	m_list.InsertColumn(0,L"单号",LVCFMT_CENTER,80);
	m_list.InsertColumn(1,L"车号",LVCFMT_RIGHT,80);
	m_list.InsertColumn(2,L"车型",LVCFMT_CENTER,80);
	m_list.InsertColumn(3,L"货物",LVCFMT_CENTER,80);
	m_list.InsertColumn(4,L"规格",LVCFMT_CENTER,80);
	m_list.InsertColumn(5,L"电话",LVCFMT_CENTER,100);
	m_list.InsertColumn(6,L"客户",LVCFMT_CENTER,250);
	m_list.InsertColumn(7,L"皮重",LVCFMT_RIGHT,100);
	m_list.InsertColumn(8,L"第1次过磅时间",LVCFMT_CENTER,180);
	m_list.InsertColumn(9,L"过磅次数",LVCFMT_CENTER,80);
	
	//return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
	return FALSE;
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 接收串口的消息，并处理
LRESULT CClientDlg::On_Receive(WPARAM wp, LPARAM lp)
{
	// 这里接收地磅数据，并分析处理后修改相关控件的显示。

	// 自动判断是新地磅还是旧地磅的数据
	int len;
	int type = 0; // 用于判断新旧地磅的数据
//	unsigned char str[1025]={0};
	memset(str,0,1024);
	len = Comm_.Read(str,1023); // 直接读串口

	for(int i=0;i<len;i++)
	{
		switch(str[i]) // 收到的第一个字符
		{
		case 0x02: // 开始标志
			// 开始搜集数据
			if(m_Start==0)
			{
				m_Start = 1;
				memset(m_dibang_data,0,32); // 清空
				m_dibang_data[m_dibang_data_pos] = str[i]; // 将字符赋值给地磅数据的全局变量
				m_dibang_data_pos++; // 地磅数据位置+1
			}
			else
			{
				m_Start=0; // 防止出现多次0x02 而没有 0x0d结束
			}
			break;

		case 0x03:
			// 结束搜集数据
			// 调用协议处理函数，分析数据。
			type = 1; // 旧地磅
			if(m_Start==1)
			{
				m_Start = 0;
				m_dibang_data[m_dibang_data_pos] = str[i];
				m_dibang_data[m_dibang_data_pos+1] = 0x00; // 无需再获取下一个字符了，直接在后面加上0x00结束字符串。
				m_dibang_data_pos = 0; // 初始化地磅数据的位置为0，防止溢出。
				OnDiBang(type); // 调用地磅处理函数
			}
			break;

		case 0x0D: // 结束标志
			// 结束搜集数据
			// 调用协议处理函数，分析数据。
			type = 2; // 新地磅
			if(m_Start==1)
			{
				m_Start = 0;
				m_dibang_data[m_dibang_data_pos] = str[i];
				m_dibang_data[m_dibang_data_pos+1] = 0x00; // 无需再获取下一个字符了，直接在后面加上0x00结束字符串。
				m_dibang_data_pos = 0; // 初始化地磅数据的位置为0，防止溢出。
				OnDiBang(type); // 调用地磅处理函数
			}
			break;

		
		default:
			if(m_Start==1)
			{
				m_dibang_data[m_dibang_data_pos] = str[i];
				m_dibang_data_pos++;
			}
			break;
		}
	}

	return 0;
}

// 地磅数据处理函数
void CClientDlg::OnDiBang(int type)
{
		// 错误的地磅数据处理
	if(type==0) return; // 如果没有符合地磅的数据直接返回
	
	// 旧地磅数据处理
	if(type==1)
	{
		// 旧地磅数据格式
		// 02 2B 30 30 30 30 30 30 30 31 42 03 #  0KG
		// 02 2B 30 30 30 30 38 30 30 31 33 03 # 80KG
		// 02 开始符号
		// 2B "+" 正数
		// 30 30 30 30 38 30 "000080" 表示80KG
		// 30 未知作用，可能也是重量的一部分
		// 31 33 可能是校验值
		// 03 结束符号
		if(m_dibang_data[0]==0x02 && m_dibang_data[1]==0x2B)
		{
			m_Weight[0] = m_dibang_data[2]; // 百吨
			m_Weight[1] = m_dibang_data[3]; // 十吨
			m_Weight[2] = m_dibang_data[4]; // 顿
			m_Weight[3] = m_dibang_data[5]; // 百公斤
			m_Weight[4] = m_dibang_data[6]; // 十公斤
			m_Weight[5] = m_dibang_data[7]; // 千克
			// 这里忽略掉后面的4个字节，直接结束。
			m_Weight[6] = 0x00; // 字符串结束标志
		}
	}

	// 新地磅数据处理
	if(type==2)
	{
		// 新地磅数据格式
		// 02 31 30 20 20 20 20 20 20 20 20 20 20 30 30 0D
		// 02 开始符号
		// 31 30 未知作用，会有变化。
		// 20 20 20 20 20 20 20 20 20 20 重量
		// 30 30 未知作用，未见变化。
		// 0D 结束标志
		
		int i=0;
		int j=0;
		while(m_dibang_data[i]!=0x0D) // 循环数据，直到遇到0x0D
		{
			if(m_dibang_data[i]==0x02) // 遇到开始标志 0x02
			{
				i+=3; // 跳过三个字符，一般为0x02 0x31 0x30 未知作用。
			}
			if(m_dibang_data[i]==0x20) // 如果遇到空格标志 0x20 则忽略
			{
				i++;
			}
			else
			{
				m_Weight[j] = m_dibang_data[i];
//				printf("char  = 0x%02X\n",m_dibang_data[i]);
				j++;
				if(m_dibang_data[i+1]==0x20) // 如果下一个字符为0x20表示已经获取完重量了，后面的数据忽略。
				{
					m_Weight[j] = 0x00; // 直接给后一个字符赋值0x00，结束字符串。
					j=0;
					break; // 跳出循环，继续执行，以便显示重量
				}
				i++;
			}
		}
	}

//	printf("m_Weight = %s \n",m_Weight);

	iWeight2 = atoi((char*)m_Weight); // 将字符型重量的值转换为数字型
	CString strWeight;
	strWeight.Format(_T("%d"),iWeight2);
	m_zhongliang.SetWindowText(strWeight); // 实时显示重量
}

// 计算金额
void CClientDlg::CalcJinE()
{
	// 获得净重
	CString JingZhong;
	m_jingzhong.GetWindowText(JingZhong);
	int iJingZhong = _ttoi(JingZhong);

	// 获得单价
	CString DanJia;
	m_danjia.GetWindowText(DanJia); // 获得单价
	float iDanJia = _ttof(DanJia); // 转换类型

	// 计算吨数 和 金额
	float iDun =0;
	float iJinE=0;
	iDun = (float)((float)iJingZhong/1000); // 吨 = 千克/1000

	if(strcmp(bill.DanJiaDanWei,"立方")==0)
	{
		// 按立方计算
		float LiFang = iDun / (float)atof(bill.MiDu); // 立方 = 吨/密度
		iJinE = iDanJia * LiFang; // 金额 = 单价 * 立方
		GetDlgItem(IDC_STATIC_Dun)->SetWindowText(L"元/立方");
	}
	else if(strcmp(bill.DanJiaDanWei,"吨")==0)
	{
		// 按吨计算
		iJinE = iDanJia * iDun; // 金额 = 单价 * 吨
		GetDlgItem(IDC_STATIC_Dun)->SetWindowText(L"元/吨");
	}

	CString JinE;
	if(iJinE > 0)
	{
		if(strcmp(bill.Type,"0")==0) // 零售
		{
			// 四舍五入个位数到十位数
			int a = 0;
			int b = 0;
			a = (int)iJinE; // 强制浮点转整数，舍去小数部分，非四舍五入
			b=a%10;//求余数,得到最后一位  
			if (b>=5) // 五入
				a=(a/10+1)*10; // 十位加一,乘于十倍
			else // 四舍
				a=(a/10)*10; // 舍去个位,乘于十倍
			/////////////////////////////
			JinE.Format(_T("%d"),a);
		}
		else // 预付款或月售
		{
			JinE.Format(_T("%.2f"),iJinE); // 保留小数点后两位
		}
		m_jine.SetWindowText(JinE); // 设置金额
	}
}

// 预览按钮
void CClientDlg::OnBnClickedButtonCom1Send()
{
	// TODO: 在此添加控件通知处理程序代码
	// 执行预览
	CPrintFrame *frame = new CPrintFrame();
	frame->Create(_T("打印预览"), this,TRUE );
}

BOOL CClientDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message==WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_RETURN: // 回车按键
			//MessageBox("回车");
			//if(GetFocus()->GetDlgCtrlID() != IDOK)
			//{
			//	pMsg->wParam = VK_TAB;
			//}
			CWnd *wnd =GetFocus();
			if(wnd != NULL)
			{
				TCHAR str[256];
				CString ClassName = _T("Button");
				GetClassName(wnd->m_hWnd,str,256);
				UINT i = wnd->GetDlgCtrlID(); // 获得控件的编号
				if(ClassName == str) // 如果是按钮控件
				{
					SendMessage(WM_COMMAND,i,(LPARAM)wnd->m_hWnd); // 发送按钮消息
				}
				if(i == IDC_EDIT_DANHAO) // 如果是“单号”控件
				{
					SendMessage(WM_COMMAND,IDC_BUTTON_GET,(LPARAM)wnd->m_hWnd); // 发送“获取”按钮消息
					return TRUE;
				}
				if(i== IDC_EDIT_CHEHAO) // 如果是“车号”控件
				{
					// 请求获得车号对应的信息
					USES_CONVERSION;
					CString strCheHao;
					m_chehao.GetWindowText(strCheHao);

					char url[256]={0};
					strcat_s(url,"http://");
					strcat_s(url,conf.ip);
					strcat_s(url,"/");
					strcat_s(url,"getchehao.php");
					strcat_s(url,"?");
					strcat_s(url,"chehao=");
					strcat_s(url,W2CA(strCheHao));

					CURLcode res;
	
					curl_easy_setopt(curl,CURLOPT_URL,url);
					curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, chehao_data);
					curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
					curl_easy_setopt(curl,CURLOPT_COOKIEFILE,"");
					res = curl_easy_perform(curl);
					m_chexing.SetFocus();
					return TRUE;
				}

					pMsg->wParam = VK_TAB; // 跳到下一个控件
			}
			break;
//		case VK_ESCAPE: // ESC 按键
//			break;
		}
	}

	if(pMsg->message==WM_SYSKEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_F4: // ALT + F4按键 通常用来退出程序
			MessageBox(_T("F4"));
			return TRUE; // 跳出，不执行退出程序
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

// 重新打开串口
void CClientDlg::OnBnClickedButtonComConn()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;

	Comm_.SetWnd(this->m_hWnd); // 串口关联窗口
	if (!Comm_.Open(conf.com1_id,A2W(conf.com1_para))) // 打开串口
	{
		m_com1.SetWindowText(_T("打开失败"));
		MessageBox(L"串口打开失败", L"串口", MB_ICONHAND);
	}
	else
	{
		char tmp[64] = {0};
		sprintf_s(tmp,"COM%d:%s",conf.com1_id,conf.com1_para);
		USES_CONVERSION;
		m_com1.SetWindowText(A2CW(tmp));
	}
}

// 登录
void CClientDlg::OnBnClickedButtonLogin()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	CString strUser, strPasswd;
	m_user.GetWindowText(strUser); // 获得用户名
	m_pwd.GetWindowText(strPasswd); // 获得密码

	char url[256]={0};
	strcat_s(url,"http://");
	strcat_s(url,conf.ip);
	strcat_s(url,"/");
	strcat_s(url,"login.php");
	strcat_s(url,"?");
	strcat_s(url,"User=");
	strcat_s(url,W2A(strUser));
	strcat_s(url,"&");
	strcat_s(url,"Passwd=");
	strcat_s(url,W2A(strPasswd));
	strcat_s(url,"&");
	strcat_s(url,"Level=1");

	CURLcode res;
	
	curl_easy_setopt(curl,CURLOPT_URL,url);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5); // 如果5秒内无法连接，则直接退出。
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, login_data);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
	curl_easy_setopt(curl,CURLOPT_COOKIEFILE,"");
	res = curl_easy_perform(curl);

	if(res==CURLE_OK) // 返回成功
	{
		struct curl_slist *cookies = NULL;
		curl_easy_getinfo(curl,CURLINFO_COOKIELIST,&cookies);
		if(cookies == NULL)
		{
			MessageBox(L"登陆失败！\n未返回Cookie数据。",L"登陆",MB_ICONHAND);
			return; // 退出
		}
		if(cookies->next == NULL) // 判断是否有第二个cookie。这里应该判断AID。
		{
			m_isLogin = 0;
			MessageBox(L"用户名或密码错误！！",L"登陆",MB_ICONHAND);
			OnBnClickedButtonLogout(); // 登出
			m_id.EnableWindow(FALSE); // 禁用
			return; // 退出
		}
		else
		{
			m_isLogin = 1; // 登陆成功

			// 处理用户名文件 user.dat
			FILE *f;
			fopen_s(&f,"user.dat","wt");
			if(f!=NULL)
			{
				POSITION pos = m_UserList.GetHeadPosition(); // 获得链表的头位置
				CString strUser1,strUser2;
				m_user.GetWindowText(strUser1);
				m_UserList.AddTail(strUser1); // 添加到链表尾
				char *str = W2A(strUser1); // 转换格式
				fputs(str,f); // 写入一行文本
				fputs("\n",f); // 写入回车换行
				while(pos != NULL) // 循环用户名链表
				{
					strUser2 = m_UserList.GetNext(pos); // 获得链表的内容
					if(strUser1.Compare(strUser2)!=0) // 比较登陆的用户是否等于链表中的用户
					{
						if(strUser2.Compare(L"")==0) break;
						m_UserList.AddTail(strUser1); // 不在链表中则添加到链表尾
						str = W2A(strUser2);
						fputs(str,f); // 写入一行文本
						fputs("\n",f); // 写入回车换行
					}
				}
				fclose(f); // 关闭文件
			}

			
		}
		OnCbnSelchangeComboHuowu(); // 获得货物对应的规格数据
	}
	else
	{
		MessageBox(L"连接服务器超时，请检查服务器地址和端口是否正确。",L"连接",MB_ICONHAND);
	}
}

// 登出
void CClientDlg::OnBnClickedButtonLogout()
{
	// TODO: 在此添加控件通知处理程序代码
	m_isLogin = 0; 

	OnBnClickedButtonQuxiao(); // 调用“取消”按钮
	m_id.EnableWindow(FALSE); // 禁用“单号”输入框
	m_list.DeleteAllItems(); // 清空LIST所有内容

	m_user.SetWindowText(_T("")); // 设置用户框为空
	m_user.EnableWindow(TRUE); // 设置用户框为可读写

	m_pwd.SetWindowText(_T("")); // 设置密码框为空
	m_pwd.EnableWindow(TRUE); // 设置密码框为可读写

	m_btn_login.EnableWindow(TRUE); // 设置登陆按钮为可操作
	m_user.SetFocus(); // 设置“用户”输入框为焦点
}

// 定时器
void CClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(nIDEvent)
	{
	case 1: // 定时器1
		OnCheLiang(); // 发生车辆在场信息请求
		return;
	}
	CDialogEx::OnTimer(nIDEvent);
}

// 提交按钮
void CClientDlg::OnBnClickedButtonTijiao()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;

	CString strDanHao,strCheHao,strCheXing; // 单号，车号，车型
	CString strDanWei,strDianHua; // 单位，电话
	CString strHuoWu,strGuiGe; // 货物，规格
	CString strPiZhong,strMaoZhong,strJingZhong; // 皮重，毛重，净重
	CString strDanJia,strJinE; // 单价，金额
	CString strBeiZhu; // 备注信息
	CString strUser; // 司磅员

	m_id.GetWindowText(strDanHao); // 单号
	m_chehao.GetWindowText(strCheHao); // 车号
	m_chexing.GetWindowText(strCheXing); // 车型
	m_danwei.GetWindowText(strDanWei); // 单位
	m_dianhua.GetWindowText(strDianHua); // 电话
	m_huowu.GetWindowText(strHuoWu); // 货物
	m_guige.GetWindowText(strGuiGe); // 规格
	m_pizhong.GetWindowText(strPiZhong); // 皮重
	m_maozhong.GetWindowText(strMaoZhong); // 毛重
	m_jingzhong.GetWindowText(strJingZhong); // 净重
	m_danjia.GetWindowText(strDanJia); // 单价
	m_jine.GetWindowText(strJinE); // 金额
	m_user.GetWindowText(strUser); // 操作员
	
	strBeiZhu.Format(L"%s",A2W(bill.BeiZhu));
	if(m_shoudong.GetCheck())
	{
		strBeiZhu += L"皮 ";
	}
	if(m_youhui.GetCheck())
	{
		strBeiZhu += L"惠 ";
	}

	// 判断值是否为空，并处理
	if(strJinE.Compare(L"")==0)
	{
		strJinE = "0";
	}

	// 设置 bill 结构
	strcpy(bill.DanHao,W2A(strDanHao)); // 单号
	strcpy(bill.CheHao,W2A(strCheHao)); // 车号
	strcpy(bill.CheXing,W2A(strCheXing)); // 车型
	strcpy(bill.DanWei,W2A(strDanWei)); // 收货单位
	strcpy(bill.DianHua,W2A(strDianHua)); // 电话
	strcpy(bill.HuoWu,W2A(strHuoWu)); // 货物名称
	strcpy(bill.GuiGe,W2A(strGuiGe)); // 货物规格
	strcpy(bill.PiZhong,W2A(strPiZhong)); // 皮重
	strcpy(bill.MaoZhong,W2A(strMaoZhong)); // 毛重
	strcpy(bill.JingZhong,W2A(strJingZhong)); // 净重
	strcpy(bill.DanJia,W2A(strDanJia)); // 单价
	strcpy(bill.JinE,W2A(strJinE)); // 金额
	strcpy(bill.BeiZhu,W2A(strBeiZhu)); // 备注
	strcpy(bill.SiBangYuan,W2A(strUser)); // 司磅员

	// 如果毛重为空，表示第一次提交
	if(m_post_id==1 || m_post_id==3)
	{
		if(strPiZhong.IsEmpty()||strPiZhong.Compare(L"0")==0) // 如果皮重为空
		{
			MessageBox(L"\"皮重\"不能为0或空，检查地磅线路等是否正常！",L"地磅",MB_ICONASTERISK);
			return;
		}
	}
	else if(m_post_id==2)// 第二次提交
	{
		if(strJingZhong.IsEmpty()||strJingZhong.Compare(L"0")==0)
		{
			MessageBox(L"\"净重\"不能为0或空，检查地磅线路等是否正常！",L"地磅",MB_ICONASTERISK);
			return;
		}
	}

	char data[1024]={0};
	sprintf_s(data,"DanHao=%s&",W2A(strDanHao)); // 单号
	sprintf_s(data,"%sCheHao=%s&",data,W2A(strCheHao)); // 车号
	sprintf_s(data,"%sCheXing=%s&",data,W2A(strCheXing)); // 车型
	sprintf_s(data,"%sDanWei=%s&",data,W2A(strDanWei)); // 单位
//	sprintf_s(data,"%sDianHua=%s&",data,W2A(strDianHua)); // 电话
	sprintf_s(data,"%sHuoWu=%s&",data,W2A(strHuoWu)); // 货物
	sprintf_s(data,"%sGuiGe=%s&",data,W2A(strGuiGe)); // 规格
	sprintf_s(data,"%sPiZhong=%s&",data,W2A(strPiZhong)); //皮重
	sprintf_s(data,"%sMaoZhong=%s&",data,W2A(strMaoZhong)); // 毛重
	sprintf_s(data,"%sJiangZhong=%s&",data,W2A(strJingZhong)); // 净重
	sprintf_s(data,"%sDanJia=%s&",data,W2A(strDanJia)); // 单价  
	sprintf_s(data,"%sJinE=%s&",data,W2A(strJinE)); // 金额
	sprintf_s(data,"%sZhuangTai=%d&",data,m_post_id); // 状态
	sprintf_s(data,"%sBeiZhu=%s&",data,W2A(strBeiZhu)); // 备注信息
	sprintf_s(data,"%sSiBangYuan=%s",data, W2A(strUser)); // 司磅员

	char url[256]={0};
	strcat_s(url,"http://");
	strcat_s(url,conf.ip);
	strcat_s(url,"/");
	strcat_s(url,"post.php");

	CURLcode res;
	curl_easy_setopt(curl,CURLOPT_URL,url);
	curl_easy_setopt(curl, CURLOPT_POST, 1L);  
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data); // POST 的数据
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, post_data); // 提交返回的数据
	curl_easy_setopt( curl, CURLOPT_WRITEDATA, this ); 
	res = curl_easy_perform(curl);

	// 获得车辆在场信息
	OnCheLiang();
}

// 打印按钮
void CClientDlg::OnBnClickedButtonDayin()
{
	// TODO: 在此添加控件通知处理程序代码
	// 执行打印
	DoPrint(); // 打印核心调用

	OnBnClickedButtonQuxiao(); // 调用“取消”按钮
}

// 获取单据信息
void CClientDlg::OnBnClickedButtonGet()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	CString strDanHao;
	m_id.GetWindowText(strDanHao); // 获得单号

	if(strDanHao.IsEmpty())
	{
		strDanHao = L"0";
		m_post_id = 1; // 获得新单号
	}
	else
	{
		int i = _ttoi(strDanHao); // 将单号转为整数
		if(i==0) // 如果单号全为0
		{
			MessageBox(L"单号不能全为：0",L"单号",MB_ICONHAND);
			return;
		}
		m_post_id = 2; // 根据单号查单据
	}

	char url[256]={0};
	strcat_s(url,"http://");
	strcat_s(url,conf.ip);
	strcat_s(url,"/");
	strcat_s(url,"getid.php");
	strcat_s(url,"?");
	strcat_s(url,"id=");
	strcat_s(url,W2A(strDanHao));

	CURLcode res;
	
	curl_easy_setopt(curl,CURLOPT_URL,url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, getid_data);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
	res = curl_easy_perform(curl);

	if(res == CURLE_OK)
	{
		// 显示单据的数据
		if(m_post_id==2)ShowBill();
		if(strcmp(bill.ZhuangTai,"0")==0) // 如果已经第一次提交
		{
			m_chehao.EnableWindow(FALSE); // 禁用车号
			m_chexing.EnableWindow(FALSE); // 禁用车型
			m_huowu.EnableWindow(FALSE); // 禁用货物
			m_guige.EnableWindow(FALSE); // 禁用规格
			m_danwei.EnableWindow(FALSE); // 禁用单位

			m_gaidan.EnableWindow(TRUE); // 启用改单按钮
		}

		if(strcmp(bill.ZhuangTai,"1")==0) // 如果已经第二次提交，则禁止再提交数据。
		{
			m_chehao.EnableWindow(FALSE); // 禁用车号
			m_chexing.EnableWindow(FALSE); // 禁用车型
			m_huowu.EnableWindow(FALSE); // 禁用货物
			m_guige.EnableWindow(FALSE); // 禁用规格
			m_danwei.EnableWindow(FALSE); // 禁用单位

			m_tijiao.EnableWindow(FALSE); // 禁用提交按钮
			m_gaidan.EnableWindow(FALSE); // 禁用改单按钮
		}
	}
}

// 编辑按钮
void CClientDlg::OnBnClickedButtonEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pizhong.EnableWindow(TRUE); // 皮重
	m_maozhong.EnableWindow(TRUE); // 毛重
	m_jingzhong.EnableWindow(TRUE); // 净重
	m_danjia.EnableWindow(TRUE); // 单价
	m_jine.EnableWindow(TRUE); // 金额
	m_tijiao.EnableWindow(TRUE); // 提交
	m_dayin.EnableWindow(TRUE); // 打印
}

// 打印相关
//设置字体并求出一页的行数，行高，边距，行宽这些基本参数
LRESULT CClientDlg::OnBeginPrinting(WPARAM wParam,LPARAM lParam) 
{
	CDC* p_dc			= (CDC*)wParam;
	CPrintInfo* p_info	= (CPrintInfo *)lParam;
	p_info->SetMaxPage(1);
	m_printer.reset();
	m_printer = std::tr1::shared_ptr<CPrinter>(new CPrinter(p_dc));
	m_printer->SetTotalLineNumber(10);
	m_printer->PreparePrinting();

	USES_CONVERSION;
	m_printer->m_title = A2W(conf.title); // 标题
	m_printer->m_id = A2W(bill.DanHao); // 单号
	m_printer->m_CheHao = (bill.CheHao); // 车号
	m_printer->m_CheXing = A2W(bill.CheXing); // 车型
	m_printer->m_DanWei = A2W(bill.DanWei); // 客户（单位）
	m_printer->m_DianHua = A2W(bill.DianHua); // 电话
	m_printer->m_HuoWu = A2W(bill.HuoWu); // 货物
	m_printer->m_GuiGe = A2W(bill.GuiGe); // 规格
	m_printer->m_PiZhong = A2W(bill.PiZhong); // 皮重
	m_printer->m_MaoZhong = A2W(bill.MaoZhong); // 毛重
	m_printer->m_JingZhong= A2W(bill.JingZhong); // 净重
	m_printer->m_DanJia = A2W(bill.DanJia); // 单价
	m_printer->m_DanJiaDanWei = A2W(bill.DanJiaDanWei); // 单价的单位
	m_printer->m_JinE = A2W(bill.JinE); // 金额
	m_printer->m_BeiZhu = A2W(bill.BeiZhu); // 备注
	m_printer->m_User = A2W(bill.SiBangYuan); // 司磅员
	m_printer->m_Times = m_post_id; // 提交次数
	m_printer->m_Type = atoi(bill.Type); // 支付类型
	
	return TRUE;
}
LRESULT CClientDlg::OnEndPrinting(WPARAM wParam,LPARAM lParam) 
{
	return 0;
}

//具体的打印过程
LRESULT CClientDlg::OnMyPrint(WPARAM wParam,LPARAM lParam)
{
	CDC* p_dc = reinterpret_cast<CDC*>(wParam);
	CPrintInfo* p_info = reinterpret_cast<CPrintInfo*>(lParam);

	if( p_info->m_nCurPage == 1 )
	{
		//画出第一页的内容
		m_printer->SetCurrentPage(0);
		m_printer->StartPage();
		m_printer->PrintHeader();
		m_printer->PrintBody();
		m_printer->EndPage();
		m_printer->EndPrinting();
	}
	return 0;
}

void CClientDlg::DoPrint()
{
	CPrintDialog dlg(FALSE,
		PD_ALLPAGES |
		PD_HIDEPRINTTOFILE |
		PD_NOPAGENUMS |
		PD_RETURNDC |
		PD_USEDEVMODECOPIES|PD_NOSELECTION);
	//全部打印

	if( IDOK == dlg.DoModal() ) // 显示打印对话框
	{
		CDC dc;
		dc.Attach(dlg.m_pd.hDC);
		std::tr1::shared_ptr<CPrinter> m_printer(new CPrinter(&dc));
		m_printer->SetTotalLineNumber(10);//如果是列表控件的内容，告诉printer有多少行
		m_printer->PreparePrinting();

		// 设置石场相关变量
		USES_CONVERSION;
		m_printer->m_title = A2W(conf.title); // 标题
		m_printer->m_id = A2W(bill.DanHao); // 单号
		m_printer->m_CheHao = (bill.CheHao); // 车号
		m_printer->m_CheXing = A2W(bill.CheXing); // 车型
		m_printer->m_DanWei = A2W(bill.DanWei); // 客户（单位）
		m_printer->m_DianHua = A2W(bill.DianHua); // 电话
		m_printer->m_HuoWu = A2W(bill.HuoWu); // 货物
		m_printer->m_GuiGe = A2W(bill.GuiGe); // 规格
		m_printer->m_PiZhong = A2W(bill.PiZhong); // 皮重
		m_printer->m_MaoZhong = A2W(bill.MaoZhong); // 毛重
		m_printer->m_JingZhong= A2W(bill.JingZhong); // 净重
		m_printer->m_DanJia = A2W(bill.DanJia); // 单价
		m_printer->m_DanJiaDanWei = A2W(bill.DanJiaDanWei); // 单价的单位
		m_printer->m_JinE = A2W(bill.JinE); // 金额
		m_printer->m_BeiZhu = A2W(bill.BeiZhu); // 备注
		m_printer->m_User = A2W(bill.SiBangYuan); // 司磅员
		m_printer->m_Times = m_post_id; // 提交次数
		m_printer->m_Type = atoi(bill.Type); // 支付类型
		memset(&bill,0,sizeof(BILL));

		if(m_printer->StartPrinting()) // 开始打印
		{
			while ( m_printer->NeedStartNewPage() )
			{
				m_printer->StartPage();
				//打印内容，自己分页
				m_printer->PrintHeader();
				m_printer->PrintBody();
				m_printer->EndPage();
			}
			m_printer->EndPrinting();
		}
		::DeleteDC(dc.Detach());
	}
}


LRESULT CClientDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	if( WM_BEGIN_PRINTING == message )
	{
		this->OnBeginPrinting(wParam,lParam);
	}
	else if( WM_END_PRINTING == message )
	{
		this->OnEndPrinting(wParam,lParam);
	}
	else if( WM_MY_PRINT == message )
	{
		this->OnMyPrint(wParam,lParam);
	}
	else if( WM_MODAL_PRINT == message )
	{
		this->DoPrint();
	}
	return CDialogEx::WindowProc(message, wParam, lParam);
}

// 交接班按钮
void CClientDlg::OnBnClickedButtonJiaojie()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;

	CString strType;
	int iType=0;
	m_type.GetWindowText(strType);
	if(strType.Compare(L"全部")==0) iType=-1;
	if(strType.Compare(L"零售")==0) iType=0;
	if(strType.Compare(L"预付款")==0) iType=1;
	if(strType.Compare(L"月结")==0) iType=2;

	CString strStart,strEnd,strUser;
	m_Date_Start.GetWindowText(strStart); // 获得开始时间
	m_Date_End.GetWindowText(strEnd); // 获得结束时间
	m_user.GetWindowText(strUser); // 获得用户名
	if(strUser.Compare(L"")==0)
	{
		MessageBox(L"请先登录，再下载！！",L"交接班报表",MB_ICONHAND);
		return;
	}

	m_jiaojie.EnableWindow(FALSE); // 禁用下载报表按钮
	m_jiaojie.SetWindowText(L"正在下载...");

	// 获得程序运行的当前路径
	CString strPath;
	if(strcmp(conf.path,"")==0) // 如果配置文件中没有设置路径
	{
		LPWSTR path = new wchar_t[MAX_PATH];   
		GetCurrentDirectory(MAX_PATH,path);
		strPath.Format(L"%s",path);
	}
	else
	{
		
		strPath = A2W(conf.path);
	}
	
	// 转换时间为文件名的一部分
	CTime Start_Time,End_Time;
	m_Date_Start.GetTime(Start_Time);
	m_Date_End.GetTime(End_Time);
	CString strStartTime,strEndTime;
	strStartTime.Format(_T("%04d%02d%02d%02d"),Start_Time.GetYear(),Start_Time.GetMonth(),Start_Time.GetDay(),Start_Time.GetHour());
	strEndTime.Format(_T("%04d%02d%02d%02d"),End_Time.GetYear(),End_Time.GetMonth(),End_Time.GetDay(),End_Time.GetHour());

	CString strFileName;
	strFileName.Format(L"%s\\report_%s_%s-%s_%s.xls",strPath,strUser,strStartTime,strEndTime,strType);

	FILE *fp;
	fopen_s(&fp,W2A(strFileName),"wb"); // 保存文件及位置

	char url[256]={0};
	strcat_s(url,"http://");
	strcat_s(url,conf.ip);
	strcat_s(url,"/");
	strcat_s(url,"Report_Excel.php");

	char data[1024]={0};
	sprintf_s(data,"SiBangYuan=%s&",W2A(strUser)); // 司磅员
	if(iType!=-1) sprintf_s(data,"%sType=%d&",data, iType); // 支付类型为零售
	sprintf_s(data,"%sstart=%s&",data,W2A(strStart)); // 开始
	sprintf_s(data,"%send=%s",data,W2A(strEnd)); // 结束

	CURLcode res;
	curl_easy_setopt(curl,CURLOPT_URL,url);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60); // 如果1分钟内无法连接，则直接退出。
	curl_easy_setopt(curl, CURLOPT_POST, 1L);  
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data); // POST 的数据
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, report_data); // 提交返回的数据
	curl_easy_setopt( curl, CURLOPT_WRITEDATA, fp ); 
	res = curl_easy_perform(curl);

	fclose(fp); // 关闭文件，提前关闭，避免等待关闭通知框
	if(res==0)
	{
		MessageBox(L"文件保存成功！！",L"下载报表",MB_ICONASTERISK);
	}
	else
	{
		MessageBox(L"下载超时，失败！！",L"下载报表",MB_ICONASTERISK);
	}
	m_jiaojie.SetWindowText(L"下载报表(&R)");
	m_jiaojie.EnableWindow(TRUE); // 启用下载报表按钮
}

// 修改单价
void CClientDlg::OnEnChangeEditDanjia()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CalcJinE(); // 计算金额
}

// 修改净重
void CClientDlg::OnEnChangeEditJingzhong()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CalcJinE(); // 计算金额
}

// 修改货物
void CClientDlg::OnCbnSelchangeComboHuowu()
{
	// TODO: 在此添加控件通知处理程序代码
	// 当修改货物时，发送HTTP请求，获得指定货物的所有规格
	m_guige.ResetContent();
	
	USES_CONVERSION;
	CString strHuoWu; 

	int pos = m_huowu.GetCurSel(); // 获得当前选项的序号
	m_huowu.GetLBText(pos,strHuoWu); // 获得指定序号的文字

	char url[256]={0};
	strcat_s(url,"http://");
	strcat_s(url,conf.ip);
	strcat_s(url,"/");
	strcat_s(url,"getguige.php");
	strcat_s(url,"?");
	strcat_s(url,"huowu=");
	strcat_s(url,W2A(strHuoWu));

	CURLcode res;
	curl_easy_setopt(curl,CURLOPT_URL,url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, guige_data);
	curl_easy_setopt( curl, CURLOPT_WRITEDATA, this ); 
	res = curl_easy_perform(curl);
}

// 修改车型
void CClientDlg::OnCbnSelchangeComboChexing()
{
	// TODO: 在此添加控件通知处理程序代码
	CalcJinE(); // 计算金额
}

// 取重量按钮
void CClientDlg::OnBnClickedButtonZhongliang()
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	CString strWeight;
	int iWeight = atoi((char*)m_Weight);
	strWeight.Format(_T("%d"),iWeight);
	// 设置第一次过磅和第二次过磅的皮重和毛重
	// 皮重
	if(m_post_id == 1)
	{
		m_pizhong.SetWindowText(strWeight); // 将值显示在皮重控件中。
	}

	// 毛重
	if(m_post_id == 2)
	{
		m_maozhong.SetWindowText(strWeight); // 将值显示在毛重控件中。
		// 净重 = 毛重 - 皮重 
		int iJingZhong,iMaoZhong,iPiZhong;
		CString MaoZhong,PiZhong,JingZhong;

		m_maozhong.GetWindowText(MaoZhong); // 获得毛重
		iMaoZhong = _ttoi(MaoZhong); // 将毛重转为整数 

		m_pizhong.GetWindowText(PiZhong); // 获得皮重
		iPiZhong = _ttoi(PiZhong); // 将皮重转为整数 

		iJingZhong = iMaoZhong - iPiZhong; // 计算净重
		JingZhong.Format(_T("%d"),iJingZhong);
		m_jingzhong.SetWindowText(JingZhong); // 将值显示在净重控件中。
		CalcJinE(); // 计算金额
	}
}

// 点击手动复选框
void CClientDlg::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	// 1、判断“优惠”复选框是否选择
	// 2、允许修改“金额”编辑框
	// 3、备注为“手动”
	if(m_shoudong.GetCheck()) // 选中状态
	{
		m_pizhong.EnableWindow(TRUE); // 启用“皮重”控件
		m_pizhong.SetReadOnly(FALSE); // 设“皮重”为非只读
		m_pizhong.SetFocus(); // 设置“皮重”文本框为焦点
		// 设置备注为“手动”
	}
	else // 未选中状态
	{
		m_pizhong.EnableWindow(FALSE); // 启用“皮重”控件
		m_pizhong.SetReadOnly(TRUE); // 设“皮重”为非只读
	}
	
}

// 点击优惠复选框
void CClientDlg::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	if( m_youhui.GetCheck()) // 选中状态
	{
		m_jine.EnableWindow(TRUE); // 启用“金额”控件
		m_jine.SetReadOnly(FALSE); // 设“金额”为非只读
		m_jine.SetFocus(); // 设置“金额”文本框为焦点
		// 设置备注为“优惠”
	}
	else // 未选中状态
	{
		m_jine.EnableWindow(FALSE); // 启用“金额”控件
		m_jine.SetReadOnly(TRUE); // 设“金额”为非只读
	}
}

// LIST双击事件处理
void CClientDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nItem = pNMListView->iItem;  // 这就是双击的item的序号
//	int nSubItem = pNMListView->iSubItem; // 这是对应的子项号
	CString sText = m_list.GetItemText(nItem, 0); // 取得这行第一列的值
	if(sText.Compare(L"")==0) return; // 如果单号为空，则返回不处理
	m_list.ModifyStyle(NULL, LVS_SHOWSELALWAYS, 0);
	m_list.SetItemState(nItem, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
	m_id.SetWindowText(sText); // 设置单号
	OnBnClickedButtonGet(); // 获得单据信息
//	m_dayin.EnableWindow(TRUE); // 开启“打印”按钮
	*pResult = 0;
}

// 取消按钮
void CClientDlg::OnBnClickedButtonQuxiao()
{
	// TODO: 在此添加控件通知处理程序代码
	memset(&bill,0,sizeof(BILL)); // 清空 bill 结构
	m_chehao.EnableWindow(FALSE); // 禁用“车号”输入框
	m_chexing.EnableWindow(FALSE); // 禁用“车型”输入框
	m_danwei.EnableWindow(FALSE); // 禁用“单位”输入框
	m_huowu.EnableWindow(FALSE); // 禁用“货物”输入框
	m_guige.EnableWindow(FALSE); // 禁用“规格”输入框
	m_pizhong.EnableWindow(FALSE); // 禁用“皮重”输入框
	m_jine.EnableWindow(FALSE); // 禁用“金额”输入框

	m_pizhong.EnableWindow(FALSE); // 皮重
	m_maozhong.EnableWindow(FALSE); // 毛重
	m_jingzhong.EnableWindow(FALSE); // 净重
	m_danjia.EnableWindow(FALSE); // 单价
	m_jine.EnableWindow(FALSE); // 金额

	m_tijiao.EnableWindow(FALSE); // 禁用提交按钮
	m_dayin.EnableWindow(FALSE); // 禁用打印按钮
	m_id.EnableWindow(TRUE); // 启用单号控件

	m_id.SetWindowText(_T("")); // 单号
	m_chehao.SetWindowText(_T("")); // 车号
	m_dianhua.SetWindowText(_T("")); // 电话
	m_danwei.SetCurSel(0); // 收货单位
	m_huowu.SetCurSel(0); // 货物名称
	m_guige.SetCurSel(0); // 货物规格
	m_pizhong.SetWindowText(_T("")); // 皮重
	m_maozhong.SetWindowText(_T("")); // 毛重
	m_jingzhong.SetWindowText(_T("")); // 净重
	m_danjia.SetWindowText(_T("")); // 单价
	m_jine.SetWindowText(_T("")); // 金额
	m_yue.SetWindowText(_T("")); // 余额
	if(m_shoudong.GetCheck()) // 手动
	{
		m_shoudong.SetCheck(FALSE);
	}
	if(m_youhui.GetCheck()) // 优惠
	{
		m_youhui.SetCheck(FALSE);
	}
	m_id.SetFocus(); // 设置单号为焦点
}

// 登陆返回数据
size_t CClientDlg::login_data(void *ptr, size_t size, size_t nmemb, void *userp)
{
	
	CClientDlg *client =(CClientDlg*)userp;

	// 这里处理会员名称
	USES_CONVERSION;
	cJSON *jsonroot = cJSON_Parse((const char*)ptr); //json根
	if(jsonroot)
	{
		client->m_huowu.ResetContent(); // 重置货物列表框
		// 获取货物名称和规格
		CList<CString ,CString> list; // 链表
		cJSON *type = cJSON_GetObjectItem(jsonroot,"type");
		cJSON *next = type->child; // type的子项
		while(next->next != NULL) // type的下一项为空
		{
			char * strHuoWu = next->string; // 货物名称
//			char * strGuiGe = next->valuestring; // 货物规格
			next = next->next; // 移动到type的下一项
			//printf("HuoWu:%s = GuiGe:%s\n",UTF8ToEncode(strHuoWu),UTF8ToEncode(strGuiGe));
			if(list.IsEmpty()) // 如果链表为空
			{
				list.AddTail(A2CW(UTF8ToEncode(strHuoWu))); // 添加到链表尾
				client->m_huowu.AddString(A2CW(UTF8ToEncode(strHuoWu)));
			}
			else // 否则循环是否相同
			{
				POSITION pos = list.GetHeadPosition(); // 获得链表的头位置
				CString pstr1 = A2CW(UTF8ToEncode(strHuoWu));
				CString pstr2;
				int isa = 0;
				while(pos != NULL)   
				{   
					pstr2 = list.GetNext(pos); // 获得内容
					if(pstr1.Compare(pstr2)==0)
					{
						isa = 1;
					}
				}
				if(isa==0)
				{
					list.AddTail(pstr1); // 添加到链表尾
					client->m_huowu.AddString(pstr1);
				}
						
			}
		}
		client->m_huowu.SetCurSel(0); // 货物名称选择第一个项		
				
		// 获取客户名称
		client->m_danwei.ResetContent(); // 清空客户控件中的所有项
		cJSON *member = cJSON_GetObjectItem(jsonroot,"member");
		int size = cJSON_GetArraySize(member); // 获得数组的长度
		for(int i=0;i<size-1;i++) // 循环所有元素，排除最后一个
		{
			cJSON* node;
			node = cJSON_GetArrayItem(member,i);
			client->m_danwei.AddString(A2CW(UTF8ToEncode(node->valuestring))); // 添加会员名称到单位控件下
		}
		client->m_danwei.SetCurSel(0);
	}
	cJSON_Delete(jsonroot);

	client->m_user.EnableWindow(FALSE); // 禁用用户输入框
	client->m_pwd.EnableWindow(FALSE);  // 禁用密码输入框 
	client->m_btn_login.EnableWindow(FALSE); // 禁用登录按钮
	client->m_id.EnableWindow(TRUE); // 启用单号控件
	client->m_id.SetFocus(); // 设置单号为焦点
	
	return size*nmemb;
}

// 单号返回数据
size_t CClientDlg::getid_data(void *ptr, size_t size, size_t nmemb, void *userp)
{
	CClientDlg *client =(CClientDlg*)userp;
	memset(&client->bill,0,sizeof(BILL)); // 清空 单据结构 的内容

	USES_CONVERSION; 
	cJSON *jsonroot = cJSON_Parse((const char*)ptr); //json根
	if(jsonroot)
	{
		if(client->m_post_id ==1) // 获得新的单号
		{
			client->m_id.SetWindowText(A2CW(cJSON_GetObjectItem(jsonroot,"id")->valuestring)); // 设置“单号”

			client->m_chexing.SetCurSel(0); // 选择车型
			client->m_huowu.SetCurSel(0);
			client->m_guige.SetCurSel(0);
			client->m_id.EnableWindow(FALSE); // 禁止“单号”输入框
			client->m_chehao.EnableWindow(TRUE); // 开启“车号”输入框
			client->m_chexing.EnableWindow(TRUE); // 开启“车型”输入框
			client->m_danwei.EnableWindow(TRUE); // 开启“收获”输入框
			client->m_huowu.EnableWindow(TRUE); // 开启“货物”输入框
			client->m_guige.EnableWindow(TRUE); // 开启“规格”输入框
			client->m_tijiao.EnableWindow(TRUE); // 启用“提交”按钮
			client->m_chehao.SetFocus(); // 设置车号为焦点
		}
		else if(client->m_post_id == 2) // 根据单号查询单据
		{
			char *strid = cJSON_GetObjectItem(jsonroot,"id")->valuestring;
			if(strcmp(strid,"0")==0)
			{
				client->MessageBox(L"无此单号！！！",L"单号",MB_ICONHAND);
				return size*nmemb; // 返回函数
			}

			strcpy_s(client->bill.DanHao,cJSON_GetObjectItem(jsonroot,"id")->valuestring); //单号
			strcpy_s(client->bill.CheHao,UTF8ToEncode(cJSON_GetObjectItem(jsonroot,"ch")->valuestring)); //车号
			strcpy_s(client->bill.CheXing,UTF8ToEncode(cJSON_GetObjectItem(jsonroot,"cx")->valuestring)); // 车型
			strcpy_s(client->bill.DianHua,cJSON_GetObjectItem(jsonroot,"dh")->valuestring); // 电话
			strcpy_s(client->bill.DanWei,UTF8ToEncode(cJSON_GetObjectItem(jsonroot,"dw")->valuestring)); // 单位
			strcpy_s(client->bill.HuoWu,UTF8ToEncode(cJSON_GetObjectItem(jsonroot,"hw")->valuestring)); // 货物
			strcpy_s(client->bill.GuiGe,cJSON_GetObjectItem(jsonroot,"gg")->valuestring); // 规格
			strcpy_s(client->bill.PiZhong,cJSON_GetObjectItem(jsonroot,"pz")->valuestring); // 皮重
			strcpy_s(client->bill.MaoZhong,cJSON_GetObjectItem(jsonroot,"mz")->valuestring); // 毛重
			strcpy_s(client->bill.JingZhong,cJSON_GetObjectItem(jsonroot,"jz")->valuestring); // 净重
			strcpy_s(client->bill.DanJia,cJSON_GetObjectItem(jsonroot,"dj")->valuestring); // 单价
			strcpy_s(client->bill.DanJiaDanWei,UTF8ToEncode(cJSON_GetObjectItem(jsonroot,"djdw")->valuestring)); // 单价单位
			strcpy_s(client->bill.MiDu,cJSON_GetObjectItem(jsonroot,"md")->valuestring); // 密度
			strcpy_s(client->bill.JinE,cJSON_GetObjectItem(jsonroot,"je")->valuestring); // 金额
			strcpy_s(client->bill.YuE,cJSON_GetObjectItem(jsonroot,"ye")->valuestring); // 余额
			strcpy_s(client->bill.BeiZhu,UTF8ToEncode(cJSON_GetObjectItem(jsonroot,"bz")->valuestring)); // 备注
			strcpy_s(client->bill.GuoBang1,cJSON_GetObjectItem(jsonroot,"gb1")->valuestring); // 过磅1时间
			strcpy_s(client->bill.GuoBang2,cJSON_GetObjectItem(jsonroot,"gb2")->valuestring); // 过磅2时间
			strcpy_s(client->bill.ChuChang,cJSON_GetObjectItem(jsonroot,"cc")->valuestring); // 出场时间
			strcpy_s(client->bill.SiBangYuan,UTF8ToEncode(cJSON_GetObjectItem(jsonroot,"sby")->valuestring)); // 司磅员
			strcpy_s(client->bill.BaoAnYuan,UTF8ToEncode(cJSON_GetObjectItem(jsonroot,"bay")->valuestring)); // 保安员
			strcpy_s(client->bill.ZhuangTai,cJSON_GetObjectItem(jsonroot,"zt")->valuestring); // 状态
			strcpy_s(client->bill.Type,cJSON_GetObjectItem(jsonroot,"type")->valuestring); // 支付类型

			client->m_id.EnableWindow(FALSE); // 禁止“单号”对话框
			client->m_tijiao.EnableWindow(TRUE); // 启用“提交”按钮
			client->m_chehao.SetFocus(); // 设置车号为焦点
		}
	}
	cJSON_Delete(jsonroot);
	return size*nmemb;
}

// 提交数据返回数据
size_t CClientDlg::post_data(void *ptr, size_t size, size_t nmemb, void *userp)
{
	CClientDlg *client =(CClientDlg*)userp;
	printf("%s\n",ptr);

	USES_CONVERSION;

	char str[16]={0};
	memcpy(str,ptr,5);
	// 这里判断提交是否成功
	if(strcmp(str,"post1")==0)
	{
		client->MessageBox(L"第一次过磅提交成功！",L"提交",MB_ICONASTERISK);
		client->m_tijiao.EnableWindow(FALSE);
	}

	if(strcmp(str,"post2")==0)
	{
		client->MessageBox(L"第二次过磅提交成功！",L"提交",MB_ICONASTERISK);
		client->m_tijiao.EnableWindow(FALSE);
	}

	if(strcmp(str,"post3")==0)
	{
		client->MessageBox(L"改单成功！",L"提交",MB_ICONASTERISK);
		client->m_tijiao.EnableWindow(FALSE);
	}

	if(strcmp(str,"ERROR")==0)
	{
		char str[512] ={0};
		char * temp = (char*)ptr;
		temp+=8;
		memcpy(str,(void*)temp,size*nmemb);
		str[511] = 0x00;
		CString strMsg;
		strMsg.Format(L"提交失败：\n%s",A2W(str));
		client->MessageBox(strMsg,L"提交",MB_ICONHAND);
		client->m_tijiao.EnableWindow(TRUE);
	}

	client->m_dayin.EnableWindow(TRUE);
	return size*nmemb;
}

// 获得规格返回数据
size_t CClientDlg::guige_data(void *ptr, size_t size, size_t nmemb, void *userp)
{
	CClientDlg *client =(CClientDlg*)userp;

	USES_CONVERSION;
	cJSON *jsonroot = cJSON_Parse((const char*)ptr); //json根
	if(jsonroot)
	{
		int size = cJSON_GetArraySize(jsonroot); // 获得数组的长度
		for(int i=0;i<size-1;i++) // 循环所有元素，排除最后一个
		{
			cJSON* node;
			node = cJSON_GetArrayItem(jsonroot,i);
			client->m_guige.AddString(A2CW(UTF8ToEncode(node->valuestring))); // 添加规格到控件下
		}
		client->m_guige.SetCurSel(0);
				
	}
	cJSON_Delete(jsonroot);
	return size*nmemb;
}

// 获得在场车辆返回数据
size_t CClientDlg::cheliang_data(void *ptr, size_t size, size_t nmemb, void *userp)
{
	CClientDlg *client =(CClientDlg*)userp;
	
	// 复制数据到 strCheLiang 缓冲
	memcpy(&client->strCheLiang[client->PosCheLiang],ptr,size*nmemb);
	client->PosCheLiang += size*nmemb;
	client->strCheLiang[client->PosCheLiang] = 0x00;
	return size*nmemb;
}

// 获得车号返回数据
size_t CClientDlg::chehao_data(void *ptr, size_t size, size_t nmemb, void *userp)
{
	CClientDlg *client =(CClientDlg*)userp;
	USES_CONVERSION;

	cJSON *jsonroot = cJSON_Parse((const char*)ptr); //json根
	if(jsonroot)
	{
		int size = cJSON_GetArraySize(jsonroot); // 获得数组的长度
		if(size>1)
		{
			cJSON* node;
			node = cJSON_GetArrayItem(jsonroot,1);
			client->m_chexing.SetWindowText(A2CW(UTF8ToEncode(node->valuestring))); // 车型

			node = cJSON_GetArrayItem(jsonroot,2);
			client->m_danwei.SetWindowText(A2CW(UTF8ToEncode(node->valuestring))); // 单位

			node = cJSON_GetArrayItem(jsonroot,3);
			client->m_huowu.SetWindowText(A2CW(UTF8ToEncode(node->valuestring))); // 货物

			node = cJSON_GetArrayItem(jsonroot,4);
			client->m_guige.SetWindowText(A2CW(UTF8ToEncode(node->valuestring))); // 规格
		}
	}
	cJSON_Delete(jsonroot);
	return size*nmemb;
}

// 车辆在场请求
void CClientDlg::OnCheLiang()
{
	if(m_isLogin == 1) // 判断是否登陆成功
	{
		memset(strCheLiang,0,16*1024);
		PosCheLiang=0;
		char url[256]={0};
		strcat_s(url,"http://");
		strcat_s(url,conf.ip);
		strcat_s(url,"/");
		strcat_s(url,"keepalive.php");

		CURLcode res;
		curl_easy_setopt(curl,CURLOPT_URL,url);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cheliang_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, this); 
		res = curl_easy_perform(curl);

		if(res==0)
		{
			USES_CONVERSION;

			cJSON *jsonroot = cJSON_Parse(strCheLiang); //json根
			if(jsonroot)
			{
				m_list.DeleteAllItems(); // 清空所有内容
				int size = cJSON_GetArraySize(jsonroot); // 获得数组的长度
				CString strCheShu;
				strCheShu.Format(L"%d",size-1);
				m_CheShu.SetWindowText(strCheShu);
				for(int i=0;i<size-1;i++) // 循环所有元素，排除最后一个
				{
					cJSON* node;
					node = cJSON_GetArrayItem(jsonroot,i);

					// 分析 JSON 并插入数据
					int nRow = m_list.InsertItem(0,A2CW(cJSON_GetObjectItem(node,"id")->valuestring));
					m_list.SetItemText(nRow,1,A2CW(UTF8ToEncode(cJSON_GetObjectItem(node,"ch")->valuestring)));
					m_list.SetItemText(nRow,2,A2CW(UTF8ToEncode(cJSON_GetObjectItem(node,"cx")->valuestring)));
					m_list.SetItemText(nRow,3,A2CW(UTF8ToEncode(cJSON_GetObjectItem(node,"hw")->valuestring)));
					m_list.SetItemText(nRow,4,A2CW(UTF8ToEncode(cJSON_GetObjectItem(node,"gg")->valuestring)));
					m_list.SetItemText(nRow,5,A2CW(UTF8ToEncode(cJSON_GetObjectItem(node,"dh")->valuestring)));
					m_list.SetItemText(nRow,6,A2CW(UTF8ToEncode(cJSON_GetObjectItem(node,"dw")->valuestring)));
					m_list.SetItemText(nRow,7,A2CW(UTF8ToEncode(cJSON_GetObjectItem(node,"pz")->valuestring)));
					m_list.SetItemText(nRow,8,A2CW(UTF8ToEncode(cJSON_GetObjectItem(node,"gb")->valuestring)));
					if(strcmp(cJSON_GetObjectItem(node,"zt")->valuestring,"0")==0)
					{
						m_list.SetItemText(nRow,9,L"第1次");
					}
					if(strcmp(cJSON_GetObjectItem(node,"zt")->valuestring,"1")==0)
					{
						m_list.SetItemText(nRow,9,L"第2次");
					}
			
				}
			}
			cJSON_Delete(jsonroot);
		}
		else
		{
//			MessageBox(L"获得在场车辆超时！！！",L"在场车辆",MB_ICONHAND);
		}
	}
}

// 显示单据的数据
void CClientDlg::ShowBill()
{
	USES_CONVERSION; 
	m_chehao.SetWindowText(A2CW(bill.CheHao)); // 车号
	m_chexing.SetWindowText(A2CW(bill.CheXing)); // 车型
	m_dianhua.SetWindowText(A2CW(bill.DianHua)); // 电话
	m_danwei.SetWindowText(A2CW(bill.DanWei)); // 单位
	m_huowu.SetWindowText(A2CW(bill.HuoWu)); // 货物
	m_guige.SetWindowText(A2CW(bill.GuiGe)); // 规格
	m_pizhong.SetWindowText(A2CW(bill.PiZhong)); // 皮重
	m_maozhong.SetWindowText(A2CW(bill.MaoZhong)); // 毛重
	m_jingzhong.SetWindowText(A2CW(bill.JingZhong)); // 净重
	m_danjia.SetWindowText(A2CW(bill.DanJia)); // 单价
	m_jine.SetWindowText(A2CW(bill.JinE)); // 金额
	m_yue.SetWindowText(A2CW(bill.YuE)); // 余额

	// 这里操作单价的单位
}

void CClientDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCheLiang();
}

// 获得交接班报表
size_t CClientDlg::report_data(void *ptr, size_t size, size_t nmemb, void *userp)
{
	int written = fwrite(ptr, size, nmemb , (FILE *)userp); // 写入文件
    return written; 
}

// 控件颜色处理
HBRUSH CClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (GetDlgItem(IDC_EDIT_ZHONGLIANG) == pWnd) // 重量文本框控件
	{
		static HBRUSH   hbrEdit = ::CreateSolidBrush( RGB(255,255,128) ); // （黄）背景颜色
		pDC->SetBkMode( TRANSPARENT ); 
		pDC->SetTextColor( RGB(255,0,0));// （红）字体颜色
		return hbrEdit;
     }
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

// 改单按钮
void CClientDlg::OnBnClickedButtonGaidan()
{
	// TODO: 在此添加控件通知处理程序代码
	m_post_id = 3; // 修改第一次单
	m_chehao.EnableWindow(TRUE); // 启用车号
	m_chexing.EnableWindow(TRUE); // 启用车型
	m_huowu.EnableWindow(TRUE); // 启用货物
	m_guige.EnableWindow(TRUE); // 启用规格
	m_danwei.EnableWindow(TRUE); // 启用单位
	m_dayin.EnableWindow(FALSE); // 禁用打印按钮

	m_danjia.SetWindowText(L""); // 设置单价为空
}
