//---------------------------------------------------------------------------


#pragma hdrstop

#include <stdlib.h>
#include <memory.h>
#include <vcl.h>
#include <stdio.h>
#include "UnitKeys.h"

static char srcData[9];

//---------------------------------------------------------------------------

//�������һ����λ������Կ
unsigned int GetRandKey()
{
  return random(95)+32;
}
//---------------------------------------------------------------------------

//������64�ֽ�������ʽ������Կ
void CheckSumBits(char* S)
{
  unsigned int i,j,sum;

  for (i=0;i<8;i++)
  {
    sum = 0x1;
    for (j=0;j<7;j++)
      sum ^= S[i*8+j];
    S[i*8+7]=sum;
  }
}
//---------------------------------------------------------------------------

//���ַ���������Կת���ֽڵ����飬һ��char��ʾһ��������λ
void BytesToBits(const char* S, char *bits, int len)
{
  int i;

  for(int i=0; i<len; ++i)
    bits[i] = (S[i>>3]>>(i&7)) & 1;
}
//---------------------------------------------------------------------------

//���ֽڵ�����ת���ַ���������Կ��һ��char��ʾһ��������λ
void BitsToBytes(char* S, const char *bits, int len)
{
  int i;

  memset(S, 0, len>>3);
  for(i=0; i<len; i++)
    S[i>>3] |= bits[i]<<(i&7);
}
//---------------------------------------------------------------------------

//Ӧ��һ���û�����In�����е�����ת����ŵ�Out������
void Transform(const char *Table, char *In, char *Out, int len)
{
  int i;
  char Temp[256];

  for (i=0;i<len;i++)
    Temp[i]=In[Table[i]-1];
  for (i=0;i<len;i++)
    Out[i]=Temp[i];
}
//---------------------------------------------------------------------------

//ѭ������Loopλ
void RotateL(char *In, char *Out, int len, int loop)
{
  char TMP[256];

  memcpy(TMP+len-loop, In, loop);
  memcpy(TMP, In+loop, len-loop);
  memcpy(Out, TMP, len);
}
//---------------------------------------------------------------------------

//����16������Կ
void MakeSubKey(char* In)
{
  int i;
  char SourceKey[64];

  //ת����ԭʼ��64�ֽ�����
  BytesToBits(In, SourceKey, 64);
//  memcpy(SourceKey, In, 64);
    
  //ȡ��C0��D0����
  Transform(PC1_Table, SourceKey, CD[0], 56);

  //��������Կ
  for (i=0;i<16;i++)
  {
    //����
    RotateL(CD[i],CD[i+1],28,LOOP_Table[i]);
    RotateL(CD[i]+28,CD[i+1]+28,28,LOOP_Table[i]);
    //�û�2����SubKeys[i]
    Transform(PC2_Table, CD[i+1], SubKeys[i], 48);
    SubKeys[i][48] = 0;
  }
}
//---------------------------------------------------------------------------

//���
void Xor(char *InA, const char *InB, int len)
{
  for(int i=0; i<len; ++i)
    InA[i] = (InA[i] ^ InB[i]) & 0x01;
}
//---------------------------------------------------------------------------

void F_func(char *In, char *Out, const char *Ki)
{
  static char MR[48];

  Transform(E_Table, In, MR, 48);
  Xor(MR, Ki, 48);
  S_func(Out, MR);
  Transform(P_Table, Out, Out, 32);
}
//---------------------------------------------------------------------------

void S_func(char *Out, const char *In)
{
  for(char i=0,j,k; i<8; ++i,In+=6,Out+=4)
  {
    j = (In[0]<<1) + In[5];
    k = (In[1]<<3) + (In[2]<<2) + (In[3]<<1) + In[4];
    BytesToBits(&S_Box[i][j][k], Out, 4);
  }
}
//---------------------------------------------------------------------------

//����IP����Ӧ�������IP^-1
void GenIPTable()
{
  int i, j;

  memset(IP_Table, 0, 64);
  memset(IPR_Table, 0, 64);

  for (i=0;i<64;i++)
  {
    j = random(64);
    while (IPR_Table[j]!=0)
      j = random(64);
    IP_Table[i] = j+1;
    IPR_Table[j] = i+1;
  }
}
//---------------------------------------------------------------------------

//DES���̣�����64λ���ģ����ܻ���ܱ�־�����64λ����
void DES(const char *Src, char *Dest, bool flag)
{
  char DestBin[64];
  int i, Loop;

  Loop = ((DesLoop>16) || (DesLoop<1)) ? 16 : DesLoop;


  //�õ�LR[0]
  BytesToBits(Src, LR[0],64);
  //������ʼ�û�
  Transform(IP_Table, LR[0], LR[0], 64);

  //����16�ּ���
  for (i=0;i<Loop;i++)
  {
    memcpy(LR[i+1],LR[i]+32,32);
    if (flag)
      F_func(LR[i]+32, LR[i+1]+32, SubKeys[i]);
    else
      F_func(LR[i]+32, LR[i+1]+32, SubKeys[Loop-1-i]);

    Xor(LR[i+1]+32, LR[i], 32);
  }

  //��R16��L16����64λ����
  RotateL(LR[Loop],LR[Loop],64,32);
  //���������û�
  Transform(IPR_Table, LR[Loop], DestBin, 64);
  //���
  BitsToBytes(Dest, DestBin, 64);
}
//---------------------------------------------------------------------------

//���ܹ���
void Encrypt(const char *Src, char *Dest)
{
  DES(Src, Dest, true);
}
//---------------------------------------------------------------------------

//���ܹ���
void DeEncrypt(const char *Src, char *Dest)
{
  DES(Src, Dest, false);
}
//---------------------------------------------------------------------------

bool SetIPTable(const char *In)
{
  int i, j;

  memcpy(IP_Table, In, 64);
  memset(IPR_Table, 0, 64);

  for (i=0;i<64;i++)
  {
    if (IPR_Table[IP_Table[i]-1]!=0)
      return false;
    IPR_Table[IP_Table[i]-1] = i+1;
  }
  return true;
}
//---------------------------------------------------------------------------

void MakeSubKey2(char* In)
{
  int i;
  char SourceKey[64];

  //ת����ԭʼ��64�ֽ�����
  BytesToBits(In, SourceKey, 64);

  for (i=0;i<16;i++)
    Transform(KeyTable[i], SourceKey, SubKeys[i],48);
}

#pragma package(smart_init)
