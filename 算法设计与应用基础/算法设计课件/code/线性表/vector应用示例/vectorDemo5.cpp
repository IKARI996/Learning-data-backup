/* �����㷨find_if()ʾ��*/

#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

//����һ������������
class GreaterThan30 
{
public:
    bool operator()(int x) const { return x > 30; }
};

int main()
{
	vector <int> myVector;
    vector <int>::iterator iter;

    //����Ԫ��ֵΪ0��9��ƽ��
    for (int i = 0; i < 10; ++i)
        myVector.push_back(i * i);
	cout<<"������������Ԫ�أ�";
    for(iter = myVector.begin();iter!=myVector.end();++iter)
        cout<<*iter<<" ";
	cout<<endl;

    //���ҵ�һ������30��Ԫ��
    vector<int>::iterator where;
    where = find_if(myVector.begin(), myVector.end(),
                  GreaterThan30());

    //������
    if (where == myVector.end())
        cout<<"û���ҵ�����30������"
            <<endl;
    else
        cout << "��һ������30����Ϊ��" 
             <<*where
             <<endl;

	system("pause");
    return 0;
}
