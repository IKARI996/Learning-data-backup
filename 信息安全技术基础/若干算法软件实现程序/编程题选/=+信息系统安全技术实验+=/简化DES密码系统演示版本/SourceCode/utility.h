/**********************************************************************
*Function: ���ú������ɹ��߰�
*Author:   �ⵤ 00234015 3��
*Date:     2003/3/13
*Version:  V1.0
***********************************************************************/
#ifndef __mypackage
#define __mypackage

#include <iostream.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>   // gets(),puts()
#include <stddef.h>
#include <fstream.h>
#include <ctype.h>
#include <time.h>
#include <string.h>


enum  Error_code {success,fail,range_error,underflow,overflow,fatal,
		  not_present,duplicate_eror,entry_inserted,entry_found,
		  internal_error};

bool users_says_yes();   //����ѯ���û�
int openInFile(ifstream&); // ���ڴ������ļ�
int openOutFile(ofstream&); // ���ڴ�����ļ�
 
#endif