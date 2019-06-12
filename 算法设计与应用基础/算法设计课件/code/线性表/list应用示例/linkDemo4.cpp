/* list�ĳ�Ա����splice(��ʾ�� */

#include <list>
#include <iostream>
#include <algorithm>

using namespace std;

void PrintF ( int& PrintInt ) 
{ 
    cout << PrintInt << endl; 
}

int main()
{
    int myArray[]={23,45,89,43,56,27,81,10,51,32,78,74};

    list <int> myList1(myArray,myArray+12);
    list <int> myList2;
    list <int>::iterator\
		iter1 = find(myList1.begin(),myList1.end(),45);
      //ʹ������ָ��myList1�ĵڶ���Ԫ��
    list <int>::iterator\
		iter2 = find(myList1.begin(),myList1.end(),81);
      //ʹ������ָ��myList1�ĵ��߸�Ԫ��
    list <int> myList3(iter2,myList1.end());
      //��myList1���߸�Ԫ��֮������乹��һ���±�

    myList2.splice(myList2.end(),myList1,myList1.begin());
    cout<<"��myList1�ĵ�һ��Ԫ���Ƶ�myList2�Ľ����"
        <<endl;
    for_each(myList2.begin(), myList2.end(), PrintF);

    //����ע�������iter2��ָ��Ԫ�ز����μӲ���
    myList2.splice(myList2.end(),myList1,iter1,iter2);
    cout<<"������myList1�ĵڶ�����������Ԫ���Ƶ�myList2�Ľ����"
        <<endl;
    for_each(myList2.begin(), myList2.end(), PrintF);

    myList2.splice(myList2.end(),myList3);
    cout<<"������myList3��ȫ��Ԫ���Ƶ�myList2��ȥ�Ľ����"
        <<endl;
    for_each(myList2.begin(), myList2.end(), PrintF);

    system("pause");
	return 0;
}
