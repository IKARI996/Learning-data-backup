#ifndef __node_h
#define __node_h

#include<string>
#include<iostream>
using namespace std;

struct Node{
	char letter;  //����
	float probability;  //�������ļ��г��ֵĸ���
	string s;  //�����ڸ������е�λ�á���0��1

	Node *next;  
	Node *lchild;
	Node *rchild;

	Node(){
		next=NULL;
		lchild=NULL;
		rchild=NULL;
		letter='\0';
		s="";
	}
    


};

#endif
