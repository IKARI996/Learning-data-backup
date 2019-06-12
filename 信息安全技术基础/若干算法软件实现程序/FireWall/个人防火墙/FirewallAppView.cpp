// FirewallAppView.cpp : implementation of the CFirewallAppView class
//

#include "stdafx.h"
#include "FirewallApp.h"
#include <winsock.h>

#include "FirewallAppDoc.h"
#include "FirewallAppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFirewallAppView

IMPLEMENT_DYNCREATE(CFirewallAppView, CFormView)

BEGIN_MESSAGE_MAP(CFirewallAppView, CFormView)
	//{{AFX_MSG_MAP(CFirewallAppView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFirewallAppView construction/destruction

CFirewallAppView::CFirewallAppView()
	: CFormView(CFirewallAppView::IDD)
{
	//{{AFX_DATA_INIT(CFirewallAppView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CFirewallAppView::~CFirewallAppView()
{
}

void CFirewallAppView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFirewallAppView)
	DDX_Control(pDX, IDC_LIST1, m_rules);
	//}}AFX_DATA_MAP
}

BOOL CFirewallAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CFirewallAppView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	RECT rc;
	m_rules.GetClientRect(&rc);
	
	/*��ʼ�������б����Ŀ��*/
	int width=rc.right-rc.left-110;
	m_rules.InsertColumn(0, "ԴIP",LVCFMT_LEFT , width/6, 0);
	m_rules.InsertColumn(1, "Դ����",LVCFMT_LEFT , width/6, 1);
	m_rules.InsertColumn(2, "Դ�˿�",LVCFMT_LEFT ,width/6, 2);
	m_rules.InsertColumn(3, "Ŀ��IP",LVCFMT_LEFT , width/6, 3);
	m_rules.InsertColumn(4, "Ŀ������",LVCFMT_LEFT , width/6, 4);
	m_rules.InsertColumn(5, "Ŀ�Ķ˿�",LVCFMT_LEFT , width/6, 5);
	m_rules.InsertColumn(6, "Э��",LVCFMT_LEFT ,60, 6);
	m_rules.InsertColumn(7, "����",LVCFMT_LEFT , 50, 7);

	m_rules.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


}

/////////////////////////////////////////////////////////////////////////////
// CFirewallAppView printing

BOOL CFirewallAppView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFirewallAppView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFirewallAppView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CFirewallAppView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CFirewallAppView diagnostics

#ifdef _DEBUG
void CFirewallAppView::AssertValid() const
{
	CFormView::AssertValid();
}

void CFirewallAppView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CFirewallAppDoc* CFirewallAppView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFirewallAppDoc)));
	return (CFirewallAppDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFirewallAppView message handlers

void CFirewallAppView::UpdateList()
{
	CFirewallAppDoc *doc = GetDocument();

	m_rules.DeleteAllItems();//����б�

	unsigned int i;
	for(i=0;i<doc->nRules;i++)
	{
		AddRuleToList(doc->rules[i]);//���������������б�
	}
}

void CFirewallAppView::AddRuleToList(RuleInfo rule)
{
	char port[6];
	LVITEM it;
	int pos;
	in_addr ip;
	
	/*�����е����ݰ�ԴIP��ַ*/
	it.mask		= LVIF_TEXT;
	it.iItem	= m_rules.GetItemCount();
	it.iSubItem	= 0;
	ip.S_un.S_addr = rule.sourceIp;
	it.pszText	= (rule.sourceIp == ALL_IP) ? "ȫ��" : inet_ntoa(ip);
	pos			= m_rules.InsertItem(&it);

	/*�����е����ݰ�Դ��������*/
	it.iItem	= pos;
	it.iSubItem	= 1;
	ip.S_un.S_addr = rule.sourceMask;
	it.pszText	= inet_ntoa(ip);
	m_rules.SetItem(&it);

	/*�����е����ݰ�Դ�˿�*/
	it.iItem	= pos;
	it.iSubItem	= 2;
	it.pszText	= (rule.sourcePort == FILTER_TCPUDP_PORT_ANY) ? "ȫ��" : itoa(rule.sourcePort, port, 10);
	m_rules.SetItem(&it);
	
	/*�����е����ݰ�Ŀ��IP��ַ*/
	it.iItem	= pos;
	it.iSubItem	= 3;
	ip.S_un.S_addr = rule.destinationIp;
	it.pszText	= (rule.destinationIp == ALL_IP) ? "ȫ��" : inet_ntoa(ip);
	m_rules.SetItem(&it);

	/*�����е����ݰ�Ŀ����������*/
	it.iItem	= pos;
	it.iSubItem	= 4;
	ip.S_un.S_addr = rule.destinationMask;
	it.pszText	= inet_ntoa(ip);
	m_rules.SetItem(&it);

	/*�����е����ݰ�Ŀ��˿�*/
	it.iItem	= pos;
	it.iSubItem = 5;
	it.pszText	= (rule.destinationPort == FILTER_TCPUDP_PORT_ANY) ? "ȫ��" : itoa(rule.destinationPort, port, 10);
	m_rules.SetItem(&it);


	it.iItem	= pos;
	it.iSubItem	= 6;

	/*�����е����ݰ��ķ�װЭ��*/
	if(rule.protocol == FILTER_PROTO_ICMP)
		it.pszText = "ICMP";
	else if(rule.protocol == FILTER_PROTO_TCP)
		it.pszText = "TCP";
	else if(rule.protocol == FILTER_PROTO_UDP)
		it.pszText = "UDP";
	else
		it.pszText = "ȫ��";

	m_rules.SetItem(&it);

	/*�����е����ݰ��Ĳ���*/
	it.iItem	= pos;
	it.iSubItem	= 7;
	it.pszText = rule.action == PF_ACTION_DROP ? "����" : "����";
	m_rules.SetItem(&it);
}
