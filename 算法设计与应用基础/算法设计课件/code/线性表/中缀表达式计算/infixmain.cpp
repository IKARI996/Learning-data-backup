// ����׺���ʽ��������������

#include "infix2postfix.h"
#include "postfixEval.h"

int main()
{
    infix2postfix iexp;
    string infix, postfix;
    postfixEval pexp;
    cout << "*****������ģ��һλ������׺���ʽת��Ϊ��׺���ʽ��������*****" << endl; 
	cout << "������һ��1λ������׺���ʽ( q to quit!) : " << endl;
	cin >> infix;
	while (infix.compare("q") != 0)
	{		
		cout << "���������׺���ʽΪ: " << infix << endl;
		iexp.setInfixExp(infix);
		// �����Ӧ�ĺ�׺���ʽ����� 
		postfix = iexp.postfixExp();			
		cout << "����Ӧ�ĺ�׺���ʽΪ " << postfix << endl;			
		// �����׺���ʽ��ֵ����� 
		pexp.setPostfixExp(postfix);			
		cout << "���ʽ������ֵ = " 
			 << pexp.evaluate() << endl << endl;
		cout << "��������һ��1λ������׺���ʽ( q to quit!) : " << endl;
		cin >> infix;
	}  
	return 0;
}
