////////////////////////////////////////////////////////////////////
// 
// FileName : Complex.cpp
// Creator  : 09388282wangda
// Date     : 2010.04.09
// Comment  : the implements for class Complex
//
////////////////////////////////////////////////////////////////////
#include "main.h"

double tempReal,tempImaginary;
Complex::Complex(){
	realPart = 1;
	imaginaryPart = 1;
}

void Complex::setData(){
	double tempReal,tempImaginary;
	cout << "������������ʵ�����鲿Ĭ����Ϊ1\n";
	cout << "��ֱ�����ʵ�����鲿���ÿո�տ�: ";
	cin >> tempReal >> tempImaginary;
	realPart = tempReal;
	imaginaryPart = tempImaginary;
	cout << endl;
}

void Complex::printData(){
	cout << "( " << realPart << " , " << imaginaryPart << " )";
}

double Complex::getImaginary(){
	return imaginaryPart;
}

double Complex::getReal(){
	return realPart;
}

void Complex::setReal(double temp){
	realPart = temp;
}

void Complex::setImaginary(double temp){
	imaginaryPart = temp;
}

void Complex::Addition(Complex y){
	extern double tempReal,tempImaginary;
	tempReal = realPart + y.getReal();
	tempImaginary = imaginaryPart + y.getImaginary();
	
}

void Complex::Subtraction(Complex y){
	extern double tempReal,tempImaginary;
	tempReal = realPart - y.getReal();
	tempImaginary = imaginaryPart - y.getImaginary();
}

void Complex::Multiplication(Complex y){
	extern double tempReal,tempImaginary;
	tempReal = realPart*(y.getReal()) - imaginaryPart*(y.getImaginary());
	tempImaginary = imaginaryPart*(y.getReal()) + realPart*(y.getImaginary());
}
