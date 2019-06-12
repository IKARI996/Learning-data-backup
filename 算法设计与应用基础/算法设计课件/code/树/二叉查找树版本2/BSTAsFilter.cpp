// FileName: BSTAsFilter.cpp

// �˳�������������arr��ֵ��ʼ������v�����а����ظ�Ԫ��
// �ò���v����filterDup()���������ظ���
// �������������ȥ�ظ�Ԫ��֮�������Ԫ��


#include <iostream>
#include <vector>
#include "BinSearchTree.h"	// BinSearchTree���

using namespace std;

// ������v�������ظ�Ԫ��
// �����ź����Ԫ��ʣ��Ԫ�ش洢��v��
template <typename T>
void filterDup(vector<T>& v);

// ��Ļ�������v
template <typename T>
void writeVector(const vector<T>& v);


int main()
{
	int arr[] = {3, 6, 3, 33, 55, 5, 55, 15, 25, 3, 5, 2, 5, 3, 55};
	int arrSize = sizeof(arr)/sizeof(int);
	vector<int> v(arr, arr+arrSize);

	// ���ԭʼ��������
	cout << "ԭʼ�������ݣ�\n";
	writeVector(v);
	// �����ظ�Ԫ�ز�����
	filterDup(v);
	// ������˲���������������
	cout << "���˲�����֮���������ݣ�\n";
	writeVector(v);
	cout << endl;
	system("pause");
	return 0;
}

template <typename T>
void filterDup(vector<T>& v)
{
	// ����������t����������
	BinSearchTree<T> t;
	BinSearchTree<T>::iterator treeIter;
	vector<T>::iterator vectorIter;

	// ���������ݲ��뵽����������t��
	// �����ظ�ֵ
	vectorIter = v.begin();
	while (vectorIter != v.end())
	{
		t.insert(*vectorIter);
		vectorIter++;
	}

	// �������v
	v.resize(0);

	// ���������
	// Ԫ�������push_back()����ѹ������ĩβ
	treeIter = t.begin();

	while (treeIter != t.end())
	{
		v.push_back(*treeIter);
		treeIter++;
	}
}

template <typename T>
void writeVector(const vector<T>& v)
{
	vector<T>::const_iterator iter;
	for(iter = v.begin(); iter != v.end(); ++iter )
	{
		cout << *iter << "  ";
	}
	cout << endl;
}
/*
Run:

2  3  5  6  15  25  33  55
*/
