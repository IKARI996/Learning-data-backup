#include <iostream.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void Encrypt(FILE*,FILE*,char*);  //����
void Decrypt(FILE*,FILE*,char*);  //����

void main()
{
    
	cout << "����������������++ Vigenere Tool ++����������������" << endl
         << "|Function: ����Vigenere�㷨���ı��ļ����������   |" << endl
	     << "|Author: �ⵤ                                     |" << endl
         << "|Run: MicroSoft Visual C++ 6.0                    |" << endl
	     << "|Data: 2003.5.5,Version 1.0 Realeased             |" << endl
	     << "|_________________________________________________|" << endl;
  
   char FILENAME1[25],FILENAME2[25]; /*�ļ�����*/
   FILE *fp, *fp2;                   /*�ļ�ָ��*/
   char key[25];                        /*��Կ����*/ 
   
   char ch;        /*�û�ȷ��*/
   int user;       /*�û�ȷ��*/
      
   cout << "��ȷ����Ҫʹ�� ==Vigenere Tool== [y,n]?" << flush; 
   cin >> ch;
   if(ch != 'y' && ch != 'Y'){
       cout << "�����˳�==Vigenere Tool==,��ӭ�ٴ�ʹ��!" << endl;
       return;
   }
   
   cout << endl
	    << "==============Vigenere Tool==============" << endl;
   cout << "���ò���:1------>�ļ�����" << endl   
	    << "         2------>�ļ�����" << endl
		<< "         3------>Quit Me!" << endl
		<< "��ѡ��[1,2,3]?" << flush;
   cin >> user;
   switch( user )
   {
      case 1:/*���ܲ���*/             
			cout << endl 
				 <<"==============Vigenere Tool==============" << endl;
            cout << "Ŀǰ����:1------>�ļ����� " << endl;
		    cout << "����������ܵ��ļ���(*.txt): " << flush;
		    gets(FILENAME1);
			
			cout << endl 
				 <<"==============Vigenere Tool==============" << endl;
            cout << "Ŀǰ����:1------>�ļ����� "<< endl;
		    cout << "��������ܺ���ļ���(*.txt): " << flush;
		    gets(FILENAME2);
            
			if((fp = fopen(FILENAME1,"r")) == NULL || (fp2 = fopen(FILENAME2,"w"))==NULL)
			{ 
                printf("Can't open file\n"); 
                return ;
			} 
			
			cout << endl 
				 <<"==============Vigenere Tool==============" << endl;
            cout << "Ŀǰ����:1------>�ļ����� "<< endl 
				 << "����������ܳ�: " << flush;
			gets(key);

			
            Encrypt(fp,fp2,key); 
            
			cout << endl 
				 <<"==============Vigenere Tool==============" << endl;
            cout << "Ŀǰ����:1------>�ļ����� "<< endl;
			printf("Vigenere Tool �������,���Ĵ���%s�ļ�\n",FILENAME2);
			break;
	  case 2:/*���ܲ���*/            
			cout << endl 
				 <<"==============Vigenere Tool==============" << endl;
            cout << "Ŀǰ����:2------>�ļ����� " << endl;
		    cout << "����������ܵ��ļ���(*.txt): " << flush;
		    gets(FILENAME1);
			
			cout << endl 
				 <<"==============Vigenere Tool==============" << endl;
            cout << "Ŀǰ����:2------>�ļ����� "<< endl;
		    cout << "��������ܺ���ļ���(*.txt): " << flush;
		    gets(FILENAME2);

			if((fp= fopen(FILENAME1,"r")) == NULL || (fp2 = fopen(FILENAME2,"w"))==NULL)
			{ 
               printf("Can't open file\n"); 
               return ;
			} 

			cout << endl 
				 <<"==============Vigenere Tool==============" << endl;
            cout << "Ŀǰ����:2------>�ļ����� "<< endl 
				 << "����������ܳ�: " << flush;
			gets(key);
            
            Decrypt(fp,fp2,key); 
            
			cout << endl 
				 <<"==============Coolest IDEA==============" << endl;
            cout << "Ŀǰ����:2--����>�ļ����� "<< endl;
			printf("Vigenere Tool�������,���Ĵ���%s�ļ�\n",FILENAME2);
			break;
	  case 3:
            cout << "�����˳�==Vigenere Tool==,��ӭ�ٴ�ʹ��!" << endl;
	    	return;
   
     }

   	fclose(fp);
    fclose(fp2);

   return;

}

void Encrypt(FILE* inFile,FILE* outFile,char* key)
{
   int len;      //��Կ����
   int i = 0;    //��i����Կ�ַ�
   char ch;      //�������ַ�   
   
   len = strlen(key);
   
   ch = getc(inFile);
   while(ch!=EOF){
	   if( (ch >='A' && ch <='Z') || (ch >='a' && ch <='z') ){ //ֻ����ĸ����
	      ch = toupper(ch); //Сд��ĸ���д��ĸ
	      ch = ch - 65;     //������� 
		  ch = (ch + (toupper(key[(i++)%len]) - 65)) % 26; //���� 
		  ch = ch + 65; //�����ĸ
	      fputc(ch,outFile);
	   }else
		  putc(ch,outFile);
	   ch = fgetc(inFile);
   }
}

void Decrypt(FILE* inFile,FILE* outFile,char* key)
{
   int len;      //��Կ����
   int i = 0;    //��i����Կ�ַ�
   char ch;      //�������ַ�   
   
   len = strlen(key);
   
   ch = getc(inFile);
   while(ch!=EOF){
	   if( (ch >='A' && ch <='Z')){ //�����ܾ�Ϊ��д��ĸ
	      ch = ch - 65; //������� 
		  ch = (ch - ((toupper(key[(i++)%len]) - 65)) + 26) % 26; // ����
	      ch = ch + 65; //�����ĸ
		  putc(ch,outFile);
	   }else
		  fputc(ch,outFile);
	   ch = fgetc(inFile);
   }
}
