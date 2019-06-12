/*     postfixEval���ʵ��       */

#include "postfixEval.h"

// �����׺���ʽ��������ֵ
int postfixEval::evaluate()
{
	int left, right, expValue;
	char ch;
	unsigned int i;
	// ɨ���׺���ʽֱ�����ʽ���� 
	for (i=0; i < postfix.length(); i++)
	{		
		// ȡ�õ�ǰ�ַ� 	
        ch = postfix[ i ];       
        //������ѹ���������ջ	
		if ( isdigit(ch) )        
			stk.push(ch - '0');	
		// ��Ϊ�������ȡ����ǰ����������ִ�����㣬�������ѹ�������ջ 
		else if (isOperator(ch))  
		{
			getOperands(left, right);
			stk.push(compute(left, right, ch));
		}// end if
	}// end for 
	// ��������ջ����Ϊ���������� 
	expValue = stk.top();
	stk.pop();
	return expValue;
}

// �Ӷ�ջ��ȡ�����Ҳ����� 
void postfixEval::getOperands(int& left, int& right)
{
    // ȡ���Ҳ����� 
	right = stk.top();
	stk.pop();
    // ȡ��������� 
	left = stk.top();
	stk.pop();
}

// ���� "left op right"
int postfixEval::compute(int left, int right, char op) const
{
	int value;
	switch(op)
	{
		case '+':	value = left + right;
					break;
		case '-':	value = left - right;
					break;
		case '*':	value = left * right;
					break;
		case '/':	if (right == 0)
					   cout << "postfixEval���ֳ�0���� " << endl;
					value = left / right;
					break;
		case '%':	if (right == 0)
					   cout << "postfixEval���ֳ�0����" << endl;
					value = left % right;
					break;
		case '^':	if (left == 0 && right == 0)
					   cout << "postfixEval����δ�����0^0 ����" << endl;
					value = 1;
					while (right > 0)
					{
						value *= left;
						right--;
					}
					break;
	}//end switch
	return value;
}

// �ж��Ƿ�Ϊ����� 
bool postfixEval::isOperator(char ch) const
{
	return ch == '+' || ch == '-' || ch == '*' || 
           ch == '/' || ch == '%' || ch == '^';
}
