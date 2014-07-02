
// ClientDlg.cpp : ʵ���ļ�
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
	SendMessage(WM_CLOSE); // �رչ��ڶԻ���
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

	//
	// CURL
	// 
	CURLcode code = curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();

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
	strcpy_s(conf.title,"���ϸۿ��ķ�ʯ��");
	strcpy_s(conf.ip,"192.168.1.5");
	conf.port = 80;
	conf.com1_id=1;
	strcpy_s(conf.com1_para,"baud=9600 parity=N data=8 stop=1");

	// �������ļ� JSON ��ʽ
	FILE *f;
	fopen_s(&f,"config","rb"); // �����ļ� config
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
			strcpy_s(conf.title,cJSON_GetObjectItem(jsonroot,"title")->valuestring); // ��ñ���

			cJSON *jsonServer=cJSON_GetObjectItem(jsonroot,"server");//ȡ Server
			strcpy_s(conf.ip,cJSON_GetObjectItem(jsonServer,"ip")->valuestring); // ���IP��ַ
			conf.port = cJSON_GetObjectItem(jsonServer,"port")->valueint; // ��ö˿�

			cJSON *jsonCOM1=cJSON_GetObjectItem(jsonroot,"com1");//ȡ COM1
			conf.com1_id = cJSON_GetObjectItem(jsonCOM1,"port")->valueint; // ���COM�˿�
			strcpy_s(conf.com1_para,cJSON_GetObjectItem(jsonCOM1,"para")->valuestring); // ���COM������
		}
		else
		{
			MessageBox(_T("�����ļ�����"),_T("config"),MB_OK);
		}
		cJSON_Delete(jsonroot);
	}

	USES_CONVERSION;
	// ��ʾ�����������IP��ַ�Ͷ˿�
	m_ip.SetWindowText(A2CW(conf.ip));
	char port[8] = {0};
	_ltoa_s(conf.port,port,6,10);
	m_port.SetWindowText(A2CW(port));

	// ���ö�ʱ��
	SetTimer(1,60000,0); // 60��

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

	m_list.InsertColumn(0,L"����",LVCFMT_CENTER,80);
	m_list.InsertColumn(1,L"����",LVCFMT_CENTER,80);
	m_list.InsertColumn(2,L"����",LVCFMT_CENTER,80);
	m_list.InsertColumn(3,L"��������",LVCFMT_CENTER,80);
	m_list.InsertColumn(4,L"������",LVCFMT_CENTER,80);
	m_list.InsertColumn(5,L"��ϵ�绰",LVCFMT_CENTER,100);
	m_list.InsertColumn(6,L"�ջ���λ",LVCFMT_CENTER,200);
	m_list.InsertColumn(7,L"Ƥ��",LVCFMT_CENTER,100);
	m_list.InsertColumn(8,L"����ʱ��",LVCFMT_CENTER,160);
	m_list.InsertColumn(9,L"����",LVCFMT_CENTER,80);
	
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
			m_Start=0; // ��ֹ���ֶ��0x02 ��û�� 0x0d����
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

	if(m_danjiadanwei.Compare(L"����")==0)
	{
		// ����������
		float LiFang = iDun / m_midu; // ���� = ��/�ܶ�
		iJinE = iDanJia * LiFang; // ��� = ���� * ����
		GetDlgItem(IDC_STATIC_Dun)->SetWindowText(L"Ԫ/����");
	}
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
				UINT i = wnd->GetDlgCtrlID(); // ��ÿؼ��ı��
				if(ClassName == str) // ����ǰ�ť�ؼ�
				{
					SendMessage(WM_COMMAND,i,(LPARAM)wnd->m_hWnd); // ���Ͱ�ť��Ϣ
				}
				if(i == IDC_EDIT_DANHAO) // ����ǡ����š��ؼ�
				{
					SendMessage(WM_COMMAND,IDC_BUTTON_GET,(LPARAM)wnd->m_hWnd); // ���͡���ȡ����ť��Ϣ
					return TRUE;
				}
				if(i== IDC_EDIT_CHEHAO) // ����ǡ����š��ؼ�
				{
					// �����ó��Ŷ�Ӧ����Ϣ
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
		sprintf_s(tmp,"COM%d:%s",conf.com1_id,conf.com1_para);
		USES_CONVERSION;  // dali
		m_com1.SetWindowText(A2CW(tmp));
	}
}

// ��¼
void CClientDlg::OnBnClickedButtonLogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	USES_CONVERSION;
	CString strUser, strPasswd;
	m_user.GetWindowText(strUser); // ����û���
	m_pwd.GetWindowText(strPasswd); // �������

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
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, login_data);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
	curl_easy_setopt(curl,CURLOPT_COOKIEFILE,"");
	res = curl_easy_perform(curl);

	struct curl_slist *cookies = NULL;
	curl_easy_getinfo(curl,CURLINFO_COOKIELIST,&cookies);
	if(cookies->next == NULL) // �ж��Ƿ��еڶ���cookie������Ӧ���ж�AID��
	{
		m_isLogin = 0;
		MessageBox(L"������󣡣�");
		return; // �˳�
	}
	else
	{
		m_isLogin = 1;
	}
	OnCbnSelchangeComboHuowu(); // ��û����Ӧ�Ĺ������
}

// �ǳ�
void CClientDlg::OnBnClickedButtonLogout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_isLogin = 0; 
	OnBnClickedButtonQuxiao(); // ������пؼ�������
	SetWindow(); // �������пؼ�
	m_user.SetWindowText(_T("")); // �����û���Ϊ��
	m_user.EnableWindow(TRUE); // �����û���Ϊ�ɶ�д

	m_pwd.SetWindowText(_T("")); // ���������Ϊ��
	m_pwd.EnableWindow(TRUE); // ���������Ϊ�ɶ�д

	m_btn_login.EnableWindow(TRUE); // ���õ�½��ťΪ�ɲ���
}

// ��ʱ��
void CClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch(nIDEvent)
	{
	case 1: // ��ʱ��1
		OnCheLiang(); // ���������ڳ���Ϣ����
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
	CString strUser; // ˾��Ա

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
	m_user.GetWindowText(strUser);
	

	strYouHui = L"";
	if(m_shoudong.GetCheck())
	{
		strYouHui += L"�ֶ�Ƥ�� ";
	}
	if(m_youhui.GetCheck())
	{
		strYouHui += L"�Żݽ�� ";
	}

	// ���ë��Ϊ�գ���ʾ��һ���ύ
	if(strMaoZhong.IsEmpty())
	{
		if(strPiZhong.IsEmpty()) // ���Ƥ��Ϊ��
		{
			MessageBox(L"\"Ƥ��\"����Ϊ�գ����ذ���·���Ƿ�������",L"�ذ�");
			return;
		}
	}
	else // �ڶ����ύ
	{
		if(strJingZhong.IsEmpty())
		{
			MessageBox(L"\"����\"����Ϊ�գ����ذ���·���Ƿ�������",L"�ذ�");
			return;
		}
	}

	char data[1024]={0};
	sprintf_s(data,"DanHao=%s&CheHao=%s&CheXing=%s&",W2A(strDanHao),W2A(strCheHao),W2A(strCheXing));
	sprintf_s(data,"%sDanWei=%s&DianHua=%s&",data,W2A(strDanWei),W2A(strDianHua));
	sprintf_s(data,"%sHuoWu=%s&GuiGe=%s&",data,W2A(strHuoWu),W2A(strGuiGe));
	sprintf_s(data,"%sPiZhong=%s&MaoZhong=%s&JiangZhong=%s&",data,W2A(strPiZhong),W2A(strMaoZhong),W2A(strJingZhong));
	sprintf_s(data,"%sDanJia=%s&JinE=%s&ZhuangTai=%d&",data,W2A(strDanJia),W2A(strJinE),m_post_id); // ���� ��� ״̬
	sprintf_s(data,"%sYouHui=%s&",data,W2A(strYouHui)); // �Ż���Ϣ
	sprintf_s(data,"%sSiBangYuan=%s",data, W2A(strUser)); // ˾��Ա

	char url[256]={0};
	strcat_s(url,"http://");
	strcat_s(url,conf.ip);
	strcat_s(url,"/");
	strcat_s(url,"post.php");

	CURLcode res;
	curl_easy_setopt(curl,CURLOPT_URL,url);
	curl_easy_setopt(curl, CURLOPT_POST, 1L);  
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, post_data);
	curl_easy_setopt( curl, CURLOPT_WRITEDATA, this ); 
	res = curl_easy_perform(curl);

	// ��ó����ڳ���Ϣ
	OnCheLiang();
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
	DaYin.m_BeiZhu = L"";
	if(m_shoudong.GetCheck())
	{
		DaYin.m_BeiZhu += L"�ֶ�Ƥ�� ";
	}
	if(m_youhui.GetCheck())
	{
		DaYin.m_BeiZhu += L"�Żݽ�� ";
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
	USES_CONVERSION;
	CString strDanHao;
	m_id.GetWindowText(strDanHao); // ��õ���

	if(strDanHao.IsEmpty())
	{
		strDanHao = L"0";
		m_post_id = 3; // ����µ���
	}
	else
	{
		int i = _ttoi(strDanHao); // ������תΪ����
		if(i==0) // �������ȫΪ0
		{
			MessageBox(L"���Ų���ȫΪ��0");
			return;
		}
		m_post_id = 5; // ���ݵ��Ų鵥��
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
}

// �༭��ť
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
	DaYin.m_BeiZhu = L"";
	if(m_shoudong.GetCheck())
	{
		DaYin.m_BeiZhu += L"�ֶ�Ƥ�� ";
	}
	if(m_youhui.GetCheck())
	{
		DaYin.m_BeiZhu += L"�Żݽ�� ";
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
	sprintf_s(str,"start http://");
	sprintf_s(str,"%s%s/",str,conf.ip);
	sprintf_s(str,"%sjiaojie.php?user=",str);
	sprintf_s(str,"%s%s",str,W2A(strUser));
//	sprintf_s(str,"%s%4d%02d%02d%%20%02d:%02d:%02d",str,st.wYear,st.wMonth,st.wDay,st.wHour-8,st.wMinute,st.wSecond); // ��ʼʱ�䣺����Ϊ�ϰ�ʱ��
//	sprintf_s(str,"%s^&end=",str); // ע����win����������������'&'��Ҫת��Ϊ'^&'
//	sprintf_s(str,"%s%4d%02d%02d%%20%02d:%02d:%02d",str,st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond); // ����ʱ��: ����Ϊ��ǰʱ��
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
	// ���޸Ļ���ʱ������HTTP���󣬻��ָ����������й��
	m_guige.ResetContent();
	
	USES_CONVERSION;
	CString strHuoWu; 

	int pos = m_huowu.GetCurSel(); // ��õ�ǰѡ������
	m_huowu.GetLBText(pos,strHuoWu); // ���ָ����ŵ�����

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
	if(m_shoudong.GetCheck()) // ѡ��״̬
	{
		m_pizhong.EnableWindow(TRUE); // ���á�Ƥ�ء��ؼ�
		m_pizhong.SetReadOnly(FALSE); // �衰Ƥ�ء�Ϊ��ֻ��
		m_pizhong.SetFocus(); // ���á�Ƥ�ء��ı���Ϊ����
		// ���ñ�עΪ���ֶ���
	}
	else // δѡ��״̬
	{
		m_pizhong.EnableWindow(FALSE); // ���á�Ƥ�ء��ؼ�
		m_pizhong.SetReadOnly(TRUE); // �衰Ƥ�ء�Ϊ��ֻ��
	}
	
}

// ����Żݸ�ѡ��
void CClientDlg::OnBnClickedCheck2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	m_dayin.EnableWindow(TRUE); // ��������ӡ����ť
	*pResult = 0;
}

// ȡ����ť
void CClientDlg::OnBnClickedButtonQuxiao()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetWindow(); // �������пؼ�
	m_tijiao.EnableWindow(FALSE); // �����ύ��ť
	m_dayin.EnableWindow(FALSE); // ���ô�ӡ��ť
	m_id.EnableWindow(TRUE); // ���õ��ſؼ�
	m_id.SetWindowText(_T("")); // ����
	m_chehao.SetWindowText(_T("")); // ����
	m_dianhua.SetWindowText(_T("")); // �绰
	m_shouhuo.SetCurSel(0); // �ջ���λ
	m_huowu.SetCurSel(0); // ��������
	m_guige.SetCurSel(0); // ������
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
	m_id.SetFocus(); // ���õ���Ϊ����
}

// ��½��������
size_t CClientDlg::login_data(void *ptr, size_t size, size_t nmemb, void *userp)
{
	
	CClientDlg *client =(CClientDlg*)userp;

	// ���ﴦ���Ա����
	USES_CONVERSION;
	cJSON *jsonroot = cJSON_Parse((const char*)ptr); //json��
	if(jsonroot)
	{
		client->m_huowu.ResetContent(); // ���û����б��
		// ��ȡ�������ƺ͹��
		CList<CString ,CString> list; // ����
		cJSON *type = cJSON_GetObjectItem(jsonroot,"type");
		cJSON *next = type->child; // type������
		while(next->next != NULL) // type����һ��Ϊ��
		{
			char * strHuoWu = next->string; // ��������
//			char * strGuiGe = next->valuestring; // ������
			next = next->next; // �ƶ���type����һ��
			//printf("HuoWu:%s = GuiGe:%s\n",UTF8ToEncode(strHuoWu),UTF8ToEncode(strGuiGe));
			if(list.IsEmpty()) // �������Ϊ��
			{
				list.AddTail(A2CW(UTF8ToEncode(strHuoWu))); // ��ӵ�����β
				client->m_huowu.AddString(A2CW(UTF8ToEncode(strHuoWu)));
			}
			else // ����ѭ���Ƿ���ͬ
			{
				POSITION pos = list.GetHeadPosition(); // ��������ͷλ��
				CString pstr1 = A2CW(UTF8ToEncode(strHuoWu));
				CString pstr2;
				int isa = 0;
				while(pos != NULL)   
				{   
					pstr2 = list.GetNext(pos); // �������
					if(pstr1.Compare(pstr2)==0)
					{
						isa = 1;
					}
				}
				if(isa==0)
				{
					list.AddTail(pstr1); // ��ӵ�����β
					client->m_huowu.AddString(pstr1);
				}
						
			}
		}
		client->m_huowu.SetCurSel(0); // ��������ѡ���һ����		
				
		// ��ȡ��Ա����
		cJSON *member = cJSON_GetObjectItem(jsonroot,"member");
		int size = cJSON_GetArraySize(member); // �������ĳ���
		for(int i=0;i<size-1;i++) // ѭ������Ԫ�أ��ų����һ��
		{
			cJSON* node;
			node = cJSON_GetArrayItem(member,i);
			client->m_shouhuo.AddString(A2CW(UTF8ToEncode(node->valuestring))); // ��ӻ�Ա���Ƶ���λ�ؼ���
		}
		client->m_shouhuo.SetCurSel(0);
	}
	cJSON_Delete(jsonroot);

	client->m_user.EnableWindow(FALSE); // �����û������
	client->m_pwd.EnableWindow(FALSE);  // ������������� 
	client->m_btn_login.EnableWindow(FALSE); // ���õ�¼��ť
	client->m_id.EnableWindow(TRUE); // ���õ��ſؼ�
	client->m_id.SetFocus(); // ���õ���Ϊ����
	
	return size*nmemb;
}

// ���ŷ�������
size_t CClientDlg::getid_data(void *ptr, size_t size, size_t nmemb, void *userp)
{
	CClientDlg *client =(CClientDlg*)userp;

	USES_CONVERSION; 
	cJSON *jsonroot = cJSON_Parse((const char*)ptr); //json��
	if(jsonroot)
	{
		if(client->m_post_id ==3) // ����µĵ���
		{
			client->m_post_id = 4; // ��һ���ύ
			client->m_type = 1;

			client->m_id.SetWindowText(A2CW(cJSON_GetObjectItem(jsonroot,"id")->valuestring)); // ���á����š�

			client->GetWindow(); // ���ÿؼ�Ϊ�ɶ�д
			client->m_id.EnableWindow(FALSE); // ��ֹ�����š��Ի���
			client->m_tijiao.EnableWindow(TRUE); // ���á��ύ����ť
			client->m_chehao.SetFocus(); // ���ó���Ϊ����
		}
		else if(client->m_post_id == 5) // ���ݵ��Ų�ѯ����
		{
			client->m_post_id = 6; // �ڶ����ύ
			client->m_type = 2;

			client->m_chehao.SetWindowText(A2CW(UTF8ToEncode(cJSON_GetObjectItem(jsonroot,"ch")->valuestring))); // ����
			client->m_dianhua.SetWindowText(A2CW(cJSON_GetObjectItem(jsonroot,"dh")->valuestring)); // �绰
			client->m_shouhuo.SetWindowText(A2CW(UTF8ToEncode(cJSON_GetObjectItem(jsonroot,"dw")->valuestring))); // ��λ
			client->m_huowu.SetWindowText(A2CW(UTF8ToEncode(cJSON_GetObjectItem(jsonroot,"hw")->valuestring))); // ����
			client->m_guige.SetWindowText(A2CW(cJSON_GetObjectItem(jsonroot,"gg")->valuestring)); // ���
			client->m_chexing.SetWindowText(A2CW(UTF8ToEncode(cJSON_GetObjectItem(jsonroot,"cx")->valuestring))); // ����
			client->m_pizhong.SetWindowText(A2CW(cJSON_GetObjectItem(jsonroot,"pz")->valuestring)); // Ƥ��
			client->m_maozhong.SetWindowText(A2CW(cJSON_GetObjectItem(jsonroot,"mz")->valuestring)); // ë��
			client->m_jingzhong.SetWindowText(A2CW(cJSON_GetObjectItem(jsonroot,"jz")->valuestring)); // ����
			client->m_danjia.SetWindowText(A2CW(UTF8ToEncode(cJSON_GetObjectItem(jsonroot,"dj")->valuestring))); // ����
			client->m_danjiadanwei = (A2CW(UTF8ToEncode(cJSON_GetObjectItem(jsonroot,"djdw")->valuestring))); // ���۵�λ
			client->m_midu = (float)atof(cJSON_GetObjectItem(jsonroot,"md")->valuestring); // �ܶ�
			client->m_jine.SetWindowText(A2CW(UTF8ToEncode(cJSON_GetObjectItem(jsonroot,"je")->valuestring))); // ���
			client->m_yue.SetWindowText(A2CW(UTF8ToEncode(cJSON_GetObjectItem(jsonroot,"ye")->valuestring))); // ���

			client->m_id.EnableWindow(FALSE); // ��ֹ�����š��Ի���
			client->m_tijiao.EnableWindow(TRUE); // ���á��ύ����ť
			client->m_chehao.SetFocus(); // ���ó���Ϊ����
		}
	}
	cJSON_Delete(jsonroot);
	return size*nmemb;
}

// �ύ���ݷ�������
size_t CClientDlg::post_data(void *ptr, size_t size, size_t nmemb, void *userp)
{
	CClientDlg *client =(CClientDlg*)userp;

	char str[16]={0};
	memcpy(str,ptr,5);
	// �����ж��ύ�Ƿ�ɹ�
	if(strcmp(str,"post1")==0)
	{
		client->MessageBox(L"��һ�ι����ύ�ɹ���");
	}

	if(strcmp(str,"post2")==0)
	{
		client->MessageBox(L"�ڶ��ι����ύ�ɹ���");
	}
	return size*nmemb;
}

// ��ù�񷵻�����
size_t CClientDlg::guige_data(void *ptr, size_t size, size_t nmemb, void *userp)
{
	CClientDlg *client =(CClientDlg*)userp;

	USES_CONVERSION;  // dali
	cJSON *jsonroot = cJSON_Parse((const char*)ptr); //json��
	if(jsonroot)
	{
		int size = cJSON_GetArraySize(jsonroot); // �������ĳ���
		for(int i=0;i<size-1;i++) // ѭ������Ԫ�أ��ų����һ��
		{
			cJSON* node;
			node = cJSON_GetArrayItem(jsonroot,i);
			client->m_guige.AddString(A2CW(UTF8ToEncode(node->valuestring))); // ��ӹ�񵽿ؼ���
		}
		client->m_guige.SetCurSel(0);
				
	}
	cJSON_Delete(jsonroot);
	return size*nmemb;
}

// ����ڳ�������������
size_t CClientDlg::cheliang_data(void *ptr, size_t size, size_t nmemb, void *userp)
{
	CClientDlg *client =(CClientDlg*)userp;
	USES_CONVERSION;

	cJSON *jsonroot = cJSON_Parse((const char*)ptr); //json��
	if(jsonroot)
	{
		client->m_list.DeleteAllItems(); // �����������
		int size = cJSON_GetArraySize(jsonroot); // �������ĳ���
		for(int i=0;i<size-1;i++) // ѭ������Ԫ�أ��ų����һ��
		{
			cJSON* node;
			node = cJSON_GetArrayItem(jsonroot,i);

			// ���� JSON ����������
			int nRow = client->m_list.InsertItem(0,A2CW(cJSON_GetObjectItem(node,"id")->valuestring));
			client->m_list.SetItemText(nRow,1,A2CW(UTF8ToEncode(cJSON_GetObjectItem(node,"ch")->valuestring)));
			client->m_list.SetItemText(nRow,2,A2CW(UTF8ToEncode(cJSON_GetObjectItem(node,"cx")->valuestring)));
			client->m_list.SetItemText(nRow,3,A2CW(UTF8ToEncode(cJSON_GetObjectItem(node,"hw")->valuestring)));
			client->m_list.SetItemText(nRow,4,A2CW(UTF8ToEncode(cJSON_GetObjectItem(node,"gg")->valuestring)));
			client->m_list.SetItemText(nRow,5,A2CW(UTF8ToEncode(cJSON_GetObjectItem(node,"dh")->valuestring)));
			client->m_list.SetItemText(nRow,6,A2CW(UTF8ToEncode(cJSON_GetObjectItem(node,"dw")->valuestring)));
			client->m_list.SetItemText(nRow,7,A2CW(UTF8ToEncode(cJSON_GetObjectItem(node,"pz")->valuestring)));
			client->m_list.SetItemText(nRow,8,A2CW(UTF8ToEncode(cJSON_GetObjectItem(node,"gb")->valuestring)));
			if(strcmp(cJSON_GetObjectItem(node,"zt")->valuestring,"0")==0)
			{
				client->m_list.SetItemText(nRow,9,L"��1��");
			}
			if(strcmp(cJSON_GetObjectItem(node,"zt")->valuestring,"1")==0)
			{
				client->m_list.SetItemText(nRow,9,L"��2��");
			}
			
		}
	}
	cJSON_Delete(jsonroot);
	return size*nmemb;
}

// ��ó��ŷ�������
size_t CClientDlg::chehao_data(void *ptr, size_t size, size_t nmemb, void *userp)
{
	CClientDlg *client =(CClientDlg*)userp;
	USES_CONVERSION;

	cJSON *jsonroot = cJSON_Parse((const char*)ptr); //json��
	if(jsonroot)
	{
		int size = cJSON_GetArraySize(jsonroot); // �������ĳ���
		if(size>1)
		{
			cJSON* node;
			node = cJSON_GetArrayItem(jsonroot,1);
			client->m_chexing.SetWindowText(A2CW(UTF8ToEncode(node->valuestring))); // ����

			node = cJSON_GetArrayItem(jsonroot,2);
			client->m_shouhuo.SetWindowText(A2CW(UTF8ToEncode(node->valuestring))); // ��λ

			node = cJSON_GetArrayItem(jsonroot,3);
			client->m_huowu.SetWindowText(A2CW(UTF8ToEncode(node->valuestring))); // ����

			node = cJSON_GetArrayItem(jsonroot,4);
			client->m_guige.SetWindowText(A2CW(UTF8ToEncode(node->valuestring))); // ���
		}
	}
	cJSON_Delete(jsonroot);
	return size*nmemb;
}

// �����ڳ�����
void CClientDlg::OnCheLiang()
{
	if(m_isLogin == 1) // �ж��Ƿ��½�ɹ�
	{
		char url[256]={0};
		strcat_s(url,"http://");
		strcat_s(url,conf.ip);
		strcat_s(url,"/");
		strcat_s(url,"keepalive.php");

		CURLcode res;
		curl_easy_setopt(curl,CURLOPT_URL,url);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cheliang_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, this); 
		res = curl_easy_perform(curl);
	}
	
}