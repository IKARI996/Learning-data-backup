/*������Ա����push_back()��insert()ʾ��*/

#include <vector>
#include <string>
#include <cassert>
#include <iostream>
#include <algorithm>  

using namespace std;

int main() 
{
    char a[]="Bjarne Stroustrup";
    char b[]="purtsuortS enrajB"; 
      //����b�е�Ԫ��Ϊa��Ԫ�صĵ���
    vector<char> myVector1(a,a+strlen(a)),myVector2;
    vector<char> myVector3(b,b+strlen(a)),myVector4;
    vector<char>::iterator iter;

    cout << "������Ա����push_back()ʾ����" 
         << endl;
    for (iter = myVector1.begin(); iter != myVector1.end(); ++iter)
        myVector2.push_back(*iter);
      //��myVector2ĩβ�����β���myVector1��Ԫ��
    assert (myVector1 == myVector2);
   
    cout << "������������Ԫ��ʾ����" 
         << endl;
    for (iter = myVector1.begin(); iter != myVector1.end(); ++iter)
        myVector4.insert(myVector4.begin(), *iter);
      //��myVector4��㴦���β���myVector1��Ԫ��
    assert (myVector4 == myVector3);

    //ͨ�������㷨reverse()��תmyVector1
    //����֤myVector4��myVector1�ķ�ת
    reverse(myVector1.begin(), myVector1.end());
    assert (myVector1 == myVector4);
    cout << "�����ȷ��" 
         << endl;
    system("pause"); 
    return 0;
}
