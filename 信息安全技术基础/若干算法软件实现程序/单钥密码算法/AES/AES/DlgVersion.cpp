// DlgVersion.cpp : implementation file
//

#include "stdafx.h"
#include "AES.h"
#include "DlgVersion.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVersion dialog


CDlgVersion::CDlgVersion(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVersion::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVersion)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgVersion::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVersion)
	DDX_Control(pDX, IDC_EDIT1, m_text);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVersion, CDialog)
	//{{AFX_MSG_MAP(CDlgVersion)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVersion message handlers
/*
����ʹ��˵����
���ܣ�
(1) ����ѡ�����ġ�ѡ��һ�������ļ���
    Ҳ�����ڡ����ġ��������������ģ�����������ļ������Ա��档
(2) ����128λ��Կ�����ߡ�192λ��Կ�����ߡ�256λ��Կ��ѡ����Կ��
(3) �������ܡ���ʼ���м��ܡ�
(4) ���ܹ��̽��н�����ʾ��
(5) ������ɺ󣬡����ġ����ڽ���ʾ���ܺ�Ľ����
(6) ���ܵĽ������01��ʽ��ʾ�ģ�����������ļ������Ա��档
���ܣ�
(1) ����ѡ�����ġ�ѡ��һ�������ļ���
(2) ����128λ��Կ�����ߡ�192λ��Կ�����ߡ�256λ��Կ��ѡ����Կ��
(3) �������ܡ���ʼ���н��ܡ�
(4) ���ܹ��̽��н�����ʾ��
(5) ������ɺ󣬡����ġ����ڽ���ʾ���ܺ�Ľ����
(6) ���ܵĽ�������ı���ʽ��ʾ�ģ�����������ļ������Ա��档
��Ȩ������
    ������Դ������޸�Ȩ������Ȩ��ָ����ʦ���С�
*/
BOOL CDlgVersion::OnInitDialog() 
{
	char str[10240];
	char* s1="����ʹ��˵����";
	char* s2="���ܣ�";
	char* s3="(1) ����ѡ�����ġ�ѡ��һ�������ļ���";
	char* s4="    Ҳ�����ڡ����ġ��������������ģ�����������ļ������Ա��档";
	char* s5="(2) ����128λ��Կ�����ߡ�192λ��Կ�����ߡ�256λ��Կ��ѡ����Կ��";
	char* s6="(3) �������ܡ���ʼ���м��ܡ�";
	char* s7="(4) ���ܹ��̽��н�����ʾ��";
	char* s8="(5) ������ɺ󣬡����ġ����ڽ���ʾ���ܺ�Ľ����";
	char* s9="(6) ���ܵĽ������01��ʽ��ʾ�ģ�����������ļ������Ա��档";
	char* s10="���ܣ�";
	char* s11="(1) ����ѡ�����ġ�ѡ��һ�������ļ���";
	char* s12="(2) ����128λ��Կ�����ߡ�192λ��Կ�����ߡ�256λ��Կ��ѡ����Կ��";
	char* s13="(3) �������ܡ���ʼ���н��ܡ�";
	char* s14="(4) ���ܹ��̽��н�����ʾ��";
	char* s15="(5) ������ɺ󣬡����ġ����ڽ���ʾ���ܺ�Ľ����";
	char* s16="(6) ���ܵĽ�������ı���ʽ��ʾ�ģ�����������ļ������Ա��档";
	char* s17="��Ȩ������";
    char* s18="    ������Դ������޸�Ȩ������Ȩ��ָ����ʦ���С�";	
	//
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	sprintf(str, "%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n",s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15,s16,s17,s18);
	
	//
	m_text.SetWindowText(str);
	m_text.UpdateWindow();
	//
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
