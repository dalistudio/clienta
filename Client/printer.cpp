#include "stdafx.h"
#include "printer.h"
#include "ClientDlg.h"
#include <math.h>
#include "../zint/zint.h"

CPrinter::CPrinter(CDC * usedc)
{
	m_dc = usedc;
	m_page_v_margin = 0;
	m_page_h_margin = 0;
	m_page_height = 0;
	m_current_y_pos = 0;
	m_line_height = 0; 
	m_is_printing_page = FALSE;
	m_mission_started = FALSE;
	m_page_number = 0;
	m_max_page = 0;
	m_total_line_number = 0;
	m_v_dist = 2;
	m_max_line_count_one_page = 0;
	m_doc_name = AfxGetAppName(); // 获得程序名
	m_need_start_new_page = TRUE;
}

CPrinter::~CPrinter()
{
	if(m_mission_started)
		EndPrinting();
}

// 开始打印
BOOL CPrinter::StartPrinting()
{
	DOCINFO info;
	::ZeroMemory(&info, sizeof(info));
	info.lpszDocName = m_doc_name;
	m_dc->StartDoc(&info);
	m_mission_started = TRUE;
	return TRUE;
}

// 结束打印
void CPrinter::EndPrinting()
{
	m_dc->EndPage();
	m_dc->EndDoc();
	m_page_number = 0;
	m_mission_started = FALSE;
}

void CPrinter::PrintLine(const CString & s)
{
}

// 设置打印字体
void CPrinter::SetPrinterFont()
{
	CFont f;
	f.CreateStockObject(ANSI_FIXED_FONT);
	m_dc->SelectObject(&f);
}

// 准备打印
void CPrinter::PreparePrinting()
{	
	ASSERT( m_total_line_number != 0 );//检查是否调用了SetTotalLineNumber
	if ( m_total_line_number == 0 )
	{
		return;
	}
	//设置字体
	SetPrinterFont();
	TEXTMETRIC tm;
	m_dc->GetTextMetrics(&tm);

	m_line_height  = tm.tmHeight + tm.tmInternalLeading; // 行高
	m_page_v_margin = m_dc->GetDeviceCaps(LOGPIXELSY) / 2; // 横向边缘
	m_page_h_margin = m_dc->GetDeviceCaps(LOGPIXELSX) / 2; // 竖向边缘
	m_page_height  = m_dc->GetDeviceCaps(VERTRES); // 页高
	m_page_width   = m_dc->GetDeviceCaps(HORZRES); // 页宽
	m_current_y_pos = m_page_v_margin;

	//求出页数
//	m_max_line_count_one_page = (int)((m_page_height-m_page_v_margin*2-50)/(m_line_height+50)); // 页的最大行数
//	m_max_page = (int)(m_total_line_number / m_max_line_count_one_page); // 最大页数
//	if( m_max_page*m_max_line_count_one_page < m_total_line_number ) m_max_page++;
	m_max_line_count_one_page = 10; // 行数
	m_max_page = 1; // 页数
}

// 打印头行
void CPrinter::PrintHeadLine()
{
}

// 打印页首
void CPrinter::PrintHeader()
{
	CFont *old_font = NULL;
	CFont fontHeader;
	fontHeader.CreatePointFont(200,_T("FixedSys"),m_dc); // 设置字体大小
	old_font=(CFont *)(m_dc->SelectObject(&fontHeader));
	int nPosY,nPosX;
	nPosY = 40;//m_page_v_margin-(3*m_line_height)/2;
	nPosX = 300;//m_page_h_margin;
	
	m_dc->TextOut(nPosX,nPosY,m_title+L"过磅单"); // 标题
	//m_dc->TextOutW(nPosX,nPosY,CString("海南港口文峰石场过磅单"));

	m_dc->SelectObject(old_font);
	fontHeader.DeleteObject();
}

// 打印页尾
void CPrinter::PrintFooter()
{
}

// 打印页体
void CPrinter::PrintBody()
{
	CFont *old_font = NULL;
	CFont data_font;
	data_font.CreatePointFont(120,_T("宋体"),m_dc);

		old_font = m_dc->SelectObject(&data_font);

		SYSTEMTIME st;
		CString strDateTime;
		GetLocalTime(&st);

		strDateTime.Format(L"打印时间：%4d-%02d-%02d %02d:%02d:%02d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
		m_dc->TextOut(60,150,strDateTime);

		//strDateTime.Format(L"单号：%4d%02d%02d %s",st.wYear,st.wMonth,st.wDay,m_id); // 单号
		strDateTime.Format(L"单号：%s",m_id); // 单号
		m_dc->TextOut(600,150,strDateTime); // 单号

		strDateTime.Format(L"电话：%s",m_DianHua);
		m_dc->TextOut(1000,150,strDateTime); // 电话
		

		// 画表格
		CPen  bi,*jbi;
		bi.CreatePen(PS_SOLID,3,RGB(0,0,0));//创建黑色画笔
		jbi=m_dc->SelectObject(&bi);//选择画笔

		for(int i=0;i<6;i++)//画水平线, 这里修改行数
		{
			//            X    Y
			m_dc->MoveTo(60,200+i*40);
			m_dc->LineTo(1320,200+i*40);
		} 

		for(int i=0;i<5;i++)//画垂直线
		{
			m_dc->MoveTo(60+i*315,200);
			m_dc->LineTo(60+i*315,240+4*40); // 这里修改列长度
		}
		m_dc->SelectObject(jbi);

		// 表单内容
		// 第一行
		m_dc->TextOut(80,207,CString("车号"));
		m_dc->TextOut(395,207,m_CheHao);

		m_dc->TextOut(730,207,CString("皮重"));
		m_dc->TextOut(1065,207,m_PiZhong+L" KG");

		// 第二行
		m_dc->TextOut(80,207+40,CString("车型"));
		m_dc->TextOut(395,207+40,m_CheXing);

		m_dc->TextOut(730,207+40,CString("毛重"));
		m_dc->TextOut(1065,207+40,m_MaoZhong+L" KG");

		// 第三行
		m_dc->TextOut(80,207+80,CString("收货单位"));
		m_dc->TextOut(395,207+80,m_DanWei);

		m_dc->TextOut(730,207+80,CString("净重"));
		m_dc->TextOut(1065,207+80,m_JingZhong+L" KG");

		// 第四行
		m_dc->TextOut(80,207+120,CString("货物名称"));
		m_dc->TextOut(395,207+120,m_HuoWu);

		m_dc->TextOut(730,207+120,CString("单价"));
		if(m_CheXing.Compare(L"大车")==0)
		{
			m_dc->TextOut(1065,207+120,m_DanJia+L" 元/立方");
		}
		else
		{
			m_dc->TextOut(1065,207+120,m_DanJia+L" 元/吨");
		}

		// 第五行
		m_dc->TextOut(80,207+160,CString("货物规格"));
		m_dc->TextOut(395,207+160,m_GuiGe);

		m_dc->TextOut(730,207+160,CString("金额"));
		m_dc->TextOut(1065,207+160,m_JinE+L" 元");

		// 第六行
//		m_dc->TextOut(80,207+200,CString("货物流向"));
//		m_dc->TextOut(395,207+200,m_LiuXiang);

//		m_dc->TextOut(730,207+200,CString("出厂时间"));
//		m_dc->TextOut(1030,207+200,m_ChuChang);

		// 页脚
		strDateTime.Format(L"司磅员：%s",m_User);
		m_dc->TextOut(60,410,strDateTime);
		m_dc->TextOut(600,410,CString("客户签名："));
		m_dc->TextOut(1000,410,CString("司机签名："));

		if(m_Times==1) // 第一次过磅
		{
			m_dc->TextOut(60,460,CString("白：存根联"));
			m_dc->TextOut(375,460,CString("红：进料联"));
		}
		if(m_Times==2) // 第二次过磅
		{
			m_dc->TextOut(60,460,CString("白：保安联"));
			m_dc->TextOut(375,460,CString("红：存根联"));
			m_dc->TextOut(690,460,CString("绿：财务联"));
			m_dc->TextOut(1005,460,CString("黄：客户联"));
		}

		// 条形码
		USES_CONVERSION;
		char * szText = T2A(m_id);
		struct zint_symbol *symbol;  
		int ret = 0;  
		symbol = ZBarcode_Create();  
		if (symbol != NULL)  
		{  
			symbol->height = 20;
			symbol->scale = 2;  
            //symbol->option_1 = 1; //容错级别  
            //symbol->option_2 = 1; //版本，决定图片大小  
			symbol->symbology = 20;//BARCODE_QRCODE;  // 条码类型

			symbol->show_hrt = 1; //可显示信息，如果设置为1，则需要设置text值  
			symbol->input_mode = UNICODE_MODE;  

			ret = ZBarcode_Encode_and_Buffer(symbol,(unsigned char *)szText,0,0);

			
			BITMAPINFOHEADER	bmih;
			bmih.biSize                  = sizeof (BITMAPINFOHEADER) ;
			bmih.biWidth                 = symbol->bitmap_width ; // 宽度
			bmih.biHeight                = -symbol->bitmap_height ; // 高度 (负数表示图像倒过来)
			bmih.biPlanes                = 1 ;
			bmih.biBitCount              = 24 ;
			bmih.biCompression           = BI_RGB ;
			bmih.biSizeImage             = symbol->bitmap_width * symbol->bitmap_height * 3;
			bmih.biXPelsPerMeter         = 0 ;
			bmih.biYPelsPerMeter         = 0 ;
			bmih.biClrUsed               = 0 ;
			bmih.biClrImportant          = 0 ;
			//SetDIBitsToDevice(m_dc->m_hDC, 800, 30, 400, 100, 0, 0,400, 100, symbol->bitmap, (BITMAPINFO*)&bmih, DIB_RGB_COLORS);
			StretchDIBits(m_dc->m_hDC,900,20,450,symbol->bitmap_height,0,0,symbol->bitmap_width,symbol->bitmap_height,symbol->bitmap,(BITMAPINFO*)&bmih,DIB_RGB_COLORS,SRCCOPY);

			/*
			//HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, _T("d:\\1.bmp"), IMAGE_BITMAP,0, 0, LR_CREATEDIBSECTION |LR_DEFAULTSIZE | LR_LOADFROMFILE);
			HBITMAP hBitmap = CreateDIBSection (NULL, (BITMAPINFO *)  &bmih, 0, (void**)symbol->bitmap, NULL, 0) ;

			BITMAP bitmap;
			::GetObject(hBitmap,sizeof(BITMAP),&bitmap);
        
			HDC dcMem;
			dcMem=::CreateCompatibleDC(m_dc->m_hDC);
			HBITMAP hOldBmp=(HBITMAP)::SelectObject(dcMem,hBitmap);     
 
			/// 复制位图到矩阵     PosY PosX 宽  高
			::StretchBlt(m_dc->m_hDC,900,30,400,100,dcMem,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);
		    ::SelectObject(dcMem,hOldBmp);

			// 清理
			::DeleteDC(dcMem);
			::DeleteObject(hBitmap);
			*/
			ZBarcode_Delete(symbol);  
		}
		

		m_dc->SelectObject (old_font);

}