// Find all anagram groups in a dictionary, and print them to
// standard output stream
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iterator>
using namespace std; 


typedef istream_iterator<string> string_input;
typedef set<string> WordSet;
typedef map<string,WordSet> WordMap;




// ��ӭ����
void welcome()
{
	cout << "******************* ��λ�ʲ���ϵͳVersion3******************\n"
		<< "�ڴʵ����ҳ��������ַ��������б�λ��" << endl;
}

// ����ʵ��ļ�,����ʵ�ģ��
void readDict(WordMap& enhancedDict)
{
	// ���û���ȡ�ļ�����
	cout << "���ȣ�������ʵ���ļ����ƣ�" << endl;
	string dictionary_name; 
	cin >> dictionary_name;
	// ���ļ�
	ifstream ifs(dictionary_name.c_str());
	// �����쳣
	if (!ifs.is_open()) 
	{
		cerr << "�쳣���ļ�"<< dictionary_name 
			<< "û���ҵ� " << endl;
		exit(1);
	}
	cout << "�ʵ������ ..." << endl;
	// ���ʵ��ļ����ݶ��뵽ӳ��enhancedDict��
	string word;
	string key;
	size_t wordCount = 0;
	while(ifs)
	{
		// ���ж�ȡ����
		getline(ifs,key);
		word = key;
		sort(key.begin(),key.end());
		// ����������������뵽�ʵ�mapģ��ʵ����
		enhancedDict[key].insert(word);
		// ���´�����Ŀ����
		++wordCount;
	}
	// ����ʵ�����
	cout << "�ʵ������ " 
		<< wordCount << " ������\n"<< endl << endl;
#if 0
	cout << "�ʵ�ռ���ڴ��СΪ"
		<< sizeof(enhancedDict) << "B" << endl << endl;
#endif;
	// �ر��ļ�
	ifs.close();
}

// ����for_each(first,last, printString)
void printString(const string& s)
{
	cout << s << "  ";
}

// ��ȡ�û����ʣ����ұ�λ�ʲ����
void analyseAnagram(const WordMap& enhancedDict)
{
	cout << "�����뵥�ʣ���������ĸ���У�" << endl;
	// ʹ��������������p�����û��ӱ�׼������cin������ַ�����
	// ֱ���û�������������־
	for (string_input p(cin); p != string_input(); ++p) 
	{
		cout << "�������뵥�ʵı�λ����..." << endl;
		string word = *p;
		// ��word�任Ϊ����������
		sort(word.begin(),word.end());

		// word�ı�λ�ʼ���
		const WordSet& anagramSet = (*(enhancedDict.find(word))).second;

		// ֱ��������ϼ���
		for_each(anagramSet.begin(),anagramSet.end(),printString);
		cout << endl;
		// �������Ϊ��
		if(anagramSet.empty())		
			cout << "  ��Ǹ��û���ҵ���λ��\n";		

		// ��ʾ��ʼ׼���µĹ���
		cout << "\n��������һ������ " 
			<< "(������end-of-file�ַ���ֹ���� ) \n"
			<< "<end-of-file�ַ���Windowsƽ̨��Ctrl+Z��UNIXƽ̨��Ctrl+D>: " << endl;
	}
}

int main() 
{
	welcome();
	WordMap dictionary;
	readDict(dictionary);
	analyseAnagram(dictionary);

	system("pause");
	return 0;
}