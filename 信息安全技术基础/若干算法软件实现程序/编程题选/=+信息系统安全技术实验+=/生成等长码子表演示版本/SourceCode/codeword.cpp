#include <iostream.h>
#include <stdio.h>
#include <string.h>
const int maxlength = 20;
void codeword(char code[maxlength],int length);

int main()
{
   cout << "����������������++ Code System ++��--��������������" << endl
        << "|Function: ��������CodeSystem�еȳ���3λCode Word |" << endl
	    << "|Author: �ⵤ                                     |" << endl
        << "|Run: MicroSoft Visual C++ 6.0                    |" << endl
	    << "|Data: 2003.5.5,Version 1.0 Realeased             |" << endl
	    << "|_________________________________________________|" << endl;
  	
   char code[maxlength];
   cout << "��������ĸ: " << flush; 
   gets(code);

   codeword(code,strlen(code));
   
   cout << "�������" << endl;
   gets(code); // ��ʱ����,���ڿ���̨�²鿴������
   
   return 0;

}

void codeword(char code[],int length)
{
   int i,j,k;
   for(i = 0;i<length;i++)
      for(j = 0;j<length;j++)
         if(i != j){
            for(k = 0;k<length;k++)
               if(i != k && j!= k ){
                 cout << code[i] << code[j] << code[k] << endl;
                }
         }
}