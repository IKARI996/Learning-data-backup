// ��������ù�����������㷨���ũ���������
#include<iostream>
#include<queue>
#include<vector>
#include<bitset>
#include<deque>

using namespace std;

// �����ߣ���4�ֶ���
enum Wader
{
	cabbage,		// Ĭ��Ϊ0
	goat,			// Ĭ��Ϊ1
	wolf,			// Ĭ��Ϊ2
	farmer			// Ĭ��Ϊ3	
};

// ����״̬���ͣ�4bit�ֱ��Ӧ4�ֹ��Ӷ���
typedef bitset<4> bitvec;

// �ж�״̬�Ƿ�ȫ
bool is_safe( const bitvec&);
// �жϴ����ӵĶ����Ƿ���ũ���ںӵ�ͬһ��
bool withFarmer(int, bitvec& );

// ���õ�������·��
void findRoute(vector<int> & path)
{
	// �����ֵĸ���״̬
	queue<int> discovering;	
	// ���ӵĳ�ʼ״̬Ϊ 0000
	discovering.push(0x00);	
	// ��ʼ״̬·����ʼ��
	path[0]=0;
	// ֻҪ������һ��״̬���Ե��������δ��������״̬
	while (!discovering.empty() && (path[15] == -1))
	{	
		// ��ȡ��ǰ������״̬
		// ��ʽ����ת����int -> bitset<4>
		bitvec curState = discovering.front();
		// ����Ԫ�ص���
		discovering.pop();
		// ũ�򵽺Ӷ԰�������ũ��Ķ���
		// ���γ����ǡ��ײˡ���
		for (int companion = 0; companion <= 3; ++companion)   
		{
			// ��ũ����ӵ�ֻ������ũ����ͬһ�ӱߵ�
			if (withFarmer(companion,curState))
			{
				// ũ����Ӻ����״̬
				bitvec nextState = curState;
				// ũ��ض�����
				nextState.flip(farmer);
				// �������ũ�򵥶����ӵ�����
				if(companion != farmer)					
					nextState.flip(companion);
				// ��״̬ʸ��ת��Ϊ��������Ϊ����Ԫ�غ�·���±�
				int nextIndex = nextState.to_ulong();
				// �����״̬�ǰ�ȫ�ģ�������δ�����֣�
				// ����״̬������һ״̬����
				if (is_safe(nextState) && ( path[nextIndex] == -1) )
				{
					// ������ǰ״̬����һ״̬����ϵ
					path[nextIndex] = curState.to_ulong();
					// ����״̬�����
					discovering.push(nextIndex);
				}//end if
			}// end if
		}//end for
	}// end while
	// ״̬��㣬û��ǰ������Ϊ-1��
	//path[0] = -1;
}

// ��ʾʵ�ʷ���
// �ӳ���״̬����ת��Ϊ������
void displayRoute(const vector<int>& path)
{
	// �����1111��״̬û��ǰ��
	// ��û�ܹ��ɹ�����Ŀ��״̬
	if (path[15] == -1)
	{
		cout << "�ù��������޽�" << endl;
		return;
	}
	// ��������ʾ��·��ת��Ϊ����ʸ����ʾ��״̬·��
	// �洢״̬·��������
	deque<bitvec> statePath;
	for(int i=15; i >0; i=path[i])
		statePath.push_front(i);
			// ������룬���·���ӳ�ʼ״̬��Ŀ��״̬��ת��
			// ��ʽ����ת����int -> bitset<4>
	// ����ʼ״̬����
	statePath.push_front(0);
	// ��ǰ״̬��������һ״̬������ת������
	bitvec current,next,trans;
	bool crossed = true;
	int step =1;
	for(unsigned int i=1; i < statePath.size(); ++i)
	{
		current = statePath[i-1];
		next = statePath[i];
		// ״̬�����еı仯λ
		trans = current ^ next;
		// ��ȡ״̬�����仯�Ķ���
		int wader = -1;
		for(int i=0;i<=2;++i)
		{	
			if( trans.test(i))
			{
				wader = i;
				break;
			}
		}
		cout << "����" << step++ << "�� ";
		switch (wader)
		{
			case goat:
				cout << "ũ������" << (crossed ? "���ӱ˰�" : "�غӴ˰�") << endl;
				break;
			case cabbage:
				cout << "ũ��Ѱײ˴�" << (crossed ? "���ӱ˰�" : "�غӴ˰�")<< endl;
				break;
			case wolf:
				cout << "ũ����Ǵ�" << (crossed ? "���ӱ˰�" : "�غӴ˰�") << endl;
				break;
			case -1:
				cout << "ũ�����" << (crossed ? "���ӱ˰�" : "�غӴ˰�")<< endl;
				break;

		}
		crossed = !crossed;
	}
	cout << "Congratulations�������������ɹ���" << endl;
}

// �ж�״̬�Ƿ�ȫ
bool is_safe( const bitvec & state)
{
	// ��԰ײ�
	if ((state[cabbage] == state[goat]) && (state[farmer] != state[goat]) )
		return false;
	// �ǳ���
	if ((state[goat] == state[wolf]) && (state[farmer] != state[wolf]))
		return false;
	// ����״̬Ϊ��ȫ״̬
	return true;
}

// �жϴ����ӵĶ����Ƿ���ũ���ںӵ�ͬһ��
// stateΪ��ǰ״̬
inline bool withFarmer(int wader,bitvec& state)
{
	return ( state[farmer] == state[wader] );
}

// ������
int main()
{
	// ��¼�Ѿ�̽��״̬��ת��·������ʼ��Ϊ-1
	vector<int> path(16, -1);	
	findRoute(path);
	displayRoute(path);
	system("pause");
	return 0;
}

