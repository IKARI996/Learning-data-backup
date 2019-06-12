#ifndef __list_h
#define __list_h

#include"node.h"

class SortedList{
public:
	SortedList();
//	~SortedList();

	bool remove(int position,Node *&x);
	bool insert(Node *x);
	int size()const;
	bool empty()const;
	void clear(Node *root);
	Node *head; 
protected:
	int count;
};
///////////////////////////////////////////////////////
SortedList::SortedList()
{
	head=NULL;
	count=0;
}
/*
SortedList::~SortedList()
{
	clear(head);
}
*/
////////////////////////////////////////////////////////
int SortedList::size()const
{
	return count;
}

void  SortedList::clear(Node *root)
{
	if(root!=NULL){
		Node *l=root->lchild;
		Node *r=root->rchild;
		delete root;
		clear(l);
		clear(r);
	}
}
/*
void SortedList::clear()
{
	Node *p=head;
	while(head!=NULL){
		p=head;
        head=head->next;
		delete p;
	}
	count=0;
}
*/
bool SortedList::empty()const
{
	return count==0; 
}

/////////////////////////////////////////////////////////
bool SortedList::insert(Node *x)
{
	Node *first,*second;   
	//��������Ҫ����Ľڵ�Ϊ��С�������ͷ
	if(count==0){ 
		head = x;
	}else if(x->probability<=head->probability ){
        x->next = head;
		head = x;
	}else{
	//Ҫ��Ȼ�Ͳ��뵽�����к���λ��
		first=head;
		//�ҵ����к���λ��
		while(first!=NULL&&x->probability > first->probability){
			second=first;
			first=first->next;
		}
		//����
		second->next =x;
		x->next=first;
	}
	count++;
	return true;
}

bool SortedList::remove(int position,Node *&x)
{
	Node *p;
//�������޽ڵ��ɾ��λ�ó�����Χ������
	if(count==0||position<0||position>=count)
		return false;
//ɾ����һ���ڵ�
	if(position==0){
		x=head;
		head=head->next;
		x->next=NULL;
		count--;
		return true;
	}	
//ɾ���м�ڵ�
	//�ҵ�ɾ����λ��
	Node *previous;
	p = head;
    for(int i=0;i<position;i++){
		previous = p;
		p= p->next;
	}
	//ɾ���ڵ�
	previous->next=p->next;
	x=p;
	x->next=NULL;
	count--;
	return true;
}

#endif

