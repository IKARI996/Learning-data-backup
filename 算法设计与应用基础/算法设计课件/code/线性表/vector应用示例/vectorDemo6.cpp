/* �����㷨search()ʾ��*/

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int main ( void )
{ 
    vector <char> targetChar;
    vector <char> vectorOfChar;
    
    //������Ҫ���ҵ��ַ�����������blue
    targetChar.push_back('b');
    targetChar.push_back('l');
    targetChar.push_back('u');
    targetChar.push_back('e');

    //���ɱ���������
    vectorOfChar.push_back('r');
    vectorOfChar.push_back('e');
    vectorOfChar.push_back('d');
    vectorOfChar.push_back('b');
    vectorOfChar.push_back('l');
    vectorOfChar.push_back('u');
    vectorOfChar.push_back('e');

    //��redblue�в���blue
    vector<char>::iterator where = 
    search(vectorOfChar.begin(), vectorOfChar.end(), 
            targetChar.begin(), targetChar.end());

    if ( where !=vectorOfChar.end())
    cout << "�ҵ��˵���blue!" << endl;

	system("pause");
    return 0;
}
