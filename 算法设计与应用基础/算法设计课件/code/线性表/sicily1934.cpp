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

#include <stdio.h>
#include <string.h>
#define maxn 500001

struct ball {
    int nxt, pre;
} balls[maxn];

int main() {
    int t, i, x, y, n, m, type;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        for (i=0;i<=n;++i) {
            balls[i].nxt = i + 1;
            balls[i].pre = i - 1;
        }
        balls[0].pre = n;
        balls[n].nxt = 0;
        
        while (m--) {
            scanf("%d%d%d", &type, &x, &y);
            balls[balls[x].nxt].pre = balls[x].pre;
            balls[balls[x].pre].nxt = balls[x].nxt;
            if (type == 1) {
                balls[x].pre = balls[y].pre;
                balls[x].nxt = y;
            } else {
                balls[x].nxt = balls[y].nxt;
                balls[x].pre = y;
            }
            balls[balls[x].pre].nxt = x;
            balls[balls[x].nxt].pre = x;
        }
        
        x = balls[0].nxt;
        while (x != 0) {
            printf("%d ", x);
            x = balls[x].nxt;
        }
        puts("");
    }
    return 0;
}
