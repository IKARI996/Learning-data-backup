/********************************************************************
Function: Caesar������㷨ʵ����ʾ�汾
Author:   �ⵤ 3�� 00234015
*********************************************************************/
#include <iostream.h>
#include <stdio.h>

#define WZ_COMMEND_NUM 4 
char *WZ_Commend_Help[] =
{
  "Caesar������㷨ʵ����ʾ�汾     ", 
  " ====׷��׿Խ,���ڴ���====       ", 
  "         ����:�ⵤ               ",
  "                                 " 
};
void wz_printhelp(); //����

int caesar();   //caesar����㷨����

int main(){
   char k;
   
   caesar();
   
   cout << "Ҫ�������б�������<y,n>��" << flush;
   cin >> k;
   while(k == 'y' || k == 'Y'){
	     caesar();
		 cout << "Ҫ�������б�������<y,n>��" << flush;
         cin >> k;
   }
   
   return 0;
}
  

int caesar()
{
   char M[10];        //�洢���������ַ�
   char C[10];        //�洢���������ַ�
   char c;            //��������ı���
   int i,k1,k2;       //���Ʊ���
   
   wz_printhelp();
   
   
   for(i=0;i<10;i++){          //������������и���ֵ' '
      M[i] = C[i] = ' ';
   }
   
   cout << "������10���ַ�:  " << flush; //��������
   for(i=0;i<10;i++){
      c = getchar();
      M[i] = c;
   }
   
   cout << "��������ַ�Ϊ��" << flush; //������ʾ
   for(i = 0;i<10;i++)
      cout << M[i];
   
   cout << endl                        //���ܹ��̣���ȡ����
	    << "Ҫ������(y,n)?" << flush;           
   cin >> c;
   if(c=='y'||c=='Y'){
      cout << "��������λ���루1-25����" <<flush;
      cin >> k1;   
      cout << "���ظ���λ���루1-25����" <<flush;
      cin >> k2;
     while(k1!=k2){
          cout << "���벻һ��!���ٴ�����!" << endl;
          cout << "��������λ���루1-25����" << flush;
          cin >> k1;   
          cout << "���ظ���λ���루1-25����" <<flush;
          cin >> k2;
     } 
     for(i = 0;i<10;i++){   //�����㷨
         if((M[i] < 'A' || M[i] > 'Z') && (M[i] <'a' || M[i] > 'z'))
		    C[i] = M[i]; 
		 else if(M[i] >= 'A' && M[i] <= 'Z') C[i] = 'A' + ((M[i] - 'A' + k1) % 26); 
	     else if(M[i] >= 'a' && M[i] <= 'z') C[i] = 'a' + ((M[i] - 'a' + k1) % 26); 
		 
     }    
	 cout << "�����Ѽ���!" << endl;
     cout << "������ʾ��" << flush;
	 for(i = 0;i<10;i++){
		 cout << C[i];
     }
	 cout << endl;
     
   }else {
	   cout << "��δ�������ģ�����ȫ��" << endl;
       return 0;
   }
   
   cout << "Ҫ�鿴������(y,n)��" << flush;            //���ܹ��̣���ȡ����
   cin >> c;
   if(c=='y'||c=='Y'){
      cout << "���н��ܣ����������룺" << flush;
      cin >> k1;
      if(k1==k2){
		  for(i = 0;i<10;i++){    //�����㷨
            if((C[i] < 'A' || C[i] > 'Z') && (C[i] <'a' || C[i] > 'z'))
		        M[i] = C[i]; 
			else if (C[i] >= 'A' && C[i] <= 'Z') M[i] = 'A' + ((C[i] - 'A' - k1 + 26) % 26); 
	        else if (C[i] >= 'a' && C[i] <= 'z') M[i] = 'a' + ((C[i] - 'a' - k1 + 26) % 26); 	  
		  }			
	  
		  cout << "������ʾ��" << flush;
	  for(i = 0;i<10;i++)
         cout << M[i];
      cout << endl;
	  }else cout << "������󣡲鿴ʧ�ܣ�" << endl;
   }

   return 0;
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

 

   return ;
}