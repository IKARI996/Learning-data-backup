#ifndef __Decry_h
#define __Decry_h
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class Decry{
public:
	Decry(ofstream *outfile,ifstream *infile1,ifstream *infile2);
	void decry();
private:
	bool getLetter(string s,char &letter)const;

    ofstream *decryedText;
	ifstream *DecryTable;
	ifstream *ciphertext;
	string code[128];//���ֱ�����
};

//////////////////////////////////////////////////
Decry::Decry(ofstream *outfile,ifstream *infile1,ifstream *infile2)
{
	decryedText=outfile;
	DecryTable=infile1;
	ciphertext=infile2;
//�����ֱ�
	char letter;
	char digit;
	char blank;
	string s;	
	while(DecryTable->peek()!=EOF){
		//������
		DecryTable->get(letter);
        DecryTable->get(blank);
		//�����ַ���
		s="";
		while(DecryTable->peek()!='\n'){
            DecryTable->get(digit);
			s=s+digit;
		}
        DecryTable->get(blank);
		//�������¼���ֺ��ַ����Ķ�Ӧ��ϵ
		code[(int)letter]=s;
	}
}

///////////////////////////////////////////////////////////////
void Decry::decry()
{
	char letter;
	char digit;
	string s;
	s="";
	while(ciphertext->peek()!=EOF){
        ciphertext->get(digit);
		s=s+digit;
		if(getLetter(s,letter)){//��s�������ֱ�
			(*decryedText)<<letter;
		    s="";
		}
				
	}
}
////////////////////////////////////////////////////////
bool Decry::getLetter(string s,char &letter)const
{
	for(int i=0;i<128;i++)
		if( s.compare(code[i])==0 ){
			letter=char(i);
			return true;
		}
	return false;
}
#endif  