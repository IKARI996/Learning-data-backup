#include<iostream.h>
#include<fstream.h>

const int LENGTH=2;
ofstream codedFile("codedData.txt"); //���ܺ���ļ�
void coding(char c[],char A[][LENGTH]);    //��c�е��ַ���A���ܺ�д���ļ�codedFile
void main()
{
	int i,j;
	char letter;
	char c[LENGTH];
	char A[LENGTH][LENGTH];//���ڴ�ż��ܵľ���
	ifstream textFile("textData.txt");//����ǰ������
	ifstream matrixFile("matrix.txt");//�����ڼ��ܵľ���
	
	if(!textFile||!matrixFile) cout<<"���ܴ��ļ���"<<endl;
//��ȡ�����ļ�
	matrixFile>>letter;
    for(i=0;i<LENGTH;i++)
		for(j=0;j<LENGTH;j++){
			A[i][j]=letter;
			matrixFile>>letter;
		}
//��ȡ���Ĳ�����
	textFile>>letter;
	for(i=0;textFile;i++){
	    c[i%LENGTH]=letter;
		if(i%LENGTH==LENGTH-1)//����ַ������ȸպ�ΪLENGTHM�������
			coding(c,A);
		textFile>>letter;
	}
	//���⴦��
	if(i%LENGTH!=0){//��������ַ������Ȳ���LENGTH������ո��ټ���
        for(j=i;j<=LENGTH;j++)
			c[j]=' ';
		coding(c,A);
	}
}

void coding(char c[],char A[][LENGTH])//��c�е��ַ���A���ܺ�д���ļ�codedFile
{
	long int cc;//����
//����,д���ļ�
	for(int i=0;i<LENGTH;i++){
		cc=0;
		for(int j=0;j<LENGTH;j++){
			cc=cc+(int)A[i][j]*(int)c[j];
			codedFile<<cc<<' ';
		}
	}
}
	

  

