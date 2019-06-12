#include "idea.h"
/************************����*******************************/
INT32 idea_dec( ULONG16 *data, /*�����ܵ�64λ�����׵�ַ */ 
                ULONG16 *outkey/*������Կ���׵�ַ*/)
{
   ULONG32 i;
   ULONG16 tmp;
   if( NULL == data || NULL == outkey){
      return FAIL;
   }

   for( i = 0 ; i < 48 ; i += 6)/*8�ֵ���*/
   {
	   handle_data( data , &outkey[i]);
       /*�����м�����*/
       tmp = data[1];
       data[1] = data[2];
       data[2] = tmp;
   }

  data[0] = MUL(data[0],outkey[48]);
  data[1] += outkey[49];
  data[2] += outkey[50];
  data[3] = MUL(data[3],outkey[51]); 

  return SUCCESS;
}

//************************����*******************************
INT32 idea_enc( ULONG16 *data, /*�����ܵ�64λ�����׵�ַ*/
                ULONG16 *outkey/*������Կ���׵�ַ*/)
{
   ULONG32 i ;
   ULONG16 tmp;
  
   if( NULL == data || NULL == outkey){
      return FAIL;
   }
   
   for( i = 0 ; i < 48 ; i += 6)/*8�ֵ���*/
   {
      handle_data( data, &outkey[i]);
      /*�����м�����*/
      tmp = data[1];
      data[1] = data[2];
      data[2] = tmp;
   }

   /*������任*/
   data[0] = MUL(data[0],outkey[48]);
   data[1] += outkey[49];
   data[2] += outkey[50];
   data[3] = MUL(data[3],outkey[51]); 
  
  return SUCCESS;
}

//************************һ�ε���*******************************

ULONG16 MUL( ULONG16 a, ULONG16 b)
{
   ULONG32 p;
   if( a == 0 && b == 0 )
   {
	   p = 0 ;
   }else if ( a == 0 )
   {
	   p = 65536*(ULONG32)b;
   }else if ( b == 0)
   {
	   p = 65536*(ULONG32)a;
   }else
   {
	   p = (ULONG32)a*(ULONG32)b;
   }

   return (ULONG16 )(p%65537);

}

INT32 handle_data( ULONG16 *data, /*�����ܵ�64λ�����׵�ַ*/
                   ULONG16 *key /* 6�鱾��ʹ�õ�16λ������Կ�׵�ַ*/)
{
   ULONG16 *D1,*D2,*D3,*D4;
   ULONG16 D57;/*�ṩ����5,7���õ��ݴ����ݵ�*/
   ULONG16 D68;/*�ṩ����6,8,9,10���õ��ݴ����ݵ�*/
   
   D1 = &data[0];
   D2 = &data[1];
   D3 = &data[2];
   D4 = &data[3];
   
   /*һ�ε�������*/
   *D1 = MUL(*D1,key[0]);/*��1��*/ 
   *D2 += key[1];/*��2��*/  
   *D3 += key[2];/*��3��*/
   *D4 = MUL(*D4,key[3]);/*��4��*/ 
   D57 = *D1 ^ *D3;/*��5��*/
   D68 = *D2 ^ *D4;/*��6��*/
   D57 = MUL(D57,key[4]);/*��7��*/
   D68 += D57;/*��8��*/
   D68 = MUL(D68,key[5]);/*��9��*/
   *D1 ^= D68;/*��11��*/
   *D3 ^= D68;/*��12��*/
   D68 += D57;/*��10��*/
   *D2 ^= D68;/*��13��*/
   *D4 ^= D68;/*��14��*/
   
   return SUCCESS;
}

//--------------------------------------------------------------------
//***********************��Կ����25λ*******************************
INT32 key_leftmove(ULONG32 *inkey)
{
   ULONG32 itmpfirst = 0,itmp = 0 ;
   ULONG32 i;
   
   inkey[0] = (inkey[0]<<25) | (inkey[0]>>7);
   /*ȡ��25λ,��Ϊǰ���Ѿ����˻���,ԭʼ�ĵ�7λ�Ѿ��Ƶ��˸�λ,����*/
   itmpfirst = inkey[0]&0x1ffffff;
   inkey[0] &= 0xfe000000;/*��25λ��0*/

   for ( i = 1 ; i < 4 ; i++)
   {
    inkey[i] = (inkey[i]<<25) | (inkey[i]>>7);
    itmp = inkey[i] & 0x1ffffff;
    inkey[i-1] |= itmp;
    inkey[i] &= 0xfe000000;/*��25λ��0*/
   }
   
   inkey[i-1] |= itmpfirst;/*�����25λ�Ƶ����25λ*/
   
   return SUCCESS;
}

//****************************������Կ*******************************
INT32 idea_makekey( ULONG32 *inkey,/*�û������128λ��Կ�׵�ַ*/
                    ULONG16 *outkey/*���ɵ�52��16λ��Կ���׵�ַ*/)
{
   ULONG32 i,j,k;
   ULONG16 *Pkey = ( ULONG16*)inkey;
   
   for(i = 0 ; i < 6; i++){
      k = i << 3; 
      for( j = 0 ; j < 8 ; j++)/*����8����Կ*/
	  {
		  outkey[k+j] = Pkey[j] ;
	  }
      
	  key_leftmove(inkey);/*128λ��Կ����25λ*/
   }

   for( i = 0 ; i < 4; i++)
   {
      outkey[48+i] = Pkey[i] ; 
   }
   
   return SUCCESS;
}

//****************************Mod(0x10001)����Ԫ�����*******************************
ULONG16 mulInv( ULONG16 x)
{
  long n1,n2,q,r,b1,b2,t;
  if(x == 0)
	  b2 = 0;
  else {
      n1 = 65537;n2 = x;b1 = 0;b2 = 1;
	  do{
		  r = (n1%n2);
		  q = (n1 - r)/n2;
          if(r == 0){ 	  
			  if(b2 < 0)b2 = b2 + 65537;
			  break;
          } else
		  {
		  n1 = n2;
		  n2 = r;
		   t = b2;
		  b2 = b1 - q*b2;
		  b1 = t;
		  }
	  }while(r != 0);
  }

  return ULONG16(b2);
}

//************************������Կ�ı��洦��*******************************
INT32 key_decryExp(ULONG16 *outkey)
{
   /*�ò��ķ���ʵ�ֻ�λ,��ȻҲ���Բ���һЩ��̼���ֱ��ʵ��*/
#if _USEDFINDTABLE_ /*�ò��*/
   ULONG16 tmpkey[52] = { 0 };
   ULONG32 i;
   
   for( i = 0 ; i < 52 ; i++)
   {
      tmpkey[i] = outkey[ wz_spkey[i] ] ;/*��λ*/
   }

   for( i = 0 ; i < 52 ; i++)
   {
      outkey[i] = tmpkey[i];
   }

   for( i = 0 ; i < 18 ; i++)
   {
      outkey[wz_spaddrever[i]] = 65536 -outkey[wz_spaddrever[i]] ;/*�滻�ɼӷ���*/
   }

   for( i = 0 ; i < 18 ; i++)
   { 
      outkey[wz_spmulrevr[i]] = mulInv(outkey[wz_spmulrevr[i]] );/*�滻�ɳ˷���*/ 
   }
#else 
   ULONG16 K1, K2, K3, K4, i;
   ULONG16 tmpkey[52] = { 0 };
   ULONG16 *pin = outkey ;
   
   ULONG16 *p = tmpkey + 52; /* �Ӻ���ǰ */
   K1 = mulInv(*pin);
   K2 = 65536 - *++pin;
   K3 = 65536 - *++pin;
   K4 = mulInv(*++pin);
   
   pin++;
   *--p = K4;
   *--p = K3;
   *--p = K2;
   *--p = K1;
   
   for(i = 0 ; i < 7; i++)
   {
	  K1 = *pin++;/*���������*/
	  K2 = *pin++;
	  *--p = K2;
	  *--p = K1;
	  
	  K1 = mulInv(*pin);
      K2 = 65536 - *++pin;
      K3 = 65536 - *++pin;
      K4 = mulInv(*++pin);
      
	  pin++;
      *--p = K4;
      *--p = K2; /* ���� */
      *--p = K3;
      *--p = K1;
   }
   
   K1 = *pin++;/*���һ�鲻����*/
   K2 = *pin++;
   *--p = K2;
   *--p = K1;

   K1 = mulInv(*pin);
   K2 = 65536 - *++pin;
   K3 = 65536 - *++pin;
   K4 = mulInv(*++pin);
   *--p = K4;
   *--p = K3;
   *--p = K2;
   *--p = K1;
   
   for(i = 0 ; i < 52 ; i++)
   {
      outkey[i] = tmpkey[i];
   }

#endif
    
   return SUCCESS;
}

//************************������Կ�Ĳ���*******************************
INT32 idea_MakeEncKey(ULONG16 *key, ULONG16 *outkey)
{
   if(NULL == outkey || NULL == key)
   {
      return FAIL;
   }

   idea_makekey( (ULONG32*)key , outkey); 
   
   return SUCCESS;
}

//************************������Կ�Ĳ���*******************************
INT32 idea_MakeDecKey(ULONG16 *key, ULONG16 *outkey)
{
   if ( NULL == outkey || NULL == key)
   {
     return FAIL;
   }

   idea_makekey( (ULONG32*)key , outkey);
   key_decryExp(outkey); 

   return SUCCESS;
}
