/* list�ĳ�Ա����unique()ʾ�� */

#include <list>
#include <iostream>
#include <algorithm>

using namespace std;

void PrintF ( int& PrintInt ) 
{ 
    cout << PrintInt << endl; 
};

//����һ����Ϊunique()�Ƚϲ���������
class EvenPair{
public:
    bool operator()(int div1,int div2)
    {
        return ! (div2 % div1);
    }
};
int main()
{
    int myArray[]={5,2,9,4,8,2,3,4,9};

    list <int> myList1(myArray,myArray+9);
    list <int> myList2(myList1);  

    //ɾ����ͬ������Ԫ��
    myList1.unique();   //û������������Ԫ��
    cout<<"ɾ����Ľ��Ϊ��"
        <<endl;
    for_each(myList1.begin(),myList1.end() ,PrintF);

    //�����ɾ����ͬ������Ԫ��
    myList1.sort();
    myList1.unique();   //ɾ��2��4��9
    cout<<"������ɾ����Ľ��Ϊ��"
        <<endl;
    for_each(myList1.begin(),myList1.end(),PrintF);

    myList2.unique( EvenPair());   //ɾ��8
    cout<<"ɾ���ڶ���Ԫ���ܱ���һ������������Ԫ�غ�Ľ��Ϊ��"
        <<endl;
    for_each(myList2.begin(),myList2.end() ,PrintF);

	system("pause");
    return 0;
}
