/* list��Ա����sort()ʾ�� */

#include <list>        //��vector��Ϊlist
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
    list <string> studentName;
    list <string>::iterator studentIterator;
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
    studentName.sort();    //�˾������޸�
    cout << "������ѧ��������" 
         << endl;
    for_each(studentName.begin(), studentName.end(), PrintF );
    
	system("pause");
	return 0;
}
