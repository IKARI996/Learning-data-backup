/* �����㷨sort()ʾ�� */

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

void PrintF(string& StringPrint) 
{ 
    cout << StringPrint << endl;
}
int main (void) 
{
    //����һ��ѧ������
    vector<string> studentName;
    vector<string>::iterator studentIterator;
    studentName.push_back("����");
    studentName.push_back("���");
    studentName.push_back("�⳱");
    studentName.push_back("����");
    studentName.push_back("����");
    studentName.push_back("�ܿ�");

    //���δ�����ѧ������
    cout << "����ǰ��ѧ��������" 
         << endl;
    for_each(studentName.begin(), studentName.end(), PrintF );

    //�������������ѧ������
    sort(studentName.begin(), studentName.end());
    cout << "������ѧ��������" 
         << endl;
    for_each(studentName.begin(), studentName.end(), PrintF );

	system("pause");
    return 0;
}
