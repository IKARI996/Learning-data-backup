/* ���ó�Ա����empty()���ж������Ƿ�Ϊ��*/

#include <vector>
#include <iostream>

using namespace std;

int main() 
{
	vector<char> myVector;
    cout << "��ʾ��δ�������:" << endl;
	
	//����������Ƿ�Ϊ��
    if(myVector.empty()==1)
		cout << "����Ϊ�գ�" << endl;   //ע��˴�����ִ���κθ��Ӳ���
    else
		cout << "������Ϊ�գ�" <<endl;

	system("pause");
    return 0;
}
