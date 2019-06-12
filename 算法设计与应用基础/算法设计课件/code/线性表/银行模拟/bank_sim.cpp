// ���з���ģ������Ա�Ĺ˿��Ŷ�ģ��

#include <iostream>
#include <queue>
#include <time.h>
#include "customer.h"

using namespace std;

const int MAX_CASHIERS = 6;   // �����������Ա��

void sim(int cashiers, double probOfArrival, int serviceTime, int lastTime);

int main()
{
    // �˿͵ĵ������ 
	double probOfArrival;
	// ÿ���˿ͽ��ܷ��������ʱ��
	int serviceTime;
	// ����ģ���������ʱ��
	int lastTime;
	
	cout << "*****��������Ƕ����ж����Ա�Ĺ˿��Ŷ�ģ�͵�ģ��***********\n" << endl;
	// ģ���ʼ�������������
	cout << "������˿͵ĵ������: ";
	cin >> probOfArrival ;
    cout << "������ÿ���˿ͽ��ܷ�������Ҫ��ʱ��(��λ����):  "; 
    cin >> serviceTime; 
	cout << "����������������ʱ�䣨��λ���֣�: ";
	cin >> lastTime;
	cout << endl;   

	// ��Է���Ա�ĸ������з��棬
    // �ó���ͬ��������Աʱ�˿ͽ��ܷ��񣨰����Ŷӣ������ 
	for ( int cashiers = 1; cashiers <= MAX_CASHIERS; ++cashiers )
		sim(cashiers, probOfArrival, serviceTime, lastTime);
	system("pause"); 
	return 0;
}

//  ģ�⺯��
void sim(int cashiers, double probOfArrival, int serviceTime, int lastTime)
{
    // ���ڴ洢�˿͵������ȥ��ʱ��
	Customer customer;				
	// �˿��ŶӶ���
	queue<Customer> waitQueue;		
	// �����˷���Ĺ˿�����
	int servedCustomers;            
	// ���н����˷���Ĺ˿͵ĵȴ�ʱ����ɵ�����
	vector<int> waitTime;           
	// �ܹ��ķ���ʱ��
	int totalServiceTime = 0;       
    // ����Ա�Ŀ���ʱ�䣨��ʱ���£� 
	int cashierTime[MAX_CASHIERS];
	
	// ��������ӳ�ʼ��
	srand(time(NULL));
	// ���������
	double rnd;	

	int count;
	// ��ÿ������Ա��ʱ����г�ʼ��
	for (count = 0; count < cashiers; ++count)
		cashierTime[count] = 0;
		
	//���濪ʼ���з��棬���ÿ����λʱ��ɨ��һ��
	for ( int t = 0; t < lastTime; t += 1)
	{
		// С�ڵ�����ʣ�˵���˿͵�����˿����
		if ((rnd = (rand()%1000)/1000.0 ) <= probOfArrival)
		{
			customer.setArrivalTime(t);
			waitQueue.push(customer);
		}
			
		// �Է���Ա������һɨ�裬�ж����Ƿ��п�, ���Ҷ����Ƿ�ǿ�
		for (count = 0; count < cashiers; ++count)
		{
			if ( (cashierTime[count] <= t) && !waitQueue.empty() 
				  && (cashierTime[count] < lastTime) )
			{
				// �˿ͳ��ӣ������ϵõ�����
				customer = waitQueue.front();
				waitQueue.pop();
				int finishService = t + serviceTime;
				// ���ù˿���ȥʱ��
				customer.setDepartureTime(finishService);
				// �˿͵ȴ�ʱ��
				waitTime.push_back( t - customer.getArrivalTime());
				// �˿������ѵ���ʱ��
				totalServiceTime += customer.totalTime();
				// ���ø÷���Ա��һ������ʱ��
				cashierTime[count] = finishService;
			}//end if 
		}// end for
	}// end for
	// �����˷���Ĺ˿�����
	servedCustomers = waitTime.size();
	// ������������˷���Ĺ˿͵����ȴ�ʱ��
	int i = 0, maxWaitTime = waitTime[0];
	for (; i < servedCustomers; i++)
		if (waitTime[i] > maxWaitTime)
			maxWaitTime = waitTime[i];

	double averageWaitTime = (double) totalServiceTime / servedCustomers - serviceTime;
	// �����ʾ
	cout << "������Ա����Ϊ                       " << cashiers << " ʱ��" << endl;	
	cout << "�õ�����Ĺ˿���Ϊ                   " << servedCustomers << endl;
	cout << "ƽ��ÿ������Ա�Ӵ��Ĺ˿���Ϊ         " << servedCustomers / cashiers << endl;
	cout << "�õ�����Ĺ˿������ĵȴ�ʱ��Ϊ     " << maxWaitTime << endl;
	cout << "�õ�����Ĺ˿�����Ҫ��ƽ���ȴ�ʱ��Ϊ " << averageWaitTime << endl;
	cout << "��ʱ��δ�õ�����Ĺ˿���Ϊ           "  << waitQueue.size() << endl;
	cout << endl;
}
