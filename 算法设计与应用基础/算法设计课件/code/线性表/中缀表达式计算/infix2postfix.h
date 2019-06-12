/*    infix2postfix�������       */
#ifndef INFIX2POSTFIX_H_
#define INFIX2POSTFIX_H_

#include <iostream>
#include <string>
#include <stack>
#include <map>

using namespace std;

class infix2postfix
{
	public:
		// Ĭ�Ϲ��캯��
        infix2postfix(){}; 
        // ���캯������ʼ����׺���ʽ
		infix2postfix(const string& infixExp):infix(infixExp){}; 
		// ������׺���ʽ infix  
		void setInfixExp(const string& infixExp){infix = infixExp;}; 
		// ��ȡ�����غ�׺���ʽ
		string postfixExp(); 	

	private:
		string infix;  			    // ����ת������׺���ʽ 		
		string postfix;		    	// ��׺���ʽ 
		stack<string> stk;		    // ���ڴ洢������Ķ�ջ 
		map<string, int> oper_prio; // ���ڴ洢����������ȼ� 
		void set_priority();  // �����������'+','-','*','/','%','^'�������ȼ� 
};
#endif
