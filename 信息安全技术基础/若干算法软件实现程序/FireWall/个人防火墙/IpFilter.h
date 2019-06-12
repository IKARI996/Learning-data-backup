// IpFilter.h: interface for the CIpFilter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPFILTER_H__E3DA54F2_89B6_440E_855C_2C562BFBD1BA__INCLUDED_)
#define AFX_IPFILTER_H__E3DA54F2_89B6_440E_855C_2C562BFBD1BA__INCLUDED_

#include "rules.h"
#include "stdafx.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIpFilter  
{
public:
	CIpFilter();
	virtual ~CIpFilter();

	bool Filtering();//ʹIP������������
	bool UnFiltering();//ʹIP��������������
	bool AddRule(RuleInfo rule);//��IP���������ӹ��˹���
	bool DeleteRule(RuleInfo rule);//��IP������ɾ������
	bool ClearAllRules();//���IP�������е����й��˹���

	in_addr GetLocalIP();//��Windows Socket����ȡ�ñ���IP��ַ
	PF_INTERFACE_STATS * GetState();//ȡ��IP�����������״̬

	int ruleCount;//IP�������еĹ��������
	DWORD localInAddr;//��¼����IP��ַ
protected:
//	void MakeFilter(RuleInfo rule,PF_FILTER_DESCRIPTOR* pf);

	INTERFACE_HANDLE drop;//��IP�������������Interface
	bool bCreateInterfaceSuccess;//��ʾ��IP�������������Interface�Ƿ񴴽��ɹ�
};

#endif // !defined(AFX_IPFILTER_H__E3DA54F2_89B6_440E_855C_2C562BFBD1BA__INCLUDED_)
