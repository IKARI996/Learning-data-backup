/* �����ı������ʾ�� */

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

//����һ����������
void PrintF(string& StringPrint)
{
    cout << StringPrint << endl;
}

int main (void) 
{
    //����һ����������Ԫ��Ϊһ�ܵ�����
    vector <string> week;
    week.push_back (" Monday ");
    week.push_back (" Tuesday ");
    week.push_back (" Wednesday ");
    week.push_back (" Thursday ");
    week.push_back (" Friday ");
    week.push_back (" Saturday ");
    week.insert(week.begin()," Sunday ");

    //�������
    for_each (week.begin(), week.end(), PrintF);

	system("pause");
    return 0;
}
