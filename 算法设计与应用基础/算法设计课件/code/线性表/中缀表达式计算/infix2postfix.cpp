/*     infix2postfix���ʵ��       */

#include "infix2postfix.h"

// �����������'+','-','*','/','%','^'�������ȼ� 
void infix2postfix::set_priority()
{
	oper_prio["#"] = 1;
	oper_prio["("] = 2;
	oper_prio["+"] = 3;
	oper_prio["-"] = 3;
	oper_prio["*"] = 4;
	oper_prio["/"] = 4;
	oper_prio["%"] = 4;
	oper_prio["^"] = 5;
	oper_prio[")"] = 6;
}

// ��ȡ�����غ�׺���ʽ
string infix2postfix::postfixExp()
{
	postfix = "";
	set_priority();
	stk.push("#");
	unsigned int i = 0;
	string input, topstk;
	for ( ; i < infix.size(); )
	{
		// ȡ�����ջ��ջ�� 
        topstk = stk.top();            
        // ȡ����ǰ������ķ���
		input = infix.substr(i, 1);    
		// ��������ķ��Ų����������ֱ�ӷ���postfix
		if ( ! oper_prio[input] )      
			postfix += input;
        // ������ķ����Ǹ������
        // ��һ���ж��������ȼ��������ջ������������ȼ�		
		else 
		{
            // ������������������ȼ��������ջ������������ȼ���
            // ���ֶԴ������������Ϊ ")" ��������� 
			if ( oper_prio[input] > oper_prio[topstk] ) 
			{
                // ��������������Ϊ")",pop��ջֱ��"("������ֱ����ջ 
				if ( input.compare(")") == 0 )           
				{
					while ( topstk.compare("(") != 0 )
					{
						postfix += topstk;
						stk.pop();
						topstk = stk.top();
					}// end while
					stk.pop();
				}
				else
					stk.push(input);
			}
			// ����������������ȼ��������ջ������������ȼ���
			// ���ֶԴ������������Ϊ "��" ��������� 
            else 
			{
                // ��������������Ϊ"(",pop��ջֱ����ջ������������ȼ��ߵ����
                // ����ֱ����ջ 
				if (input.compare("(") != 0)
				{
					postfix += topstk;
					stk.pop();
					// ��ջ�󣬼�������һ��ջ��������Ƚ����ȼ� 
					continue; 
				}// end if 
				stk.push(input);
			}// end if 
		}// end else 
		// ȡ infix ����һ��Ԫ������
		++i;						  
	}// end for
	// �������ջ��ʣ��ķ���pop��ջ,ֱ������������־ "#" 
	topstk = stk.top();
	while (topstk.compare("#") != 0 )  
	{
		postfix += topstk;
		stk.pop();
		topstk = stk.top();
	}// end while
	return postfix;
}
