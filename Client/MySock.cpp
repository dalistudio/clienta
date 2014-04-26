// MySock.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MySock.h"
#include "Client.h"
#include "ClientDlg.h"


// CMySock

CMySock::CMySock()
{
	m_pDlg = NULL;
}

CMySock::~CMySock()
{
	m_pDlg = NULL;
}

// CMySock ��Ա����
// ���ӷ�����
void CMySock::OnConnect(int nErrorCode)
{
	if (0 == nErrorCode)
	{
		m_pDlg->OnConnected();
	}
	CAsyncSocket::OnConnect(nErrorCode);
}

// ��������
void CMySock::OnReceive(int nErrorCode)
{
	if (0 == nErrorCode)
	{
		m_pDlg->OnRvc();
	}
	CAsyncSocket::OnReceive(nErrorCode);
}

// ��������
void CMySock::OnClose(int nErrorCode)
{
	if ( 0 == nErrorCode)
	{
		m_pDlg->OnClose();
	}
	CAsyncSocket::OnClose(nErrorCode);
}

void CMySock::SetDlg(CClientDlg* pDlg)
{
	if (NULL != pDlg)
	{
		m_pDlg = pDlg;
	}
}