// FirewallAppDoc.h : interface of the CFirewallAppDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIREWALLAPPDOC_H__615C5245_0FBE_434A_B124_2EAEB8BBD20B__INCLUDED_)
#define AFX_FIREWALLAPPDOC_H__615C5245_0FBE_434A_B124_2EAEB8BBD20B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Rules.h"

//���屾���˷���ǽ����������
#define MAX_RULES 100

class CFirewallAppDoc : public CDocument
{
protected: // create from serialization only
	CFirewallAppDoc();
	DECLARE_DYNCREATE(CFirewallAppDoc)

// Attributes
public:
	unsigned int nRules;//��¼�������Ŀ
	RuleInfo rules[MAX_RULES];//��¼���������

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFirewallAppDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	bool DeleteRule(unsigned int position);//ɾ��ָ��������ڲ���ʾ
	bool ResetRules();//������еĹ���
	bool AddRule(RuleInfo rule);//����һ������

	virtual ~CFirewallAppDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CFirewallAppDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIREWALLAPPDOC_H__615C5245_0FBE_434A_B124_2EAEB8BBD20B__INCLUDED_)
