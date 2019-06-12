#ifndef MAIN_H
#define MAIN_H
#endif

#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <iomanip>
#include <time.h>
#include <conio.h>

#define SIZE 6
#define PRELIMIT 0.0000000001           // if a number is less than 0.0000000001, then make it zero
#define TITLE "                     ��ѧ����ʵ�ó��� V3.3.0 by wdx\n"
#define HELPTITLE "                      �����ĵ� V1.1 by wdx\n"
using namespace std;

void welcome(void);
bool rflx(int a[SIZE][SIZE],int n);		// determine whether the given matrix is reflexive
bool irflx(int a[SIZE][SIZE],int n);	// determine whether the given matrix is irreflexive
bool sym(int a[SIZE][SIZE],int n);		// determine whether the given matrix is symmetric
bool asym(int a[SIZE][SIZE],int n);		// determine whether the given matrix is asymmetric
bool atsym(int a[SIZE][SIZE],int n);	// determine whether the given matrix is antisymmetric
bool tran(int a[SIZE][SIZE],int n);		// determine whether the given matrix is transitive
bool equi(void);						// determine whether the given matrix is equivalence
bool partOrder(void);					// determine whether the given matrix is partially ordered
void reset(void);						// reset all the bool value to true
void printMat(int a[SIZE][SIZE],int n); // print the matrix and inverse or implement
bool setDataF1(int mtx[SIZE][SIZE],int vmtx[SIZE][SIZE], int imtx[SIZE][SIZE] ,int n);	// initialize the very beginning data for function 1
bool setDataF2(int mtx[SIZE][SIZE],int n);												// initialize the very beginning data for function 2
bool setSize(void);						// set the size of the matrix
void welcomeScreen1(void);				// function selected
void upgradeInfor(void);				// show the upgrade information
void end(void);							// end the program
void judgeRelation(void);				// judge the relation ~~ function 1
void mtxCalculate(void);				// for function 2
void detailCal(int mtx1[SIZE][SIZE],int mtx2[SIZE][SIZE],int rlsmtx[SIZE][SIZE],int n); // the details in matrix times matrix
void solveEquation(void);				// for function 4
void complexCal();						// for function 3
void helpDocSelect();				    // for function a
void F1Help();							// help document for function 1
void F2Help();							// help document for function 2
void F3Help();							// help document for function 3
void F4Help();							// help document for function 4	
void F5Help();                          // help document for function 5
void aboutMe();							// something about wdx	
void thankList();						// thankList for function d
void copyData(int mtx1[SIZE][SIZE],int mtx2[SIZE][SIZE],int n);							// copy the data from one matrix to another			
void closureCal();						// for function 5
void mtxPlus(int mtx1[SIZE][SIZE],int mtx2[SIZE][SIZE], int rltmtx[SIZE][SIZE],int n);							// the function for adding one logical matrix to another
void Warshall(int mtx[SIZE][SIZE],int rltmtx[SIZE][SIZE],int n);                        // warshall alg
void Tetris();							// for game function
void Welcome(void);			//��ӭ���棬���ڽ��ܰ��������Ͱ�Ȩ��Ϣ
void Select(void);			//���ڳ�ʼ��ѡ���ѶȺ��ٶ�
void Left(void);			//�������Ƶĺ���
void Right(void);			//�������Ƶĺ���
void Down(void);			//�������Ƶĺ���
void Display(void);			//��ʾ����ĺ���
void GotoXY(int x, int y);	//��λ����ĺ���
void Block_Random(void);	//���ѡ�񷽿�ĺ���
void Fill_Block(void);		//������Ϸ�ռ�ĺ��� 
void Clean_Block(void);		//�����Ϸ����ĺ���
void Change_Block(void);	//ʵ�ֱ��εĺ���
void Pause(void);			//ʵ����ͣ�ĺ���
void Check_Block(void);		//�����ײ������
void End(void);				//�����ĺ���
void Check_Line(void);		//����С����Ҽӷֵĺ���
void Clean_Line(int l);		//��ȥ�еĺ���


class Complex{
	double realPart;
	double imaginaryPart;
public:
	Complex();
	void setData();
	void setReal(double temp);
	void setImaginary(double temp);
	double getReal();
	double getImaginary();
	void printData();
	void Addition(Complex y);
	void Subtraction(Complex y);
	void Multiplication(Complex y);
};

class GaussSolveMtx{
private:
	vector< vector <double> > equationMtx;
	vector<double> answerMtx;
	unsigned int mn;
public:
	void inputEquation();
	void solveEquation();
	void outputAnswer();
};