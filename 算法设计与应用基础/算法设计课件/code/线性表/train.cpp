//  ���������ڲ��Ե����г�˳�����ȷ��  
#include <iostream>
#include <string>
#include <algorithm>
#include <stack>
 
using namespace std;
// ����ԭ������ 
void trainJudge(const string &istr);

int main()
{    
	string istr;
	cout << "������ϣ�����ȳ������г�˳��"
         <<"(���Ȳ�����6�����������������1��6֮��)";
    cout << "(q�Ƴ�����)" << endl;
	cin >> istr;
	
	while( istr != "q")
	{
           // ���� trainJudge�����жϵ����Ƿ�ɹ��������ؽ�� 
           cout << "������������жϵĹ��̣�" << endl; 
           trainJudge(istr);
           cout << "������ϣ�����ȳ������г�˳��"
         <<"(���Ȳ�����6�����������������1��6֮��)";
    cout << "(q�Ƴ�����)" << endl;
           cin >> istr;
     }		
	return 0;
}

// �жϳ�������˳����ȷ���ļ����� 
void trainJudge(const string &istr)
{
    string numbs = "123456";
    string ostr, cstk;
    int i = 0, j;
	string strleft = numbs;
	stack<char> stk;
	stk.push('#');
	for (; i < istr.length(); ++i)
	{
        // ��������ȳ����Ų��ǽ��� 1 �� 6 ֮�䣬���� 
       if (numbs.find(istr[i]) > 6)
        {   cerr << "��������һ�����������: " << istr[i] 
                 << " ����λ���� "<< i << " ������������������" << endl;
            return;
        }
        
        // ���ȹ����еĶ�ջ���ѵ��ȳ����������� 
        cout << " ����ջ = " << cstk << " ��� = " << ostr << endl;
        // ��������ȳ�����ջ������ֱ����ջ���� 
        if (istr[i] == stk.top())
        {
             ostr += stk.top();
             stk.pop();
             cstk.erase(cstk.length()-1, cstk.length());
             continue;
        }
        // �����ȳ�������ջ�������δ�����ȵĳ�����Ѱ�� 
        j = strleft.find(istr[i]);
        // �����ȳ�����Ҳ���� δ�����ȵĳ����У�˵������ʧ�� 
        if ( j < 0 )
        {
             cout << " ���Ȳ��ܳɹ�ʵ�֣�����������һ���µĵ���˳��" 
             << endl << endl;
            return;
        }
        
        //  �����ȳ�����δ�����ȵĳ����У����Խ��е���
        // �Ȱ�ǰ������δ���ȳ�����ջ���ٽ������ȳ�����ջ 
        for (int k = 0; k <= j; k++)
        {
            stk.push(strleft[k]);
            cstk += strleft[k];
        }
        ostr += stk.top();
        stk.pop();
        cstk.erase(cstk.length()-1, cstk.length());
        // ʣ���δ�����ȳ����ĺ��� 
        strleft = strleft.substr(j+1, 5); 
    }
       // ������ȳɹ�  
       cout << "\n ���Ⱥ�õ���� = " << ostr << " ���ͬ�� "  
            << "���ȵ��������� = " << istr << endl;
       cout << "\n Congratulations�������ȳɹ���" << endl << endl;
}
