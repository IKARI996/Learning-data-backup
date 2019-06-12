// rules.h: interface for the RuleInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RULES_H__E17E8B01_BD09_4B6E_BF0B_41D33F3DCC4A__INCLUDED_)
#define AFX_RULES_H__E17E8B01_BD09_4B6E_BF0B_41D33F3DCC4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Fltdefs.h"

class RuleInfo  
{
public:
	DWORD sourceIp;//���˹����ԴIP��ַ
	DWORD sourceMask;//���˹����Դ��������
	WORD sourcePort;//���˹����Դ�˿�

	DWORD destinationIp;//���˹����Ŀ��IP��ַ
	DWORD destinationMask;//���˹����Ŀ����������
	WORD destinationPort;//���˹����Ŀ��˿�

	DWORD protocol;//���˹���ķ��Э��(��ʹ�õ�����Э��)
	PFFORWARD_ACTION action;//���˹���Ĳ���,�Ƕ�����ת��
	bool bOut;//��ʶ�Ƿ����������ݰ����˹���
	
	RuleInfo operator = (const RuleInfo& src);//���˹���ĸ�ֵ������

	RuleInfo();
	virtual ~RuleInfo();

};

const DWORD ALL_IP = 0;
const DWORD ALL_MASK = 0xFFFFFFFF;

#endif // !defined(AFX_RULES_H__E17E8B01_BD09_4B6E_BF0B_41D33F3DCC4A__INCLUDED_)
