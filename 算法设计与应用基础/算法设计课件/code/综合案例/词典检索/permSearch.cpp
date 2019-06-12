// Program to find all anagrams of a given word, using a dictionary
// read from a file
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;
typedef istream_iterator<string> string_input;


// ��ӭ����
void welcome()
{
	cout << "******************* ��λ�ʲ���ϵͳVersion1******************\n"
		<< "�ڴʵ����ҳ��������ַ��������б�λ��" << endl;
}

// ����ʵ��ļ�,���Դʵ䵥��.���дʵ�������
void readDict(vector<string> & dictionary)
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
	// ���ʵ��ļ����ݶ��뵽�ַ�������dictionary��
	copy(string_input(ifs), string_input(),
		back_inserter(dictionary));
	// Ϊ���ں���Ĳ��Ҳ������Դʵ�����
	sort(dictionary.begin(),dictionary.end());
	// ����ʵ�����
	cout << "�ʵ������ " 
		<< dictionary.size() << " ������\n\n";
	// �ر��ļ�
	ifs.close();
}

// ��ȡ�û����ʣ����ұ�λ�ʲ����
void analyseAnagram(const vector<string> & dictionary)
{
	cout << "�����뵥�ʣ���������ĸ���У�" << endl;
	// ʹ��������������p�����û��ӱ�׼������cin������ַ�����
	// ֱ���û�������������־
	for (string_input p(cin); p != string_input(); ++p) 
	{
		cout << "�������뵥�ʵı�λ����..." << endl;
		string word = *p;
		// ������word�����Ա�����ȫ����
		sort(word.begin(), word.end());
		// ��¼�Ƿ��ڴʵ��в��ұ�λ�ʳɹ�
		bool found_one = false;

		do 
		{
			if (binary_search(dictionary.begin(),
					dictionary.end(),
					word))
			// �Դʵ�Ĵ������ж��ֲ��ң�������ҳɹ���
			// ����ñ�λ�ʣ�����found_oneΪtrue
			{
				cout << "  " << word ;
				found_one = true;
			}
		} while (next_permutation(word.begin(), word.end()));
			// ��ð��մʵ�˳�����һ�����У�����ɹ�����ʼ��һ�ֲ���
		// û���ҵ�������
		if (!found_one) 
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
	vector<string> dictionary;
	readDict(dictionary);
	analyseAnagram(dictionary);

	system("pause");
	return 0;
}

