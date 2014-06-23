
// ClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"
#include "strtoken.h"
#include "uni2utf8.h"
#include "../cjson/cJSON.h"
#include "PrintFrame.h"
#include "PrintView.h"
#include "printer.h"
#include <memory>

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
	SendMessage(WM_CLOSE);
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
	DDX_Control(pDX, IDC_COMBO_CHEXING, m_chexing);
	DDX_Control(pDX, IDC_COMBO_HUOWU, m_huowu);
	DDX_Control(pDX, IDC_COMBO_GUIGE, m_guige);
	DDX_Control(pDX, IDC_EDIT_IP, m_ip);
	DDX_Control(pDX, IDC_EDIT_PORT, m_port);
	DDX_Control(pDX, IDC_EDIT_COM1, m_com1);
	DDX_Control(pDX, IDC_EDIT_USER, m_user);
	DDX_Control(pDX, IDC_EDIT_PWD, m_pwd);
	DDX_Control(pDX, IDC_EDIT_DANHAO, m_id);
	DDX_Control(pDX, IDC_EDIT_CHEHAO, m_chehao);
	DDX_Control(pDX, IDC_EDIT_DIANHUA, m_dianhua);
	DDX_Control(pDX, IDC_EDIT_SHOUHUO, m_shouhuo);
	DDX_Control(pDX, IDC_EDIT_PIZHONG, m_pizhong);
	DDX_Control(pDX, IDC_EDIT_MAOZHONG, m_maozhong);
	DDX_Control(pDX, IDC_EDIT_JINGZHONG, m_jingzhong);
	DDX_Control(pDX, IDC_EDIT_DANJIA, m_danjia);
	DDX_Control(pDX, IDC_EDIT_JINE, m_jine);
	DDX_Control(pDX, IDC_EDIT_YUE, m_yue);
	DDX_Control(pDX, IDC_CHECK1, m_shoudong);
	DDX_Control(pDX, IDC_CHECK2, m_youhui);
	DDX_Control(pDX, IDC_EDIT_ZHONGLIANG, m_zhongliang);
	DDX_Control(pDX, IDC_BUTTON_NET_CONN, m_btn_net);
	DDX_Control(pDX, IDC_BUTTON_LOGIN, m_btn_login);
	DDX_Control(pDX, IDC_BUTTON_DAYIN, m_dayin);
	DDX_Control(pDX, IDC_BUTTON_TIJIAO, m_tijiao);
	DDX_Control(pDX, IDC_LIST1, m_list); // 车辆信息
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_MESSAGE(ON_COM_RECEIVE, On_Receive) // 如果收到 ON_COM_RECEIVE 消息，调用接收函数
	ON_BN_CLICKED(IDC_BUTTON_COM1_SEND, &CClientDlg::OnBnClickedButtonCom1Send)
	ON_BN_CLICKED(IDC_BUTTON_ZHONGLIANG, &CClientDlg::OnBnClickedButtonZhongliang)
	ON_BN_CLICKED(IDC_BUTTON_NET_CONN, &CClientDlg::OnBnClickedButtonNetConn)
	ON_BN_CLICKED(IDC_BUTTON_COM_CONN, &CClientDlg::OnBnClickedButtonComConn)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CClientDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_LOGOUT, &CClientDlg::OnBnClickedButtonLogout)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_TIJIAO, &CClientDlg::OnBnClickedButtonTijiao)
	ON_BN_CLICKED(IDC_BUTTON_DAYIN, &CClientDlg::OnBnClickedButtonDayin)
	ON_BN_CLICKED(IDC_BUTTON_GET, &CClientDlg::OnBnClickedButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &CClientDlg::OnBnClickedButtonEdit)

//	ON_WM_ACTIVATE()
ON_BN_CLICKED(IDC_BUTTON_FIND, &CClientDlg::OnBnClickedButtonFind)
ON_BN_CLICKED(IDC_BUTTON_JIAOJIE, &CClientDlg::OnBnClickedButtonJiaojie)
ON_EN_CHANGE(IDC_EDIT_DANJIA, &CClientDlg::OnEnChangeEditDanjia)
ON_EN_CHANGE(IDC_EDIT_JINGZHONG, &CClientDlg::OnEnChangeEditJingzhong)
ON_CBN_SELCHANGE(IDC_COMBO_HUOWU, &CClientDlg::OnCbnSelchangeComboHuowu)
ON_CBN_SELCHANGE(IDC_COMBO_CHEXING, &CClientDlg::OnCbnSelchangeComboChexing)
ON_BN_CLICKED(IDC_CHECK1, &CClientDlg::OnBnClickedCheck1)
ON_BN_CLICKED(IDC_CHECK2, &CClientDlg::OnBnClickedCheck2)
ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CClientDlg::OnNMDblclkList1)
ON_BN_CLICKED(IDC_BUTTON_QUXIAO, &CClientDlg::OnBnClickedButtonQuxiao)
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

	memset(m_Weight,0,16); // 清空重量的全局变量
	memset(m_dibang_data,0,32); // 清空地磅数据
	m_dibang_data_pos = 0;
	m_Start = 0; // 是否开始收集地磅数据
	m_type = 0;
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
	SetWindow(); // 禁用控件
	m_tijiao.EnableWindow(FALSE); // 禁用“提交”按钮
	m_dayin.EnableWindow(FALSE); // 禁用“打印”按钮

	memset(&conf,0,sizeof(CONF));
	strcpy(conf.title,"海南港口文峰石场");
	strcpy(conf.ip,"192.168.1.5");
	conf.port = 80;
	conf.com1_id=1;
	strcpy(conf.com1_para,"baud=9600 parity=N data=8 stop=1");
	strcpy(conf.cookie,"");
	strcpy(conf.sid,"");
	strcpy(conf.aid,"");

	// 打开配置文件 JSON 格式
	FILE *f=fopen("config","rb"); // 配置文件 config
	if(f==NULL)
	{
		MessageBox(_T("打开配置文件失败！"), _T("config"), MB_OK);
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
			strcpy(conf.title,cJSON_GetObjectItem(jsonroot,"title")->valuestring); // 获得标题

			cJSON *jsonServer=cJSON_GetObjectItem(jsonroot,"server");//取 Server
			strcpy(conf.ip,cJSON_GetObjectItem(jsonServer,"ip")->valuestring); // 获得IP地址
			conf.port = cJSON_GetObjectItem(jsonServer,"port")->valueint; // 获得端口

			cJSON *jsonCOM1=cJSON_GetObjectItem(jsonroot,"com1");//取 COM1
			conf.com1_id = cJSON_GetObjectItem(jsonCOM1,"port")->valueint; // 获得COM端口
			strcpy(conf.com1_para,cJSON_GetObjectItem(jsonCOM1,"para")->valuestring); // 获得COM的属性
		}
		else
		{
			MessageBox(_T("配置文件错误！",_T("config"),MB_OK));
		}
		cJSON_Delete(jsonroot);
	}

	// 设置定时器
	SetTimer(1,10000,0); // 10秒

	// 连接服务器
	OnBnClickedButtonNetConn();

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

	// 重量
	GetDlgItem(IDC_EDIT_ZHONGLIANG)->SetFont(m_Font);

	// 标题
	USES_CONVERSION;  // dali
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
	GetDlgItem(IDC_STATIC_SHOUHUO)->SetFont(m_Font);
	GetDlgItem(IDC_EDIT_SHOUHUO)->SetFont(m_Font);

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

	m_chexing.AddString(_T("大车"));
	m_chexing.AddString(_T("小车"));
	m_chexing.SetCurSel(0); // 选择第一项“大车”

	m_huowu.AddString(_T("青石"));
	m_huowu.AddString(_T("半青石"));
	m_huowu.AddString(_T("石粉"));
	m_huowu.AddString(_T("混合"));
	m_huowu.AddString(_T("峰石"));
	m_huowu.AddString(_T("二片石"));
	m_huowu.SetCurSel(0);

	m_guige.AddString(_T("0.5"));
	m_guige.AddString(_T("1.2"));
	m_guige.AddString(_T("1.3"));
	m_guige.SetCurSel(0);

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

	m_list.InsertColumn(0,L"单号",LVCFMT_CENTER,100);
	m_list.InsertColumn(1,L"车号",LVCFMT_CENTER,80);
	m_list.InsertColumn(2,L"车型",LVCFMT_CENTER,80);
	m_list.InsertColumn(3,L"货物名称",LVCFMT_CENTER,80);
	m_list.InsertColumn(4,L"货物规格",LVCFMT_CENTER,80);
	m_list.InsertColumn(5,L"联系电话",LVCFMT_CENTER,100);
	m_list.InsertColumn(6,L"收货单位",LVCFMT_CENTER,200);
	m_list.InsertColumn(7,L"皮重",LVCFMT_CENTER,100);
	m_list.InsertColumn(8,L"过磅时间",LVCFMT_CENTER,200);
	
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
	unsigned char str[8]={0};
	len = com1.read((char *)str, 2);
	int type = 0; // 用于判断新旧地磅的数据

	switch(str[0]) // 收到的第一个字符
	{
	case 0x02: // 开始标志
		// 开始搜集数据
		if(m_Start==0)
		{
			m_Start = 1;
			m_dibang_data[m_dibang_data_pos] = str[0]; // 将字符赋值给地磅数据的全局变量
			m_dibang_data_pos++; // 地磅数据位置+1
		}
		else
		{
			m_Start==0; // 防止出现多次0x02 而没有 0x0d结束
		}
		return 0; // 返回

	case 0x03:
		// 结束搜集数据
		// 调用协议处理函数，分析数据。
		type = 1; // 旧地磅
		if(m_Start==1)
		{
			m_Start = 0;
			m_dibang_data[m_dibang_data_pos] = str[0];
			m_dibang_data[m_dibang_data_pos+1] = 0x00; // 无需再获取下一个字符了，直接在后面加上0x00结束字符串。
			m_dibang_data_pos = 0; // 初始化地磅数据的位置为0，防止溢出。
			break; // 中断switch继续执行，以便分析地磅数据。
		}
		else
		{
			return 0; // 返回
		}
	case 0x0D: // 结束标志
		// 结束搜集数据
		// 调用协议处理函数，分析数据。
		type = 2; // 新地磅
		if(m_Start==1)
		{
			m_Start = 0;
			m_dibang_data[m_dibang_data_pos] = str[0];
			m_dibang_data[m_dibang_data_pos+1] = 0x00; // 无需再获取下一个字符了，直接在后面加上0x00结束字符串。
			m_dibang_data_pos = 0; // 初始化地磅数据的位置为0，防止溢出。
			break; // 中断switch继续执行，以便分析地磅数据。
		}
		else
		{
			return 0; // 返回
		}
		
	default:
		if(m_Start==1)
		{
			m_dibang_data[m_dibang_data_pos] = str[0];
			m_dibang_data_pos++;
		}
		return 0; // 返回
	}

	// 错误的地磅数据处理
	if(type==0) return 0; // 如果没有符合地磅的数据直接返回
	
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
	m_zhongliang.SetWindowText(strWeight+L"KG"); // 实时显示重量

	return 0;
}

// 计算金额
void CClientDlg::CalcJinE()
{
	// 获得净重
	CString JingZhong;
	m_jingzhong.GetWindowText(JingZhong);
	int iJingZhong = _ttoi(JingZhong);

	// 获得车型
//	CString CheXing;
//	m_chexing.GetWindowText(CheXing);

	// 获得单价
	CString DanJia;
	m_danjia.GetWindowText(DanJia); // 获得单价
	int iDanJia = _ttoi(DanJia); // 转换类型

	// 计算吨数 和 金额
	float iDun =0;
	float iJinE=0;
	iDun = (float)((float)iJingZhong/1000); // 吨 = 千克/1000

//	if(CheXing.Compare(L"大车")==0)
	if(m_danjiadanwei.Compare(L"立方")==0)
	{
		// 按立方计算
		float LiFang = iDun / m_midu; // 立方 = 吨/密度
		iJinE = iDanJia * LiFang; // 金额 = 单价 * 立方
		GetDlgItem(IDC_STATIC_Dun)->SetWindowText(L"元/立方");
	}
//	else if(CheXing.Compare(L"小车")==0)
	else if(m_danjiadanwei.Compare(L"吨")==0)
	{
		// 按吨计算
		iJinE = iDanJia * iDun; // 金额 = 单价 * 吨
		GetDlgItem(IDC_STATIC_Dun)->SetWindowText(L"元/吨");
	}

	if(iJinE > 0)
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

		CString JinE;
		JinE.Format(_T("%d"),a);
		m_jine.SetWindowText(JinE); // 设置金额
	}
}

void CClientDlg::OnBnClickedButtonCom1Send()
{
	// TODO: 在此添加控件通知处理程序代码
	// 执行预览
	CPrintFrame *frame = new CPrintFrame();
	frame->Create(_T("打印预览"), this,TRUE );
}

// 连接网络
void CClientDlg::OnConnected()
{
	USES_CONVERSION;  // dali
	m_ip.SetWindowText(A2CW(conf.ip));
	char tmp[16]={0};
	sprintf(tmp,"%d",conf.port);
	m_port.SetWindowText(A2CW(tmp));
	printf("连接服务器成功\n");
	m_btn_net.SetWindowText(_T("连接成功"));
	m_btn_net.EnableWindow(FALSE);
	//MessageBox("连接成功");
}

// 接收网络数据
void CClientDlg::OnRvc()
{
	memset(&m_net_rvc_data,0,10240);
	m_net_rvc_len = m_Conn.Receive(m_net_rvc_data,10239);
	if (SOCKET_ERROR != m_net_rvc_len)
	{
		printf("%s\n",m_net_rvc_data);
		switch(m_post_id)
		{
		case 1: // 保持连接
			OnKeepalive();
			break;
		case 2: // 用户登录请求
			OnLogin();
			break;
		case 3: // 获得新的账单号
			OnGet1();
			break;
		case 4: // 提交第一次过磅单
			OnPost1();
			break;
		case 5: // 获得第一次过磅的数据，即第二次过磅
			OnGet2();
			break;
		case 6: // 第二次过磅单
			OnPost2();
			break;
		}
	}
}

// 关闭网络
void CClientDlg::OnClose()
{
	m_Conn.Close();
}

void CClientDlg::GetData(char *url, char *para)
{
	char Data[1024] = {0};
	strcat(Data,"GET ");
	strcat(Data,url);
	strcat(Data,"?");
	strcat(Data,para);
	strcat(Data," HTTP/1.1\r\n");
	strcat(Data,"Host: ");
	strcat(Data,conf.ip);
	strcat(Data,"\r\n");
	strcat(Data,"Connection: Keep-Alive\r\n");
	strcat(Data,"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n");
	strcat(Data,"User-Agent: Mozilla/5.0 (Windows Client; Dali Wang<wangdali@qq.com>)\r\n");
	strcat(Data,"Accept-Language: zh-CN,zh;q=0.8\r\n");
	if(strcmp(conf.cookie,"")!=0)
	{
		strcat(Data,"Cookie: ");
		strcat(Data,conf.cookie);
		strcat(Data,"\r\n");
	}
	strcat(Data,"\r\n");

	if(m_Conn.Send(Data,strlen(Data))==SOCKET_ERROR) // 如果发送返回-1，表示错误
	{
		if(GetLastError()==WSAEWOULDBLOCK)
		{
		}
		else
		{
			m_Conn.Close(); // 关闭连接
		}
	}
	printf("%s\n",Data);
}

void CClientDlg::PostData(char *url, char *para)
{
	char Data[1024] = {0};
	strcat(Data,"POST ");
	strcat(Data,url);
	strcat(Data," HTTP/1.1\r\n");
	strcat(Data,"Host: ");
	strcat(Data,conf.ip);
	strcat(Data,"\r\n");
	strcat(Data,"Connection: Keep-Alive\r\n");
	strcat(Data,"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n");
	strcat(Data,"User-Agent: Mozilla/5.0 (Windows Client; Dali Wang<wangdali@qq.com>)\r\n");
	strcat(Data,"Accept-Language: zh-CN,zh;q=0.8\r\n");
	if(strcmp(conf.cookie,"")!=0)
	{
		strcat(Data,"Cookie: ");
		strcat(Data,conf.cookie);
		strcat(Data,"\r\n");
	}
	strcat(Data,"Content-Type: application/x-www-form-urlencoded\r\n");
	strcat(Data,"Content-Length: ");
	char tmp[16] = {0};
	sprintf(tmp,"%d",strlen(para));
	strcat(Data,tmp);
	strcat(Data,"\r\n");
	strcat(Data,"\r\n");
	strcat(Data,para);

	if(m_Conn.Send(Data,strlen(Data))==SOCKET_ERROR) // 如果发送返回-1，表示错误
	{
		if(GetLastError()==WSAEWOULDBLOCK)
		{
		}
		else
		{
			m_Conn.Close(); // 关闭连接
		}
	}
	printf("%s\n",Data);
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
				UINT i = wnd->GetDlgCtrlID();
				if(ClassName == str)
				{
					SendMessage(WM_COMMAND,i,(LPARAM)wnd->m_hWnd); // 发送按钮消息
				}
				if(i == IDC_EDIT_DANHAO) // 如果是单号控件
				{
					SendMessage(WM_COMMAND,IDC_BUTTON_GET,(LPARAM)wnd->m_hWnd); // 发送按钮消息
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

// 连接服务器
void CClientDlg::OnBnClickedButtonNetConn()
{
	// TODO: 在此添加控件通知处理程序代码
	// 初始化Socket
	m_Conn.SetDlg(this);
	if (m_Conn.Create())
	{
		printf("创建Socket成功\n");
	}
	else
	{
		MessageBox(_T("创建Socket失败！"));
	}
	USES_CONVERSION;  // dali
	m_Conn.Connect(A2CW(conf.ip),conf.port);
}

// 重新打开串口
void CClientDlg::OnBnClickedButtonComConn()
{
	// TODO: 在此添加控件通知处理程序代码
	// 初始化串口
	if(!com1.open(conf.com1_id,conf.com1_para))
	{
		m_com1.SetWindowText(_T("打开失败"));
//		MessageBox("串口1打开失败", "串口", MB_OK);
	}
	else
	{
		com1.set_hwnd(m_hWnd);
		char tmp[64] = {0};
		sprintf(tmp,"COM%d:%s",conf.com1_id,conf.com1_para);
		USES_CONVERSION;  // dali
		m_com1.SetWindowText(A2CW(tmp));
	}
}

// 登录
void CClientDlg::OnBnClickedButtonLogin()
{
	// TODO: 在此添加控件通知处理程序代码

	USES_CONVERSION; // dali
	m_post_id = 2; // 提交ID为2
	char Data[256] ={0};
	strcat(Data,"User=");
	CString strUser =_T("");
	m_user.GetWindowText(strUser); // 获得用户名
	strcat(Data,W2A(strUser)); // 设置用户名
	strcat(Data,"&Passwd=");
	CString strPwd = _T("");
	m_pwd.GetWindowText(strPwd); // 获得密码
	strcat(Data,W2A(strPwd)); // 设置密码
	strcat(Data,"&Level=1"); // 这里Level=1
	GetData("/login.php",(char*)&Data); // 发送 GET 请求
}

// 登出
void CClientDlg::OnBnClickedButtonLogout()
{
	// TODO: 在此添加控件通知处理程序代码
	m_user.SetWindowText(_T(""));
	m_user.EnableWindow(TRUE);
	m_pwd.SetWindowText(_T(""));
	m_pwd.EnableWindow(TRUE);
	m_btn_login.EnableWindow(TRUE);
	memset(&(conf.cookie),0,256);
	memset(&(conf.sid),0,256);
	memset(&(conf.aid),0,256);
}

// 保持连接
void CClientDlg::OnKeepalive()
{
	if(strcmp(conf.aid,"")==0)
	{
		return;
	}
	// 在这里处理车辆信息
	TOKEN * t = (TOKEN *)malloc(sizeof(TOKEN));
	TOKEN * l = (TOKEN *)malloc(sizeof(TOKEN));

	char *tStr ,*lStr;
	tStr = strtoken(t,(char*)&m_net_rvc_data,"\r\n"); // 响应行
	lStr = strtoken(l,(char*)tStr," "); // HTTP/1.1
	lStr = strtoken(l,NULL," "); // 200 
	if(strcmp(lStr,"200")==0)
	{
		while(t->data!=NULL)
		{
			tStr = strtoken(t,NULL, "\r\n");
			if(strcmp(tStr,"")==0) // 空行
			{
				tStr = strtoken(t,NULL, "\r\n"); // 得到相应体长度
				tStr = strtoken(t,NULL, "\r\n"); // 得到相应体内容
				break;
			}
		}
		if(strcmp(tStr,"")==0) // 如果返回的数据为空
		{
			MessageBox(L"无车辆信息!!!",L"数据库");
		}
		else
		{
			USES_CONVERSION;  // dali
			cJSON *jsonroot = cJSON_Parse(tStr); //json根
			if(jsonroot)
			{
				m_list.DeleteAllItems(); // 清空所有内容
				int size = cJSON_GetArraySize(jsonroot); // 获得数组的长度
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
				}
			}
			else
			{
				MessageBox(L"服务器返回车辆信息错误！",L"服务器");
			}
			cJSON_Delete(jsonroot);
		}
	}
}

// 用户登录
void CClientDlg::OnLogin()
{
	// 如果返回 200 和 SetCookie ，则禁用登录相关控件
	TOKEN * t = (TOKEN *)malloc(sizeof(TOKEN));
	TOKEN * l = (TOKEN *)malloc(sizeof(TOKEN));
	TOKEN * c = (TOKEN *)malloc(sizeof(TOKEN));
	TOKEN * a = (TOKEN *)malloc(sizeof(TOKEN));
	char *tStr ,*lStr, *cStr, *aStr;
	tStr = strtoken(t,(char*)&m_net_rvc_data,"\r\n");
	lStr = strtoken(l,(char*)tStr," "); // HTTP/1.1
	lStr = strtoken(l,NULL," "); // 200 
	if(strcmp(lStr,"200")==0)
	{
		while(t->data!=NULL)
		{
			tStr = strtoken(t,NULL, "\r\n");
			cStr = strtoken(c,tStr,":");
			if(strcmp(cStr,"Set-Cookie")==0)
			{
				// 这里应该判断是否存在“AID”身份标识，
				// 存在则登录成功，否则登录失败。
				cStr = strtoken(c,NULL,":");
				aStr = strtoken(a,cStr,"=");
				if(strcmp(aStr," PHPSESSID")==0) // 会话ID
				{
					strcpy(conf.sid,cStr); // 设置SID的值
				}

				if(strcmp(aStr," AID")==0) // 身份ID
				{
					strcpy(conf.aid,cStr); // 设置AID的值
				}	
			}
		} // while

		if(strcmp(conf.sid,"") > 0 && strcmp(conf.aid,"")>0)
		{
			strcpy(conf.cookie,conf.sid); // 设置Cookie的值
			strcat(conf.cookie,";");
			strcat(conf.cookie,conf.aid);
			m_user.EnableWindow(FALSE); // 禁用用户输入框
			m_pwd.EnableWindow(FALSE);  // 禁用密码输入框 
			m_btn_login.EnableWindow(FALSE); // 禁用登录按钮
			m_id.EnableWindow(TRUE); // 启用单号控件
			m_id.SetFocus(); // 设置单号为焦点
			
		}
		else
		{
			MessageBox(_T("用户名 或 密码 错误！"),_T("登录失败"));
		}
	}
}

// 请求一个新的单号
void CClientDlg::OnGet1()
{
	GetWindow();
//	m_jingzhong.SetReadOnly(TRUE);
//	m_danjia.SetReadOnly(TRUE);

	TOKEN * t = (TOKEN *)malloc(sizeof(TOKEN));
	TOKEN * l = (TOKEN *)malloc(sizeof(TOKEN));

	char *tStr ,*lStr, *cStr;
	tStr = strtoken(t,(char*)&m_net_rvc_data,"\r\n"); // 响应行
	lStr = strtoken(l,(char*)tStr," "); // HTTP/1.1
	lStr = strtoken(l,NULL," "); // 200 
	if(strcmp(lStr,"200")==0)
	{
		while(t->data!=NULL)
		{
			tStr = strtoken(t,NULL, "\r\n");
			if(strcmp(tStr,"")==0) // 空行
			{
				tStr = strtoken(t,NULL, "\r\n"); // 得到相应体长度
				tStr = strtoken(t,NULL, "\r\n"); // 得到相应体内容
				break;
			}
		}
		if(strcmp(tStr,"")==0) // 如果返回的数据为空
		{
			MessageBox(L"无可用的单号!!!",L"数据库");
		}
		else
		{
			USES_CONVERSION;  // dali
			cJSON *jsonroot = cJSON_Parse(tStr); //json根
			if(jsonroot)
			{
				m_id.SetWindowText(A2CW(cJSON_GetObjectItem(jsonroot,"id")->valuestring)); // 设置“单号”
				m_post_id = 4; // 第一次提交
			}
			else
			{
				MessageBox(L"服务器返回单号错误！",L"服务器");
			}
			cJSON_Delete(jsonroot);

			m_id.EnableWindow(FALSE); // 禁止“单号”对话框
			m_tijiao.EnableWindow(TRUE); // 启用“提交”按钮
			m_chehao.SetFocus(); // 设置车号为焦点
		}
		
	}
}

// 根据单号，请求单据信息
void CClientDlg::OnGet2()
{
	SetWindow(); // 禁用所有控件
//	m_jingzhong.EnableWindow(TRUE); // 启用“净重”控件
//	m_danjia.EnableWindow(TRUE); // 启用“单价”控件
//	m_jingzhong.SetReadOnly(FALSE); // 设“净重”为非只读
//	m_danjia.SetReadOnly(FALSE); // 设“单价”为非只读


	// 分析返回数据，并显示出来。
	TOKEN * t = (TOKEN *)malloc(sizeof(TOKEN));
	TOKEN * l = (TOKEN *)malloc(sizeof(TOKEN));

	char *tStr;
	char *lStr;
	tStr = strtoken(t,(char*)&m_net_rvc_data,"\r\n"); // 响应行
	lStr = strtoken(l,(char*)tStr," "); // HTTP/1.1
	lStr = strtoken(l,NULL," "); // 200 
	if(strcmp(lStr,"200")==0)
	{
		while(t->data!=NULL)
		{
			tStr = strtoken(t,NULL, "\r\n");
			if(strcmp(tStr,"")==0) // 空行
			{
				tStr = strtoken(t,NULL, "\r\n"); // 得到相应体长度
				tStr = strtoken(t,NULL, "\r\n"); // 得到相应体内容
				break;
			}
		}
		if(strcmp(tStr,"")==0) // 如果返回的数据为空
		{
			MessageBox(L"单号不存在!",L"数据库");
			SetWindow(); // 禁用所有控件
			m_id.EnableWindow(TRUE); // 启用单号控件

			m_id.SetWindowText(_T("")); // 单号
			m_chehao.SetWindowText(_T("")); // 车号
			m_dianhua.SetWindowText(_T("")); // 电话
			m_shouhuo.SetWindowText(_T("")); // 收货单位
			m_guige.SetWindowText(_T("")); // 货物规格
			m_pizhong.SetWindowText(_T("")); // 皮重
			m_maozhong.SetWindowText(_T("")); // 毛重
			m_jingzhong.SetWindowText(_T("")); // 净重
			m_danjia.SetWindowText(_T("")); // 单价
			m_jine.SetWindowText(_T("")); // 金额
			m_yue.SetWindowText(_T("")); // 余额

			m_dayin.EnableWindow(FALSE); // 禁用“打印”按钮
			m_id.SetFocus();
		}
		else
		{
			USES_CONVERSION;  // dali
			cJSON *jsonroot = cJSON_Parse(tStr); //json根
			if(jsonroot)
			{
				m_chehao.SetWindowText(A2CW(UTF8ToEncode(cJSON_GetObjectItem(jsonroot,"ch")->valuestring))); // 车号
				m_dianhua.SetWindowText(A2CW(cJSON_GetObjectItem(jsonroot,"dh")->valuestring)); // 电话
				m_shouhuo.SetWindowText(A2CW(UTF8ToEncode(cJSON_GetObjectItem(jsonroot,"dw")->valuestring))); // 单位
				m_huowu.SetWindowText(A2CW(UTF8ToEncode(cJSON_GetObjectItem(jsonroot,"hw")->valuestring))); // 货物
				m_guige.SetWindowText(A2CW(cJSON_GetObjectItem(jsonroot,"gg")->valuestring)); // 规格
				m_chexing.SetWindowText(A2CW(UTF8ToEncode(cJSON_GetObjectItem(jsonroot,"cx")->valuestring))); // 车型
				m_pizhong.SetWindowText(A2CW(cJSON_GetObjectItem(jsonroot,"pz")->valuestring)); // 皮重
				m_maozhong.SetWindowText(A2CW(cJSON_GetObjectItem(jsonroot,"mz")->valuestring)); // 毛重
				m_jingzhong.SetWindowText(A2CW(cJSON_GetObjectItem(jsonroot,"jz")->valuestring)); // 净重
				m_danjia.SetWindowText(A2CW(UTF8ToEncode(cJSON_GetObjectItem(jsonroot,"dj")->valuestring))); // 单价
				m_danjiadanwei = (A2CW(UTF8ToEncode(cJSON_GetObjectItem(jsonroot,"djdw")->valuestring))); // 单价单位
				m_midu = atof(cJSON_GetObjectItem(jsonroot,"md")->valuestring); // 密度
				m_jine.SetWindowText(A2CW(UTF8ToEncode(cJSON_GetObjectItem(jsonroot,"je")->valuestring))); // 金额
				m_yue.SetWindowText(A2CW(UTF8ToEncode(cJSON_GetObjectItem(jsonroot,"ye")->valuestring))); // 余额
				m_post_id = 6; // 第二次提交
			}
			cJSON_Delete(jsonroot);
		}
	}
	if(strcmp(lStr,"400")==0)
		MessageBox(_T("文件没有找到！"),_T("网络连接"));
	if(strcmp(lStr,"500")==0)
		MessageBox(_T("服务器错误！！！"),_T("网络连接"));

	m_tijiao.EnableWindow(TRUE); // 启用“提交”按钮
//	m_jingzhong.SetFocus(); // 设置净重为焦点

//	free(t);
//	free(l);
}

// 第一次提交单据
void CClientDlg::OnPost1()
{
//	MessageBox(L"第一次过磅");
	// 判断第一次提交是否正确
	// 如果正确就跳转到“打印”按钮
	m_dayin.EnableWindow(TRUE); // 启用“打印”按钮
	m_tijiao.EnableWindow(FALSE); // 禁用“提交”按钮
	m_dayin.SetFocus();
}

// 第二次提交单据
void CClientDlg::OnPost2()
{
//	MessageBox(L"第二次过磅");
	// 判断第二次提交是否正确
	// 如果正确就跳转到“打印”按钮
	m_dayin.EnableWindow(TRUE); // 启用“打印”按钮
	m_tijiao.EnableWindow(FALSE); // 禁用“提交”按钮
	m_dayin.SetFocus();
}

// 定时器
void CClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(nIDEvent)
	{
	case 1:
		m_post_id = 1; // 提交ID为1
		GetData("/keepalive.php","");
		return;
	}
	CDialogEx::OnTimer(nIDEvent);
}

// 提交按钮
void CClientDlg::OnBnClickedButtonTijiao()
{
	// TODO: 在此添加控件通知处理程序代码
	// 第一次提交：m_post_id = 4; 
	// 第二次提交：m_post_id = 6; 
	// 需要判断是第一次提交还是第二次提交
	

	USES_CONVERSION;

	CString strDanHao,strCheHao,strCheXing; // 单号，车号，车型
	CString strDanWei,strDianHua; // 单位，电话
	CString strHuoWu,strGuiGe; // 货物，规格
	CString strPiZhong,strMaoZhong,strJingZhong; // 皮重，毛重，净重
	CString strDanJia,strJinE; // 单价，金额
	CString strYouHui; // 优惠信息

	m_id.GetWindowText(strDanHao); // 单号
	m_chehao.GetWindowText(strCheHao); // 车号
	m_chexing.GetWindowText(strCheXing); // 车型
	m_shouhuo.GetWindowText(strDanWei); // 单位
	m_dianhua.GetWindowText(strDianHua); // 电话
	m_huowu.GetWindowText(strHuoWu); // 货物
	m_guige.GetWindowText(strGuiGe); // 规格
	m_pizhong.GetWindowText(strPiZhong); // 皮重
	m_maozhong.GetWindowText(strMaoZhong); // 毛重
	m_jingzhong.GetWindowText(strJingZhong); // 净重
	m_danjia.GetWindowText(strDanJia); // 单价
	m_jine.GetWindowText(strJinE); // 金额
	if(m_shoudong.GetCheck())
	{
		strYouHui = L"手动";
	}
	if(m_youhui.GetCheck())
	{
		strYouHui = L"优惠";
	}

	// 如果毛重为空，表示第一次提交
	if(strMaoZhong.IsEmpty())
	{
		if(strPiZhong.IsEmpty()) // 如果皮重为空
		{
			MessageBox(L"\"皮重\"不能为空，检查地磅线路等是否正常！",L"地磅");
			return;
		}
//		else
//		{
//			m_post_id = 4; // 第一次提交
//		}
	}
	else // 第二次提交
	{
		if(strJingZhong.IsEmpty())
		{
			MessageBox(L"\"净重\"不能为空，检查地磅线路等是否正常！",L"地磅");
			return;
		}
//		else
//		{
//			m_post_id = 6;
//		}
		
	}

	char str[1024]={0};
	sprintf(str,"DanHao=%s&CheHao=%s&CheXing=%s&",W2A(strDanHao),W2A(strCheHao),W2A(strCheXing));
	sprintf(str,"%sDanWei=%s&DianHua=%s&",str,W2A(strDanWei),W2A(strDianHua));
	sprintf(str,"%sHuoWu=%s&GuiGe=%s&",str,W2A(strHuoWu),W2A(strGuiGe));
	sprintf(str,"%sPiZhong=%s&MaoZhong=%s&JiangZhong=%s&",str,W2A(strPiZhong),W2A(strMaoZhong),W2A(strJingZhong));
	if(m_type==1) m_post_id = 4;
	if(m_type==2) m_post_id = 6;
	sprintf(str,"%sDanJia=%s&JinE=%s&ZhuangTai=%d&",str,W2A(strDanJia),W2A(strJinE),m_post_id); // 单价 金额 状态
	sprintf(str,"%sYouHui=%s&",str,W2A(strYouHui)); // 优惠信息

	CString strUser;
	m_user.GetWindowText(strUser);
	sprintf(str,"%sSiBangYuan=%s",str, W2A(strUser)); // 司磅员
	PostData("/post.php",str);

}

// 打印按钮
void CClientDlg::OnBnClickedButtonDayin()
{
	// TODO: 在此添加控件通知处理程序代码
	DaYin.m_title = conf.title;
	m_id.GetWindowText(DaYin.m_id);
	m_chehao.GetWindowText(DaYin.m_CheHao);
	m_chexing.GetWindowText(DaYin.m_CheXing);
	m_shouhuo.GetWindowText(DaYin.m_DanWei);
	m_dianhua.GetWindowText(DaYin.m_DianHua);
	m_huowu.GetWindowText(DaYin.m_HuoWu);
	m_guige.GetWindowText(DaYin.m_GuiGe);
	m_pizhong.GetWindowText(DaYin.m_PiZhong);
	m_maozhong.GetWindowText(DaYin.m_MaoZhong);
	m_jingzhong.GetWindowText(DaYin.m_JingZhong);
	m_danjia.GetWindowText(DaYin.m_DanJia);
	m_jine.GetWindowText(DaYin.m_JinE);
	// 备注
	if(m_shoudong.GetCheck())
	{
		DaYin.m_BeiZhu = L"手动";
	}
	if(m_youhui.GetCheck())
	{
		DaYin.m_BeiZhu = L"优惠";
	}
	m_user.GetWindowText(DaYin.m_User);


	// 清空文本框的数据，并将焦点设置在单号处。
	SetWindow(); // 禁用所有控件
	m_id.EnableWindow(TRUE); // 启用单号控件

	m_id.SetWindowText(_T("")); // 单号
	m_chehao.SetWindowText(_T("")); // 车号
	m_dianhua.SetWindowText(_T("")); // 电话
	m_shouhuo.SetWindowText(_T("")); // 收货单位
	m_guige.SetWindowText(_T("")); // 货物规格
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

	m_dayin.EnableWindow(FALSE); // 禁用“打印”按钮
	m_id.SetFocus();

	// 执行打印
	DoPrint();
}

// 设置禁用控件
void CClientDlg::SetWindow()
{
	m_id.EnableWindow(FALSE); // 单号
	m_chehao.EnableWindow(FALSE); // 车号
	m_chexing.EnableWindow(FALSE); // 车型
	m_dianhua.EnableWindow(FALSE); // 电话
	m_shouhuo.EnableWindow(FALSE); // 单位
	m_huowu.EnableWindow(FALSE); // 货物
	m_guige.EnableWindow(FALSE); // 规格
	m_pizhong.EnableWindow(FALSE); // 皮重
	m_maozhong.EnableWindow(FALSE); // 毛重
	m_jingzhong.EnableWindow(FALSE); // 净重
	m_danjia.EnableWindow(FALSE); // 单价
	m_jine.EnableWindow(FALSE); // 金额
}

// 设置启用控件
void CClientDlg::GetWindow()
{
	m_id.EnableWindow(TRUE); // 单号
	m_chehao.EnableWindow(TRUE); // 车号
	m_chexing.EnableWindow(TRUE); // 车型
	m_dianhua.EnableWindow(TRUE); // 电话
	m_shouhuo.EnableWindow(TRUE); // 单位
	m_huowu.EnableWindow(TRUE); // 货物
	m_guige.EnableWindow(TRUE); // 规格
	m_pizhong.EnableWindow(TRUE); // 皮重
	m_maozhong.EnableWindow(TRUE); // 毛重
	m_jingzhong.EnableWindow(TRUE); // 净重
	m_danjia.EnableWindow(TRUE); // 单价
	m_jine.EnableWindow(TRUE); // 金额
}

// 获取单据信息
void CClientDlg::OnBnClickedButtonGet()
{
	// TODO: 在此添加控件通知处理程序代码
	SYSTEMTIME st;
	GetLocalTime(&st);
	char str[32]={0};
	sprintf(str,"date=%4d%02d%02d&id=",st.wYear,st.wMonth,st.wDay); // 当前日期

	CString strId;
	m_id.GetWindowText(strId);

	if(strId.IsEmpty()) // 判断“单号”是否为空
	{
		// 获取单号
		m_post_id = 3; // 提交ID为3
		m_type = 1;
		strcat(str,"0");
		GetData("/getid.php",str); // 获得一个新的单号

		m_tijiao.SetFocus(); // 设置单号为焦点
	}
	else
	{
		int i = _ttoi(strId); 
		if(i==0)
		{
			MessageBox(L"单号不能全为：0");
			return;
		}

		// 根据单号获取单据信息
		m_post_id = 5; // 提交ID为5
		m_type = 2;
		// 这里需要生成当前的日期和获得单号
		CString id=L"";
		m_id.GetWindowText(id);
		USES_CONVERSION;
		strcat(str,W2A(id));
		GetData("/getid.php",str); // 提交放行请求
		m_tijiao.SetFocus(); // 设置单号为焦点
	}
}


void CClientDlg::OnBnClickedButtonEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	GetWindow();
	m_pizhong.SetReadOnly(FALSE);
	m_maozhong.SetReadOnly(FALSE);
	m_jingzhong.SetReadOnly(FALSE);
	m_danjia.SetReadOnly(FALSE);
	m_jine.SetReadOnly(FALSE);
	m_tijiao.EnableWindow(TRUE);
	m_dayin.EnableWindow(TRUE);
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

	DaYin.m_title = conf.title;
	m_id.GetWindowText(DaYin.m_id);
	m_chehao.GetWindowText(DaYin.m_CheHao);
	m_chexing.GetWindowText(DaYin.m_CheXing);
	m_shouhuo.GetWindowText(DaYin.m_DanWei);
	m_dianhua.GetWindowText(DaYin.m_DianHua);
	m_huowu.GetWindowText(DaYin.m_HuoWu);
	m_guige.GetWindowText(DaYin.m_GuiGe);
	m_pizhong.GetWindowText(DaYin.m_PiZhong);
	m_maozhong.GetWindowText(DaYin.m_MaoZhong);
	m_jingzhong.GetWindowText(DaYin.m_JingZhong);
	m_danjia.GetWindowText(DaYin.m_DanJia);
	m_jine.GetWindowText(DaYin.m_JinE);
	// 备注
	if(m_shoudong.GetCheck())
	{
		DaYin.m_BeiZhu = L"手动";
	}
	if(m_youhui.GetCheck())
	{
		DaYin.m_BeiZhu = L"优惠";
	}
	m_user.GetWindowText(DaYin.m_User);

	// 设置石场相关变量
	m_printer->m_title = DaYin.m_title; // 标题
	m_printer->m_id = DaYin.m_id;// 单号
	m_printer->m_CheHao = DaYin.m_CheHao; // 车号
	m_printer->m_CheXing = DaYin.m_CheXing; // 车型
	m_printer->m_DanWei = DaYin.m_DanWei; // 收货单位
	m_printer->m_DianHua = DaYin.m_DianHua; // 电话
	m_printer->m_HuoWu = DaYin.m_HuoWu; // 货物名称
	m_printer->m_GuiGe = DaYin.m_GuiGe; // 货物规格
	m_printer->m_PiZhong = DaYin.m_PiZhong; // 皮重
	m_printer->m_MaoZhong = DaYin.m_MaoZhong; // 毛重
	m_printer->m_JingZhong = DaYin.m_JingZhong; // 净重
	m_printer->m_DanJia = DaYin.m_DanJia; // 单价
	m_printer->m_JinE = DaYin.m_JinE; // 金额
	m_printer->m_BeiZhu = DaYin.m_BeiZhu; // 备注
	m_printer->m_User = DaYin.m_User; // 司磅员
	m_printer->m_Times  = m_type; // 过磅次数
	
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
//	else
//	{
		//画出第二页的内容
//		m_printer->SetCurrentPage(1);
//		m_printer->StartPage();
//		m_printer->PrintHeader();
//		m_printer->PrintBody();
//		m_printer->EndPage();
//		m_printer->EndPrinting();
//	}
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

	if( IDOK == dlg.DoModal() )
	{
		CDC dc;
		dc.Attach(dlg.m_pd.hDC);
		std::tr1::shared_ptr<CPrinter> printer(new CPrinter(&dc));
		printer->SetTotalLineNumber(10);//如果是列表控件的内容，告诉printer有多少行
		printer->PreparePrinting();

		// 设置石场相关变量
		printer->m_title = DaYin.m_title; // 标题
		printer->m_id = DaYin.m_id;// 单号
		printer->m_CheHao = DaYin.m_CheHao; // 车号
		printer->m_CheXing = DaYin.m_CheXing; // 车型
		printer->m_DanWei = DaYin.m_DanWei; // 收货单位
		printer->m_DianHua = DaYin.m_DianHua; // 电话
		printer->m_HuoWu = DaYin.m_HuoWu; // 货物名称
		printer->m_GuiGe = DaYin.m_GuiGe; // 货物规格
		printer->m_PiZhong = DaYin.m_PiZhong; // 皮重
		printer->m_MaoZhong = DaYin.m_MaoZhong; // 毛重
		printer->m_JingZhong = DaYin.m_JingZhong; // 净重
		printer->m_DanJia = DaYin.m_DanJia; // 单价
		printer->m_JinE = DaYin.m_JinE; // 金额
		printer->m_BeiZhu = DaYin.m_BeiZhu; // 备注
		printer->m_User = DaYin.m_User; // 司磅员

		if(printer->StartPrinting())
		{
			while ( printer->NeedStartNewPage() )
			{
				printer->StartPage();
				//打印内容，自己分页
				printer->PrintHeader();
				printer->PrintBody();
				printer->EndPage();
			}
			printer->EndPrinting();
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

// 查询按钮
void CClientDlg::OnBnClickedButtonFind()
{
	// TODO: 在此添加控件通知处理程序代码
}

// 交接班按钮
void CClientDlg::OnBnClickedButtonJiaojie()
{
	// TODO: 在此添加控件通知处理程序代码
//	SYSTEMTIME st;
//	GetLocalTime(&st);
	USES_CONVERSION;
	CString strUser;
	m_user.GetWindowText(strUser);
	char str[1024]={0};
	sprintf(str,"start http://");
	sprintf(str,"%s%s/",str,conf.ip);
	sprintf(str,"%sjiaojie.php?user=",str);
	sprintf(str,"%s%s",str,W2A(strUser));
//	sprintf(str,"%s%4d%02d%02d%%20%02d:%02d:%02d",str,st.wYear,st.wMonth,st.wDay,st.wHour-8,st.wMinute,st.wSecond); // 开始时间：设置为上班时间
//	sprintf(str,"%s^&end=",str); // 注意在win的命令行批处理中'&'需要转意为'^&'
//	sprintf(str,"%s%4d%02d%02d%%20%02d:%02d:%02d",str,st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond); // 结束时间: 设置为当前时间
	system(str);
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
	CString HuoWu;
	m_huowu.GetWindowText(HuoWu); // 获得货物的名称
	if(HuoWu.Compare(L"青石")==0)
	{
		m_guige.ResetContent(); // 清空下拉列表
		m_guige.AddString(_T("0.5"));
		m_guige.AddString(_T("1.2"));
		m_guige.AddString(_T("1.3"));
		m_guige.SetCurSel(0);
		return;
	}
	if(HuoWu.Compare(L"半青石")==0)
	{
		m_guige.ResetContent();
		m_guige.AddString(_T("0.5"));
		m_guige.AddString(_T("1.3"));
		m_guige.AddString(_T("2.4"));
		m_guige.SetCurSel(0);
		return;
	}
	m_guige.ResetContent();
	m_guige.AddString(_T("0"));
	m_guige.SetCurSel(0);
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
	// 设置第一次过磅和第二次过磅的皮重和毛重
	// 皮重
	if(m_type == 1)
	{
		m_pizhong.SetWindowText(A2W((char*)m_Weight)); // 将值显示在皮重控件中。
	}

	// 毛重
	if(m_type == 2)
	{
		m_maozhong.SetWindowText(A2W((char*)m_Weight)); // 将值显示在毛重控件中。
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
	if(m_shoudong.GetCheck() && m_youhui.GetCheck())
	{
		m_shoudong.SetCheck(FALSE);
		MessageBox(L"不能同时选择\"手动\"和\"优惠\"");
		return;
	}
	if(m_shoudong.GetCheck()) // 选中状态
	{
		m_jine.EnableWindow(TRUE); // 启用“金额”控件
		m_jine.SetReadOnly(FALSE); // 设“金额”为非只读
		m_jine.SetFocus(); // 设置“金额”文本框为焦点
		// 设置备注为“手动”
	}
	else // 未选中状态
	{
		m_jine.EnableWindow(FALSE); // 启用“金额”控件
		m_jine.SetReadOnly(TRUE); // 设“金额”为非只读
	}
	
}

// 点击优惠复选框
void CClientDlg::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_shoudong.GetCheck() && m_youhui.GetCheck())
	{
		m_youhui.SetCheck(FALSE);
		MessageBox(L"不能同时选择\"手动\"和\"优惠\"");
		return;
	}
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
	CString sText = m_list.GetItemText(nItem, 0);
	m_list.ModifyStyle(NULL, LVS_SHOWSELALWAYS, 0);
	m_list.SetItemState(nItem, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
	m_id.SetWindowText(sText); // 设置单号
	OnBnClickedButtonGet(); // 获得单据信息
	*pResult = 0;
}

// 取消按钮
void CClientDlg::OnBnClickedButtonQuxiao()
{
	// TODO: 在此添加控件通知处理程序代码
	SetWindow(); // 禁用所有控件
	m_id.EnableWindow(TRUE); // 启用单号控件
	m_id.SetWindowText(_T("")); // 单号
	m_chehao.SetWindowText(_T("")); // 车号
	m_dianhua.SetWindowText(_T("")); // 电话
	m_shouhuo.SetWindowText(_T("")); // 收货单位
	m_guige.SetWindowText(_T("")); // 货物规格
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
}
