/**********************************************************************
*Function: ��DES�����㷨��ʵ��
*Author:   �ⵤ 00234015 3�ţ��������2000��
*Date:     2003/4/20
*Version:  V1.0
***********************************************************************/
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


//===========���û�������һ�ֽڵ�����===========
void GetPlaintext(packed_data& plaintext);


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


//============������DES���ܽ��ܹ���===========
//----DES����----
void Encryption(packed_data& plaintext,packed_data& ciphertext,packed_data& K1,packed_data& K2);
//----DES����----
void Decryption(packed_data& ciphertext,packed_data& plaintext,packed_data& K1,packed_data& K2);


//============����������============
int main()
{ 
    cout << "��������++Simple DES Presentation Program++��������" << endl
    	 << "|         <===========Welcome===========>         |" << endl
	     << "|Author: Dan,Wu  Sofeware Engineering 00 No.3     |" << endl
         << "|Run: MicroSoft Visual C++ 6.0                    |" << endl
	     << "|Data:2003.4.20,Version 1.0 Realeased             |" << endl
	     << "|_________________________________________________|" << endl;
    
	packed_data plaintext,ciphertext;  //����&����  
    packed_data K1,K2;                 //��ԿK1&K2

//******************************��������******************************
	
	GenerateKey(K1,K2);                
    cout << "��Կ����:" << endl;
	cout << "K1 :";
	PrintBitStream(K1);
	cout << "K2 :";
	PrintBitStream(K2);
    cout << endl << endl;

//******************************��������******************************
	
	cout << "��������++Simple DES Presentation Program++��������" << endl
    	 << "|         <===========Welcome===========>         |" << endl
	     << "|Author: Dan,Wu  Sofeware Engineering 00 No.3     |" << endl
         << "|Run: MicroSoft Visual C++ 6.0                    |" << endl
	     << "|Data:2003.4.20,Version 1.0 Realeased             |" << endl
	     << "|_________________________________________________|" << endl;

	GetPlaintext(plaintext);    

//******************************��    ��******************************
    cout << endl << endl
		 << "��������++Simple DES Presentation Program++��������" << endl
    	 << "|         <===========Welcome===========>         |" << endl
	     << "|Author: Dan,Wu  Sofeware Engineering 00 No.3     |" << endl
         << "|Run: MicroSoft Visual C++ 6.0                    |" << endl
	     << "|Data:2003.4.20,Version 1.0 Realeased             |" << endl
	     << "|_________________________________________________|" << endl;

	cout << "�Ƿ�Ҫ����DES����[y,n]:  " << flush;
	char makesure;
	cin >> makesure;
	if(makesure == 'Y' || makesure == 'y'){
	
	   Encryption(plaintext,ciphertext,K1,K2);

//******************************��    ��******************************
       cout << endl << endl
		    << "��������++Simple DES Presentation Program++��������" << endl
      	    << "|         <===========Welcome===========>         |" << endl
	        << "|Author: Dan,Wu  Sofeware Engineering 00 No.3     |" << endl
            << "|Run: MicroSoft Visual C++ 6.0                    |" << endl
	        << "|Data:2003.4.20,Version 1.0 Realeased             |" << endl
	        << "|_________________________________________________|" << endl;
	   cout << "�Ƿ�Ҫ���н���[y,n]:  " << flush;
	   char make_sure;
	   cin >> make_sure;
	   if(make_sure == 'Y' || make_sure == 'y'){
          Decryption(ciphertext,plaintext,K1,K2);
          cout << "Warning: DES����&������ɣ������˳�!!!!!!" << endl;
	   }else cout << "Warning: DES������ɣ������˳�!!!!!!" << endl;
	}else cout << "Warning: DES����δ��ɣ������˳�!!!!!!" << endl;
    
	return 0;
}
void ToBitStream(char& ini_char,packed_data& ini_char_bitstream)
{
//**********���½��ַ�ת����λ��bit stream**********
    ini_char_bitstream.No_1 = (ini_char&0200) >> 7;
	ini_char_bitstream.No_2 = (ini_char&0100) >> 6;
	ini_char_bitstream.No_3 = (ini_char&040) >> 5;
	ini_char_bitstream.No_4 = (ini_char&020) >> 4;
	ini_char_bitstream.No_5 = (ini_char&010) >> 3;
	ini_char_bitstream.No_6 = (ini_char&04) >> 2;
	ini_char_bitstream.No_7 = (ini_char&02) >> 1;
	ini_char_bitstream.No_8 = (ini_char&01) >> 0;
}
void ToChar(packed_data& ini_char_bitstream,char& ini_char)
{
//**********���½�λ��bit stream ת�����ַ�**********
    ini_char = 'a';
	ini_char = ini_char&0;
	ini_char = ini_char|ini_char_bitstream.No_1 << 7;
	ini_char = ini_char|ini_char_bitstream.No_2 << 6;
	ini_char = ini_char|ini_char_bitstream.No_3 << 5;
	ini_char = ini_char|ini_char_bitstream.No_4 << 4;
	ini_char = ini_char|ini_char_bitstream.No_5 << 3;
	ini_char = ini_char|ini_char_bitstream.No_6 << 2;
	ini_char = ini_char|ini_char_bitstream.No_7 << 1;
	ini_char = ini_char|ini_char_bitstream.No_8 << 0;    
}
void CopyBitStream(packed_data& to,packed_data& from)
{
//**********���½�λ��from������λ��to**********
   to.No_1 = from.No_1;
   to.No_2 = from.No_2;
   to.No_3 = from.No_3;
   to.No_4 = from.No_4;
   to.No_5 = from.No_5;
   to.No_6 = from.No_6;
   to.No_7 = from.No_7;
   to.No_8 = from.No_8;
}
void PrintBitStream(packed_data& toprintbitstream)
{
//**********����λ��bit stream��ӡ��ʾ**********
	cout << toprintbitstream.No_1 << toprintbitstream.No_2
   	     << toprintbitstream.No_3 << toprintbitstream.No_4
	     << toprintbitstream.No_5 << toprintbitstream.No_6
	     << toprintbitstream.No_7 << toprintbitstream.No_8
		 << endl;
}
void GetPlaintext(packed_data& plaintext)
{
//**********�������û�����8λ������**********  
  char ini_plaintext[9];  //8-bit������
  char make_sure;
  cout << "������8λ����(0��1���������): " << flush;
  gets(ini_plaintext);
  while(strlen(ini_plaintext) != 8){
     cout << "���ĳ��Ȳ���!����������8λ����(0��1���������): " << flush;
     gets(ini_plaintext);
  }  
  cout << "�������8λ������: " << ini_plaintext << endl;
  cout << "��ȷ��[y,n]: " << flush;
  cin >> make_sure;
  while(make_sure != 'Y' && make_sure != 'y'){
     cout << "������8λ����(0��1���������): " << flush;
     gets(ini_plaintext);
     while(strlen(ini_plaintext) != 8){
        cout << "���ĳ��Ȳ���!����������8λ����(0��1���������): " << flush;
        gets(ini_plaintext);
	 }  
     cout << "�������8λ������: " << ini_plaintext << endl;
     cout << "��ȷ��[y,n]: " << flush;
     cin >> make_sure;
  }  
  plaintext.No_1 = ini_plaintext[0]-'0';
  plaintext.No_2 = ini_plaintext[1]-'0';
  plaintext.No_3 = ini_plaintext[2]-'0';
  plaintext.No_4 = ini_plaintext[3]-'0';
  plaintext.No_5 = ini_plaintext[4]-'0';
  plaintext.No_6 = ini_plaintext[5]-'0';
  plaintext.No_7 = ini_plaintext[6]-'0';
  plaintext.No_8 = ini_plaintext[7]-'0';

  return;
}
void GenerateKey(packed_data& K1,packed_data& K2)
{
//**********���²�����ԿK1 �� K2**********
    struct key_data{
		unsigned No_1:1;
		unsigned No_2:1;
		unsigned No_3:1;
		unsigned No_4:1;
		unsigned No_5:1;
		unsigned No_6:1;
		unsigned No_7:1;
		unsigned No_8:1;
        unsigned No_9:1;
		unsigned No_10:1;
	};               //�ɽ���λ������λ��
  char ini_key[11];  //10-bit�����û����������G(0��1���������)
  key_data p10_key;  //��G��P10�û�
//**********�������û���������G(0��1���������)**********
  char make_sure;
  cout << "������ԭʼ10λ����G(0��1���������): " << flush;
  gets(ini_key);
  while(strlen(ini_key) != 10){
     cout << "���볤�Ȳ���!����������10λ����G(0��1���������): " << flush;
     gets(ini_key);
  }  
  cout << "�������10λ������: " << ini_key << endl;
  cout << "��ȷ��[y,n]: " << flush;
  cin >> make_sure;
  while(make_sure != 'Y' && make_sure != 'y'){
     cout << "������ԭʼ10λ����G(0��1���������): " << flush;
     gets(ini_key);
     while(strlen(ini_key) != 10){
        cout << "���볤�Ȳ���!����������10λ����G(0��1���������): " << flush;
        gets(ini_key);
	 }  
     cout << "�������10λ������: " << ini_key << endl;
     cout << "��ȷ��[y,n]: " << flush;
     cin >> make_sure;
  }  
//**********������P10=(3 5 2 7 4 10 1 9 8 6)�û�**********
  p10_key.No_1 = ini_key[2]-'0';
  p10_key.No_2 = ini_key[4]-'0';
  p10_key.No_3 = ini_key[1]-'0';
  p10_key.No_4 = ini_key[6]-'0';
  p10_key.No_5 = ini_key[3]-'0';
  p10_key.No_6 = ini_key[9]-'0';
  p10_key.No_7 = ini_key[0]-'0';
  p10_key.No_8 = ini_key[8]-'0';
  p10_key.No_9 = ini_key[7]-'0';
  p10_key.No_10 = ini_key[5]-'0';
//**********��������벿�ֵ�ѭ������һλ:LS��1**********
  key_data Ls1_left_p10_key;
  Ls1_left_p10_key.No_1 = p10_key.No_2;
  Ls1_left_p10_key.No_2 = p10_key.No_3;
  Ls1_left_p10_key.No_3 = p10_key.No_4;
  Ls1_left_p10_key.No_4 = p10_key.No_5;
  Ls1_left_p10_key.No_5 = p10_key.No_1;
//**********�������Ұ벿�ֵ�ѭ������һλ:LS��1**********
  key_data Ls1_right_p10_key;
  Ls1_right_p10_key.No_1 = p10_key.No_7;
  Ls1_right_p10_key.No_2 = p10_key.No_8;
  Ls1_right_p10_key.No_3 = p10_key.No_9;
  Ls1_right_p10_key.No_4 = p10_key.No_10;
  Ls1_right_p10_key.No_5 = p10_key.No_6;
//**********������Q8 = (6 3 7 4 8 5 10 9)�任,�õ�K1*********
  K1.No_1 = Ls1_right_p10_key.No_1;
  K1.No_2 = Ls1_left_p10_key.No_3;
  K1.No_3 = Ls1_right_p10_key.No_2;
  K1.No_4 = Ls1_left_p10_key.No_4;
  K1.No_5 = Ls1_right_p10_key.No_3;
  K1.No_6 = Ls1_left_p10_key.No_5;
  K1.No_7 = Ls1_right_p10_key.No_5;
  K1.No_8 = Ls1_right_p10_key.No_4;
//**********��������벿�ֵ�ѭ�����ƶ�λ:LS��2**********
  key_data Ls2_left_p10_key;
  Ls2_left_p10_key.No_1 = Ls1_left_p10_key.No_3;
  Ls2_left_p10_key.No_2 = Ls1_left_p10_key.No_4;
  Ls2_left_p10_key.No_3 = Ls1_left_p10_key.No_5;
  Ls2_left_p10_key.No_4 = Ls1_left_p10_key.No_1;
  Ls2_left_p10_key.No_5 = Ls1_left_p10_key.No_2;
//**********�������Ұ벿�ֵ�ѭ�����ƶ�λ:LS��2**********
  key_data Ls2_right_p10_key;
  Ls2_right_p10_key.No_1 = Ls1_right_p10_key.No_3;
  Ls2_right_p10_key.No_2 = Ls1_right_p10_key.No_4;
  Ls2_right_p10_key.No_3 = Ls1_right_p10_key.No_5;
  Ls2_right_p10_key.No_4 = Ls1_right_p10_key.No_1;
  Ls2_right_p10_key.No_5 = Ls1_right_p10_key.No_2;
//**********������Q8 = (6 3 7 4 8 5 10 9)�任,�õ�K2*********
  K2.No_1 = Ls2_right_p10_key.No_1;
  K2.No_2 = Ls2_left_p10_key.No_3;
  K2.No_3 = Ls2_right_p10_key.No_2;
  K2.No_4 = Ls2_left_p10_key.No_4;
  K2.No_5 = Ls2_right_p10_key.No_3;
  K2.No_6 = Ls2_left_p10_key.No_5;
  K2.No_7 = Ls2_right_p10_key.No_5;
  K2.No_8 = Ls2_right_p10_key.No_4;
}
void IP(packed_data& plaintext_bitstream)
{
//**********���¶�������IP=(2 6 3 1 4 8 5 7)���û�**********
   packed_data temp;
   CopyBitStream(temp,plaintext_bitstream);
   plaintext_bitstream.No_1 = temp.No_2;
   plaintext_bitstream.No_2 = temp.No_6;
   plaintext_bitstream.No_3 = temp.No_3;
   plaintext_bitstream.No_4 = temp.No_1;
   plaintext_bitstream.No_5 = temp.No_4;
   plaintext_bitstream.No_6 = temp.No_8;
   plaintext_bitstream.No_7 = temp.No_5;
   plaintext_bitstream.No_8 = temp.No_7;
}
void ReverseIP(packed_data& plaintext_bitstream)
{ 
//**********���¶�������IP�����û�=(4 1 3 5 7 2 8 6)**********
   packed_data temp;
   CopyBitStream(temp,plaintext_bitstream);
   plaintext_bitstream.No_1 = temp.No_4;
   plaintext_bitstream.No_2 = temp.No_1;
   plaintext_bitstream.No_3 = temp.No_3;
   plaintext_bitstream.No_4 = temp.No_5;
   plaintext_bitstream.No_5 = temp.No_7;
   plaintext_bitstream.No_6 = temp.No_2;
   plaintext_bitstream.No_7 = temp.No_8;
   plaintext_bitstream.No_8 = temp.No_6;
}
void EP(packed_data& right_plaintext_bitstream,packed_data& EP_bitstream)
{
//**********���¶������Ұ벿����E/P(1 2 3 4)=(4 1 2 3 2 3 4 1)**********
   EP_bitstream.No_1 = right_plaintext_bitstream.No_8;
   EP_bitstream.No_2 = right_plaintext_bitstream.No_5;
   EP_bitstream.No_3 = right_plaintext_bitstream.No_6;
   EP_bitstream.No_4 = right_plaintext_bitstream.No_7;
   EP_bitstream.No_5 = right_plaintext_bitstream.No_6;
   EP_bitstream.No_6 = right_plaintext_bitstream.No_7;
   EP_bitstream.No_7 = right_plaintext_bitstream.No_8;
   EP_bitstream.No_8 = right_plaintext_bitstream.No_5;
}
void XOR1(packed_data& EP_bitstream,packed_data& K1_bitstream,packed_data& EP_XOR_K1_bitstream)
{
//**********���¶�E/P_bitstream��K1���������**********
   char ep,K1,ep_xor_K1;
   ToChar(EP_bitstream,ep);
   ToChar(K1_bitstream,K1);
   ep_xor_K1 = ep^K1;
   ToBitStream(ep_xor_K1,EP_XOR_K1_bitstream);
}
void S0(packed_data& left_EP_XOR_K1_bitstream,packed_data& S0_twobit_output)
{
//**********�������������S0�õ�two bit���**********
	int S0[4][4] = {{1,0,3,2}
	               ,{3,2,1,0}
				   ,{0,2,1,3}
				   ,{3,1,3,2}};
	int i = left_EP_XOR_K1_bitstream.No_1*2 +left_EP_XOR_K1_bitstream.No_4;
    int j = left_EP_XOR_K1_bitstream.No_2*2 +left_EP_XOR_K1_bitstream.No_3;
    S0_twobit_output.No_1 = S0[i][j]/2;
    S0_twobit_output.No_2 = S0[i][j]%2;
}
void S1(packed_data& right_EP_XOR_K1_bitstream,packed_data& S1_twobit_output)
{
//**********�������������S1�õ�two bit���**********
	int S1[4][4] = {{0,1,2,3}
	               ,{2,0,1,3}
				   ,{1,0,3,2}
				   ,{2,1,0,0}};
	int i = right_EP_XOR_K1_bitstream.No_5*2 +right_EP_XOR_K1_bitstream.No_8;
    int j = right_EP_XOR_K1_bitstream.No_6*2 +right_EP_XOR_K1_bitstream.No_7;
    S1_twobit_output.No_3 = S1[i][j]/2;
    S1_twobit_output.No_4 = S1[i][j]%2;
}
void P4(packed_data& S0S1_output)
{
//**********���¶�S0S1-four bitstream��P4=(2 4 3 1)�û�**********
   packed_data temp;
   CopyBitStream(temp,S0S1_output);
   S0S1_output.No_1 = temp.No_2;
   S0S1_output.No_2 = temp.No_4;
   S0S1_output.No_3 = temp.No_3;
   S0S1_output.No_4 = temp.No_1;
}
void XOR2(packed_data& S0S1_output,packed_data& left_plaintext_bitstream,packed_data& left_XOR_S0S1_bitstream)
{
//**********���¶�P4��plaintext���󲿷����������**********   
   if(S0S1_output.No_1 == left_plaintext_bitstream.No_1)
	   left_XOR_S0S1_bitstream.No_1 = 0; 
   else left_XOR_S0S1_bitstream.No_1 = 1;
   if(S0S1_output.No_2 == left_plaintext_bitstream.No_2)
	   left_XOR_S0S1_bitstream.No_2 = 0; 
   else left_XOR_S0S1_bitstream.No_2 = 1;
   if(S0S1_output.No_3 == left_plaintext_bitstream.No_3)
	   left_XOR_S0S1_bitstream.No_3 = 0; 
   else left_XOR_S0S1_bitstream.No_3 = 1;
   if(S0S1_output.No_4 == left_plaintext_bitstream.No_4)
	   left_XOR_S0S1_bitstream.No_4 = 0; 
   else left_XOR_S0S1_bitstream.No_4 = 1;
}
void SW(packed_data& left_XOR_S0S1_bitstream,packed_data& right_plaintext_bitstream,packed_data& second_plaintext_bitstream)
{
	second_plaintext_bitstream.No_1 = right_plaintext_bitstream.No_5;
    second_plaintext_bitstream.No_2 = right_plaintext_bitstream.No_6;
    second_plaintext_bitstream.No_3 = right_plaintext_bitstream.No_7;
    second_plaintext_bitstream.No_4 = right_plaintext_bitstream.No_8;
    second_plaintext_bitstream.No_5 = left_XOR_S0S1_bitstream.No_1;
    second_plaintext_bitstream.No_6 = left_XOR_S0S1_bitstream.No_2;
    second_plaintext_bitstream.No_7 = left_XOR_S0S1_bitstream.No_3;
    second_plaintext_bitstream.No_8 = left_XOR_S0S1_bitstream.No_4;
}
void Encryption(packed_data& plaintext,packed_data& ciphertext,packed_data& K1,packed_data& K2)
{

//******************************IP******************************
	IP(plaintext);                     //IP�û�
    cout << endl  << "IP�û�������:" << endl;	
	PrintBitStream(plaintext);

//******************************f(k)_1******************************
	packed_data EP_bitstream;          
	EP(plaintext,EP_bitstream);        //E/P��չ�û�
    cout <<"**************************************************" << endl
         <<"E/P��չ�û�:" << endl;	
    PrintBitStream(EP_bitstream);
   
	packed_data EP_XOR_K1_bitstream;
	XOR1(EP_bitstream,K1,EP_XOR_K1_bitstream);//(E/P)^K1
    cout <<"**************************************************" << endl
         <<"E/P��չ�û�&K1���������:" << endl;
    PrintBitStream(EP_XOR_K1_bitstream);
	
	packed_data S0S1_output;
    S0(EP_XOR_K1_bitstream,S0S1_output);  //�����S0
    cout <<"**************************************************" << endl
         <<"�����S0���:" << endl;
	cout << S0S1_output.No_1 << S0S1_output.No_2 << endl;
    
	S1(EP_XOR_K1_bitstream,S0S1_output);  //�����S1
    cout <<"**************************************************" << endl
         <<"�����S1���:" << endl;
	cout << S0S1_output.No_3 << S0S1_output.No_4 << endl;
    
	P4(S0S1_output);                       //P4�û�
    cout <<"**************************************************" << endl
         <<"P4�û�:" << endl;
	cout << S0S1_output.No_1 << S0S1_output.No_2
		 << S0S1_output.No_3 << S0S1_output.No_4 << endl;
    
	packed_data left_XOR_S0S1_bitstream;   //P4^���ĵ���벿��
	XOR2(S0S1_output,plaintext,left_XOR_S0S1_bitstream);
    cout <<"**************************************************" << endl
         <<"���ĵ���벿����P4���������:" << endl;
	cout << left_XOR_S0S1_bitstream.No_1 << left_XOR_S0S1_bitstream.No_2
		 << left_XOR_S0S1_bitstream.No_3 << left_XOR_S0S1_bitstream.No_4 << endl;

//*******************************SW*********************************
	packed_data second_plaintext;          //SW���� 
  	SW(left_XOR_S0S1_bitstream,plaintext,second_plaintext);
    cout <<"**************************************************" << endl
         <<"SW����:" << endl;
	PrintBitStream(second_plaintext);

//******************************f(k)_2******************************
    packed_data second_EP_bitstream;          
	EP(second_plaintext,second_EP_bitstream);        //E/P��չ�û�
    cout <<"**************************************************" << endl
         <<"E/P��չ�û�:" << endl;	
    PrintBitStream(second_EP_bitstream);
   
	packed_data second_EP_XOR_K2_bitstream;
	XOR1(second_EP_bitstream,K2,second_EP_XOR_K2_bitstream);//(E/P)^K2
    cout <<"**************************************************" << endl
         <<"E/P��չ�û�&K2���������:" << endl;
    PrintBitStream(second_EP_XOR_K2_bitstream);
	
	packed_data second_S0S1_output;
    S0(second_EP_XOR_K2_bitstream,second_S0S1_output);  //�����S0
    cout <<"**************************************************" << endl
         <<"�����S0���:" << endl;
	cout << second_S0S1_output.No_1 << second_S0S1_output.No_2 << endl;
    
	S1(second_EP_XOR_K2_bitstream,second_S0S1_output);  //�����S1
    cout <<"**************************************************" << endl
         <<"�����S1���:" << endl;
	cout << second_S0S1_output.No_3 << second_S0S1_output.No_4 << endl;
    
	P4(second_S0S1_output);                       //P4�û�
    cout <<"**************************************************" << endl
         <<"P4�û�:" << endl;
	cout << second_S0S1_output.No_1 << second_S0S1_output.No_2
		 << second_S0S1_output.No_3 << second_S0S1_output.No_4 << endl;
    
	packed_data second_left_XOR_S0S1_bitstream;   //P4^���ĵ���벿��
	XOR2(second_S0S1_output,second_plaintext,second_left_XOR_S0S1_bitstream);
    cout <<"**************************************************" << endl
         <<"���ĵ���벿����P4���������:" << endl;
	cout << second_left_XOR_S0S1_bitstream.No_1 
		 << second_left_XOR_S0S1_bitstream.No_2
		 << second_left_XOR_S0S1_bitstream.No_3 
		 << second_left_XOR_S0S1_bitstream.No_4 
		 << endl;

//******************************ReverseIP******************************
	packed_data input_ReverseIP; 
    input_ReverseIP.No_1 = second_left_XOR_S0S1_bitstream.No_1;
    input_ReverseIP.No_2 = second_left_XOR_S0S1_bitstream.No_2;
	input_ReverseIP.No_3 = second_left_XOR_S0S1_bitstream.No_3;
	input_ReverseIP.No_4 = second_left_XOR_S0S1_bitstream.No_4;
	input_ReverseIP.No_5 = second_plaintext.No_5;
	input_ReverseIP.No_6 = second_plaintext.No_6;
	input_ReverseIP.No_7 = second_plaintext.No_7;
	input_ReverseIP.No_8 = second_plaintext.No_8;
    ReverseIP(input_ReverseIP);

//******************************��������******************************
	CopyBitStream(ciphertext,input_ReverseIP);
    cout <<"**************************************************" << endl
         <<"����������:" << endl;
	PrintBitStream(ciphertext);
}
void Decryption(packed_data& ciphertext,packed_data& plaintext,packed_data& K1,packed_data& K2)
{
//******************************IP******************************
	IP(ciphertext);                     //IP�û�
    cout <<"**************************************************" << endl
         <<"IP�û�������:" << endl;	
	PrintBitStream(ciphertext);

//******************************f(k)_2******************************
	packed_data EP_bitstream;          
	EP(ciphertext,EP_bitstream);        //E/P��չ�û�
    cout <<"**************************************************" << endl
         <<"E/P��չ�û�:" << endl;	
    PrintBitStream(EP_bitstream);
   
	packed_data EP_XOR_K2_bitstream;
	XOR1(EP_bitstream,K2,EP_XOR_K2_bitstream);//(E/P)^K2
    cout <<"**************************************************" << endl
         <<"E/P��չ�û�&K2���������:" << endl;
    PrintBitStream(EP_XOR_K2_bitstream);
	
	packed_data S0S1_output;
    S0(EP_XOR_K2_bitstream,S0S1_output);  //�����S0
    cout <<"**************************************************" << endl
         <<"�����S0���:" << endl;
	cout << S0S1_output.No_1 << S0S1_output.No_2 << endl;
    
	S1(EP_XOR_K2_bitstream,S0S1_output);  //�����S1
    cout <<"**************************************************" << endl
         <<"�����S1���:" << endl;
	cout << S0S1_output.No_3 << S0S1_output.No_4 << endl;
    
	P4(S0S1_output);                       //P4�û�
    cout <<"**************************************************" << endl
         <<"P4�û�:" << endl;
	cout << S0S1_output.No_1 << S0S1_output.No_2
		 << S0S1_output.No_3 << S0S1_output.No_4 << endl;
    
	packed_data left_XOR_S0S1_bitstream;   //P4^���ĵ���벿��
	XOR2(S0S1_output,ciphertext,left_XOR_S0S1_bitstream);
    cout <<"**************************************************" << endl
         <<"���ĵ���벿����P4���������:" << endl;
	cout << left_XOR_S0S1_bitstream.No_1 << left_XOR_S0S1_bitstream.No_2
		 << left_XOR_S0S1_bitstream.No_3 << left_XOR_S0S1_bitstream.No_4 << endl;

//*******************************SW*********************************
	packed_data second_ciphertext;          //SW���� 
  	SW(left_XOR_S0S1_bitstream,ciphertext,second_ciphertext);
    cout <<"**************************************************" << endl
         <<"SW����:" << endl;
	PrintBitStream(second_ciphertext);

//******************************f(k)_1******************************
    packed_data second_EP_bitstream;          
	EP(second_ciphertext,second_EP_bitstream);        //E/P��չ�û�
    cout <<"**************************************************" << endl
         <<"E/P��չ�û�:" << endl;	
    PrintBitStream(second_EP_bitstream);
   
	packed_data second_EP_XOR_K1_bitstream;
	XOR1(second_EP_bitstream,K1,second_EP_XOR_K1_bitstream);//(E/P)^K1
    cout <<"**************************************************" << endl
         <<"E/P��չ�û�&K1���������:" << endl;
    PrintBitStream(second_EP_XOR_K1_bitstream);
	
	packed_data second_S0S1_output;
    S0(second_EP_XOR_K1_bitstream,second_S0S1_output);  //�����S0
    cout <<"**************************************************" << endl
         <<"�����S0���:" << endl;
	cout << second_S0S1_output.No_1 << second_S0S1_output.No_2 << endl;
    
	S1(second_EP_XOR_K1_bitstream,second_S0S1_output);  //�����S1
    cout <<"**************************************************" << endl
         <<"�����S1���:" << endl;
	cout << second_S0S1_output.No_3 << second_S0S1_output.No_4 << endl;
    
	P4(second_S0S1_output);                       //P4�û�
    cout <<"**************************************************" << endl
         <<"P4�û�:" << endl;
	cout << second_S0S1_output.No_1 << second_S0S1_output.No_2
		 << second_S0S1_output.No_3 << second_S0S1_output.No_4 << endl;
    
	packed_data second_left_XOR_S0S1_bitstream;   //P4^���ĵ���벿��
	XOR2(second_S0S1_output,second_ciphertext,second_left_XOR_S0S1_bitstream);
    cout <<"**************************************************" << endl
         <<"���ĵ���벿����P4���������:" << endl;
	cout << second_left_XOR_S0S1_bitstream.No_1 
		 << second_left_XOR_S0S1_bitstream.No_2
		 << second_left_XOR_S0S1_bitstream.No_3 
		 << second_left_XOR_S0S1_bitstream.No_4 
		 << endl;

//******************************ReverseIP******************************
	packed_data input_ReverseIP; 
    input_ReverseIP.No_1 = second_left_XOR_S0S1_bitstream.No_1;
    input_ReverseIP.No_2 = second_left_XOR_S0S1_bitstream.No_2;
	input_ReverseIP.No_3 = second_left_XOR_S0S1_bitstream.No_3;
	input_ReverseIP.No_4 = second_left_XOR_S0S1_bitstream.No_4;
	input_ReverseIP.No_5 = second_ciphertext.No_5;
	input_ReverseIP.No_6 = second_ciphertext.No_6;
	input_ReverseIP.No_7 = second_ciphertext.No_7;
	input_ReverseIP.No_8 = second_ciphertext.No_8;
    ReverseIP(input_ReverseIP);

//******************************�ָ�����***************************
	CopyBitStream(plaintext,input_ReverseIP);
    cout <<"**************************************************" << endl
         <<"�ָ�������:" << endl;
	PrintBitStream(plaintext);
}
