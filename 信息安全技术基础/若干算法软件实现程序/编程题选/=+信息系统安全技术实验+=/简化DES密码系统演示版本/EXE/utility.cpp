/**********************************************************************
*Function: ���ù��߰�
*Author:   �ⵤ 00234015 3��
*Date:     2003/3/13
*Version:  V1.0
***********************************************************************/
#include "utility.h"
bool users_says_yes()  //ʵ��ѯ���û�����
{
  int c;
  bool initial_response = true;
  do{
     if(initial_response)
     	cout << "(y,n)?" << flush;
     else
	    cout << " Response with either y or n:" << flush;
     do{   //ʡ�Ի��С��ո�TAB��
	    c = cin.get();
     }while(c == '\n' || c == ' ' || c == '\t');
     initial_response = false;
  }while(c != 'y' && c != 'Y' && c != 'n' && c != 'N' );

  return (c == 'y' || c == 'Y');

}

int openInFile(ifstream& inFile)
{
   char fileName[20];
   cout << "׼���������ļ����������ļ���: " << flush;
   gets(fileName);
   inFile.open(fileName);
   if(!inFile){
      cout << "Can't open file:" << fileName << endl;
      return(1);	
   }
   return 0;
}

int openOutFile(ofstream& outFile)
{
   char fileName[20];
   cout << "׼��������ļ����������ļ���: " << flush;
   gets(fileName);
   outFile.open(fileName);
   if(!outFile){
      cout << "Can't open file:" << fileName << endl;
      return(1);	
   }
   return 0;
}

