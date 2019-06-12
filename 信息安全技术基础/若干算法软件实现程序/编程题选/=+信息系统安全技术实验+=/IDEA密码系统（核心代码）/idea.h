#ifndef idea_h
#define idea_h

#include "utility.h"

typedef int INT32;
typedef char INT8;
typedef unsigned char ULONG8;
typedef unsigned short ULONG16;
typedef unsigned long ULONG32;

#define SUCCESS 0 
#define FAIL -1

#define _USEDFINDTABLE_ 1 /*�Ƿ���ò��ʵ��*/

/*����ʱ��Կ�Ļ�λ��*/
//ULONG16 outkey[52] = { 0 };

static ULONG8 wz_spkey[52] = { 
       48,49,50,51,46,47,
	   42,44,43,45,40,41,/*������Կ����,2,3λҪ����:44<->43*/
	   36,38,37,39,34,35,/*������Կ����,2,3λҪ����:38<->37*/
	   30,32,31,33,28,29,/*������Կ����,2,3λҪ����:32<->31*/
	   24,26,25,27,22,23,/*������Կ����,2,3λҪ����:26<->25*/
	   18,20,19,21,16,17,/*������Կ����,2,3λҪ����:20<->19*/
	   12,14,13,15,10,11,/*������Կ����,2,3λҪ����:14<->13*/
	    6, 8, 7, 9, 4, 5,/*������Կ����,2,3λҪ����:8<->7*/
	    0, 1, 2, 3
};

static ULONG8 wz_spmulrevr[18] = {/*��˷����λ*/
        0,3,6,9,12,15,18,21,24,27,30,33,36,39,42,45,48,51
};

static ULONG8 wz_spaddrever[18] ={/*��ӷ����λ*/
        1,2,7,8,13,14,19,20,25,26,31,32,37,38,43,44,49,50
};
//-------------------------------------------------------------------

ULONG16 MUL( ULONG16 a, ULONG16 b);/*�˷�����(a*b)mod(0x10001)*/

INT32 handle_data( ULONG16 *data, /*�����ܵ�64λ�����׵�ַ*/
                   ULONG16 *key /* 6�鱾��ʹ�õ�16λ������Կ�׵�ַ*/);

INT32 idea_dec( ULONG16 *data, /*�����ܵ�64λ�����׵�ַ*/ 
                ULONG16 *outkey/*������Կ���׵�ַ*/);

INT32 idea_enc( ULONG16 *data, /*�����ܵ�64λ�����׵�ַ*/
                ULONG16 *outkey/*������Կ���׵�ַ*/);

//-------------------------------------------------------------------
ULONG16 mulInv( ULONG16 x);/*ȡx��(%0x10001L)�˷���*/

INT32 key_leftmove(ULONG32 *inkey);/*��Կ����λ����*/

INT32 key_decryExp(ULONG16 *outkey);/*������Կ�ı��洦��*/

INT32 idea_makekey( ULONG32 *inkey,/*�û������128λ��Կ�׵�ַ*/
                    ULONG16 *outkey/*���ɵ�52��16λ��Կ���׵�ַ*/);

INT32 idea_MakeEncKey(ULONG16 *key, ULONG16 *outkey);/*������Կ*/

INT32 idea_MakeDecKey(ULONG16 *key, ULONG16 *outkey);/*������Կ*/

//-------------------------------------------------------------------

#endif