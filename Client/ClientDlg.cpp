
// ClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"
#include "../cjson/cJSON.h"

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
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CClientDlg �Ի���




CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CHEXING, m_cbCheXing);
	DDX_Control(pDX, IDC_COMBO_HUOWU, m_cbHuoWu);
	DDX_Control(pDX, IDC_COMBO_GUIGE, m_cbGuiGe);
	DDX_Control(pDX, IDC_COMBO_LIUXIANG, m_cbLiuXiang);
	DDX_Control(pDX, IDC_EDIT6, m_ip);
	DDX_Control(pDX, IDC_EDIT7, m_port);
	DDX_Control(pDX, IDC_EDIT8, m_com1);
	DDX_Control(pDX, IDC_EDIT10, m_com2);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_MESSAGE(ON_COM_RECEIVE, On_Receive) // ����յ� ON_COM_RECEIVE ��Ϣ�����ý��պ���
	ON_BN_CLICKED(IDC_BUTTON_COM, &CClientDlg::OnBnClickedButtonCom)
	ON_BN_CLICKED(IDC_BUTTON_COM1_SEND, &CClientDlg::OnBnClickedButtonCom1Send)
	ON_BN_CLICKED(IDC_BUTTON_COM2_SEND, &CClientDlg::OnBnClickedButtonCom2Send)
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
	
	memset(&conf,0,sizeof(CONF));
	strcpy(conf.title,"���ϸۿ��ķ�ʯ��");
	strcpy(conf.ip,"192.168.203.5");
	conf.port = 80;
	conf.com1_name=1;
	strcpy(conf.com1_parm,"9600,8,N,1");
	conf.com2_name=2;
	strcpy(conf.com2_parm,"9600,8,N,1");

	// �������ļ� JSON ��ʽ
	FILE *f=fopen("config","rb"); // �����ļ� config
	if(f==NULL)
	{
		MessageBox("�������ļ�ʧ�ܣ�", "config", MB_OK);
	}


	// ��ʼ��Socket
	m_Conn.SetDlg(this);
	if (m_Conn.Create())
	{
		printf("����Socket�ɹ�\n");
	}
	else
	{
		MessageBox("����Socketʧ�ܣ�");
	}

	// ���ӷ�����
	if (0 == m_Conn.Connect(conf.ip,conf.port))
	{
		m_ip.SetWindowText(conf.ip);
		char tmp[16]={0};
		sprintf(tmp,"%d",conf.port);
		m_port.SetWindowText(tmp);
		printf("���ӷ������ɹ�\n");
	}
	else
	{
		MessageBox("���ӷ�����ʧ��", "����", MB_OK);
	}

	// ��ʼ������
	if(!com1.open(conf.com1_name))
	{
		m_com2.SetWindowText("��ʧ��");
//		MessageBox("����1��ʧ��", "����", MB_OK);
	}
	else
	{
		com1.set_hwnd(m_hWnd);
		char tmp[64] = {0};
		sprintf(tmp,"COM%d,%s",conf.com1_name,conf.com1_parm);
		m_com1.SetWindowText(tmp);
	}

	if(!com2.open(conf.com2_name))
	{
		m_com2.SetWindowText("��ʧ��");
//		MessageBox("����2��ʧ��", "����", MB_OK);
	}
	else
	{
		com2.set_hwnd(m_hWnd);
		char tmp[64] = {0};
		sprintf(tmp,"COM%d,%s",conf.com2_name,conf.com2_parm);
		m_com2.SetWindowText(tmp);
	}

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
		"����");				// ��������

	// ����
	GetDlgItem(IDC_EDIT_TITLE)->SetWindowText(conf.title);
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

	// ��������
	GetDlgItem(IDC_STATIC_LIUXIANG)->SetFont(m_Font);
	GetDlgItem(IDC_COMBO_LIUXIANG)->SetFont(m_Font);


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

	/////////////////////////////////

	// �ύ��ť
	GetDlgItem(IDC_BUTTON_TIJIAO)->SetFont(m_Font);

	// ��ӡ��ť
	GetDlgItem(IDC_BUTTON_DAYIN)->SetFont(m_Font);

	/////////////////////////////////

	m_cbCheXing.AddString("��");
	m_cbCheXing.AddString("С��");
	m_cbCheXing.SetCurSel(0); // ѡ���һ��󳵡�

	m_cbHuoWu.AddString("��ʯ");
	m_cbHuoWu.AddString("����ʯ");
	m_cbHuoWu.AddString("ʯ��");
	m_cbHuoWu.AddString("���");
	m_cbHuoWu.AddString("��ʯ");
	m_cbHuoWu.AddString("Ƭʯ");
	m_cbHuoWu.SetCurSel(0);

	m_cbGuiGe.AddString("0.5");
	m_cbGuiGe.AddString("1.2");
	m_cbGuiGe.AddString("1.3");
	m_cbGuiGe.AddString("1.45");
	m_cbGuiGe.AddString("1.55");
	m_cbGuiGe.AddString("2.4");

	m_cbLiuXiang.AddString("���");
	m_cbLiuXiang.AddString("����");


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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
	
	int len;
	char str[100];

	if(wp==3)
	{
		len = com1.read(str, 100);
		printf("COM1: %s\n",str);
	}

	if(wp==9)
	{
		len = com2.read(str, 100);
		printf("COM2: %s\n",str);
	}
	if(len > 0)
	{
		char com_str[10];
		strcpy(com_str, "COM");
		ltoa((long)wp, com_str + 3, 10); //	WPARAM ����˿ں�
		m_e += com_str;
		m_e += " : ";
		m_e += str;
		m_e += "\r\n";
		GetDlgItem(IDC_EDIT_INFO)->SetWindowText(m_e);
	}
	
	return 0;
}

void CClientDlg::OnBnClickedButtonCom()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//GetData("/","");
	PostData("/post.php","name=dali");

}


void CClientDlg::OnBnClickedButtonCom1Send()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	com1.write("COM1-test");
	CString strEdit("");
	GetDlgItem(IDC_EDIT_CHEHAO)->GetWindowText(strEdit);
	if (strEdit.IsEmpty())
	{
		return;
	}
	char SendBuf[512] = {0};
	strcpy(SendBuf,strEdit);
	m_Conn.Send(SendBuf,strlen(SendBuf));
}


void CClientDlg::OnBnClickedButtonCom2Send()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	com2.write("COM2-test");
}

// ��������
void CClientDlg::OnConnected()
{
	//MessageBox("���ӳɹ�");
}

// ������������
void CClientDlg::OnRvc()
{
	char szRcv[1025] = {0};
	int nRcved = m_Conn.Receive(szRcv,1024);
	if (SOCKET_ERROR != nRcved)
	{
		//strcat(szRcv,"\r\n");
		printf("%s\n",szRcv);
		GetDlgItem(IDC_EDIT_INFO)->SetWindowText(szRcv);
	}
}

// �ر�����
void CClientDlg::OnClose()
{
	m_Conn.Close();
}

void CClientDlg::GetData(char *url, char *parm)
{
	char Data[1024] = {0};
	strcat(Data,"GET ");
	strcat(Data,url);
	strcat(Data,parm);
	strcat(Data," HTTP/1.1\r\n");
	strcat(Data,"Host: ");
	strcat(Data,conf.ip);
	strcat(Data,"\r\n");
	strcat(Data,"Connection: Keep-Alive\r\n");
	strcat(Data,"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n");
	strcat(Data,"User-Agent: Mozilla/5.0 (Windows Client; Dali Wang<wangdali@qq.com>)\r\n");
	strcat(Data,"Accept-Language: zh-CN,zh;q=0.8\r\n");
	strcat(Data,"\r\n");
	m_Conn.Send(Data,strlen(Data));
}

void CClientDlg::PostData(char *url, char *parm)
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
	strcat(Data,"Content-Type: application/x-www-form-urlencoded\r\n");
	strcat(Data,"Content-Length: ");
	char tmp[16] = {0};
	sprintf(tmp,"%d",strlen(parm));
	strcat(Data,tmp);
	strcat(Data,"\r\n");
	strcat(Data,"\r\n");
	strcat(Data,parm);
	m_Conn.Send(Data,strlen(Data));
}

BOOL CClientDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message==WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_RETURN: // �س�����
			MessageBox("�س�");
			return TRUE;
		case VK_ESCAPE: // ESC ����
			return TRUE;
		}
	}

	if(pMsg->message==WM_SYSKEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_F4: // ALT + F4���� ͨ�������˳�����
			MessageBox("F4");
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
