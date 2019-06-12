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

int main()
{
    int t, n, m;
    int type, x, y;
    list<int> ball_list;
    list<int>::iterator pos;
    for(scanf("%d",&t);t>0;t--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1; i <= n; i++) ball_list.push_back(i);
        for( ;m>0;m-- )
        {
            scanf("%d%d%d", &type, &x, &y);
            if (type == 1)
            {
                ball_list.remove(x); /* ɾ����x */ 
                pos = find(ball_list.begin(), ball_list.end(), y); /* ����λ�� */
                ball_list.insert(pos, x); 
            } else
            {
                ball_list.remove(x); /* ɾ����x */ 
                pos = find(ball_list.begin(), ball_list.end(), y) ; 
                pos ++; /* ����λ�� */
                ball_list.insert(pos, x);               
            }
        }
        while( !ball_list.empty() )
        {
            printf("%d ", ball_list.front());
            ball_list.pop_front();
        }
        printf("\n");
    } 

    return 0;
}