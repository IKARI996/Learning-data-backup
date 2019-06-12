// Find all anagram groups in a dictionary, and print them to
// standard output stream
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
using namespace std; 
#include "StringPair.h"	    // Definitions of PairString

typedef istream_iterator<string> string_input;
typedef vector<StringPair>::const_iterator CSP_Iter;

// ��ӭ����
void welcome()
{
	cout << "******************* ��λ�ʲ���ϵͳVersion2******************\n"
		<< "�ڴʵ����ҳ��������ַ��������б�λ��" << endl;
}

// ����ʵ��ļ�,����ʵ�ģ��
void readDict(vector<StringPair>& enhancedDict)
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
	cout << "�ʵ������ ..." << flush;
	// ���ʵ��ļ����ݶ��뵽�ַ�������enhancedDict��
	// ��һ����������string��StringPair����ʽ����ת��
	// ��StringPair�ĵ��������캯���������ת��
	copy(string_input(ifs), string_input(),
		back_inserter(enhancedDict));
	// Ϊ���ں���Ĳ��Ҳ������Դʵ�����
	sort(enhancedDict.begin(),enhancedDict.end());
	// ����ʵ�����
	cout << "�ʵ������ " 
		<< enhancedDict.size() << " ������\n\n";
	// �ر��ļ�
	ifs.close();
}

// ����for_each(first,last, printString)
void printString(const string& s)
{
	cout << s << "  ";
}

// ��ȡ�û����ʣ����ұ�λ�ʲ����
void analyseAnagram(const vector<StringPair>& enhancedDict)
{
	cout << "�����뵥�ʣ���������ĸ���У�" << endl;
	// ʹ��������������p�����û��ӱ�׼������cin������ַ�����
	// ֱ���û�������������־
	for (string_input p(cin); p != string_input(); ++p) 
	{
		cout << "�������뵥�ʵı�λ����..." << endl;
		string word = *p;
		// ��word����wordP
		StringPair wordP(word);
		pair<CSP_Iter,CSP_Iter> word_range 
			= equal_range(enhancedDict.begin(),enhancedDict.end(),wordP);
			// �Դʵ�Ĵ������ж��ֲ��ҵ�һ���汾
		// ��¼wordP������ʵ��е�λ���Ͻ���½�
		CSP_Iter startPos = word_range.first;
		CSP_Iter finishPos = word_range.second;
		// ��¼�ڴʵ��в��ұ�λ���Ƿ�ɹ�
		bool existAnagram = (startPos != finishPos);
		// ����ô������б�λ��
		for_each(startPos, finishPos,printString);
		cout << endl;
		// û���ҵ�������
		if (!existAnagram) 
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
	vector<StringPair> dictionary;
	readDict(dictionary);
	analyseAnagram(dictionary);

#if 0
// �����ǿ�ʹʵ䣬�����۲�
	ofstream ofs("enhancedDict.txt");
	CSP_Iter curPos = dictionary.begin();
	while(curPos != dictionary.end())
	{
		ofs << (*curPos).first << "\t";
		ofs << (*curPos).second << "\n";
		curPos++;
	}
#endif

	system("pause");
	return 0;
}