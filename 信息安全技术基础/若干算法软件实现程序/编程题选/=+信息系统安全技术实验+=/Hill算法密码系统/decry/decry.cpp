#include<iostream.h>
#include<fstream.h>

const int LENGTH=2;
ofstream textFile("codedData.txt"); //���ܺ���ļ�
void deCoding(char c[],char A[][LENGTH]);    //��c�е��ַ���A���ܺ�д���ļ�textFile
void main()
{
	int i,j;
	char letter;
	char c[LENGTH];//���ڴ������ж�ȡ�ַ���
	char B[LENGTH][LENGTH];//���ڴ�ż��ܵľ���
	char A[LENGTH][LENGTH];//���ڴ�ż��ܵľ���������
	ifstream codedFile("textData.txt");//����ǰ������
	ifstream matrixFile("matrix.txt");//�����ڼ��ܵľ���
	
	if(!codedFile||!matrixFile) cout<<"���ܴ��ļ���"<<endl;
//��ȡ�����ļ�
	matrixFile>>letter;
    for(i=0;i<LENGTH;i++)
		for(j=0;j<LENGTH;j++){
			B[i][j]=letter;
			matrixFile>>letter;
		}
//������������������
	A[0][0]=B[1][1];
	A[0][1]=-B[0][1];
	A[1][0]=-B[1][0];
	A[1][1]=-B[0][0];
//��ȡ���Ĳ�����
	codedFile>>letter;
	for(i=0;codedFile;i++){
	    c[i%LENGTH]=letter;
		if(i%LENGTH==LENGTH-1)//����ַ������ȸպ�ΪLENGTHM�������
			deCoding(c,A);
		codedFile>>letter;
	}
}

void deCoding(char c[],char A[][LENGTH])//��c�е��ַ���A���ܺ�д���ļ�textFile
{
	int cc;//����
//����,д���ļ�
	for(int i=0;i<LENGTH;i++){
		cc=0;
		for(int j=0;j<LENGTH;j++){
			cc=cc+(int)A[i][j]*(int)c[j];
			textFile<<char(cc)<<' ';
		}
	}
}
	

  

