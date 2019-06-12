// File: testBTree.cpp

// �˳�����ʾ�������ĸ����㷨
// ���ȹ���һ�ö�����������Ļ�ϴ�ֱ���
// ���򡢺��򼰲�α��������� 
// �������ĸ߶ȣ�������Ҷ�ڵ����
// ����֤�˸��ơ�ɾ���������Ĳ��� 

#include <iostream>

#include "BTNode.h"		// BTNode�� 
#include "BTreelib.h"	// BTNode�� 

using namespace std;

//ʵ�ú���makeCharTree������һ�����ַ�Ϊ�ڵ����ݵĶ�����
BTNode<char> *makeCharTree();

//�����㷨��visit����������ڵ�����ֵ 
void printChar(char& elem)
{
    string seperator = "  "; 
    cout <<  elem << seperator;
} 

int main()
{
	//�������ĸ� 
    BTNode<char> *root1, *root2;

	// ��������� 
	root1 = makeCharTree();

	// ��ʾ��
	cout << "ԭʼ����ͼʾ��" << endl;
	const int charWidth=1;
	const int ScreenWidth=64;
	displayTree(root1, charWidth,ScreenWidth);
	cout << endl << endl;
	
	//�ڵ���������
    cout << "���������" ;
    inOrder(root1, printChar);
    cout << endl;
    
   	//�ڵ�ĺ������
    cout << "���������" ;
    postOrder(root1, printChar);
    cout << endl;
    
   	//�ڵ�Ĳ�α���
    cout << "��α�����" ;
    levelOrder(root1, printChar);
    cout << endl<<endl;
    
    //Ҷ������
    int leafCount = 0;
    countLeaf(root1, leafCount);
    cout << "Ҷ�ڵ���Ŀ�ǣ�"
         << leafCount << endl; 
    cout << "��������ǣ�"
         << depth (root1) <<endl; 

	//����root1�ĸ�������Ϊroot2
	root2 = copyTree(root1);

	// ��ʾ���ĸ��� 
	cout << "ԭʼ���ĸ�����ͼʾ��" << endl;
	displayTree(root2, charWidth,ScreenWidth);
	cout << endl;

	// ���������
	clearTree(root1);
	clearTree(root2);
	
	cout << "��root1���õ�clearTree֮���ͼʾ��" << endl;
	displayTree(root1, charWidth,ScreenWidth);
	cout << endl << endl;

    cout<<"���س�����������:" << endl;
    cin.get(); 
	return 0;
}


BTNode<char> *makeCharTree()
{
	// 9 BTNode ָ�룬ָ��9���ڵ���
	BTNode<char> *root, *b, *c, *d, *e, *f, *g, *h, *i;
	g = new BTNode<char> ('G');
	h = new BTNode<char> ('H');
	i = new BTNode<char> ('I');
	d = new BTNode<char> ('D',(BTNode<char> *)NULL, g);
	e = new BTNode<char> ('E',h, i);
	f = new BTNode<char> ('F');
	b = new BTNode<char> ('B',d, (BTNode<char> *)NULL);
	c = new BTNode<char> ('C',e, f);
	root = new BTNode<char> ('A',b, c);
	return root;
}
