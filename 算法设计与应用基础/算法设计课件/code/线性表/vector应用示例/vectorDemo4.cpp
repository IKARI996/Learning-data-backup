/* �����㷨findʾ��*/

#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>  

using namespace std;

int main()
{
    char str[]="I am a good girl";
   
    vector <char> myVector(str,str+strlen(str));

    //���ҵ�һ�γ��ֵ�Ԫ��g
    vector<char>::iterator
      where = find(myVector.begin(), myVector.end(), 'g');

    assert (*where == 'g' && *(where + 1) == 'o');
    cout << "���ҽ����ȷ��." << endl;

	system("pause");
    return 0;
}
