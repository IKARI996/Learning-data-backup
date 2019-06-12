// ������ʵ�ֶ�һ�����н��л����������
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
// ������ivec���� d λ�Ļ�������ĺ�������
void radixSort(vector<int> &ivec, int d);

// ������
int main()
{
	vector<int> ivec;
	int i = 0, tmp, d;
	// ��������л�����������У�����һ����������
	cout << "��������Ҫ���л�����������У��ÿո�������������0��ʾ������룩\n";
	cin >> tmp;
	while ( tmp != 0 )
	{
		ivec.push_back(tmp);
		cin >> tmp;
	}
	cout << "\n��������Ҫ���л�����������λ����" << endl;
	cin >> d;
	// �������л���
	cout << "\n����Ĵ����л�������������ǣ�" << endl;
	for ( i = 0; i < ivec.size(); ++i)
		cout << ivec[i] << "  ";
	cout << endl;
	// ����radixSort�������л�������
	radixSort(ivec, d);
	// ����������������ʾ
	cout << "\n�������������õ�������Ϊ��" << endl;
	for ( i = 0; i < ivec.size(); ++i)
		cout << ivec[i] << "  ";
	system("pause"); 
	return 0;
}

// ������ivec���� d λ�Ļ�������
void radixSort(vector<int> &ivec, int d)
{
	int i, j;
	int digit = 1;			
    // 10����Ӧ��λ�Ķ��� 		
	queue<int> digitQueue[10];
	for ( i = 0; i < d; ++i)		
	{
		// �������е������ν�����Ӧλ�Ķ�����
		for (j = 0; j < ivec.size(); j++)
			digitQueue[(ivec[j] / digit) % 10].push(ivec[j]);
			
		// �����пռ���գ�����������������������
        j = 0;
		for (int digitVal = 0; digitVal < 10; ++digitVal)
			while (!digitQueue[digitVal].empty())
			{
				ivec[j] = digitQueue[digitVal].front();
				digitQueue[digitVal].pop();
				j++;
			}
			
		// ÿ����һλ�������򣬾ͽ��м��������ʾ
		cout << "������ " << i << "�������õ������У�" << endl;
		for ( j = 0; j < ivec.size(); ++j)
			cout << ivec[j] << "  ";
		cout << endl;
		
		// �Ӹ�λ����ʼ��ֱ����dλ��
		digit *= 10;
	}
}
