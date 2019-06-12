#include <map>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;
//��� 
void put_map(map<int, string> Map, char *name) 
{ 
    map<int, string>::iterator it;
    
    cout << "The contents of " << name << " : " << endl; 
    for(it = Map.begin(); it != Map.end(); it++) 
        cout << it->first << " " << it->second << " " <<endl; 
    cout<<endl; 
} 

int main()
{
    map<int, string> mapStudent;
    mapStudent.insert(pair<int, string>(1,"student_one"));//ֻ�ɲ��벻�ɸ��� 
    mapStudent.insert(map<int, string>::value_type (2,"student_two"));//ֻ�ɲ��벻�ɸ��� 
    mapStudent[3] = "student_three";//�ɸ��ǿɲ��� 
    map<int, string>::iterator it;
    
    //���� 
    cout << "����1���������������" <<endl;
    it= mapStudent.find(1);
    if(it!= mapStudent.end())
    {
        cout<<" the value is "<<it->second<<endl;
    }
    else
    {
        cout<<"Do not Find"<<endl;
    }
    
    //�õ�����ɾ��
    cout << "�õ�����ɾ��1" <<endl;
    it = mapStudent.find(1);
    cout << "ɾ��ǰ" << endl; 
    put_map(mapStudent,"mapStudent"); 
    mapStudent.erase(it);
    cout << "ɾ����" << endl; 
    put_map(mapStudent,"mapStudent"); 
    
    //�ùؼ���ɾ��
    cout << "�ùؼ���ɾ��2" <<endl;
    cout << "ɾ��ǰ" << endl; 
    put_map(mapStudent,"mapStudent"); 
    int n = mapStudent.erase(2);//���ɾ���˻᷵��1�����򷵻�0
    cout << "ɾ����" << endl; 
    put_map(mapStudent,"mapStudent");
    
    //�õ���������Ƭ��ɾ��������map���
    cout << "�õ���������Ƭ��ɾ��������map���" <<endl;
    cout << "ɾ��ǰ" << endl; 
    put_map(mapStudent,"mapStudent"); 
    mapStudent.erase(mapStudent.begin(), mapStudent.end());
    cout << "ɾ����" << endl; 
    put_map(mapStudent,"mapStudent"); 
    //��Ƭɾ��Ҫע����ǣ�Ҳ��STL�����ԣ�ɾ��������һ��ǰ�պ󿪵ļ���
    
    system("pause");
    return 0;
}
