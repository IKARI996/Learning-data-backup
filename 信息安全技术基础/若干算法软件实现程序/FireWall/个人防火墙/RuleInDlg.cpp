// RuleInDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FirewallApp.h"
#include "RuleInDlg.h"
#include "util.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRuleInDlg dialog


CRuleInDlg::CRuleInDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRuleInDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRuleInDlg)
	m_portsource = 0;
	m_action = _T("����");
	m_protocol = _T("ȫ��");
	//}}AFX_DATA_INIT
}


void CRuleInDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRuleInDlg)
	DDX_Control(pDX, IDC_IPADDRESS2, m_srcMask);
	DDX_Control(pDX, IDC_IPADDRESS1, m_srcIp);
	DDX_Text(pDX, IDC_EDIT2, m_portsource);
	DDV_MinMaxInt(pDX, m_portsource, 0, 65535);
	DDX_CBString(pDX, IDC_COMBO1, m_action);
	DDX_CBString(pDX, IDC_COMBO2, m_protocol);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRuleInDlg, CDialog)
	//{{AFX_MSG_MAP(CRuleInDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRuleInDlg message handlers

/**
 *	���ӹ��˹���
 *
 */
void CRuleInDlg::OnOK() 
{
	UpdateData(TRUE);
	
	/*ȡ�ù����ԴIP*/
	if(!m_srcIp.IsBlank())
	{
		m_srcIp.GetAddress(rule.sourceIp);
		convertDWORD(&rule.sourceIp);
	}
	else rule.sourceIp = ALL_IP;
	
	/*ȡ�ù����Դ����*/
	if(!m_srcMask.IsBlank())
	{
		m_srcMask.GetAddress(rule.sourceMask);
		convertDWORD(&rule.sourceMask);
	}
	else rule.sourceMask = ALL_MASK;

	/*ȡ�ù����Э��*/
	if(m_protocol == "TCP")
		rule.protocol = FILTER_PROTO_TCP;
	else if(m_protocol == "UDP")
		rule.protocol = FILTER_PROTO_UDP;
	else if(m_protocol == "ICMP")
		rule.protocol = FILTER_PROTO_ICMP;
	else
		rule.protocol = FILTER_PROTO_ANY;

	/*�Եù�����Ӧ�Ĳ���,Ŀǰ������ǽ��û��֧�ָù���*/
	if(m_action == "")
	{
		AfxMessageBox("��ѡ�����");
		return;
	}
	else
	{
		if(m_action == "Forward")
			rule.action = PF_ACTION_FORWARD;
		else
			rule.action = PF_ACTION_DROP;
	}

	/*ȡ�ù����Դ�˿�*/
	rule.sourcePort = m_portsource;

	/*����ʶ���������ݰ����˹���*/
	rule.bOut = false;
	
	CDialog::OnOK();
}
