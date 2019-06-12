#ifndef decrytion_h
#define decrytion_h

#include "utility.h"
//===========λ�νṹ�壬����BitStream�Ĳ���===========
struct packed_data 
{
	unsigned No_1:1;
	unsigned No_2:1;
	unsigned No_3:1;
	unsigned No_4:1;
	unsigned No_5:1;
	unsigned No_6:1;
	unsigned No_7:1;
	unsigned No_8:1;
};


//===========���¼����Ƿ����BitStream�����ļ������ߺ���===========
//----��Charת����BitStream----
void ToBitStream(char& ini_char,packed_data& ini_char_bitstream);
//----��BitStreamת����Char----
void ToChar(packed_data& ini_char_bitstream,char& ini_char);
//----ʵ��BitStream���࿽��----
void CopyBitStream(packed_data& to,packed_data& from);
//----��ӡ��ʾBitStream----
void PrintBitStream(packed_data& toprintbitstream);

//===========���û�����ԭʼ���룬�õ�K1&K2===========
void GenerateKey(packed_data& K1,packed_data& K2);


//============������DES���ܹ��̸��ຯ��===========
//----IP----
void IP(packed_data& plaintext_bitstream);
//----Reverse IP----
void ReverseIP(packed_data& plaintext_bitstream);
//----E/P----
void EP(packed_data& right_plaintext_bitstream,packed_data& EP_bitstream);
//----E/P XOR K1----
void XOR1(packed_data& EP_bitstream,packed_data& K1_bitstream,packed_data& EP_XOR_K1_bitstream);
//----�����S0----
void S0(packed_data& left_EP_XOR_K1_bitstream,packed_data& S0_twobit_output);
//----�����S1----
void S1(packed_data& right_EP_XOR_K1_bitstream,packed_data& S1_twobit_output);
//----P4----
void P4(packed_data& S0S1_output);
//----p4 XOR ������벿��----
void XOR2(packed_data& S0S1_output,packed_data& left_plaintext_bitstream,packed_data& left_XOR_S0S1_bitstream);
//----SW----
void SW(packed_data& left_XOR_S0S1_bitstream,packed_data& right_plaintext_bitstream,packed_data& second_plaintext_bitstream);


//============������DES���ܹ���===========
//----DES����----
void Decryption(packed_data& ciphertext,packed_data& plaintext,packed_data& K1,packed_data& K2);


#endif