#ifndef __Encry_h
#define __Encry_h
#include<fstream>
#include<string>
using namespace std;

class Encry{
public:
	Encry(ifstream *infile1,ifstream *infile2,ofstream *outfile);
	void encry();
private:
    ifstream *plaintext;
	ifstream *EncryTable;
	ofstream *ciphertext;
	string code[128];//���ֱ�����
};

//////////////////////////////////////////////////
Encry::Encry(ifstream *infile1,ifstream *infile2,ofstream *outfile)
{
	plaintext=infile1;
	EncryTable=infile2;
	ciphertext=outfile;
//�����ֱ�
	char letter;
	char digit;
	char blank;
	string s;	
	while(EncryTable->peek()!=EOF){
		//������
		EncryTable->get(letter);
        EncryTable->get(blank);
		//�����ַ���
		s="";
		while(EncryTable->peek()!='\n'){
            EncryTable->get(digit);
			s=s+digit;
		}
        EncryTable->get(blank);
		//�������¼���ֺ��ַ����Ķ�Ӧ��ϵ
		code[(int)letter]=s;
	}
}

///////////////////////////////////////////////////////////////
void Encry::encry()
{
	char letter;
	string s;
	while(plaintext->peek()!=EOF){
        plaintext->get(letter);
		s=code[letter];
		(*ciphertext)<<s;		
	}
}
#endif  