/*    postfixEval�������       */
#ifndef POSTFIXEVAL_H_
#define POSTFIXEVAL_H_

#include <iostream>
#include <string>
#include <stack>

using namespace std;

class postfixEval
{
	public:
        // Ĭ�Ϲ��캯��
		postfixEval(){}; 
	    // ���ú�׺���ʽ
		void setPostfixExp(const string& postfixExp){postfix = postfixExp;};
		// �����׺���ʽ��������ֵ
        int evaluate(); 
	private:
		string postfix;                // ����ֵ�ĺ�׺���ʽ 			
		stack<int> stk;	   // ��Ų������Ķ�ջ		
		void getOperands(int& left, int& right); // �Ӷ�ջ��ȡ�����Ҳ����� 
		int compute(int left, int right, char op) const;// ���� "left op right"
		bool isOperator(char ch) const; // �ж��Ƿ�Ϊ����� 
};
#endif
