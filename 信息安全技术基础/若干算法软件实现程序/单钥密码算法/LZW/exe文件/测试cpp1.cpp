//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>  //zqw
#pragma hdrstop
#include "Unit1.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
#define MaxWndSize 2048   // ���ڵ����ߴ�
#define MaxMatch 2048     // ���ƥ��ĳ���
#define BlockLen 65536    // ÿ�ζ����ڴ���ļ���Ĵ�С

int CurByte;              // ѹ���ļ���ǰλ�õ��ֽ�ƫ��
int CurBit;               // ѹ���ļ���ǰλ�õ�λƫ��

//---------------------------------------------------------------------------

// �������㷨ʵ�ֵ�һ����ĺ���


//****************************************************************************//
// ���ܣ��ڻ��������в����ƥ�䴮����KMP�㷨��
// ����˵����
//        window - �������ڵ���ʼָ��
//	  Start - ��ƥ�䴮����ʼλ�ã���lookahead���ڵ���ʼλ�ã�
//	  Offset - ƥ�䴮�ڻ��������ڵ�ƫ�ƣ����ڽ��ս��
//	  Len - ƥ�䴮�ĳ��ȣ����ڽ��ս��
// ����ֵ���ҵ����ȴ���1��ƥ�䴮�򷵻�true�����򷵻�false
//****************************************************************************//
bool FindMatch(BYTE* window, int Start, int* Offset, int* Len)
{
    int Fail[MaxMatch];  // ���ʧ�亯��
    int FailCount;       // ��¼ʧ�亯���Ѿ������˼���
    int P1;              // Ŀ�괮��ɨ��ָ��
    int P2;              // ��ƥ�䴮��ɨ��ָ��
    int MatchLen;        // ƥ�䳤��
    int temp;

    // ��ʼ������
    P1=0;
    P2=0;
    FailCount=0;
    Fail[0]=-1;
    MatchLen=0;
    (*Len)=0;

    // ���ƥ�䴮
    while( P1 < Start && P2 < MaxMatch - 1 )
    {
        // ��Ӧ���ַ�ƥ��
    	if( window[P1] == window[Start+P2] )
    	{
      	    P1++;
	    P2++;
	    MatchLen++;     // ����ƥ�䳤�ȣ�1

            // ��P2����û����ʧ�亯���������ʧ�亯��Fail[P2]
	    if( P2 > FailCount )
	    {
	    	temp = Fail[P2-1];
                // ���Ƽ���Fail[P2]
	    	while( window[Start+P2]!= window[Start+temp+1] && temp>=0)
		    temp = Fail[temp];
		if( window[Start+P2] == window[Start+temp+1])
		    Fail[P2]=temp+1;
		else Fail[P2]=-1;
                // ʧ�亯������ֵ��һ
		FailCount++;
            }
        }
	else
	{
	    if( P2 == 0 ) P1++;
	    else
	    {
                // ������ƥ��ĳ��ȳ�����ʷ��¼�����޸���ʷ��¼
	    	if( MatchLen >(*Len) )
	    	{
                    (*Len) = MatchLen;
		    (*Offset) = P1 - MatchLen;
		}
                // ʧ��󣬼���Ѱ������ƥ��λ��
		P2=Fail[P2-1]+1;
		MatchLen = P2;
            }
        }
    }
    // ������ƥ��ĳ��ȳ�����ʷ��¼�����޸���ʷ��¼
    if( MatchLen > (*Len) )
    {
    	(*Len) = MatchLen;
    	(*Offset) = P1 - MatchLen;
    }

    if( *Len > 1 ) return true;
    else return false;
}


//****************************************************************************//
// ���ܣ�ѹ���������е�����
// ����˵����
//        src - Դ�����ڴ滺��������ѹ����������ָ��
//	  srclen - Դ���ݿ飨��ѹ�����������ֽڳ���
//	  dest - Ŀ�������ڴ滺���������ѹ����ı��룩ָ��
// ����ֵ��ѹ�������ݵĳ��ȣ�������������ѹ�����ݵĳ��ȣ��㡪�������޷�ѹ��
//         ������������
//****************************************************************************//
int Compress(BYTE* src, int srclen, BYTE* dest)
{
    BYTE* window;    // �������ڵ���ʼλ��
    int CurWndSize;  // ��ǰ���ڴ�С
    int Lookahead;   // ��ǰ�����ڵ���ʼλ��
    int post;        // ��ѹ�����ݵļ���ֵ
    int off;         // ƥ�䴮�ڻ��������ڵ�ƫ��
    int len;         // ƥ�䴮�ĳ���

    // �ж��쳣
    if (srclen > BlockLen)  return -1;

    // ��ʼ������
    CurByte = 0;
    CurBit = 0;
    window = src;
    CurWndSize = 0;  //zqw
    Lookahead = 0 ;

    for (post =0; post < srclen; post++ )
    {
        // ���޷�ѹ��
        if (CurByte >= srclen)  return 0;

        // ���ҵ����ȴ���һ��ƥ�䴮
	if (FindMatch(window, Lookahead, &off, &len))
	{
	    // ��������ʽ��flag��len��offset��
            // �����flag����1������Ϊ1bit��
            CodeOutput(dest, 1, 1, FALSE);
            // ���len�� �ñ���
	    CodeOutput(dest, len, 0, TRUE);
            // ���ƥ��λ���ڻ��������е�ƫ�ƣ�λ���ɵ�ǰ���ڴ�С����
            CodeOutput(dest, off, UpperLog2(CurWndSize), FALSE);

	    // ���ڻ���
            if( CurWndSize == MaxWndSize ) window = window + len;
            else if( CurWndSize + len > MaxWndSize)
            {
                window = window + ( CurWndSize + len - MaxWndSize );
                CurWndSize = MaxWndSize;
                Lookahead = MaxWndSize;
            }
            else
            {
                CurWndSize = CurWndSize + len;  //zqw
	        Lookahead = Lookahead + len ;
            }

            post = post + len - 1;
        }
	else
	{
	    // ���������ƥ���ַ�����ʽ��flag��char��
	    CodeOutput(dest, 0, 1, FALSE);
	    CodeOutput(dest, (DWORD)(src[post]), 8, FALSE);

	    // ���ڻ���
            if( CurWndSize == MaxWndSize ) window = window + 1;
            else
            {
                CurWndSize++;  //zqw
                Lookahead++;
            }
        }
    }

    // ����ѹ�������ݵĳ���
    int destlen = CurByte + ((CurBit) ? 1 : 0);

    if (destlen >= srclen)  return 0;
    return destlen;
}


//****************************************************************************//
// ���ܣ���ѹ���������е�����
// ����˵����
//        source - Դ�����ڴ滺���������ս�ѹ��������ݣ�ָ��
//	  srclen - Դ���ݿ��ֽڳ���
//	  dest - ѹ�������ڴ滺����ָ��
// ����ֵ����ѹ�ɹ�����true�����ɹ�����false
//****************************************************************************//
BOOL Extract(BYTE* source, int srclen, BYTE* dest)
{
    BYTE* window;    // ��������ָ��
    int CurWndSize;  // ��ǰ���ڴ�С
    int i;           // Դ��������λ�ü���

    // ��ʼ������
    CurByte = 0;
    CurBit = 0;
    window = source;
    CurWndSize = 0;

    // �ж��쳣
    if (srclen > BlockLen)   return FALSE;

    for (i = 0; i < srclen; i++)
    {
        // ����־λ
    	BYTE b = GetBit(dest[CurByte], CurBit);
    	MovePos(&CurByte, &CurBit, 1);
        // �������ַ�
    	if (b == 0)
    	{
            // ���Ƶ����ַ���8 bits)
      	    CopyBits(source + i, 0, dest + CurByte, CurBit, 8);
	    MovePos(&CurByte, &CurBit, 8);
	    CurWndSize++;
        }
        // ����ƥ���ʽ��flag��len��offset��
	else
	{
            // ������ƥ�䴮�ĳ���len��len�ѽ��� �ñ��룬��Ҫ����
	    int q = -1;
            int len, off;
	    DWORD dw = 0;
	    BYTE* pb;
	    while (b != 0)
	    {
	    	q++;
	    	b = GetBit(dest[CurByte], CurBit);
	    	MovePos(&CurByte, &CurBit, 1);
	    }
            if (q > 0)
	    {
	    	pb = (BYTE*)&dw;
	    	CopyBits(pb + (32 - q) / 8, (32 - q) % 8, dest + CurByte, CurBit, q);
	    	MovePos(&CurByte, &CurBit, q);
	    	InvertDWord(&dw);
	    	len = 1;
	    	len <<= q;
	    	len += dw;
	    	len += 1;
	    }
	    else
	    	len = 2;

            // ������ƫ����off
	    dw = 0;
	    pb = (BYTE*)&dw;
	    int bits = UpperLog2(CurWndSize);
	    CopyBits(pb + (32 - bits) / 8, (32 - bits) % 8, dest + CurByte, CurBit, bits);
	    MovePos(&CurByte, &CurBit, bits);
	    InvertDWord(&dw);
	    off = (int)dw;

	    // ���ҵ���ƥ�䴮�����������
	    for (int j = 0; j < len; j++)
	    {
	    	source[i + j] = window[off + j];
	    }
	    CurWndSize += len;
	    i += len - 1;
        }

        // ���ڻ���
	if (CurWndSize > MaxWndSize)
	{
	    window += CurWndSize - MaxWndSize;
	    CurWndSize = MaxWndSize;
        }
    }
    return TRUE;
}


//****************************************************************************//
// �¼���������Compress��ť�����ʱ������
// ���ܣ�ѹ��ָ�����ļ�
//****************************************************************************//
void __fastcall TForm1::btnCompressClick(TObject *Sender)
{
    BYTE SourceBuf[BlockLen];     // Դ�����ڴ滺��������ѹ����������
    BYTE DestBuf[BlockLen + 16];  // Ŀ�������ڴ滺���������ѹ����ı��룩
    FILE* in;                     // �����ļ�ָ��
    FILE* out;                    // ����ļ�ָ��
    long soulen;                  // �����ļ����ܳ���
    int destlen;                 // ѹ���ļ����ܳ���
    WORD flag1;   // �����ڴ滺���������ݿ�ĳ��ȣ�0��ʾ����BlockLen
    WORD flag2;                   // ����ڴ滺���������ݿ�ĳ���
    int remain;                   // Դ�ļ�ʣ�೤��
    int act;                      // ��ǰ�����ʵ�ʳ���

    // �����ļ�������
    char* SouFileName = new char[ Edit1->Text.Length() + 1 ];
    // ����ļ�������
    char* DestFileName = new char[ Edit2->Text.Length() + 1 ];
    strcpy( SouFileName, Edit1->Text.c_str() );
    strcpy( DestFileName, Edit2->Text.c_str() );

    // �Զ�����ֻ����ʽ��Դ�ļ�
    in = fopen( SouFileName , "rb" );
    if (in == NULL)
    {
        Label1->Caption = "Դ�ļ��޷���! ��������Ƿ���ȷ!";
	return;
    }
    // �Զ�����д��ʽ��Ŀ���ļ�
    out = fopen(DestFileName, "wb");
    if (out == NULL)
    {
        Label1->Caption = "Ŀ���ļ��޷���! ��������Ƿ���ȷ!";
	fclose(in);
	return;
    }

    // ��ָ���Ƶ��ļ���β
    fseek(in, 0, SEEK_END);
    // ��ǰָ��λ�ã��������ļ�����
    soulen = ftell(in);
    // ��ָ���Ƶ��ļ���ͷ
    fseek(in, 0, SEEK_SET);

    Label1->Caption = "ѹ�������У� ���Ժ�";
    Label2->Visible = false;
    Label3->Visible = false;
    Label4->Visible = false;
    Label5->Visible = false;
    remain = soulen;
    while ( remain > 0 )
    {
        // ��ʵ�ʶ���ĳ���
	act = min(BlockLen, remain);
        // һ��Block���ڴ滺����
	fread(SourceBuf, act, 1, in);
	remain -= act;
        // flag1��¼���ζ�������ݿ�ĳ��ȣ�0��ʾ����BlockLen
	if (act == BlockLen)
	    flag1 = 0;
	else
	    flag1 = act;
        // ��ÿ�����ݿ�Ŀ�ͷд�뱾�ζ���ĳ���
        fwrite(&flag1, sizeof(WORD), 1, out);

        // ѹ������ı�
	destlen = Compress((BYTE*)SourceBuf, act, (BYTE*)DestBuf);
        // ������ѹ��
	if (destlen == 0)
        {
	    flag2 = flag1;
	    fwrite(&flag2, sizeof(WORD), 1, out);
            // ��Դ����ֱ�������ѹ���ļ�
	    fwrite(SourceBuf, act, 1, out);
        }
	else
	{
	    flag2 = (WORD)destlen;
            // д��ѹ�������ݿ�ĳ���
	    fwrite(&flag2, sizeof(WORD), 1, out);
            // ��ѹ���������д��Ŀ���ļ�
	    fwrite(DestBuf, destlen, 1, out);
        }
    }

    // ��ʾ��ʾ��Ϣ
    Label2->Visible = true;
    Label3->Visible = true;
    Label4->Visible = true;
    Label5->Visible = true;
    Label1->Caption = "�ļ�ѹ���ɹ���";
    Label2->Caption = "ѹ��ǰ�ļ���С(KB)��";
    Label3->Caption = "ѹ�����ļ���С(KB)��";
    Label4->Caption = IntToStr( soulen/1024 );
    Label5->Caption = IntToStr( ftell(out)/1024 );
    // �ر��ļ�
    fclose(in);
    fclose(out);
}


//****************************************************************************//
// �¼���������Extract��ť�����ʱ������
// ���ܣ���ѹ��ָ�����ļ�
//****************************************************************************//
void __fastcall TForm1::btnExtractClick(TObject *Sender)
{
    BYTE SourceBuf[BlockLen];      // Դ�����ڴ滺����
    BYTE DestBuf[BlockLen + 16];   // ѹ�������ڴ滺����
    FILE* in;                      // �����ļ�ָ��
    FILE* out;                     // ����ļ�ָ��
    long soulen;                   // �����ļ����ܳ���
    WORD flag1;   // �����ݿ��δѹ��ǰ�ĳ��ȣ�0��ʾ����BlockLen
    WORD flag2;                    // �����ݿ�ѹ����ĳ���
    int remain;                    // Դ�ļ�ʣ�೤��
    int act;                       // ��ǰ�����ʵ�ʳ���

    // �����ļ�������
    char* SouFileName = new char[ Edit1->Text.Length() + 1 ];
    // ����ļ�������
    char* DestFileName = new char[ Edit2->Text.Length() + 1 ];
    strcpy( SouFileName, Edit1->Text.c_str() );
    strcpy( DestFileName, Edit2->Text.c_str() );

    // �Զ�����ֻ����ʽ��Դ�ļ�
    in = fopen(SouFileName , "rb");
    if (in == NULL)
    {
        Label1->Caption = "Դ�ļ��޷���!��������Ƿ���ȷ!";
    	return;
    }
    // �Զ�����д��ʽ��Ŀ���ļ�
    out = fopen(DestFileName, "wb");
    if (out == NULL)
    {
        Label1->Caption = "Ŀ���ļ��޷���!��������Ƿ���ȷ!";
	fclose(in);
	return;
    }

    // ��ָ���Ƶ��ļ���β
    fseek(in, 0, SEEK_END);
    // ��ǰָ��λ�ã��������ļ�����
    soulen = ftell(in);
    // ��ָ���ƻ��ļ���ͷ
    fseek(in, 0, SEEK_SET);

    remain = soulen;
    Label1->Caption = "��ѹ�����У� ���Ժ�";
    Label2->Visible = false;
    Label3->Visible = false;
    Label4->Visible = false;
    Label5->Visible = false;
    while (remain > 0)
    {
        // ���������ݿ��δѹ��ǰ�ĳ���
    	fread(&flag1, sizeof(WORD), 1, in);
        // �����ݿ�ѹ����ĳ���
    	fread(&flag2, sizeof(WORD), 1, in);
    	remain -= 2 * sizeof(WORD);

        // ��������ݿ�ѹ��ǰʵ�ʳ���
    	if (flag1 == 0)
     	    act = BlockLen;
	else
	    act = flag1;
	remain-= flag2 ? (flag2) : act;

        // ����ѹ����ֱ�Ӷ���
	if (flag2 == flag1)
	{
	    fread(SourceBuf, act, 1, in);
        }
	else
	{
	    fread(DestBuf, flag2, 1, in);
            // ��ѹ������ı�
	    if (!Extract((BYTE*)SourceBuf, act, (BYTE*)DestBuf))
            {
                Label1->Caption = "��ѹ���ɹ���";
	        fclose(in);
	        fclose(out);
	        return;
	    }
        }
        // �����������ѽ�ѹ������������ļ�
        fwrite((BYTE*)SourceBuf, act, 1, out);
    }

    // ��ʾ��ʾ��Ϣ
    Label2->Visible = true;
    Label3->Visible = true;
    Label4->Visible = true;
    Label5->Visible = true;
    Label1->Caption = "�ļ���ѹ�ɹ���";
    Label2->Caption = "��ѹǰ�ļ���С(KB)��";
    Label3->Caption = "��ѹ���ļ���С(KB)��";
    Label4->Caption = IntToStr( soulen/1024 );
    Label5->Caption = IntToStr( ftell(out)/1024 );
    // �ر��ļ�
    fclose(in);
    fclose(out);
}


//---------------------------------------------------------------------------

// ������Ϊ��ʵ�����ѹ�������һ�������λ��������


//****************************************************************************//
// ���ܣ���ָ������ʽ���ѹ�����뵽���������
// ����˵����
//        dest - ���������ָ��
//	  code - Ҫ�������
//	  bits - Ҫ�����λ��
//	  isGamma - �Ƿ����Ϊ�ñ���
//****************************************************************************//
void CodeOutput(BYTE* dest, DWORD code, int bits, BOOL isGamma)
{
    // �� isGamma �� true����� code ���� �ñ��룬�����
    if ( isGamma )
    {
    	BYTE* pb;    // �ֽ�������
    	DWORD out;   // ˫��������

    	// �������λ��
    	int GammaCode = (int)code - 1;
    	int q = LowerLog2(GammaCode);

        // ���q��1
    	if (q > 0)
    	{
            out = 0xffff;
	    pb = (BYTE*)&out;
	    CopyBits(dest + CurByte, CurBit, pb, 0, q);
	    MovePos(&CurByte, &CurBit, q);
        }

	// ���һ��0
	out = 0;
	pb = (BYTE*)&out;
	CopyBits(dest + CurByte, CurBit, pb + 3, 7, 1);
	MovePos(&CurByte, &CurBit, 1);

        // �������, qλ
	if (q > 0)
	{
            // ����out = Code - 2^q
	    int sh = 1;
	    sh <<= q;
	    out = GammaCode - sh;
	    pb = (BYTE*)&out;
	    InvertDWord(&out);
	    CopyBits(dest + CurByte, CurBit,
	    		pb + (32 - q) / 8, (32 - q) % 8, q);
	    MovePos(&CurByte, &CurBit, q);
        }
    }
    // �� isGamma �� false,������� �ñ���
    else
    {
    	DWORD dw = (DWORD)code;
    	BYTE* pb = (BYTE*)&dw;
    	InvertDWord(&dw);
    	CopyBits(dest + CurByte, CurBit,
    		pb + (32 - bits) / 8, (32 - bits) % 8, bits);
	MovePos(&CurByte, &CurBit, bits);
    }
}


//****************************************************************************//
// ���ܣ���С��log2(n)����С����
//****************************************************************************//
int UpperLog2(int n)
{
    int i = 0;
    if (n > 0)
    {
    	int m = 1;
    	while(1)
    	{
    	    if (m >= n)
	    return i;
	    m <<= 1;
	    i++;
        }
    }
    else
    return -1;
}


//****************************************************************************//
// ���ܣ������log2(n)���������
//****************************************************************************//
int LowerLog2(int n)
{
    int i = 0;
    if (n > 0)
    {
    	int m = 1;
    	while(1)
    	{
            if (m == n)
	    return i;
	    if (m > n)
	    return i - 1;
	    m <<= 1;
	    i++;
        }
    }
    else
    return -1;
}


//****************************************************************************//
// ���ܣ�������λ����numλ
// ����˵����
//       piByte - �ֽ�ƫ��
//       piBit - �ֽ���λƫ��
//       num - ����λ��
//****************************************************************************//
void MovePos(int* piByte, int* piBit, int num)
{
	num += (*piBit);
	(*piByte) += num / 8;
	(*piBit) = num % 8;
}


//****************************************************************************//
// ���ܣ����ֽ�byte�ĵ�posλ��ֵ���Ӹ�λ����ߣ���ʼ����
// ����ֵ��0��1������Ϊ�ֽ�
//****************************************************************************//
BYTE GetBit(BYTE byte, int pos)
{
    int j = 1;
    j <<= 7 - pos;
    if (byte & j)
    	return 1;
    else
    	return 0;
}


//****************************************************************************//
// ���ܣ�����˫�ֵĴ��˳��ʹ��Ӹ�λ�ֽڵ���λ�ֽ�����
// ����˵����pDW ��ָ��������DWORD
//****************************************************************************//
void InvertDWord(DWORD* pDW)
{
	union UDWORD{
                    DWORD dw;
                    BYTE b[4];
                    };
	UDWORD* pUDW = (UDWORD*)pDW;
	BYTE b;
	b = pUDW->b[0];
        pUDW->b[0] = pUDW->b[3];
        pUDW->b[3] = b;
	b = pUDW->b[1];
        pUDW->b[1] = pUDW->b[2];
        pUDW->b[2] = b;
}


//****************************************************************************//
// ���ܣ���һ���ֽڷ�Χ�ڸ���λ��
// ǰ��������Ҫ���Ƶ�λ����һ���ֽڷ�Χ��
// ����˵����
//        memDest - Ŀ��������
//	  nDestPos - Ŀ����������һ���ֽ��е���ʼλ
//	  memSrc - Դ������
//	  nSrcPos - Դ��������һ���ֽڵ�����ʼλ
//	  nBits - Ҫ���Ƶ�λ��
//****************************************************************************//
void CopyBitsInAByte(BYTE* memDest, int nDestPos, BYTE* memSrc,
                     int nSrcPos, int nBits)
{
    BYTE b1, b2;
    b1 = *memSrc;
    // �����ø��Ƶ�λ��0
    b1 <<= nSrcPos; b1 >>= 8 - nBits;
    // ��Դ��Ŀ���ֽڶ���
    b1 <<= 8 - nBits - nDestPos;
    // ����ֵΪ1��λ
    *memDest |= b1;
    // �����ø��Ƶ�λ��1
    b2 = 0xff; b2 <<= 8 - nDestPos;
    b1 |= b2;
    b2 = 0xff; b2 >>= nDestPos + nBits;
    b1 |= b2;
    // ����ֵΪ0��λ
    *memDest &= b1;
}


//****************************************************************************//
// ���ܣ������ڴ��е�λ��
// ǰ��������Ҫ���Ƶ������������������غ�
// ����˵����
//        memDest - Ŀ��������
//	  nDestPos - Ŀ����������һ���ֽ��е���ʼλ
//	  memSrc - Դ������
//	  nSrcPos - Դ��������һ���ֽڵ�����ʼλ
//	  nBits - Ҫ���Ƶ�λ��
//        ˵�� - ��ʼλ���ֽڵĸ�λ����λ���������ң�����
//****************************************************************************//
void CopyBits(BYTE* memDest, int nDestPos, BYTE* memSrc,
              int nSrcPos, int nBits)
{
    int iByteDest = 0, iBitDest;
    int iByteSrc = 0, iBitSrc = nSrcPos;
    int nBitsToFill, nBitsCanFill;
    while (nBits > 0)
    {
    	// ����Ҫ��Ŀ������ǰ�ֽ�����λ��
    	nBitsToFill = min(nBits, iByteDest ? 8 : 8 - nDestPos);
    	// Ŀ������ǰ�ֽ�Ҫ������ʼλ
    	iBitDest = iByteDest ? 0 : nDestPos;
    	// �������һ�δ�Դ�������и��Ƶ�λ��
    	nBitsCanFill = min(nBitsToFill, 8 - iBitSrc);
    	// �ֽ��ڸ���
    	CopyBitsInAByte(memDest + iByteDest, iBitDest,
    		memSrc + iByteSrc, iBitSrc, nBitsCanFill);
    	// �����û�и����� nBitsToFill ��
    	if (nBitsToFill > nBitsCanFill)
    	{
    	    iByteSrc++;
            iBitSrc = 0;
            iBitDest += nBitsCanFill;
	    CopyBitsInAByte(memDest + iByteDest, iBitDest, memSrc + iByteSrc,
                       iBitSrc, nBitsToFill - nBitsCanFill);
	    iBitSrc += nBitsToFill - nBitsCanFill;
        }
	else
	{
	    iBitSrc += nBitsCanFill;
	    if (iBitSrc >= 8)
	    {
	    	iByteSrc++;
                iBitSrc = 0;
	    }
        }
        // �Ѿ������nBitsToFillλ
        nBits -= nBitsToFill;
	iByteDest++;
    }
}


//---------------------------------------------------------------------------

//****************************************************************************//
// �¼���������Form Load�¼�������
// ���ܣ�����һЩ����ĳ�ʼ������.
//****************************************************************************//
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
    Label1->Caption = "׼����������ѡ��Ҫѹ�����ѹ���ļ���";
    Label2->Visible = false;
    Label3->Visible = false;
    Label4->Visible = false;
    Label5->Visible = false;
}

//---------------------------------------------------------------------------


