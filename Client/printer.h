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
	int m_page_v_margin;	//纵向边距
	int m_page_h_margin;	//横向边距
	int m_page_height;		//页高,包括margin
	int m_page_width;		//页宽,包括margin
	int m_current_y_pos;	//纵向当前打印到哪个位置了，如果到了页底部要调用EndPage重新开一页
	int m_line_height;		//行高，包括字体高度和行间距
	int m_v_dist;			//行间距
	BOOL m_is_printing_page;//正在打印页
	BOOL m_mission_started;	//打印任务已经开始
	BOOL m_need_start_new_page;//需要开始新的一页

	int m_max_page;			//总页码
	int m_page_number;		//当前页码
	int m_total_line_number; //要打印的内容的总行数，不包括页脚页眉，只包括数据行
	int m_max_line_count_one_page;
	CString m_doc_name;		//页眉文字

public:
	// 石场单据内容的变量
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
	CString m_DanJiaDanWei; // 单价单位
	CString m_JinE; // 金额
	CString m_BeiZhu; // 备注
	CString m_User; // 司磅员
	int m_Times; // 过磅次数
	int m_Type; // 支持类型


	void PreparePrinting();	//设置字体，根据dc计算一些参数
	BOOL StartPrinting();
	void EndPrinting();
	void PrintHeadLine();	//打印列名行
	void PrintHeader();		//打印页眉
	void PrintFooter();		//打印页脚
	void PrintBody();		//打印一页的内容
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

