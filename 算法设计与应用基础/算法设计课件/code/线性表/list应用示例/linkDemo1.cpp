/* List�ĵ�������vector�ĵ������ıȽ�*/

#include <list>
#include <vector> 
#include <string>
#include <iostream>
#include <algorithm>  

using namespace std;

int main() 
{
    int m='a';
        // ��ʽ����ת����'a'��ASCII��ת��Ϊ���� 
    list <char> myList;
    list <char>::iterator link_iter;
    vector <char> myVec;
    vector <char>::iterator v_iter; 

    //���ַ�abcdef�������
    for (int i=0;i<6;i++)
    {
        // ��ʽ����ת��������ת��ΪASCII��
        myList.push_back(m+i);
        myVec.push_back(m+i);
    } 

    //�ж�ɾ���ַ���ĵ������Ƿ���Ч
    link_iter = find(myList.begin(), myList.end(), 'c');
    cout<<"ɾ��link��һ���ڵ�Ԫ��"<<endl; 
    myList.erase(link_iter++); 
    if (*link_iter=='d')
        cout<<"��ʱ��������ָԪ��Ϊ��"
		    <<*link_iter
            <<endl
            <<"ɾ��Ԫ��֮�󣬵�����������Ч"
			<<endl
			<<endl;

    v_iter = find(myVec.begin(), myVec.end(), 'c');
    cout<<"ɾ��vector��һ���ڵ�Ԫ��"<<endl; 
    myVec.erase(v_iter++); 
    if (*v_iter=='d')
        cout<<*v_iter
            <<endl
            <<"������������Ч"<<endl;
    else
        cout<<"��ɾ��Ԫ��֮��ĵ�������Ч"<<endl; 

    system("pause"); 
    return 0;
}

