// IpFilter.cpp: implementation of the CIpFilter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FirewallApp.h"
#include "IpFilter.h"
#include <stdlib.h>
#define  WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "fltdefs.h"
#include "util.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIpFilter::CIpFilter()
{
	bCreateInterfaceSuccess = false;
	ruleCount = 0;

	/* ����һ�����ݹ��˹��������ݰ��Ĺ��˽ӿ� */
	DWORD retD = PfCreateInterface( 0, PF_ACTION_FORWARD, PF_ACTION_FORWARD,FALSE, TRUE, &drop );
    ///* ����һ�����ݹ��˹���������ݰ��Ĺ��˽ӿ� */
	//DWORD retD = PfCreateInterface( 0, PF_ACTION_DROP, PF_ACTION_DROP,FALSE, FALSE, &drop );
	if(retD == NO_ERROR){
		bCreateInterfaceSuccess = true;
	}
	
	in_addr ip = GetLocalIP();
	localInAddr = ip.S_un.S_addr;
}

CIpFilter::~CIpFilter()
{
	if(bCreateInterfaceSuccess){
		PfDeleteInterface(drop);
	}
}

/**
 *	ͨ�������˽ӿڰ󶨵�����IP�ķ���ʹ�ù�������������
 *
 **/
bool CIpFilter::Filtering()
{
	DWORD retD = PfBindInterfaceToIPAddress(drop,PF_IPV4,(PBYTE) & localInAddr);
	return (retD == NO_ERROR);
}

/**
 *	ͨ�������˽ӿ�ȡ���뱾��IP�İ󶨵ķ���ʹ�ù��������ٷ�������
 *
 **/
bool CIpFilter::UnFiltering()
{
	DWORD retD = PfUnBindInterface(drop);
	return (retD == NO_ERROR );
}

/**
 *	��IP����������һ������,�ȸ��ݹ��򴴽�һ��Filter������,
 *	Ȼ���Filter�����Ӽ��뵽��IP��������ص�Interface����
 *
 **/
bool CIpFilter::AddRule(RuleInfo rule)
{
	PF_FILTER_DESCRIPTOR pf ;

	/* ����Filter������ */
	pf.dwFilterFlags     = FD_FLAGS_NOSYN;
	int a = FD_FLAGS_NOSYN;
    pf.dwRule            = 0;
    pf.pfatType          = PF_IPV4;
    pf.fLateBound        = 0;
    pf.dwProtocol    = rule.protocol;
    pf.wSrcPort      = rule.sourcePort;
    pf.wDstPort      = rule.destinationPort;
	pf.SrcAddr		 = (PBYTE) & rule.sourceIp;
	pf.SrcMask       = (PBYTE) & rule.sourceMask;
	pf.DstAddr       = (PBYTE) & rule.destinationIp;
	pf.DstMask       = (PBYTE) & rule.destinationMask;
    pf.wSrcPortHighRange = pf.wSrcPort;
    pf.wDstPortHighRange = pf.wDstPort;

	DWORD ret;
	
	/* ���ݹ���������ݰ��ķ�������Filter�����Ӽ��뵽Inteface�� */
	if(rule.bOut) ret = PfAddFiltersToInterface(drop,0,NULL,1,&pf,NULL);
	else ret = PfAddFiltersToInterface(drop,1,&pf,0,NULL,NULL);
	if(ret == NO_ERROR) ruleCount ++;
	return ret == NO_ERROR;
}


/**
 *	ɾ����ָ��������ص�Interface �е�Filter������
 *
 **/
bool CIpFilter::DeleteRule(RuleInfo rule)
{	
	PF_FILTER_DESCRIPTOR pf ;

	/* ���ݹ���������ù�����Ӧ��Filter������*/
	pf.dwFilterFlags     = FD_FLAGS_NOSYN;
	int a = FD_FLAGS_NOSYN;
    pf.dwRule            = 0;
    pf.pfatType          = PF_IPV4;
    pf.fLateBound        = 0;
    pf.dwProtocol    = rule.protocol;
    pf.wSrcPort      = rule.sourcePort;
    pf.wDstPort      = rule.destinationPort;
	pf.SrcAddr		 = (PBYTE) & rule.sourceIp;
	pf.SrcMask       = (PBYTE) & rule.sourceMask;
	pf.DstAddr       = (PBYTE) & rule.destinationIp;
	pf.DstMask       = (PBYTE) & rule.destinationMask;
    pf.wSrcPortHighRange = pf.wSrcPort;
    pf.wDstPortHighRange = pf.wDstPort;


	DWORD ret;
	/* ���ݹ���������ݰ��ķ�����ɾ��Interface��������ص�Filter������ */
	if(rule.bOut) ret = PfRemoveFiltersFromInterface(drop,0,NULL,1,&pf);
	else ret = PfRemoveFiltersFromInterface(drop,1,&pf,0,NULL);
	if(ret == NO_ERROR) ruleCount --;
	return ret == NO_ERROR;

}


/**
 *	ͨ���ͷ����������ص�Interface,
 *	����������һ���µ�Interface,
 *	������Interface��������������,
 *	�Ӷ�ʵ����������й��˹���Ĺ���
 *	
 **/
bool CIpFilter::ClearAllRules()
{
	bool result = false;
	DWORD retDD = PfDeleteInterface(drop);
	DWORD retDC = PfCreateInterface( 0, PF_ACTION_DROP, PF_ACTION_DROP,FALSE, TRUE, &drop );

	if(UnFiltering()
		&& retDD == NO_ERROR
		&& retDC == NO_ERROR){
		result = true;
	}
	return result;
}


/**
 *	ͨ��Windows Socket��ȡ�ñ���IP
 *
 **/
in_addr CIpFilter::GetLocalIP()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	hostent* localHost;

	wVersionRequested = MAKEWORD( 2, 2 );
	WSAStartup( wVersionRequested, &wsaData );	
	localHost = gethostbyname("");	
	WSACleanup();
	
	in_addr* localIP = (struct in_addr *)localHost->h_addr_list[0];
	return *localIP;
}


/**
 *	����API ȡ�����������ص�Interface��ص�״̬����
 *
 **/
PF_INTERFACE_STATS * CIpFilter::GetState()
{
	PF_INTERFACE_STATS * ret;
	DWORD size = 0, retFlag = 0;
	int x = sizeof(PF_INTERFACE_STATS);
	ret = (PF_INTERFACE_STATS *)new char[sizeof(PF_INTERFACE_STATS)];
	retFlag = PfGetInterfaceStatistics(drop,ret,&size,FALSE);
	if(retFlag != NO_ERROR)
	{
		/*�ظ�һ���ĵ��ô���,���ṩ�ɹ����õĸ���*/
		for(int i = 0; i < 10; i ++){
			delete ret;
			ret = (PF_INTERFACE_STATS *)new char[size];
			retFlag = PfGetInterfaceStatistics(drop,ret,&size,FALSE);
			if(retFlag == NO_ERROR) break;
		}
		if(retFlag != NO_ERROR) return NULL;
	}
	return ret;
}

