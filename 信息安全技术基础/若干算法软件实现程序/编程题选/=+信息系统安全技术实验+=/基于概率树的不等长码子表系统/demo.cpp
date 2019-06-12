#include<iostream>
#include<fstream>
#include<string>
using namespace std;

#include"codeTable.h"
#include"encry.h"
#include"decry.h"

#define WZ_COMMEND_NUM 4 
#define WZUSEHELPNUM 7
void wz_printhelp();

char *WZ_Commend_Help[] =
{
  "���ڲ��ȳ����ӱ���ܽ��ܹ���     ", 
  "====׷��׿Խ,���ڴ���====        ", 
  "--------����:�ⵤ--------        ",
  "                                 " 
};


char *WZ_USE_HELP[]=
{
  "����5������:",
  "\t1.Ҫ���ܵ����ģ�plaintext.txt",
  "\t2.���ӱ�keyTable.txt",
  "\t3.���ܺ�����ģ�ciphertext.txt",
  "\t4.���ܺ�����ģ�decryedText.txt", 
  "\t",
  "--------------------------------------------"
};

void main()
{
    wz_printhelp();  //��ʾ

	ifstream plaintext("plaintext.txt");  //�����ļ� 
    ofstream keyTable("keyTable.txt");    //���ֱ�
    //�������ֱ�
	CodeTable c(&plaintext,&keyTable);
	c.buildCodeTable();
	keyTable.close(); 
	plaintext.close();
	

	ifstream plaintext2("plaintext.txt");  //����Ҫ��ͷ����
	ifstream keyTable2("keyTable.txt");    //���ֱ�
	ofstream ciphertext("ciphertext.txt"); //����
    //�����ֱ����
    Encry e(&plaintext2,&keyTable2,&ciphertext);
	e.encry();

	plaintext2.close();
	keyTable2.close(); 
	ciphertext.close();

    ofstream decryedText("decryedText.txt");//����Ҫ��ͷ����
	ifstream keyTable3("keyTable.txt");    //���ֱ�
	ifstream ciphertext2("ciphertext.txt");//����
    //�����ֱ����
	Decry d(&decryedText,&keyTable3,&ciphertext2);
	d.decry();

	decryedText.close();
	keyTable3.close();
	ciphertext2.close();

}

void wz_printhelp()
{
   int i ;
   printf("\t");
   for( i = 0 ; i < 22 ; i++)
   {
      printf("%c ",5);
   }

   printf("\n");

   for( i = 0 ; i < WZ_COMMEND_NUM ; i++)
   {
      printf("\t%c\t%s %c\n",5,WZ_Commend_Help[i],5); 
   }

   printf("\t");
   for ( i = 0 ; i < 22 ; i++)
   {
	   printf("%c ",5);
   } 

   printf("\n");

   for( i = 0 ; i < WZUSEHELPNUM ; i++)
   {
      printf("\t%s\n",WZ_USE_HELP[i]);
   }

   return ;
}