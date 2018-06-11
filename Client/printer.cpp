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
	m_doc_name = AfxGetAppName(); // ��ó�����
	m_need_start_new_page = TRUE;
}

CPrinter::~CPrinter()
{
	if(m_mission_started)
		EndPrinting();
}

// ��ʼ��ӡ
BOOL CPrinter::StartPrinting()
{
	DOCINFO info;
	::ZeroMemory(&info, sizeof(info));
	info.lpszDocName = m_doc_name;
	m_dc->StartDoc(&info);
	m_mission_started = TRUE;
	return TRUE;
}

// ������ӡ
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

// ���ô�ӡ����
void CPrinter::SetPrinterFont()
{
	CFont f;
	f.CreateStockObject(ANSI_FIXED_FONT);
	m_dc->SelectObject(&f);
}

// ׼����ӡ
void CPrinter::PreparePrinting()
{	
	ASSERT( m_total_line_number != 0 );//����Ƿ������SetTotalLineNumber
	if ( m_total_line_number == 0 )
	{
		return;
	}
	//��������
	SetPrinterFont();
	TEXTMETRIC tm;
	m_dc->GetTextMetrics(&tm);

	m_line_height  = tm.tmHeight + tm.tmInternalLeading; // �и�
	m_page_v_margin = m_dc->GetDeviceCaps(LOGPIXELSY) / 2; // �����Ե
	m_page_h_margin = m_dc->GetDeviceCaps(LOGPIXELSX) / 2; // �����Ե
	m_page_height  = m_dc->GetDeviceCaps(VERTRES); // ҳ��
	m_page_width   = m_dc->GetDeviceCaps(HORZRES); // ҳ��
	m_current_y_pos = m_page_v_margin;

	//���ҳ��
//	m_max_line_count_one_page = (int)((m_page_height-m_page_v_margin*2-50)/(m_line_height+50)); // ҳ���������
//	m_max_page = (int)(m_total_line_number / m_max_line_count_one_page); // ���ҳ��
//	if( m_max_page*m_max_line_count_one_page < m_total_line_number ) m_max_page++;
	m_max_line_count_one_page = 10; // ����
	m_max_page = 1; // ҳ��
}

// ��ӡͷ��
void CPrinter::PrintHeadLine()
{
}

// ��ӡҳ��
void CPrinter::PrintHeader()
{
	CFont *old_font = NULL;
	CFont fontHeader;
	fontHeader.CreatePointFont(200,_T("FixedSys"),m_dc); // ���������С
	old_font=(CFont *)(m_dc->SelectObject(&fontHeader));
	int nPosY,nPosX;
	nPosY = 40;//m_page_v_margin-(3*m_line_height)/2;
	nPosX = 300;//m_page_h_margin;

// ����20180606	
//	m_dc->TextOut(nPosX,nPosY,m_title+L"������"); // ����+������

	m_dc->SelectObject(old_font);
	fontHeader.DeleteObject();
}

// ��ӡҳβ
void CPrinter::PrintFooter()
{
}

// ��ӡҳ��
void CPrinter::PrintBody()
{
	CFont *old_font = NULL;
	CFont data_font;
	data_font.CreatePointFont(120,_T("����"),m_dc);

		old_font = m_dc->SelectObject(&data_font);

		SYSTEMTIME st;
		CString strDateTime;
		GetLocalTime(&st);


//		printf("��һ�ι���ʱ�䣺%s\n",m_GuoBang1);
//		printf("�ڶ��ι���ʱ�䣺%s\n",m_GuoBang2);


		// ��������
		switch(m_Times)
		{
		case 1: // ��һ�ι���
			{
				strDateTime.Format(L"ʱ�䣺%s",m_GuoBang1); // �����ݿ�ȡ�ö��ι���ʱ��
				break;
			}
		case 2: // �ڶ��ι���
			{
				if(m_GuoBang2.IsEmpty())
				{
					strDateTime.Format(L"ʱ�䣺%s",m_GuoBang1); // �����������ݿ�ȡ��һ�ι���ʱ��
				}
				else
				{
					strDateTime.Format(L"ʱ�䣺%s",m_GuoBang2); // �����ݿ�ȡ�ö��ι���ʱ��
				}
				break;
			}
		case 3: // ��һ�ι����ĵ�
			{
				strDateTime.Format(L"ʱ�䣺%s",m_GuoBang1); // �����ݿ�ȡ�ö��ι���ʱ��
				break;
			}
		default:
			strDateTime.Format(L"��ǰ��%4d-%02d-%02d %02d:%02d:%02d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
		}


		// ���ʱ���ֶ�Ϊ��
		if(strDateTime.IsEmpty())
		{
			strDateTime.Format(L"��ǰ��%4d-%02d-%02d %02d:%02d:%02d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
		}
		m_dc->TextOut(60,150,strDateTime); // ʱ��


		strDateTime.Format(L"�绰��%s",m_DianHua);
		m_dc->TextOut(500,150,strDateTime); // �绰

		strDateTime.Format(L"���ţ�%s",m_id); // ����
		m_dc->TextOut(800,150,strDateTime); // ����

		// �����
		CPen  bi,*jbi;
		bi.CreatePen(PS_SOLID,3,RGB(0,0,0));//������ɫ����
		jbi=m_dc->SelectObject(&bi);//ѡ�񻭱�

		for(int i=0;i<7;i++)//��ˮƽ��, �����޸�����
		{
			//            X    Y
			m_dc->MoveTo(60,200+i*40);
			m_dc->LineTo(1320,200+i*40);
		} 

		for(int i=0;i<5;i++)//����ֱ��
		{
			m_dc->MoveTo(60+i*315,200);
			if(i==0)
			{
				m_dc->LineTo(60+i*315,240+5*40); // �����޸��г���
			}
			else if(i==4)
			{
				m_dc->LineTo(60+i*315,240+5*40); // �����޸��г���
			}
			else
			{
				m_dc->LineTo(60+i*315,240+4*40); // �����޸��г���
			}
		}
		m_dc->SelectObject(jbi);

		// ������
		// ��һ��
		m_dc->TextOut(80,207,CString("����"));
		m_dc->TextOut(395,207,m_CheHao);

		// ����20180606
		/*
		m_dc->TextOut(730,207,CString("Ƥ��"));
		if(m_PiZhong.IsEmpty() || m_PiZhong==L"0")
		{
			m_PiZhong = L"";
			m_dc->TextOut(1065,207,m_PiZhong);
		}
		else
		{
			m_dc->TextOut(1065,207,m_PiZhong+L" KG");
		}
		*/

		// �ڶ���
		m_dc->TextOut(80,207+40,CString("����"));
		// ����20180606
		// m_dc->TextOut(395,207+40,m_CheXing);

		// ����20180606
		/*
		m_dc->TextOut(730,207+40,CString("ë��"));
		if(m_MaoZhong.IsEmpty() || m_MaoZhong==L"0")
		{
			m_MaoZhong = L"";
			m_dc->TextOut(1065,207+40,m_MaoZhong);
		}
		else
		{
			m_dc->TextOut(1065,207+40,m_MaoZhong+L" KG");
		}
		*/

		// ������
		m_dc->TextOut(80,207+80,CString("�ͻ�")); // �ɵ�λ���Ƹ�Ϊ�ͻ�
		m_dc->TextOut(395,207+80,m_DanWei);

		// ����
		m_dc->TextOut(730,207+80,CString("JZ"));
		if(m_JingZhong.IsEmpty() || m_JingZhong==L"0")
		{
			m_JingZhong = L"";
			m_dc->TextOut(1065,207+80,m_JingZhong);
		}
		else
		{
			m_dc->TextOut(1065,207+80,m_JingZhong+L" KG");
		}

		// ������
		m_dc->TextOut(80,207+120,CString("����"));
		m_dc->TextOut(395,207+120,m_HuoWu);

		// ����20180606
		/*
		if(m_Type==0) // ֻ�����۲Ŵ�ӡ����
		{
			m_dc->TextOut(730,207+120,CString("����"));
			if(m_DanJia.IsEmpty() || m_DanJia==L"0")
			{
				m_DanJia =L"";
				m_dc->TextOut(1065,207+120,m_DanJia);
			}
			else
			{
				m_dc->TextOut(1065,207+120,m_DanJia+L" Ԫ/"+ m_DanJiaDanWei);
			}
		}
		*/

		// ������
		m_dc->TextOut(80,207+160,CString("���"));
		m_dc->TextOut(395,207+160,m_GuiGe);

		// ����20180606
		/*
		if(m_Type==0) // ֻ�����۲Ŵ�ӡ���
		{
			m_dc->TextOut(730,207+160,CString("���"));
			if(m_JinE.IsEmpty() || m_JinE==L"0")
			{
				m_JinE =L"";
				m_dc->TextOut(1065,207+160,m_JinE);
			}
			else
			{
				m_dc->TextOut(1065,207+160,m_JinE+L" Ԫ");
			}
		}
		*/

		// ������
		m_dc->TextOut(80,207+200,CString("��ע��"));
		// ����20180606
		//m_dc->TextOut(200,207+200,m_BeiZhu);

		// ҳ��
		strDateTime.Format(L"˾��Ա��%s",m_User);
		m_dc->TextOut(60,450,strDateTime);
// ����20180606
//		m_dc->TextOut(600,450,CString("�ͻ�ǩ����"));
		m_dc->TextOut(1000,450,CString("˾��ǩ����"));

		// ������
		USES_CONVERSION;
		char * szText = T2A(m_id);
		struct zint_symbol *symbol;  
		int ret = 0;  
		symbol = ZBarcode_Create();  
		if (symbol != NULL)  
		{  
//			symbol->height = 20;
			symbol->scale = 2;  

            symbol->option_1 = 1; // QR�ݴ���  
            symbol->option_2 = 2; // QR�汾������ͼƬ��С  
			symbol->symbology = 58;// QR��������
//			symbol->symbology = 20;// ��������

			symbol->show_hrt = 1; //����ʾ��Ϣ���������Ϊ1������Ҫ����textֵ  
			symbol->input_mode = UNICODE_MODE;  

			ret = ZBarcode_Encode_and_Buffer(symbol,(unsigned char *)szText,0,0);

			
			BITMAPINFOHEADER	bmih;
			bmih.biSize                  = sizeof (BITMAPINFOHEADER) ;
			bmih.biWidth                 = symbol->bitmap_width ; // ���
			bmih.biHeight                = -symbol->bitmap_height ; // �߶� (������ʾͼ�񵹹���)
			bmih.biPlanes                = 1 ;
			bmih.biBitCount              = 24 ;
			bmih.biCompression           = BI_RGB ;
			bmih.biSizeImage             = symbol->bitmap_width * symbol->bitmap_height * 3;
			bmih.biXPelsPerMeter         = 0 ;
			bmih.biYPelsPerMeter         = 0 ;
			bmih.biClrUsed               = 0 ;
			bmih.biClrImportant          = 0 ;

//			StretchDIBits(m_dc->m_hDC,900,20,450,symbol->bitmap_height,0,0,symbol->bitmap_width,symbol->bitmap_height,symbol->bitmap,(BITMAPINFO*)&bmih,DIB_RGB_COLORS,SRCCOPY); // һά������
			StretchDIBits(m_dc->m_hDC,1100,70,120,120,0,0,symbol->bitmap_width,symbol->bitmap_height,symbol->bitmap,(BITMAPINFO*)&bmih,DIB_RGB_COLORS,SRCCOPY); // ��ά��

			ZBarcode_Delete(symbol);  
		}
		

		m_dc->SelectObject (old_font);

}