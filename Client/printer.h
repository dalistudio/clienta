#ifndef H_CDDE948C_BF98_4d28_BDE9_356B25238FDB_H
#define H_CDDE948C_BF98_4d28_BDE9_356B25238FDB_H
class CPrinter 
{
public:
	CPrinter(CDC * dc);
	virtual ~CPrinter();
	void PrintLine(const CString & s);
	
protected:
	CDC* m_dc;
	int m_page_v_margin;	//����߾�
	int m_page_h_margin;	//����߾�
	int m_page_height;		//ҳ��,����margin
	int m_page_width;		//ҳ��,����margin
	int m_current_y_pos;	//����ǰ��ӡ���ĸ�λ���ˣ��������ҳ�ײ�Ҫ����EndPage���¿�һҳ
	int m_line_height;		//�иߣ���������߶Ⱥ��м��
	int m_v_dist;			//�м��
	BOOL m_is_printing_page;//���ڴ�ӡҳ
	BOOL m_mission_started;	//��ӡ�����Ѿ���ʼ
	BOOL m_need_start_new_page;//��Ҫ��ʼ�µ�һҳ

	int m_max_page;			//��ҳ��
	int m_page_number;		//��ǰҳ��
	int m_total_line_number; //Ҫ��ӡ�����ݵ���������������ҳ��ҳü��ֻ����������
	int m_max_line_count_one_page;
	CString m_doc_name;		//ҳü����

public:
	// ʯ���������ݵı���
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
	CString m_DanJiaDanWei; // ���۵�λ
	CString m_JinE; // ���
	CString m_BeiZhu; // ��ע
	CString m_User; // ˾��Ա
	int m_Times; // ��������
	int m_Type; // ֧������


	void PreparePrinting();	//�������壬����dc����һЩ����
	BOOL StartPrinting();
	void EndPrinting();
	void PrintHeadLine();	//��ӡ������
	void PrintHeader();		//��ӡҳü
	void PrintFooter();		//��ӡҳ��
	void PrintBody();		//��ӡһҳ������
	void StartPage()
	{
		ASSERT(m_dc);if(m_dc)m_dc->StartPage();
		m_page_number++;
	}
	void EndPage()
	{
		ASSERT(m_dc);if(m_dc)m_dc->EndPage();
	}
	int GetPageNumber() { return m_page_number; }
	void SetDocName( CString doc_name ) { m_doc_name = doc_name; }
	void SetCurrentPage( int page_num ) { m_page_number = page_num; }
	virtual void SetPrinterFont();
public:
	BOOL IsMissionStarted(){ return m_mission_started; }
	BOOL IsPrintingPage(){ return m_is_printing_page; }
	void SetTotalLineNumber( int total_number )
	{
		m_total_line_number = total_number; 
	}
	BOOL NeedStartNewPage()
	{ 
		return ( m_page_number < m_max_page); 
	}
};
#endif

