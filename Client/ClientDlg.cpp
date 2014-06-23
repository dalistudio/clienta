
// ClientDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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

// ���������ڶԻ���ʱִ��
void CAboutDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//MessageBox(L"����");
	SendMessage(WM_CLOSE);
	CDialogEx::OnLButtonDown(nFlags, point);
}

// CClientDlg �Ի���




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
	DDX_Control(pDX, IDC_LIST1, m_list); // ������Ϣ
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_MESSAGE(ON_COM_RECEIVE, On_Receive) // ����յ� ON_COM_RECEIVE ��Ϣ�����ý��պ���
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


// CClientDlg ��Ϣ�������

BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	memset(m_Weight,0,16); // ���������ȫ�ֱ���
	memset(m_dibang_data,0,32); // ��յذ�����
	m_dibang_data_pos = 0;
	m_Start = 0; // �Ƿ�ʼ�ռ��ذ�����
	m_type = 0;
	iWeight1 = 0;
	iWeight2 = 0;

#ifdef _DEBUG // ���԰濪��
	// ���������д��� 
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

	// Ĭ������
	SetWindow(); // ���ÿؼ�
	m_tijiao.EnableWindow(FALSE); // ���á��ύ����ť
	m_dayin.EnableWindow(FALSE); // ���á���ӡ����ť

	memset(&conf,0,sizeof(CONF));
	strcpy(conf.title,"���ϸۿ��ķ�ʯ��");
	strcpy(conf.ip,"192.168.1.5");
	conf.port = 80;
	conf.com1_id=1;
	strcpy(conf.com1_para,"baud=9600 parity=N data=8 stop=1");
	strcpy(conf.cookie,"");
	strcpy(conf.sid,"");
	strcpy(conf.aid,"");

	// �������ļ� JSON ��ʽ
	FILE *f=fopen("config","rb"); // �����ļ� config
	if(f==NULL)
	{
		MessageBox(_T("�������ļ�ʧ�ܣ�"), _T("config"), MB_OK);
	}
	else
	{
		fseek(f,0,SEEK_END); // �����ļ�β
		long len=ftell(f); // ����ļ�����
		fseek(f,0,SEEK_SET); // �����ļ�ͷ
		char *data=(char*)malloc(len+1); // �����ļ��ռ�
		fread(data,1,len,f); // ��ȡ�ļ�����
		fclose(f); // �ر��ļ�
		cJSON *jsonroot = cJSON_Parse(data); //json��
		if(jsonroot)
		{
			strcpy(conf.title,cJSON_GetObjectItem(jsonroot,"title")->valuestring); // ��ñ���

			cJSON *jsonServer=cJSON_GetObjectItem(jsonroot,"server");//ȡ Server
			strcpy(conf.ip,cJSON_GetObjectItem(jsonServer,"ip")->valuestring); // ���IP��ַ
			conf.port = cJSON_GetObjectItem(jsonServer,"port")->valueint; // ��ö˿�

			cJSON *jsonCOM1=cJSON_GetObjectItem(jsonroot,"com1");//ȡ COM1
			conf.com1_id = cJSON_GetObjectItem(jsonCOM1,"port")->valueint; // ���COM�˿�
			strcpy(conf.com1_para,cJSON_GetObjectItem(jsonCOM1,"para")->valuestring); // ���COM������
		}
		else
		{
			MessageBox(_T("�����ļ�����",_T("config"),MB_OK));
		}
		cJSON_Delete(jsonroot);
	}

	// ���ö�ʱ��
	SetTimer(1,10000,0); // 10��

	// ���ӷ�����
	OnBnClickedButtonNetConn();

	// ��ʼ������
	OnBnClickedButtonComConn();

	///////////////////////

	CFont *m_Font;
	m_Font = new CFont; 
	m_Font->CreateFont(
		32, // ����߶�
		13,	// ������
		0,	// �ı��е���б��
		0,	// �ַ����ߵ���б��
		100,	// ����Ĵ�ϸ
		FALSE,	// �Ƿ�б��
		FALSE,	// �Ƿ��»���
		0,		// �Ƿ�ɾ����
		ANSI_CHARSET,			// ������ַ���
		OUT_DEFAULT_PRECIS,		// �ַ����������
		CLIP_DEFAULT_PRECIS,	// �ַ��Ĳü�����
		DEFAULT_QUALITY,		// �ַ����������
		FF_SWISS,				// �ַ�����������
		_T("����"));				// ��������

	// ����
	GetDlgItem(IDC_EDIT_ZHONGLIANG)->SetFont(m_Font);

	// ����
	USES_CONVERSION;  // dali
	GetDlgItem(IDC_EDIT_TITLE)->SetWindowText(A2CW(conf.title));
	GetDlgItem(IDC_EDIT_TITLE)->SetFont(m_Font);
	//////////////////////////////////////

	// ����
	GetDlgItem(IDC_STATIC_DANHAO)->SetFont(m_Font);
	GetDlgItem(IDC_EDIT_DANHAO)->SetFont(m_Font);
	
	// ����
	GetDlgItem(IDC_STATIC_CHEHAO)->SetFont(m_Font);
	GetDlgItem(IDC_EDIT_CHEHAO)->SetFont(m_Font);

	// �绰
	GetDlgItem(IDC_STATIC_DIANHUA)->SetFont(m_Font);
	GetDlgItem(IDC_EDIT_DIANHUA)->SetFont(m_Font);

	// ��������
	GetDlgItem(IDC_STATIC_HUOWU)->SetFont(m_Font);
	GetDlgItem(IDC_COMBO_HUOWU)->SetFont(m_Font);

	// ������
	GetDlgItem(IDC_STATIC_GUIGE)->SetFont(m_Font);
	GetDlgItem(IDC_COMBO_GUIGE)->SetFont(m_Font);

	// �ջ���λ
	GetDlgItem(IDC_STATIC_SHOUHUO)->SetFont(m_Font);
	GetDlgItem(IDC_EDIT_SHOUHUO)->SetFont(m_Font);

	// ���
	GetDlgItem(IDC_STATIC_YUE)->SetFont(m_Font);
	GetDlgItem(IDC_STATIC_YEY)->SetFont(m_Font);

	// Ƥ�ص�λ
	GetDlgItem(IDC_STATIC_PZKG)->SetFont(m_Font);

	// ë�ص�λ
	GetDlgItem(IDC_STATIC_MZKG)->SetFont(m_Font);

	// ���ص�λ
	GetDlgItem(IDC_STATIC_JZKG)->SetFont(m_Font);

	// ��λ
	GetDlgItem(IDC_STATIC_JE)->SetFont(m_Font);

	////////////////////////////////

	// ����
	GetDlgItem(IDC_STATIC_CHEXING)->SetFont(m_Font);
	GetDlgItem(IDC_COMBO_CHEXING)->SetFont(m_Font);

	// Ƥ��
	GetDlgItem(IDC_STATIC_PIZHONG)->SetFont(m_Font);
	GetDlgItem(IDC_EDIT_PIZHONG)->SetFont(m_Font);

	// ë��
	GetDlgItem(IDC_STATIC_MAOZHONG)->SetFont(m_Font);
	GetDlgItem(IDC_EDIT_MAOZHONG)->SetFont(m_Font);

	// ����
	GetDlgItem(IDC_STATIC_JINGZHONG)->SetFont(m_Font);
	GetDlgItem(IDC_EDIT_JINGZHONG)->SetFont(m_Font);

	// ����
	GetDlgItem(IDC_STATIC_DANJIA)->SetFont(m_Font);
	GetDlgItem(IDC_EDIT_DANJIA)->SetFont(m_Font);

	// ���
	GetDlgItem(IDC_STATIC_JINE)->SetFont(m_Font);
	GetDlgItem(IDC_EDIT_JINE)->SetFont(m_Font);

	// ���
	GetDlgItem(IDC_STATIC_YUE)->SetFont(m_Font);
	GetDlgItem(IDC_EDIT_YUE)->SetFont(m_Font);

	/////////////////////////////////

	// ȡ������ť
	GetDlgItem(IDC_BUTTON_ZHONGLIANG)->SetFont(m_Font);

	// �ύ��ť
	GetDlgItem(IDC_BUTTON_TIJIAO)->SetFont(m_Font);

	// ��ӡ��ť
	GetDlgItem(IDC_BUTTON_DAYIN)->SetFont(m_Font);

	/////////////////////////////////

	m_chexing.AddString(_T("��"));
	m_chexing.AddString(_T("С��"));
	m_chexing.SetCurSel(0); // ѡ���һ��󳵡�

	m_huowu.AddString(_T("��ʯ"));
	m_huowu.AddString(_T("����ʯ"));
	m_huowu.AddString(_T("ʯ��"));
	m_huowu.AddString(_T("���"));
	m_huowu.AddString(_T("��ʯ"));
	m_huowu.AddString(_T("��Ƭʯ"));
	m_huowu.SetCurSel(0);

	m_guige.AddString(_T("0.5"));
	m_guige.AddString(_T("1.2"));
	m_guige.AddString(_T("1.3"));
	m_guige.SetCurSel(0);

	///////////////////////////////
	// ������Ϣ�б�����
	LONG lStyle; 
	lStyle = GetWindowLong(m_list.m_hWnd, GWL_STYLE);// ��ȡ��ǰ����style 
	lStyle &= ~LVS_TYPEMASK; // �����ʾ��ʽλ 
	lStyle |= LVS_REPORT; // ����style 
	SetWindowLong(m_list.m_hWnd, GWL_STYLE, lStyle);// ����style 
	DWORD dwStyle = m_list.GetExtendedStyle(); 
	dwStyle |= LVS_EX_FULLROWSELECT;// ѡ��ĳ��ʹ���и�����ֻ������report ����listctrl �� 
	dwStyle |= LVS_EX_GRIDLINES;// �����ߣ�ֻ������report ����listctrl �� 
//	dwStyle |= LVS_EX_CHECKBOXES;//item ǰ����checkbox �ؼ� 
	m_list.SetExtendedStyle(dwStyle); // ������չ��� 

	m_list.InsertColumn(0,L"����",LVCFMT_CENTER,100);
	m_list.InsertColumn(1,L"����",LVCFMT_CENTER,80);
	m_list.InsertColumn(2,L"����",LVCFMT_CENTER,80);
	m_list.InsertColumn(3,L"��������",LVCFMT_CENTER,80);
	m_list.InsertColumn(4,L"������",LVCFMT_CENTER,80);
	m_list.InsertColumn(5,L"��ϵ�绰",LVCFMT_CENTER,100);
	m_list.InsertColumn(6,L"�ջ���λ",LVCFMT_CENTER,200);
	m_list.InsertColumn(7,L"Ƥ��",LVCFMT_CENTER,100);
	m_list.InsertColumn(8,L"����ʱ��",LVCFMT_CENTER,200);
	
	//return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ���մ��ڵ���Ϣ��������
LRESULT CClientDlg::On_Receive(WPARAM wp, LPARAM lp)
{
	// ������յذ����ݣ�������������޸���ؿؼ�����ʾ��
	// �Զ��ж����µذ����Ǿɵذ�������
	int len;
	unsigned char str[8]={0};
	len = com1.read((char *)str, 2);
	int type = 0; // �����ж��¾ɵذ�������

	switch(str[0]) // �յ��ĵ�һ���ַ�
	{
	case 0x02: // ��ʼ��־
		// ��ʼ�Ѽ�����
		if(m_Start==0)
		{
			m_Start = 1;
			m_dibang_data[m_dibang_data_pos] = str[0]; // ���ַ���ֵ���ذ����ݵ�ȫ�ֱ���
			m_dibang_data_pos++; // �ذ�����λ��+1
		}
		else
		{
			m_Start==0; // ��ֹ���ֶ��0x02 ��û�� 0x0d����
		}
		return 0; // ����

	case 0x03:
		// �����Ѽ�����
		// ����Э�鴦�������������ݡ�
		type = 1; // �ɵذ�
		if(m_Start==1)
		{
			m_Start = 0;
			m_dibang_data[m_dibang_data_pos] = str[0];
			m_dibang_data[m_dibang_data_pos+1] = 0x00; // �����ٻ�ȡ��һ���ַ��ˣ�ֱ���ں������0x00�����ַ�����
			m_dibang_data_pos = 0; // ��ʼ���ذ����ݵ�λ��Ϊ0����ֹ�����
			break; // �ж�switch����ִ�У��Ա�����ذ����ݡ�
		}
		else
		{
			return 0; // ����
		}
	case 0x0D: // ������־
		// �����Ѽ�����
		// ����Э�鴦�������������ݡ�
		type = 2; // �µذ�
		if(m_Start==1)
		{
			m_Start = 0;
			m_dibang_data[m_dibang_data_pos] = str[0];
			m_dibang_data[m_dibang_data_pos+1] = 0x00; // �����ٻ�ȡ��һ���ַ��ˣ�ֱ���ں������0x00�����ַ�����
			m_dibang_data_pos = 0; // ��ʼ���ذ����ݵ�λ��Ϊ0����ֹ�����
			break; // �ж�switch����ִ�У��Ա�����ذ����ݡ�
		}
		else
		{
			return 0; // ����
		}
		
	default:
		if(m_Start==1)
		{
			m_dibang_data[m_dibang_data_pos] = str[0];
			m_dibang_data_pos++;
		}
		return 0; // ����
	}

	// ����ĵذ����ݴ���
	if(type==0) return 0; // ���û�з��ϵذ�������ֱ�ӷ���
	
	// �ɵذ����ݴ���
	if(type==1)
	{
		// �ɵذ����ݸ�ʽ
		// 02 2B 30 30 30 30 30 30 30 31 42 03 #  0KG
		// 02 2B 30 30 30 30 38 30 30 31 33 03 # 80KG
		// 02 ��ʼ����
		// 2B "+" ����
		// 30 30 30 30 38 30 "000080" ��ʾ80KG
		// 30 δ֪���ã�����Ҳ��������һ����
		// 31 33 ������У��ֵ
		// 03 ��������
		if(m_dibang_data[0]==0x02 && m_dibang_data[1]==0x2B)
		{
			m_Weight[0] = m_dibang_data[2]; // �ٶ�
			m_Weight[1] = m_dibang_data[3]; // ʮ��
			m_Weight[2] = m_dibang_data[4]; // ��
			m_Weight[3] = m_dibang_data[5]; // �ٹ���
			m_Weight[4] = m_dibang_data[6]; // ʮ����
			m_Weight[5] = m_dibang_data[7]; // ǧ��
			// ������Ե������4���ֽڣ�ֱ�ӽ�����
			m_Weight[6] = 0x00; // �ַ���������־
		}
	}

	// �µذ����ݴ���
	if(type==2)
	{
		// �µذ����ݸ�ʽ
		// 02 31 30 20 20 20 20 20 20 20 20 20 20 30 30 0D
		// 02 ��ʼ����
		// 31 30 δ֪���ã����б仯��
		// 20 20 20 20 20 20 20 20 20 20 ����
		// 30 30 δ֪���ã�δ���仯��
		// 0D ������־
		
		int i=0;
		int j=0;
		while(m_dibang_data[i]!=0x0D) // ѭ�����ݣ�ֱ������0x0D
		{
			if(m_dibang_data[i]==0x02) // ������ʼ��־ 0x02
			{
				i+=3; // ���������ַ���һ��Ϊ0x02 0x31 0x30 δ֪���á�
			}
			if(m_dibang_data[i]==0x20) // ��������ո��־ 0x20 �����
			{
				i++;
			}
			else
			{
				m_Weight[j] = m_dibang_data[i];
//				printf("char  = 0x%02X\n",m_dibang_data[i]);
				j++;
				if(m_dibang_data[i+1]==0x20) // �����һ���ַ�Ϊ0x20��ʾ�Ѿ���ȡ�������ˣ���������ݺ��ԡ�
				{
					m_Weight[j] = 0x00; // ֱ�Ӹ���һ���ַ���ֵ0x00�������ַ�����
					j=0;
					break; // ����ѭ��������ִ�У��Ա���ʾ����
				}
				i++;
			}
		}
	}

	

//	printf("m_Weight = %s \n",m_Weight);

	iWeight2 = atoi((char*)m_Weight); // ���ַ���������ֵת��Ϊ������
	CString strWeight;
	strWeight.Format(_T("%d"),iWeight2);
	m_zhongliang.SetWindowText(strWeight+L"KG"); // ʵʱ��ʾ����

	return 0;
}

// ������
void CClientDlg::CalcJinE()
{
	// ��þ���
	CString JingZhong;
	m_jingzhong.GetWindowText(JingZhong);
	int iJingZhong = _ttoi(JingZhong);

	// ��ó���
//	CString CheXing;
//	m_chexing.GetWindowText(CheXing);

	// ��õ���
	CString DanJia;
	m_danjia.GetWindowText(DanJia); // ��õ���
	int iDanJia = _ttoi(DanJia); // ת������

	// ������� �� ���
	float iDun =0;
	float iJinE=0;
	iDun = (float)((float)iJingZhong/1000); // �� = ǧ��/1000

//	if(CheXing.Compare(L"��")==0)
	if(m_danjiadanwei.Compare(L"����")==0)
	{
		// ����������
		float LiFang = iDun / m_midu; // ���� = ��/�ܶ�
		iJinE = iDanJia * LiFang; // ��� = ���� * ����
		GetDlgItem(IDC_STATIC_Dun)->SetWindowText(L"Ԫ/����");
	}
//	else if(CheXing.Compare(L"С��")==0)
	else if(m_danjiadanwei.Compare(L"��")==0)
	{
		// ���ּ���
		iJinE = iDanJia * iDun; // ��� = ���� * ��
		GetDlgItem(IDC_STATIC_Dun)->SetWindowText(L"Ԫ/��");
	}

	if(iJinE > 0)
	{
		// ���������λ����ʮλ��
		int a = 0;
		int b = 0;
		a = (int)iJinE; // ǿ�Ƹ���ת��������ȥС�����֣�����������
		b=a%10;//������,�õ����һλ  
		if (b>=5) // ����
			a=(a/10+1)*10; // ʮλ��һ,����ʮ��
		else // ����
			a=(a/10)*10; // ��ȥ��λ,����ʮ��
		/////////////////////////////

		CString JinE;
		JinE.Format(_T("%d"),a);
		m_jine.SetWindowText(JinE); // ���ý��
	}
}

void CClientDlg::OnBnClickedButtonCom1Send()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ִ��Ԥ��
	CPrintFrame *frame = new CPrintFrame();
	frame->Create(_T("��ӡԤ��"), this,TRUE );
}

// ��������
void CClientDlg::OnConnected()
{
	USES_CONVERSION;  // dali
	m_ip.SetWindowText(A2CW(conf.ip));
	char tmp[16]={0};
	sprintf(tmp,"%d",conf.port);
	m_port.SetWindowText(A2CW(tmp));
	printf("���ӷ������ɹ�\n");
	m_btn_net.SetWindowText(_T("���ӳɹ�"));
	m_btn_net.EnableWindow(FALSE);
	//MessageBox("���ӳɹ�");
}

// ������������
void CClientDlg::OnRvc()
{
	memset(&m_net_rvc_data,0,10240);
	m_net_rvc_len = m_Conn.Receive(m_net_rvc_data,10239);
	if (SOCKET_ERROR != m_net_rvc_len)
	{
		printf("%s\n",m_net_rvc_data);
		switch(m_post_id)
		{
		case 1: // ��������
			OnKeepalive();
			break;
		case 2: // �û���¼����
			OnLogin();
			break;
		case 3: // ����µ��˵���
			OnGet1();
			break;
		case 4: // �ύ��һ�ι�����
			OnPost1();
			break;
		case 5: // ��õ�һ�ι��������ݣ����ڶ��ι���
			OnGet2();
			break;
		case 6: // �ڶ��ι�����
			OnPost2();
			break;
		}
	}
}

// �ر�����
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

	if(m_Conn.Send(Data,strlen(Data))==SOCKET_ERROR) // ������ͷ���-1����ʾ����
	{
		if(GetLastError()==WSAEWOULDBLOCK)
		{
		}
		else
		{
			m_Conn.Close(); // �ر�����
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

	if(m_Conn.Send(Data,strlen(Data))==SOCKET_ERROR) // ������ͷ���-1����ʾ����
	{
		if(GetLastError()==WSAEWOULDBLOCK)
		{
		}
		else
		{
			m_Conn.Close(); // �ر�����
		}
	}
	printf("%s\n",Data);
}

BOOL CClientDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message==WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_RETURN: // �س�����
			//MessageBox("�س�");
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
					SendMessage(WM_COMMAND,i,(LPARAM)wnd->m_hWnd); // ���Ͱ�ť��Ϣ
				}
				if(i == IDC_EDIT_DANHAO) // ����ǵ��ſؼ�
				{
					SendMessage(WM_COMMAND,IDC_BUTTON_GET,(LPARAM)wnd->m_hWnd); // ���Ͱ�ť��Ϣ
					return TRUE;
				}

					pMsg->wParam = VK_TAB; // ������һ���ؼ�
			}
			break;
//		case VK_ESCAPE: // ESC ����
//			break;
		}
	}

	if(pMsg->message==WM_SYSKEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_F4: // ALT + F4���� ͨ�������˳�����
			MessageBox(_T("F4"));
			return TRUE; // ��������ִ���˳�����
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

// ���ӷ�����
void CClientDlg::OnBnClickedButtonNetConn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��ʼ��Socket
	m_Conn.SetDlg(this);
	if (m_Conn.Create())
	{
		printf("����Socket�ɹ�\n");
	}
	else
	{
		MessageBox(_T("����Socketʧ�ܣ�"));
	}
	USES_CONVERSION;  // dali
	m_Conn.Connect(A2CW(conf.ip),conf.port);
}

// ���´򿪴���
void CClientDlg::OnBnClickedButtonComConn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��ʼ������
	if(!com1.open(conf.com1_id,conf.com1_para))
	{
		m_com1.SetWindowText(_T("��ʧ��"));
//		MessageBox("����1��ʧ��", "����", MB_OK);
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

// ��¼
void CClientDlg::OnBnClickedButtonLogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	USES_CONVERSION; // dali
	m_post_id = 2; // �ύIDΪ2
	char Data[256] ={0};
	strcat(Data,"User=");
	CString strUser =_T("");
	m_user.GetWindowText(strUser); // ����û���
	strcat(Data,W2A(strUser)); // �����û���
	strcat(Data,"&Passwd=");
	CString strPwd = _T("");
	m_pwd.GetWindowText(strPwd); // �������
	strcat(Data,W2A(strPwd)); // ��������
	strcat(Data,"&Level=1"); // ����Level=1
	GetData("/login.php",(char*)&Data); // ���� GET ����
}

// �ǳ�
void CClientDlg::OnBnClickedButtonLogout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_user.SetWindowText(_T(""));
	m_user.EnableWindow(TRUE);
	m_pwd.SetWindowText(_T(""));
	m_pwd.EnableWindow(TRUE);
	m_btn_login.EnableWindow(TRUE);
	memset(&(conf.cookie),0,256);
	memset(&(conf.sid),0,256);
	memset(&(conf.aid),0,256);
}

// ��������
void CClientDlg::OnKeepalive()
{
	if(strcmp(conf.aid,"")==0)
	{
		return;
	}
	// �����ﴦ������Ϣ
	TOKEN * t = (TOKEN *)malloc(sizeof(TOKEN));
	TOKEN * l = (TOKEN *)malloc(sizeof(TOKEN));

	char *tStr ,*lStr;
	tStr = strtoken(t,(char*)&m_net_rvc_data,"\r\n"); // ��Ӧ��
	lStr = strtoken(l,(char*)tStr," "); // HTTP/1.1
	lStr = strtoken(l,NULL," "); // 200 
	if(strcmp(lStr,"200")==0)
	{
		while(t->data!=NULL)
		{
			tStr = strtoken(t,NULL, "\r\n");
			if(strcmp(tStr,"")==0) // ����
			{
				tStr = strtoken(t,NULL, "\r\n"); // �õ���Ӧ�峤��
				tStr = strtoken(t,NULL, "\r\n"); // �õ���Ӧ������
				break;
			}
		}
		if(strcmp(tStr,"")==0) // ������ص�����Ϊ��
		{
			MessageBox(L"�޳�����Ϣ!!!",L"���ݿ�");
		}
		else
		{
			USES_CONVERSION;  // dali
			cJSON *jsonroot = cJSON_Parse(tStr); //json��
			if(jsonroot)
			{
				m_list.DeleteAllItems(); // �����������
				int size = cJSON_GetArraySize(jsonroot); // �������ĳ���
				for(int i=0;i<size-1;i++) // ѭ������Ԫ�أ��ų����һ��
				{
					cJSON* node;
					node = cJSON_GetArrayItem(jsonroot,i);

					// ���� JSON ����������
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
				MessageBox(L"���������س�����Ϣ����",L"������");
			}
			cJSON_Delete(jsonroot);
		}
	}
}

// �û���¼
void CClientDlg::OnLogin()
{
	// ������� 200 �� SetCookie ������õ�¼��ؿؼ�
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
				// ����Ӧ���ж��Ƿ���ڡ�AID����ݱ�ʶ��
				// �������¼�ɹ��������¼ʧ�ܡ�
				cStr = strtoken(c,NULL,":");
				aStr = strtoken(a,cStr,"=");
				if(strcmp(aStr," PHPSESSID")==0) // �ỰID
				{
					strcpy(conf.sid,cStr); // ����SID��ֵ
				}

				if(strcmp(aStr," AID")==0) // ���ID
				{
					strcpy(conf.aid,cStr); // ����AID��ֵ
				}	
			}
		} // while

		if(strcmp(conf.sid,"") > 0 && strcmp(conf.aid,"")>0)
		{
			strcpy(conf.cookie,conf.sid); // ����Cookie��ֵ
			strcat(conf.cookie,";");
			strcat(conf.cookie,conf.aid);
			m_user.EnableWindow(FALSE); // �����û������
			m_pwd.EnableWindow(FALSE);  // ������������� 
			m_btn_login.EnableWindow(FALSE); // ���õ�¼��ť
			m_id.EnableWindow(TRUE); // ���õ��ſؼ�
			m_id.SetFocus(); // ���õ���Ϊ����
			
		}
		else
		{
			MessageBox(_T("�û��� �� ���� ����"),_T("��¼ʧ��"));
		}
	}
}

// ����һ���µĵ���
void CClientDlg::OnGet1()
{
	GetWindow();
//	m_jingzhong.SetReadOnly(TRUE);
//	m_danjia.SetReadOnly(TRUE);

	TOKEN * t = (TOKEN *)malloc(sizeof(TOKEN));
	TOKEN * l = (TOKEN *)malloc(sizeof(TOKEN));

	char *tStr ,*lStr, *cStr;
	tStr = strtoken(t,(char*)&m_net_rvc_data,"\r\n"); // ��Ӧ��
	lStr = strtoken(l,(char*)tStr," "); // HTTP/1.1
	lStr = strtoken(l,NULL," "); // 200 
	if(strcmp(lStr,"200")==0)
	{
		while(t->data!=NULL)
		{
			tStr = strtoken(t,NULL, "\r\n");
			if(strcmp(tStr,"")==0) // ����
			{
				tStr = strtoken(t,NULL, "\r\n"); // �õ���Ӧ�峤��
				tStr = strtoken(t,NULL, "\r\n"); // �õ���Ӧ������
				break;
			}
		}
		if(strcmp(tStr,"")==0) // ������ص�����Ϊ��
		{
			MessageBox(L"�޿��õĵ���!!!",L"���ݿ�");
		}
		else
		{
			USES_CONVERSION;  // dali
			cJSON *jsonroot = cJSON_Parse(tStr); //json��
			if(jsonroot)
			{
				m_id.SetWindowText(A2CW(cJSON_GetObjectItem(jsonroot,"id")->valuestring)); // ���á����š�
				m_post_id = 4; // ��һ���ύ
			}
			else
			{
				MessageBox(L"���������ص��Ŵ���",L"������");
			}
			cJSON_Delete(jsonroot);

			m_id.EnableWindow(FALSE); // ��ֹ�����š��Ի���
			m_tijiao.EnableWindow(TRUE); // ���á��ύ����ť
			m_chehao.SetFocus(); // ���ó���Ϊ����
		}
		
	}
}

// ���ݵ��ţ����󵥾���Ϣ
void CClientDlg::OnGet2()
{
	SetWindow(); // �������пؼ�
//	m_jingzhong.EnableWindow(TRUE); // ���á����ء��ؼ�
//	m_danjia.EnableWindow(TRUE); // ���á����ۡ��ؼ�
//	m_jingzhong.SetReadOnly(FALSE); // �衰���ء�Ϊ��ֻ��
//	m_danjia.SetReadOnly(FALSE); // �衰���ۡ�Ϊ��ֻ��


	// �����������ݣ�����ʾ������
	TOKEN * t = (TOKEN *)malloc(sizeof(TOKEN));
	TOKEN * l = (TOKEN *)malloc(sizeof(TOKEN));

	char *tStr;
	char *lStr;
	tStr = strtoken(t,(char*)&m_net_rvc_data,"\r\n"); // ��Ӧ��
	lStr = strtoken(l,(char*)tStr," "); // HTTP/1.1
	lStr = strtoken(l,NULL," "); // 200 
	if(strcmp(lStr,"200")==0)
	{
		while(t->data!=NULL)
		{
			tStr = strtoken(t,NULL, "\r\n");
			if(strcmp(tStr,"")==0) // ����
			{
				tStr = strtoken(t,NULL, "\r\n"); // �õ���Ӧ�峤��
				tStr = strtoken(t,NULL, "\r\n"); // �õ���Ӧ������
				break;
			}
		}
		if(strcmp(tStr,"")==0) // ������ص�����Ϊ��
		{
			MessageBox(L"���Ų�����!",L"���ݿ�");
			SetWindow(); // �������пؼ�
			m_id.EnableWindow(TRUE); // ���õ��ſؼ�

			m_id.SetWindowText(_T("")); // ����
			m_chehao.SetWindowText(_T("")); // ����
			m_dianhua.SetWindowText(_T("")); // �绰
			m_shouhuo.SetWindowText(_T("")); // �ջ���λ
			m_guige.SetWindowText(_T("")); // ������
			m_pizhong.SetWindowText(_T("")); // Ƥ��
			m_maozhong.SetWindowText(_T("")); // ë��
			m_jingzhong.SetWindowText(_T("")); // ����
			m_danjia.SetWindowText(_T("")); // ����
			m_jine.SetWindowText(_T("")); // ���
			m_yue.SetWindowText(_T("")); // ���

			m_dayin.EnableWindow(FALSE); // ���á���ӡ����ť
			m_id.SetFocus();
		}
		else
		{
			USES_CONVERSION;  // dali
			cJSON *jsonroot = cJSON_Parse(tStr); //json��
			if(jsonroot)
			{
				m_chehao.SetWindowText(A2CW(UTF8ToEncode(cJSON_GetObjectItem(jsonroot,"ch")->valuestring))); // ����
				m_dianhua.SetWindowText(A2CW(cJSON_GetObjectItem(jsonroot,"dh")->valuestring)); // �绰
				m_shouhuo.SetWindowText(A2CW(UTF8ToEncode(cJSON_GetObjectItem(jsonroot,"dw")->valuestring))); // ��λ
				m_huowu.SetWindowText(A2CW(UTF8ToEncode(cJSON_GetObjectItem(jsonroot,"hw")->valuestring))); // ����
				m_guige.SetWindowText(A2CW(cJSON_GetObjectItem(jsonroot,"gg")->valuestring)); // ���
				m_chexing.SetWindowText(A2CW(UTF8ToEncode(cJSON_GetObjectItem(jsonroot,"cx")->valuestring))); // ����
				m_pizhong.SetWindowText(A2CW(cJSON_GetObjectItem(jsonroot,"pz")->valuestring)); // Ƥ��
				m_maozhong.SetWindowText(A2CW(cJSON_GetObjectItem(jsonroot,"mz")->valuestring)); // ë��
				m_jingzhong.SetWindowText(A2CW(cJSON_GetObjectItem(jsonroot,"jz")->valuestring)); // ����
				m_danjia.SetWindowText(A2CW(UTF8ToEncode(cJSON_GetObjectItem(jsonroot,"dj")->valuestring))); // ����
				m_danjiadanwei = (A2CW(UTF8ToEncode(cJSON_GetObjectItem(jsonroot,"djdw")->valuestring))); // ���۵�λ
				m_midu = atof(cJSON_GetObjectItem(jsonroot,"md")->valuestring); // �ܶ�
				m_jine.SetWindowText(A2CW(UTF8ToEncode(cJSON_GetObjectItem(jsonroot,"je")->valuestring))); // ���
				m_yue.SetWindowText(A2CW(UTF8ToEncode(cJSON_GetObjectItem(jsonroot,"ye")->valuestring))); // ���
				m_post_id = 6; // �ڶ����ύ
			}
			cJSON_Delete(jsonroot);
		}
	}
	if(strcmp(lStr,"400")==0)
		MessageBox(_T("�ļ�û���ҵ���"),_T("��������"));
	if(strcmp(lStr,"500")==0)
		MessageBox(_T("���������󣡣���"),_T("��������"));

	m_tijiao.EnableWindow(TRUE); // ���á��ύ����ť
//	m_jingzhong.SetFocus(); // ���þ���Ϊ����

//	free(t);
//	free(l);
}

// ��һ���ύ����
void CClientDlg::OnPost1()
{
//	MessageBox(L"��һ�ι���");
	// �жϵ�һ���ύ�Ƿ���ȷ
	// �����ȷ����ת������ӡ����ť
	m_dayin.EnableWindow(TRUE); // ���á���ӡ����ť
	m_tijiao.EnableWindow(FALSE); // ���á��ύ����ť
	m_dayin.SetFocus();
}

// �ڶ����ύ����
void CClientDlg::OnPost2()
{
//	MessageBox(L"�ڶ��ι���");
	// �жϵڶ����ύ�Ƿ���ȷ
	// �����ȷ����ת������ӡ����ť
	m_dayin.EnableWindow(TRUE); // ���á���ӡ����ť
	m_tijiao.EnableWindow(FALSE); // ���á��ύ����ť
	m_dayin.SetFocus();
}

// ��ʱ��
void CClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch(nIDEvent)
	{
	case 1:
		m_post_id = 1; // �ύIDΪ1
		GetData("/keepalive.php","");
		return;
	}
	CDialogEx::OnTimer(nIDEvent);
}

// �ύ��ť
void CClientDlg::OnBnClickedButtonTijiao()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��һ���ύ��m_post_id = 4; 
	// �ڶ����ύ��m_post_id = 6; 
	// ��Ҫ�ж��ǵ�һ���ύ���ǵڶ����ύ
	

	USES_CONVERSION;

	CString strDanHao,strCheHao,strCheXing; // ���ţ����ţ�����
	CString strDanWei,strDianHua; // ��λ���绰
	CString strHuoWu,strGuiGe; // ������
	CString strPiZhong,strMaoZhong,strJingZhong; // Ƥ�أ�ë�أ�����
	CString strDanJia,strJinE; // ���ۣ����
	CString strYouHui; // �Ż���Ϣ

	m_id.GetWindowText(strDanHao); // ����
	m_chehao.GetWindowText(strCheHao); // ����
	m_chexing.GetWindowText(strCheXing); // ����
	m_shouhuo.GetWindowText(strDanWei); // ��λ
	m_dianhua.GetWindowText(strDianHua); // �绰
	m_huowu.GetWindowText(strHuoWu); // ����
	m_guige.GetWindowText(strGuiGe); // ���
	m_pizhong.GetWindowText(strPiZhong); // Ƥ��
	m_maozhong.GetWindowText(strMaoZhong); // ë��
	m_jingzhong.GetWindowText(strJingZhong); // ����
	m_danjia.GetWindowText(strDanJia); // ����
	m_jine.GetWindowText(strJinE); // ���
	if(m_shoudong.GetCheck())
	{
		strYouHui = L"�ֶ�";
	}
	if(m_youhui.GetCheck())
	{
		strYouHui = L"�Ż�";
	}

	// ���ë��Ϊ�գ���ʾ��һ���ύ
	if(strMaoZhong.IsEmpty())
	{
		if(strPiZhong.IsEmpty()) // ���Ƥ��Ϊ��
		{
			MessageBox(L"\"Ƥ��\"����Ϊ�գ����ذ���·���Ƿ�������",L"�ذ�");
			return;
		}
//		else
//		{
//			m_post_id = 4; // ��һ���ύ
//		}
	}
	else // �ڶ����ύ
	{
		if(strJingZhong.IsEmpty())
		{
			MessageBox(L"\"����\"����Ϊ�գ����ذ���·���Ƿ�������",L"�ذ�");
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
	sprintf(str,"%sDanJia=%s&JinE=%s&ZhuangTai=%d&",str,W2A(strDanJia),W2A(strJinE),m_post_id); // ���� ��� ״̬
	sprintf(str,"%sYouHui=%s&",str,W2A(strYouHui)); // �Ż���Ϣ

	CString strUser;
	m_user.GetWindowText(strUser);
	sprintf(str,"%sSiBangYuan=%s",str, W2A(strUser)); // ˾��Ա
	PostData("/post.php",str);

}

// ��ӡ��ť
void CClientDlg::OnBnClickedButtonDayin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// ��ע
	if(m_shoudong.GetCheck())
	{
		DaYin.m_BeiZhu = L"�ֶ�";
	}
	if(m_youhui.GetCheck())
	{
		DaYin.m_BeiZhu = L"�Ż�";
	}
	m_user.GetWindowText(DaYin.m_User);


	// ����ı�������ݣ��������������ڵ��Ŵ���
	SetWindow(); // �������пؼ�
	m_id.EnableWindow(TRUE); // ���õ��ſؼ�

	m_id.SetWindowText(_T("")); // ����
	m_chehao.SetWindowText(_T("")); // ����
	m_dianhua.SetWindowText(_T("")); // �绰
	m_shouhuo.SetWindowText(_T("")); // �ջ���λ
	m_guige.SetWindowText(_T("")); // ������
	m_pizhong.SetWindowText(_T("")); // Ƥ��
	m_maozhong.SetWindowText(_T("")); // ë��
	m_jingzhong.SetWindowText(_T("")); // ����
	m_danjia.SetWindowText(_T("")); // ����
	m_jine.SetWindowText(_T("")); // ���
	m_yue.SetWindowText(_T("")); // ���
	if(m_shoudong.GetCheck()) // �ֶ�
	{
		m_shoudong.SetCheck(FALSE);
	}
	if(m_youhui.GetCheck()) // �Ż�
	{
		m_youhui.SetCheck(FALSE);
	}

	m_dayin.EnableWindow(FALSE); // ���á���ӡ����ť
	m_id.SetFocus();

	// ִ�д�ӡ
	DoPrint();
}

// ���ý��ÿؼ�
void CClientDlg::SetWindow()
{
	m_id.EnableWindow(FALSE); // ����
	m_chehao.EnableWindow(FALSE); // ����
	m_chexing.EnableWindow(FALSE); // ����
	m_dianhua.EnableWindow(FALSE); // �绰
	m_shouhuo.EnableWindow(FALSE); // ��λ
	m_huowu.EnableWindow(FALSE); // ����
	m_guige.EnableWindow(FALSE); // ���
	m_pizhong.EnableWindow(FALSE); // Ƥ��
	m_maozhong.EnableWindow(FALSE); // ë��
	m_jingzhong.EnableWindow(FALSE); // ����
	m_danjia.EnableWindow(FALSE); // ����
	m_jine.EnableWindow(FALSE); // ���
}

// �������ÿؼ�
void CClientDlg::GetWindow()
{
	m_id.EnableWindow(TRUE); // ����
	m_chehao.EnableWindow(TRUE); // ����
	m_chexing.EnableWindow(TRUE); // ����
	m_dianhua.EnableWindow(TRUE); // �绰
	m_shouhuo.EnableWindow(TRUE); // ��λ
	m_huowu.EnableWindow(TRUE); // ����
	m_guige.EnableWindow(TRUE); // ���
	m_pizhong.EnableWindow(TRUE); // Ƥ��
	m_maozhong.EnableWindow(TRUE); // ë��
	m_jingzhong.EnableWindow(TRUE); // ����
	m_danjia.EnableWindow(TRUE); // ����
	m_jine.EnableWindow(TRUE); // ���
}

// ��ȡ������Ϣ
void CClientDlg::OnBnClickedButtonGet()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SYSTEMTIME st;
	GetLocalTime(&st);
	char str[32]={0};
	sprintf(str,"date=%4d%02d%02d&id=",st.wYear,st.wMonth,st.wDay); // ��ǰ����

	CString strId;
	m_id.GetWindowText(strId);

	if(strId.IsEmpty()) // �жϡ����š��Ƿ�Ϊ��
	{
		// ��ȡ����
		m_post_id = 3; // �ύIDΪ3
		m_type = 1;
		strcat(str,"0");
		GetData("/getid.php",str); // ���һ���µĵ���

		m_tijiao.SetFocus(); // ���õ���Ϊ����
	}
	else
	{
		int i = _ttoi(strId); 
		if(i==0)
		{
			MessageBox(L"���Ų���ȫΪ��0");
			return;
		}

		// ���ݵ��Ż�ȡ������Ϣ
		m_post_id = 5; // �ύIDΪ5
		m_type = 2;
		// ������Ҫ���ɵ�ǰ�����ںͻ�õ���
		CString id=L"";
		m_id.GetWindowText(id);
		USES_CONVERSION;
		strcat(str,W2A(id));
		GetData("/getid.php",str); // �ύ��������
		m_tijiao.SetFocus(); // ���õ���Ϊ����
	}
}


void CClientDlg::OnBnClickedButtonEdit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetWindow();
	m_pizhong.SetReadOnly(FALSE);
	m_maozhong.SetReadOnly(FALSE);
	m_jingzhong.SetReadOnly(FALSE);
	m_danjia.SetReadOnly(FALSE);
	m_jine.SetReadOnly(FALSE);
	m_tijiao.EnableWindow(TRUE);
	m_dayin.EnableWindow(TRUE);
}

// ��ӡ���
//�������岢���һҳ���������иߣ��߾࣬�п���Щ��������
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
	// ��ע
	if(m_shoudong.GetCheck())
	{
		DaYin.m_BeiZhu = L"�ֶ�";
	}
	if(m_youhui.GetCheck())
	{
		DaYin.m_BeiZhu = L"�Ż�";
	}
	m_user.GetWindowText(DaYin.m_User);

	// ����ʯ����ر���
	m_printer->m_title = DaYin.m_title; // ����
	m_printer->m_id = DaYin.m_id;// ����
	m_printer->m_CheHao = DaYin.m_CheHao; // ����
	m_printer->m_CheXing = DaYin.m_CheXing; // ����
	m_printer->m_DanWei = DaYin.m_DanWei; // �ջ���λ
	m_printer->m_DianHua = DaYin.m_DianHua; // �绰
	m_printer->m_HuoWu = DaYin.m_HuoWu; // ��������
	m_printer->m_GuiGe = DaYin.m_GuiGe; // ������
	m_printer->m_PiZhong = DaYin.m_PiZhong; // Ƥ��
	m_printer->m_MaoZhong = DaYin.m_MaoZhong; // ë��
	m_printer->m_JingZhong = DaYin.m_JingZhong; // ����
	m_printer->m_DanJia = DaYin.m_DanJia; // ����
	m_printer->m_JinE = DaYin.m_JinE; // ���
	m_printer->m_BeiZhu = DaYin.m_BeiZhu; // ��ע
	m_printer->m_User = DaYin.m_User; // ˾��Ա
	m_printer->m_Times  = m_type; // ��������
	
	return TRUE;
}
LRESULT CClientDlg::OnEndPrinting(WPARAM wParam,LPARAM lParam) 
{
	return 0;
}

//����Ĵ�ӡ����
LRESULT CClientDlg::OnMyPrint(WPARAM wParam,LPARAM lParam)
{
	CDC* p_dc = reinterpret_cast<CDC*>(wParam);
	CPrintInfo* p_info = reinterpret_cast<CPrintInfo*>(lParam);

	if( p_info->m_nCurPage == 1 )
	{
		//������һҳ������
		m_printer->SetCurrentPage(0);
		m_printer->StartPage();
		m_printer->PrintHeader();
		m_printer->PrintBody();
		m_printer->EndPage();
		m_printer->EndPrinting();
	}
//	else
//	{
		//�����ڶ�ҳ������
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
	//ȫ����ӡ

	if( IDOK == dlg.DoModal() )
	{
		CDC dc;
		dc.Attach(dlg.m_pd.hDC);
		std::tr1::shared_ptr<CPrinter> printer(new CPrinter(&dc));
		printer->SetTotalLineNumber(10);//������б�ؼ������ݣ�����printer�ж�����
		printer->PreparePrinting();

		// ����ʯ����ر���
		printer->m_title = DaYin.m_title; // ����
		printer->m_id = DaYin.m_id;// ����
		printer->m_CheHao = DaYin.m_CheHao; // ����
		printer->m_CheXing = DaYin.m_CheXing; // ����
		printer->m_DanWei = DaYin.m_DanWei; // �ջ���λ
		printer->m_DianHua = DaYin.m_DianHua; // �绰
		printer->m_HuoWu = DaYin.m_HuoWu; // ��������
		printer->m_GuiGe = DaYin.m_GuiGe; // ������
		printer->m_PiZhong = DaYin.m_PiZhong; // Ƥ��
		printer->m_MaoZhong = DaYin.m_MaoZhong; // ë��
		printer->m_JingZhong = DaYin.m_JingZhong; // ����
		printer->m_DanJia = DaYin.m_DanJia; // ����
		printer->m_JinE = DaYin.m_JinE; // ���
		printer->m_BeiZhu = DaYin.m_BeiZhu; // ��ע
		printer->m_User = DaYin.m_User; // ˾��Ա

		if(printer->StartPrinting())
		{
			while ( printer->NeedStartNewPage() )
			{
				printer->StartPage();
				//��ӡ���ݣ��Լ���ҳ
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
	// TODO: �ڴ����ר�ô����/����û���
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

// ��ѯ��ť
void CClientDlg::OnBnClickedButtonFind()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

// ���Ӱఴť
void CClientDlg::OnBnClickedButtonJiaojie()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
//	sprintf(str,"%s%4d%02d%02d%%20%02d:%02d:%02d",str,st.wYear,st.wMonth,st.wDay,st.wHour-8,st.wMinute,st.wSecond); // ��ʼʱ�䣺����Ϊ�ϰ�ʱ��
//	sprintf(str,"%s^&end=",str); // ע����win����������������'&'��Ҫת��Ϊ'^&'
//	sprintf(str,"%s%4d%02d%02d%%20%02d:%02d:%02d",str,st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond); // ����ʱ��: ����Ϊ��ǰʱ��
	system(str);
}

// �޸ĵ���
void CClientDlg::OnEnChangeEditDanjia()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CalcJinE(); // ������
}

// �޸ľ���
void CClientDlg::OnEnChangeEditJingzhong()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CalcJinE(); // ������
}

// �޸Ļ���
void CClientDlg::OnCbnSelchangeComboHuowu()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString HuoWu;
	m_huowu.GetWindowText(HuoWu); // ��û��������
	if(HuoWu.Compare(L"��ʯ")==0)
	{
		m_guige.ResetContent(); // ��������б�
		m_guige.AddString(_T("0.5"));
		m_guige.AddString(_T("1.2"));
		m_guige.AddString(_T("1.3"));
		m_guige.SetCurSel(0);
		return;
	}
	if(HuoWu.Compare(L"����ʯ")==0)
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

// �޸ĳ���
void CClientDlg::OnCbnSelchangeComboChexing()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CalcJinE(); // ������
}

// ȡ������ť
void CClientDlg::OnBnClickedButtonZhongliang()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	USES_CONVERSION;
	// ���õ�һ�ι����͵ڶ��ι�����Ƥ�غ�ë��
	// Ƥ��
	if(m_type == 1)
	{
		m_pizhong.SetWindowText(A2W((char*)m_Weight)); // ��ֵ��ʾ��Ƥ�ؿؼ��С�
	}

	// ë��
	if(m_type == 2)
	{
		m_maozhong.SetWindowText(A2W((char*)m_Weight)); // ��ֵ��ʾ��ë�ؿؼ��С�
		// ���� = ë�� - Ƥ�� 
		int iJingZhong,iMaoZhong,iPiZhong;
		CString MaoZhong,PiZhong,JingZhong;

		m_maozhong.GetWindowText(MaoZhong); // ���ë��
		iMaoZhong = _ttoi(MaoZhong); // ��ë��תΪ���� 

		m_pizhong.GetWindowText(PiZhong); // ���Ƥ��
		iPiZhong = _ttoi(PiZhong); // ��Ƥ��תΪ���� 

		iJingZhong = iMaoZhong - iPiZhong; // ���㾻��
		JingZhong.Format(_T("%d"),iJingZhong);
		m_jingzhong.SetWindowText(JingZhong); // ��ֵ��ʾ�ھ��ؿؼ��С�
		CalcJinE(); // ������
	}
}

// ����ֶ���ѡ��
void CClientDlg::OnBnClickedCheck1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// 1���жϡ��Żݡ���ѡ���Ƿ�ѡ��
	// 2�������޸ġ����༭��
	// 3����עΪ���ֶ���
	if(m_shoudong.GetCheck() && m_youhui.GetCheck())
	{
		m_shoudong.SetCheck(FALSE);
		MessageBox(L"����ͬʱѡ��\"�ֶ�\"��\"�Ż�\"");
		return;
	}
	if(m_shoudong.GetCheck()) // ѡ��״̬
	{
		m_jine.EnableWindow(TRUE); // ���á����ؼ�
		m_jine.SetReadOnly(FALSE); // �衰��Ϊ��ֻ��
		m_jine.SetFocus(); // ���á����ı���Ϊ����
		// ���ñ�עΪ���ֶ���
	}
	else // δѡ��״̬
	{
		m_jine.EnableWindow(FALSE); // ���á����ؼ�
		m_jine.SetReadOnly(TRUE); // �衰��Ϊ��ֻ��
	}
	
}

// ����Żݸ�ѡ��
void CClientDlg::OnBnClickedCheck2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_shoudong.GetCheck() && m_youhui.GetCheck())
	{
		m_youhui.SetCheck(FALSE);
		MessageBox(L"����ͬʱѡ��\"�ֶ�\"��\"�Ż�\"");
		return;
	}
	if( m_youhui.GetCheck()) // ѡ��״̬
	{
		m_jine.EnableWindow(TRUE); // ���á����ؼ�
		m_jine.SetReadOnly(FALSE); // �衰��Ϊ��ֻ��
		m_jine.SetFocus(); // ���á����ı���Ϊ����
		// ���ñ�עΪ���Żݡ�
	}
	else // δѡ��״̬
	{
		m_jine.EnableWindow(FALSE); // ���á����ؼ�
		m_jine.SetReadOnly(TRUE); // �衰��Ϊ��ֻ��
	}
}

// LIST˫���¼�����
void CClientDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nItem = pNMListView->iItem;  // �����˫����item�����
//	int nSubItem = pNMListView->iSubItem; // ���Ƕ�Ӧ�������
	CString sText = m_list.GetItemText(nItem, 0);
	m_list.ModifyStyle(NULL, LVS_SHOWSELALWAYS, 0);
	m_list.SetItemState(nItem, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
	m_id.SetWindowText(sText); // ���õ���
	OnBnClickedButtonGet(); // ��õ�����Ϣ
	*pResult = 0;
}

// ȡ����ť
void CClientDlg::OnBnClickedButtonQuxiao()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetWindow(); // �������пؼ�
	m_id.EnableWindow(TRUE); // ���õ��ſؼ�
	m_id.SetWindowText(_T("")); // ����
	m_chehao.SetWindowText(_T("")); // ����
	m_dianhua.SetWindowText(_T("")); // �绰
	m_shouhuo.SetWindowText(_T("")); // �ջ���λ
	m_guige.SetWindowText(_T("")); // ������
	m_pizhong.SetWindowText(_T("")); // Ƥ��
	m_maozhong.SetWindowText(_T("")); // ë��
	m_jingzhong.SetWindowText(_T("")); // ����
	m_danjia.SetWindowText(_T("")); // ����
	m_jine.SetWindowText(_T("")); // ���
	m_yue.SetWindowText(_T("")); // ���
	if(m_shoudong.GetCheck()) // �ֶ�
	{
		m_shoudong.SetCheck(FALSE);
	}
	if(m_youhui.GetCheck()) // �Ż�
	{
		m_youhui.SetCheck(FALSE);
	}
}
