// FileName: StringPair.h
// �������pair<string, string>��StringPair�࣬
// �ṩ����ǿ�Ĺ��ܣ��������˴����͵���غ���

#ifndef STRING_PAIR
#define	STRING_PAIR

#include <functional>		// For sort
#include <utility>			// For pair
using namespace std;

struct StringPair : public pair<string, string> 
{
	// Ĭ�Ϲ��캯��
	StringPair() : pair<string, string>(string(), string())
	{
		 //
	}
	// ���캯����pair��first��Ա��second��Ա��������
	// ʵ������string���͵�StringPair���͵�ת��
	StringPair(const string& s) : pair<string, string>(s, s) 
	{
		sort(first.begin(), first.end());
	}

	// �û��Զ�������ת��Ϊ����
	// ���ʳ��Ͻ�StringPairת��Ϊstring
	operator string() const 
	{ 
		return second; 
	}
};

// �������<������
// ����StringPair��С�ں���
bool operator<(const StringPair& p,const StringPair& q) 
{
	return p.first < q.first;
}

// �������==������
// ����StringPair����Ⱥ���
bool operator==(const StringPair& p,const StringPair& q) 
{
	return p.first == q.first;
}


#endif /* STRING_PAIR */ 
