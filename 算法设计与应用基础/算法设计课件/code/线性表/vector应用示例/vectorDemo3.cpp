/*��������ɾ��Ԫ��ʾ��*/

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main (void) 
{
    vector <int> vector1;
    vector <int>::iterator iter;

    //����0��9��Ԫ�����η���vector1��
    for (int i = 0; i < 10; ++i)  
        vector1.push_back(i);
    cout<<"��ǰ�����е�Ԫ�أ�";
    for(iter=vector1.begin();iter!=vector1.end()-1;++iter)
        cout<<*iter;
	cout<<endl;

    //ɾ�����һ��Ԫ��9
    vector1.pop_back();   
    cout<<"ɾ��9�����������:"<<vector1.size()<<endl;

    // ɾ����һ��Ԫ��0
    vector1.erase(vector1.begin());  
    cout<<"��ɾ��0�����������:"<<vector1.size()<<endl;

    //ɾ����ֵΪ5��Ԫ��
    remove(vector1.begin(),vector1.end(),5);
    cout<<"��ɾ��5�󣬵�ǰ�����е�Ԫ�أ�";
    for(iter=vector1.begin();iter!=vector1.end()-1;++iter)
        cout<<*iter;
    cout<<endl;
      
    // ɾ������ʣ��Ԫ��
    vector1.erase(vector1.begin(), vector1.end());  
    cout<<"ɾ������ʣ��Ԫ�غ����������:"<<vector1.size()<<endl;
    
	system("pause"); 
    return 0;
}
