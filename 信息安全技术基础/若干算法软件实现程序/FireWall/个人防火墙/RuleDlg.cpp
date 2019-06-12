// RuleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FirewallApp.h"
#include "RuleDlg.h"
#include "util.h"

#include "rules.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRuleDlg dialog


CRuleDlg::CRuleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRuleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRuleDlg)
	m_portDestination = 0;
	m_action = _T("����");
	m_protocol = _T("ȫ��");
	//}}AFX_DATA_INIT
}


void CRuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRuleDlg)
	DDX_Control(pDX, IDC_IPADDRESS4, m_destMask);
	DDX_Control(pDX, IDC_IPADDRESS3, m_destIp);
	DDX_Text(pDX, IDC_EDIT4, m_portDestination);
	DDV_MinMaxUInt(pDX, m_portDestination, 0, 65535);
	DDX_CBString(pDX, IDC_COMBO3, m_action);
	DDX_CBString(pDX, IDC_COMBO4, m_protocol);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRuleDlg, CDialog)
	//{{AFX_MSG_MAP(CRuleDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRuleDlg message handlers

/**
 *	��ȡ���˹���
 *
 */
void CRuleDlg::OnOK() 
{
	UpdateData(TRUE);

	/*ȡ�ù��˹����Ŀ��IP��ַ*/
	if(!m_destIp.IsBlank())
	{
		m_destIp.GetAddress(rule.destinationIp);
		/*�ӿؼ���ȡ�õ�IP���ڲ���ʾ��ϵͳAPIʹ�õ��ڲ���ʾ������ͬ,
		  ��ȡ��IP�ڲ���ʾת��ΪϵͳAPIʹ�õ��ڲ���ʾ*/
		convertDWORD(&rule.destinationIp);
	}
	else rule.destinationIp = ALL_IP;//Ϊ�ձ�ʾȫ��IP


	/*ȡ�ù��˹����Ŀ������*/
	if(!m_destMask.IsBlank())
	{
		m_destMask.GetAddress(rule.destinationMask);
		convertDWORD(&rule.destinationMask);
	}
	else rule.destinationMask = ALL_MASK;//Ϊ�ձ�ʾȫ������


	/*ȡ�ù��˹����Э��*/
	if(m_protocol == "TCP")
		rule.protocol = FILTER_PROTO_TCP;
	else if(m_protocol == "UDP")
		rule.protocol = FILTER_PROTO_UDP;
	else if(m_protocol == "ICMP")
		rule.protocol = FILTER_PROTO_ICMP;
	else
		rule.protocol = FILTER_PROTO_ANY;

	/*ȡ�ù��˹���Ĳ���,Ŀǰ������ǽ��û��֧�ָù���*/
	if(m_action == "")
	{
		AfxMessageBox("��ѡ�����");
		return;
	}
	else
	{
		if(m_action == "����")
			rule.action = PF_ACTION_FORWARD;
		else
			rule.action = PF_ACTION_DROP;
	}

	/*���˹����Ŀ��˿�*/
	rule.destinationPort = m_portDestination;

	/*����ʶ�����������ݰ��Ĺ��˹���*/
	rule.bOut = true;
	
	CDialog::OnOK();
}
