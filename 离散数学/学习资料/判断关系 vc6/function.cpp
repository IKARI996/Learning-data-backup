////////////////////////////////////////////////////////////////////////
//
// FileName : function.cpp
// Creator  : wdx
// Date     : 2010-03-25 02:23
// Comment  : The implement for the relations-judging for discrete 
//			  mathematical structures
//
////////////////////////////////////////////////////////////////////////
#ifndef MAIN_H
#define MAIN_H
#endif

#include "main.h"

bool ifrflx = true, ifirflx = true, ifsym = true;
bool ifasym = true, ifatsym = true, iftran = true;
bool ifequi = true, ifpartOder = true;
extern int nn;

bool rflx(int a[SIZE][SIZE],int nn){
	for (int t = 0; t < nn; ++t)
	{	
		if (a[t][t] != 1)
		{	
			ifrflx = false;
			cout << " ԭʼ���� ���� �Է���(not reflexive)!" << endl;
			break;
		}
	}
	if (ifrflx == true)
		cout << " ԭʼ���� �� �Է���(reflexive)!" << endl;
	return true;
}

bool irflx(int a[SIZE][SIZE],int nn){
	for (int t = 0; t < nn; ++t)
	{
		if (a[t][t] != 0)
		{
			ifirflx = false;
			cout << " ԭʼ���� ���� ���Է���(not irreflexive)!" << endl;
			break;
		}
	}
	if (ifirflx == true)
	{
		cout << " ԭʼ���� �� ���Է���(irreflexive)!" << endl;
	}
	return true;
}

bool sym(int a[SIZE][SIZE],int nn){
	for (int i = 0; i < nn; i++)
	{
		for (int j = i + 1; j < nn; j++)
		{
			if (a[i][j] != a[j][i])
			{
				ifsym = false;
				cout << " ԭʼ���� ���� �ԳƵ�(not symmetric)!" << endl;
				break;
			}
		}
		if (ifsym == false)
		{
			break;
		}
	}
	if (ifsym == true)
	{
		cout << " ԭʼ���� �� �ԳƵ�(symmetric)!" << endl;
		
	}
	return true;
}

bool asym(int a[SIZE][SIZE],int nn){
	if (ifirflx == false)
	{
		ifasym = false;
		cout << " ԭʼ���� ���� �ǶԳƵ�(not asymmetric)!" << endl;
	}
	else
	{
		for (int i = 0; i < nn; i++)
		{
			for (int j = i + 1; j < nn; j++)
			{
				if (a[i][j] == a[j][i])
				{
					ifasym = false;
					cout << " ԭʼ���� ���� �ǶԳƵ�(not asymmetric)!" << endl;
					break;
				}
			}
			if (ifasym == false)
				break;
			
		}
	}
	if (ifasym == true)
	{
		cout << " ԭʼ���� �� �ǶԳƵ�(asymmetric)!" << endl;
	}
	return true;
}

bool atsym(int a[SIZE][SIZE],int nn){
	if (ifasym == false)
	{
		for (int i = 0; i < nn; i++)
		{
			for (int j = i + 1; j < nn; j++)
			{
				if (a[i][j] == a[j][i] && a[i][j] == 1)
				{
					ifatsym = false;
					cout << " ԭʼ���� ���� ���ԳƵ�(not antisymmetric)!" << endl;
					break;
				}
			}
			if (ifatsym == false)
			{
				break;
			}
		}
	}
	if (ifatsym == true)
	{
		cout << " ԭʼ���� �� ���ԳƵ�(antisymmetric)!" << endl;
	}
	return true;
}

bool tran(int a[SIZE][SIZE],int nn){
	
	int i = 0, j = 0, k = 0;
	for (i = 0; i < nn; i++)
		for (j = 0; j < nn; j++)
			if (a[i][j] == 1)
				for (k = 0; k < nn; k++)
					if (a[j][k] == 1 && a[i][k] != 1)
						iftran = false;
	if (iftran == true)
		cout << " ԭʼ���� �� ���ݵ�(transitive)!" << endl;
	if (iftran == false)
		cout << " ԭʼ���� ���� ���ݵ�(not transitive)!" << endl;
	return true;
}

bool equi(){
	if (ifrflx == ifsym && ifsym == iftran && iftran == true)
		cout << " ԭʼ���� �� �ȼ۵�(equivalent)!" << endl;
	else
	{
		cout << " ԭʼ���� ���� �ȼ۵�(not equivalent)!" << endl;
		ifequi = false;
	}
	return true;
}

bool partOrder(){
	if (ifrflx == ifasym && ifasym == iftran && iftran == true)
		cout << " ԭʼ���� �� ƫ���(partically ordered)!" << endl;
	else
	{
		cout << " ԭʼ���� ���� ƫ���(not partically ordered)!" << endl;
		ifpartOder = false;
	}
	return true;
}

void reset(){
	ifrflx = true; 
	ifirflx = true; 
	ifsym = true;
	ifasym = true; 
	ifatsym = true;
	iftran = true;
	ifequi = true;
	ifpartOder = true;
}

void printMat(int a[SIZE][SIZE],int nn){
	cout << "******************" << endl;
	for (int i = 0; i < nn; i++)
	{
		for(int j =0; j < nn; j++)
		{
			cout << a[i][j] << "  ";
		}
		cout << endl;
	}
	cout << "******************" << endl;
}

bool setDataF1(int mtx[SIZE][SIZE],int vmtx[SIZE][SIZE], int imtx[SIZE][SIZE] ,int nn){
	int i = 0,j = 0;
	char temp[SIZE];
	
	cout << "\n�����������ʱ�Ͻ������ 0 �� 1 ������!!\n";
	for(i = 0; i < nn; i++)
	{
		cout << "elements in line " << i+1 << " : ";
		cin >> temp;
		for (j = 0; j < nn; j++)
		{	
			if ((temp[j] - '0') < 0 || (temp[j] - '0') > 1)
			{
				cout << "�������Ƿ������˻ع���ѡ����棡��\n";
				system("pause");
				return false;
			}
			mtx[i][j] = temp[j] - '0';
			vmtx[j][i] = temp[j] - '0';
			if (temp[j] - '0' == 1)
				imtx[i][j] = 0;
			else
				imtx[i][j] = 1;
		}
	}
	return true;
}

bool setSize(void){
	char temp;
	cout << "���������ĳ���(���): " << endl;
	cout << "���ֵ���ó��� 6 !!" << endl;
	cout << "size = ";
	cin >> temp;
	nn = temp - '0';
	if ( nn < 2 || nn > 6)
	{
		cout << "�������Ƿ������˻ع���ѡ����棡��\n";
		system("pause");
		return false;
	}
	else
		return true;
}

void judgeRelation(void){
	system("cls");
	cout << TITLE
		 << "*******************************************************************\n"
	  	 << "                      ���㵥һ����ĸ��ֹ�ϵ\n"
		 << endl;
	
	int mtx[SIZE][SIZE];
	int vmtx[SIZE][SIZE];   // inverse
	int imtx[SIZE][SIZE];	// implement
	bool pass = true;

	pass = setSize();	
	if (pass == true)
	{
		pass = setDataF1(mtx,vmtx,imtx,nn);
	}
	
	system("cls");
	cout << TITLE
		 << "*******************************************************************\n"
		 << "                      ���㵥һ����ĸ��ֹ�ϵ\n"
		 << endl;
	if (pass == true)
	{
		cout << "ԭʼ��������:" << endl;
		printMat(mtx,nn);
		cout << "������������:" << endl;
		printMat(imtx,nn);
		cout << "���������:" << endl;
		printMat(vmtx,nn);
		cout << "\n\t����Ϊԭʼ�����жϽ׶�:\n";
		
		rflx(mtx,nn);
		irflx(mtx,nn);
		sym(mtx,nn);
		asym(mtx,nn);
		atsym(mtx,nn);
		tran(mtx,nn);
		equi();
		partOrder();
	}
	reset();
	system("pause");
	welcomeScreen1();
}

void mtxCalculate(){
	int mtx1[SIZE][SIZE];
	int mtx2[SIZE][SIZE];
	int rslmtx[SIZE][SIZE];
	bool pass = true;
	int type = 0;
	int power = 1;
	system("cls");
	cout << TITLE
	     << "*******************************************************************\n"
		 << "                       ���������߼����\n"
		 << endl;
	pass = setSize();
	cout << "                   ��ѡ������߼���˵�����:\n"
		 << "              1:����������ˣ����������ǲ�һ���ġ�\n"
		 << "              2:���������ƽ�������η�������ߴη����㡣\n"
		 << "��������: ";
	cin >> type;
	
	if (type == 1)
	{
		system("cls");
		cout << TITLE
			<< "*******************************************************************\n"
			<< "                  ����������ˣ����������ǲ�һ����\n"
			<< endl;
		if (pass == true)
		{
			cout << "�������һ�����������: \n";
			pass = setDataF2(mtx1,nn);
			cout << "������ڶ������������: \n";
			pass = setDataF2(mtx2,nn);
		}
		system("cls");
		cout << TITLE
			<< "*******************************************************************\n"
			<< "                     ��������������߼����\n"
			<< endl;
		if (pass == true)
		{
			cout << " ��һ����������: \n";
			printMat(mtx1,nn);
			cout << " �ڶ�����������: \n";
			printMat(mtx2,nn);
			detailCal(mtx1,mtx2,rslmtx,nn);
			cout << " �˻�Ϊ: \n";
			printMat(rslmtx,nn);		
		}
		system("pause");
		welcomeScreen1();
	}
	else if (type == 2)
	{
		system("cls");
		cout << TITLE
			 << "*******************************************************************\n"
			 << "               ���������ƽ�������η�������ߴη�����\n"
			 << endl;
		cout << "�������������: \n";
		pass = setDataF2(mtx1,nn);
		cout << "����������Ҫ�Ĵη���(ƽ������2����������3...���������): ";
		cin >> power;
		copyData(mtx1,mtx2,nn);
		for(int times = 1; times < power; times++)
		{
			detailCal(mtx1,mtx2,mtx1,nn);
		}
		cout << "����ľ�������: \n";
		printMat(mtx1,nn);
		system("pause");
		welcomeScreen1();
	}
	else
	{
		cout << "\n�������ˣ��������������е����ֲ������롣\n";
		system("pause");
		welcomeScreen1();
	}

	
}

bool setDataF2(int mtx[SIZE][SIZE],int nn){
	int i = 0,j = 0;
	char temp[SIZE];
	cout << "�����������ʱ�Ͻ������ 0 �� 1 ������!!\n";
	for(i = 0; i < nn; i++)
	{
		cout << "elements in line " << i+1 << " : ";
		cin >> temp;
		for (j = 0; j < nn; j++)
		{	
			if ((temp[j] - '0') < 0 || (temp[j] - '0') > 1)
			{
				cout << "�������Ƿ������˻ع���ѡ����棡��\n";
				system("pause");
				return false;
			}
			mtx[i][j] = temp[j] - '0';
		}
	}
	return true;
}

void detailCal(int mtx1[SIZE][SIZE],int mtx2[SIZE][SIZE],int rlsmtx[SIZE][SIZE],int nn){
	int tempSum = 0,ai = 0, aj= 0, bj = 0;
	for(ai = 0; ai < nn; ai++)
	{
		for(bj = 0; bj < nn; bj++)
		{
			for(aj = 0; aj < nn; aj++)    
			{
				tempSum=tempSum + mtx1[ai][aj] * mtx2[aj][bj];  
				if (tempSum == 1)
				{
					break;
				}
			}	
			rlsmtx[ai][bj]= tempSum;
			tempSum = 0;
		}
	}
}

void solveEquation(){
	system("cls");
	cout << TITLE
		 << "*******************************************************************\n"
         << "                  ���Ԫ������Ľ�(���þ���)\n"
		 << endl
		 << "���㷨Ϊ��˹�㷨�����������У����ǲ���\n"
		 << "�������̱��������ɽ⣬��ô����Ĵ𰸺ܿ��������⣬���쳣����˼��\n"
		 << "*******************************************************************\n";
	GaussSolveMtx myEqu;
    myEqu.inputEquation();
    myEqu.solveEquation();
    myEqu.outputAnswer();
	system("pause");
	welcomeScreen1();
}


void complexCal(){
	extern double tempReal,tempImaginary;
	system("cls");
	cout << TITLE
		 << "*******************************************************************\n"
		 << "                  ���㸴���ĸ�������(�ӡ�������)\n"
	     << endl;
	Complex a,b,c;
	cout << "�����õ�һ��������ֵ\n";
	a.setData();
	cout << "�����õڶ���������ֵ\n";
	b.setData();
	cout << "���������ֱ�Ϊ: \n";
	a.printData();
	b.printData();
	cout << "\n�����������:";
	a.Addition(b);
	c.setReal(tempReal);
	c.setImaginary(tempImaginary);
	c.printData();
	cout << "\n�����������:";
	a.Subtraction(b);
	c.setReal(tempReal);
	c.setImaginary(tempImaginary);
	c.printData();
	cout << "\n�����������:";
	a.Multiplication(b);
	c.setReal(tempReal);
	c.setImaginary(tempImaginary);
	c.printData();
	cout << endl;
	system("pause");
	welcomeScreen1();
}

void copyData(int mtx1[SIZE][SIZE],int mtx2[SIZE][SIZE],int nn){
	for (int i = 0; i < nn; i++)
	{
		for (int j = 0; j < nn; j++)
		{
			mtx2[i][j] = mtx1[i][j];
		}
	}
}

void closureCal(){
	int mtx[SIZE][SIZE];
	int vmtx[SIZE][SIZE];   // inverse
	int imtx[SIZE][SIZE];	// implement
	int rltmtx[SIZE][SIZE];
	int equalmtx[SIZE][SIZE];
	bool pass = true;
	// initializer for equal matrix
	for (int k = 0; k < SIZE; k++)
	{
		for (int l = 0; l < SIZE; l++)
		{
			if (k == l)
			{
				equalmtx[k][l] = 1;
			}
			else
				equalmtx[k][l] = 0;
		}
	}

	system("cls");
	cout << TITLE
		 << "*******************************************************************\n"
		 << "               ��������Է��հ����ԳƱհ������ݱհ�\n"
	     << endl;
	pass = setSize();
	if (pass == true)
	{
		pass = setDataF1(mtx,vmtx,imtx,nn);
	}
	if (pass == true)
	{
		mtxPlus(mtx,equalmtx,rltmtx,nn);
		cout << "�þ���Ϊ:\n";
		printMat(mtx,nn);
		cout << "���Է��հ�Ϊ: \n";
		printMat(rltmtx,nn);
		mtxPlus(mtx,vmtx,rltmtx,nn);
		cout << "��ԳƱհ�Ϊ: \n";
		printMat(rltmtx,nn);
		cout << "�䴫�ݱհ�Ϊ: \n";
		Warshall(mtx,rltmtx,nn);
		printMat(rltmtx,nn);
	}
	system("pause");
	welcomeScreen1();
}

void mtxPlus(int mtx1[SIZE][SIZE],int mtx2[SIZE][SIZE],int rltmtx[SIZE][SIZE],int nn){
	for (int i = 0; i < nn; i++)
	{
		for (int j = 0 ; j < nn; j++)
		{
			rltmtx[i][j] = mtx1[i][j] + mtx2[i][j];
			if (rltmtx[i][j] > 1)
			{
				rltmtx[i][j] = 1;
			}
		}
	}
}

void Warshall(int mtx[SIZE][SIZE],int rltmtx[SIZE][SIZE],int nn){
	int i,j,k;
	copyData(mtx,rltmtx,nn);
	for(k=0;k<nn;k++)
		for(i=0;i<nn;i++)                                /*warshall*/
			for(j=0;j<nn;j++)
				rltmtx[i][j] += rltmtx[i][j] + rltmtx[i][k] * rltmtx[k][j];
			
	for(i=0;i<nn;i++)
		for(j=0;j<nn;j++)
		{                                /*��rltmtx[]��0�ֵΪ1*/
			if(!rltmtx[i][j]) continue;
			else rltmtx[i][j]=1;
		}
}