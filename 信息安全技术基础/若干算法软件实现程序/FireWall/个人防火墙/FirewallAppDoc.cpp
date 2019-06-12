// FirewallAppDoc.cpp : implementation of the CFirewallAppDoc class
//

#include "stdafx.h"
#include "FirewallApp.h"

#include "FirewallAppDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFirewallAppDoc

IMPLEMENT_DYNCREATE(CFirewallAppDoc, CDocument)

BEGIN_MESSAGE_MAP(CFirewallAppDoc, CDocument)
	//{{AFX_MSG_MAP(CFirewallAppDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFirewallAppDoc construction/destruction

CFirewallAppDoc::CFirewallAppDoc()
{
	nRules = 0;
}

CFirewallAppDoc::~CFirewallAppDoc()
{
}

BOOL CFirewallAppDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFirewallAppDoc serialization

void CFirewallAppDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFirewallAppDoc diagnostics

#ifdef _DEBUG
void CFirewallAppDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFirewallAppDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFirewallAppDoc commands

/**
 *	����һ���ض��Ĺ���
 **/
bool CFirewallAppDoc::AddRule(RuleInfo rule)
{
	if(nRules >= MAX_RULES)//���������Ѿ��ﵽ���ֵ,����������
	{
		AfxMessageBox("�Ѿ��ﵽ��������Ŀ");
		return false;
	}

	else
	{
		rules[nRules] = rule;
		nRules++;
	}

	return true;
}

/**
 *	�������й���	
 **/
bool CFirewallAppDoc::ResetRules()
{
	nRules = 0;
	return true;
}

/** 
 *	ɾ��ָ���Ĺ���
 **/
bool CFirewallAppDoc::DeleteRule(unsigned int position)
{
	
	if(position >= nRules)//��ָ���Ĺ��������еĹ�����,��ɾ��
		return false;

	if(position != nRules - 1)
	{
		unsigned int i;

		for(i = position + 1;i<nRules;i++)//����ɾ������֮��Ĺ���������ǰ��λ,��ճ���λ��
		{
			rules[i - 1] = rules[i];
		}
	}
	nRules--;
	return true;
}
