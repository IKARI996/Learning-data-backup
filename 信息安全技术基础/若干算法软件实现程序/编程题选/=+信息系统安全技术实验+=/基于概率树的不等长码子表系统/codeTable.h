#include<iostream>
#include<fstream>
#include<string>
using namespace std;

#ifndef __codeTable_h
#define __codeTable_h

#include"node.h"
#include"list.h"

const int NUM=128;

class CodeTable{
public:
	CodeTable(ifstream *infile,ofstream *outfile);
	~CodeTable();
	void  buildCodeTable();  //�������ֱ�
private:
	void buildList();    //�������ֵĸ�����
	void buildTree();    //�����ֵĸ������������ֵĸ�����
	//������������ѭ���������ֱ�
	void recursiveBuildCodeTable(Node *tree);
	void add(Node *root,string s);
	void clear(Node *root);

	SortedList probabilityList;  //���ֵĸ�����
	Node *tree;     //����
	ifstream *plaintext;  //����
	ofstream *codeTable;  //���ֱ�
};
//////////////////////////////////////////////////////////////
CodeTable::CodeTable(ifstream *infile,ofstream *outfile)
{
	plaintext=infile;
	codeTable=outfile;
	tree=NULL;
}

CodeTable::~CodeTable()
{
    clear(tree);
//	plaintext=NULL;
//	codeTable=NULL;
}

void  CodeTable::buildCodeTable()
{
	buildList();
	buildTree();
	recursiveBuildCodeTable(tree);
}
	

//////////////////////////////////////////////////////////////
void CodeTable::buildList()
{
//ͳ�����ĵ����ֵĸ���
	int p[NUM];
	int num=0;
	char letter;
	Node *x;

	for(int i=0;i<NUM;i++)
		p[i]=0;
	while(plaintext->peek()!=EOF){
		plaintext->get(letter);
		p[int(letter)]++;
        num++;
	}
//ͳ�ƽ�����������
	for(int j=0;j<NUM;j++){
		//�ҵ��ļ��г��ֵ��ַ�
		if(p[j]!=0){
			x=new Node();//�½��
			x->letter=j;  //����
			x->probability=(p[j]/float(num) );  //����
			//���������
		    probabilityList.insert(x);
		}
		
	}		
}
void CodeTable::buildTree()
{
	Node *r,*l,*n;
	if(probabilityList.size()<=1)
		tree=probabilityList.head;
	else{
	  while(probabilityList.size()>1){
		n=new Node();
		probabilityList.remove(0,l);
		probabilityList.remove(0,r);
		n->lchild = l;
		n->rchild = r;
		n->probability=l->probability+r->probability;
		probabilityList.insert(n);
	  }
	  tree = n;
	  add(tree->lchild,"0");
	  add(tree->rchild,"1");
	}
		
}
void CodeTable::recursiveBuildCodeTable(Node *tree)
{
	if(tree!=NULL){
		//�����ֱ�������ּ���Ӧ��0/1�ַ���
		if(tree->lchild==NULL&&tree->rchild==NULL)
		    (*codeTable)<<tree->letter<<' '<<tree->s<<endl;
		recursiveBuildCodeTable(tree->lchild);
		recursiveBuildCodeTable(tree->rchild);
//		delete tree;
	}
}

void  CodeTable::add(Node *root,string s)
{//������Ҷ�ӵ��ַ�����0,������Ҷ�ӵ��ַ�����1
		  if(root != NULL){
			  	root->s = s;
			    string c1,c2;
				c1=s+"0";
				c2=s+"1";				
				add(root->lchild,c1);
				add(root->rchild,c2);
		  }
}

void  CodeTable::clear(Node *root)
{
	if(root!=NULL){
		Node *l=root->lchild;
		Node *r=root->rchild;
		delete root;
		clear(l);
		clear(r);
	}
}

#endif