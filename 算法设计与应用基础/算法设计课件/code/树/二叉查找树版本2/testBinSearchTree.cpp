// File: testBinSearchTree.cpp

// �˳�����ʾ������������Ļ�������
// �������ù��캯������һ�ö�������������������"insight"
// ֮��Ը�������������insert()��erase()��display()



#include "BinSearchTree.h"	// BinSearchTree���

int main()
{
	cout <<"********************��ʾ�������������ܵ�Ӧ�ó���************************"<<endl;

	//�˲�����ʾ���Ĺ�������
	char* ch = "insight";
	BinSearchTree<char> t(ch, ch+7);
	BinSearchTree<char>::iterator iter;
	const int charWidth=1;
	const int ScreenWidth=80;
	cout << "��ʼ��:" << endl;
	t.display(charWidth,ScreenWidth);
	cout << endl << endl;
	cout << "������������Ԫ��Ϊ:"<<endl;
	for(iter = t.begin();iter !=t.end();iter++)
		cout<< *iter;
	cout <<endl;

	//�˲�����ʾ���Ĳ������
	BinSearchTree<char>::iterator tIter;
	pair<BinSearchTree<char>::iterator, bool> p;
	string str = "coding" ;
	cout << "��ʼ����"<<str <<"��������"<<endl;
	for( unsigned int i = 0; i < str.length(); i++ )
	{
		p = t.insert(str[i]);
		if(p.second == false)
			cout << str[i] << "���ظ���ĸ" << endl;
	}
	cout << "��ʱ��Ϊ��" << endl;
	t.display(charWidth,ScreenWidth);
	cout << endl <<endl;
		cout << "������������ʱ��Ԫ��Ϊ��"<<endl;
	for(iter = t.begin();iter !=t.end();iter++)
		cout<< *iter;
	cout <<endl;

	//�˲�����ʾ����ɾ������
	cout <<"����ڵ�ɾ��,ֱ����Ϊ�գ���ʼ����"<<endl;
	iter = t.begin();
	while(iter != t.end())
	{
		cout << *iter<<"��ɾ�������"<<endl; 		 
		t.erase(iter++);
		t.display(charWidth,ScreenWidth);
		cout<<endl<<endl;
	}

	cout<<"�밴�س�����������:" ;
	cin.get();
	return 0;
}
