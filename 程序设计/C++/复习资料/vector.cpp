#include <iostream> 
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

//��������� 
void put_vector(vector<int> arr, char* name)
{
    std::vector<int>::iterator it;  
    
    cout << "The contents of " << name << " : "; 
    for(it=arr.begin(); it!=arr.end();++it )
    {
        cout << *it << " ";
    }
    cout << endl; 
}

int main()
{
    vector<int> arr;//��ʼ��һ��������
    vector<int> arr2(10,-1);//��ʼ�����ȵ�vector
    vector<int> arr2_copy(arr2);//������ʼ��
    vector<int>::iterator it;
    //β������ 
    cout << "push_back(6) and push_back(8) and push_back(3) and push_back(8)" << endl;
    arr.push_back(6);
    arr.push_back(8);
    arr.push_back(3);
    arr.push_back(8);
    put_vector(arr,"arr");
    //���������� 
    cout << "erase the third" << endl; 
    arr.erase(arr.begin()+2);
    put_vector(arr,"arr");
    //���������
    cout << "insert 4 into the third" << endl; 
    arr.insert(arr.begin()+2,4);
    put_vector(arr,"arr");     
    //����β��һ�� 
    cout << "pop_back" << endl; 
    arr.pop_back();
    put_vector(arr,"arr");     
    //����ֻ�ܱȽ��������ͣ���Ҫ�Ƚ��Զ�����ģ�����������д�ϱȽϺ�����д����Ѱ
    sort(arr.begin(),arr.end()); // ��С����
    put_vector(arr,"arr"); 
    
    system("pause"); 
    return 0; 
}
