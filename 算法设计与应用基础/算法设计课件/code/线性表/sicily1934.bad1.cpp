/*****
�ƶ�С�� ballsmoving.cpp
����㣺����;��������Ӧʹ��ʹ������ʵ�ֳ�ʱ��
�Ѷȣ�1
��Ŀ����������һЩС�򣬴��������α��Ϊ1,2,3,...,n. �����ִ������ָ�1����2�������У�
1 X Y��ʾ��С��X�ƶ���С��Y����ߣ�
2 X Y��ʾ��С��X�ƶ���С��Y�ұߡ�
ָ�֤�Ϸ�����X������Y��
���磬��ʼ״̬1,2,3,4,5,6��С��ִ��1 1 4��С��1���ƶ���С��4����ߣ���2,3,1,4,5,6�������ִ��2 3 5�����3�����Ƶ�5���ұߣ���2,1,4,5,3,6��
���룺
��һ��Ϊһ������t��0<t<10������ʾ��������������ÿ�����������ĵ�һ��Ϊ��������n��0<n<=500000����m��0<m<100000����n��ʾС��ĸ�����mΪָ������������m��ÿ��Ϊһ��ָ�
�����
Ϊÿ�����������������һ�У����������������У��м��ÿո�ָ���
����������
2
6 2
1 1 4
2 3 5
5 1
2 1 5
���������
2 1 4 5 3 6
2 3 4 5 1
*/

#include <cstdio>
#include <list>
#include <algorithm>
using namespace std;

int n,m;
int num[500005];
int testCase;
int x1, y1, type1;


void operate(int type,int xNum,int yNum)
{
    int x = 0 , y = 0;
    for(int i=1 ; i <= n ; i++)
    {
        if(num[i] == xNum)
        {
            x = i;
            if(y)
                break;
        }
        if(num[i] == yNum)
        {
            y = i;
            if(x)
                break;
        }
    }
    if( type == 1)
    {   
        if( x < y)
        {
            int xNum = num[x]; 
            for(int i = x + 1 ; i < y ; i++)
                num[i-1] = num[i];
            num[y-1] = xNum;            
        }
        else
        {
            int xNum = num[x]; 
            for(int i = x - 1 ; i >= y ; i--)
                num[i+1] = num[i];
            num[y-1] = xNum;    
        }
    }
    else
    {
        if( x < y)
        {
            int xNum = num[x]; 
            for(int i = x + 1 ; i <= y ; i++)
                num[i-1] = num[i];
            num[y] = xNum;          
        }
        else
        {
            int xNum = num[x]; 
            for(int i = x - 1 ; i > y ; i--)
                num[i+1] = num[i];
            num[y+1] = xNum;    
        }
    }
}


int main()
{
    cin >> testCase ; 

    for(int i = 0 ; i < testCase ; i++)
    {
        cin >> n >> m;
        for(int j = 0 ; j <= n ; j++)
            num[j] = j;
        for(int k = 0 ; k < m ; k++)
        {
            cin >> type1 >> x1 >> y1;
            operate(type1,x1,y1);
        }

        for(int p = 1 ; p <= n ; p++)
            cout << num[p] <<" " ;
        cout << endl;
    }
}
