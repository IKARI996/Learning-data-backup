// ���������ڽ�10������ת��Ϊ���������������2��16֮�䣩 
// �����û�����0ʱ���� 
#include <iostream>
#include <stack>
#include <string>

using namespace std;
// ����ԭ������
string dec2base( int num, int base);

int main()
{
	int num, base;	// decimal number and base

	cout << "�������ת���Ľ���(����2��16֮��)������0����" << endl;
	cin >> base;

	// continue until the user enters a base of 0
	while (base != 0)
	{
        cout << "�������ת����ʮ������" << endl; 
        cin >> num; 
		cout << " ʮ������ " << num << " ת��Ϊ " << base << " ������Ϊ "
			  << dec2base(num, base) << endl;

		cout << "�������ת���Ľ���"
		  << "(����2��16֮��)������0����" << endl;
	cin >> base;
	}// end while
	return 0;
}
// ��10������ת��Ϊ�����������������2��16֮�䣩
string dec2base( int num, int base)
{
	// digitCharΪ�ֿ��ַ�����numStr���ڴ洢����ַ���
	string digitChar = "0123456789ABCDEF", numStr = "";
	// ������ʱ�洢�����Ķ�ջ
    stack<char> stk;
    
	// ����ֱ������Ϊ�� 
	do
	{		
		// ������ѹ���ջ
        stk.push(digitChar[num % base]);  
		num /= base;
	} while (num != 0);	
	
	// ��������ջ��ջ����������ַ�����
    while (!stk.empty()) 
	{
		numStr += stk.top();
		stk.pop();	
	}//end while 
	return numStr;
}
