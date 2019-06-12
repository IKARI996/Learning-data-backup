// FileName: BTreelib.h
// ��������⺯��ͷ�ļ�

#ifndef TREE_LIBRARY_FUNCTIONS
#define TREE_LIBRARY_FUNCTIONS

#include <iostream>
#include <strstream>
#include <iomanip>
#include <string>
#include <queue>

#ifndef NULL
#include <cstddef>
#endif  // NULL

#include "BTNode.h"		// use BTNode class

using namespace std;

// ����ݹ���ʶ�������visit�����Ƕ��ƺ���
template <typename T>
void inOrder(BTNode<T> *t, void visit(T& item));

// ����ݹ���ʶ�������visit�����Ƕ��ƺ��� 
template <typename T>
void postOrder(BTNode<T> *t, void visit(T& item));

// ���ղ��˳��������ʶ�������visit�Ƕ��ƺ��� 
template <typename T>
void levelOrder(BTNode<T> *t, void visit(T& item));

// �����ò���count���ۼƶ�����Ҷ�ڵ�ĵ���Ŀ,count����ʼ��Ϊ0 
template <typename T>
void countLeaf(BTNode<T> *t, int& count);

// ���ض���������� 
template <typename T>
int depth (BTNode<T> *t);

// ������t�ĸ����������µĸ�����ָ��
template <typename T>
BTNode<T> *copyTree(BTNode<T> *t);

// ������ɾ���������Ľڵ�
template <typename T>
void deleteTree(BTNode<T> *t);

// ��deleteTree()ɾ���������нڵ㣬���������ڵ㸳ֵΪ��
template <typename T>
void clearTree(BTNode<T> * & t);

// ��ֱ��ʾ������������ڵ�ֵ
//�ڵ�ֵ�Ŀ�Ȳ�����dataWidth,��Ļ���ΪscreenWidth 
template <typename T>
void displayTree(const BTNode<T> *t, const int dataWidth=1,const int screenWidth=64);

template <typename T>
void inOrder(BTNode<T> *t, void visit(T& item))
{
   // ������Ϊ��ʱ���ݹ������ֹ
   if (t != NULL)
   {
      inOrder(t->left, visit);	// ����������
      visit(t->data);	// ���ʽڵ� 
      inOrder(t->right, visit);	// ����������
   }
}

template <typename T>
void postOrder(BTNode<T> *t, void visit(T& item))
{
   // ������Ϊ��ʱ���ݹ������ֹ
   if (t != NULL)
   {
      postOrder(t->left, visit);	// ����������
      postOrder(t->right, visit);	// ����������
      visit(t->data);			// ���ʽڵ� 
   }
}

template <typename T>
void levelOrder(BTNode<T> *t, void visit(T& item))
{
   // �洢ÿ���ڵ���ֵܽڵ㵽�����У��������԰�������һ���˳���������
   queue<BTNode<T> *> q;
   BTNode<T> *p;

   // �ڶ����в�����ڵ�����ʼ������
   q.push(t);

   // �����������̣�ֱ�����п� 
   while(!q.empty())
   {
      // �Ӷ�����ɾ��ǰ�˽ڵ㣬�����ʽڵ�
      p = q.front();
      q.pop();
      visit( p->data);

	  // ����������ӽڵ㣬�������뵽����
      if(p->left != NULL)
			q.push(p->left);
      // ����������ӽڵ㣬���뵽���У�ʹ���������ֵ�
      if(p->right != NULL)
			q.push(p->right);
   }
}

//���ò���count����ʼ��Ϊ0 
template <typename T>
void countLeaf (BTNode<T> *t, int& count)
{
   if (t != NULL)
   {
      // ���t�Ƿ�ΪҶ�ڵ�
      // ����ǣ�count��1
      if (t->left == NULL && t->right == NULL)
         count++;
      countLeaf(t->left, count);	// ���������������� 
      countLeaf(t->right, count);	// ����������������
   }
}

//ʹ�ú�������㷨���������
template <typename T>
int depth (BTNode<T> *t)
{
   int depthLeft, depthRight, depthval;
   if (t == NULL)
	  // ��������ȶ�Ϊ-1
	  depthval = -1;
   else
	{
		//����t�������������
		depthLeft= depth(t->left);
		//����t�������������
		depthRight= depth(t->right);
		//��tΪ�����������Ϊ��1+ �����������������ȣ� 
		depthval = 1 +
			(depthLeft > depthRight ? depthLeft : depthRight);
   }
   return depthval;
}

template <typename T>
BTNode<T> *copyTree(BTNode<T> *t)
{
   // newNode ָ���㷨�������½ڵ㣬
   //newLptr��newRptrָ��newNode����������
   BTNode<T> *newLeft, *newRight, *newNode;

   // �������ʱֹͣ�ݹ����
   if (t == NULL)
      return NULL;

   // �Ե����Ϲ����������ȹ�������������Ȼ���츸�ڵ㡣
   // �ڽڵ�t�������������ĸ�����������ڵ�ָ�븳ֵ��newLeft
   newLeft = copyTree(t->left);
   // �����������ĸ�����������ڵ�ָ�븳ֵ��newRight 
   newRight = copyTree(t->right);

   // �����½ڵ㣬��ڵ�ֵ��t��ֵ��ͬ�����ӽڵ��Ǳ����Ƶ�t������
   newNode = new BTNode<T> (t->data, newLeft, newRight);

   // �����¸��Ƶ����ĸ��ڵ��ָ��
   return newNode;
}

template <typename T>
void deleteTree(BTNode<T> *t)
{
    // ���������ɾ��t������������Ȼ��ɾ���ڵ�t
    if (t != NULL)
    {
        deleteTree(t->left);
        deleteTree(t->right);
        delete t;
    }
}

template <typename T>
void clearTree(BTNode<T> * & t)
{
	deleteTree(t);
	t = NULL; //��ʱ��ΪNULL 
}

//�����ṹ
//���displayTree�нڵ����꣨x��y���ļ�¼
struct Info
{
    //Ĭ�Ϲ��캯�� 
    Info() {} 
    //��ʼ�����캯��
    Info(int indent, int level):xIndent(indent),yLevel(level) {}; 
    int xIndent,yLevel;
};

template <typename T>
void displayTree(BTNode<T> *t, const int dataWidth,const int screenWidth=64)
{
   // �洢ÿ���ڵ�Ķ���
   queue<BTNode<T> *> q;
   //��Žڵ��ӡ��Ϣ�Ķ��У� 
   
   queue<Info>QI; 
   BTNode<T> *currNode;
   Info currInfo; 
   int units (screenWidth/dataWidth); 
   int offset = units/2;
   //��ǰ�ڵ��������  
   int currlevel = -1;
   //��ǰ�ڵ��ͬ���ǰһ�ڵ�������� 
   int preX;    
    
   //�����Ϊ�գ��˳� 
   if (t == NULL)
      return;

   // �ڶ���q�в�����ڵ�����ʼ������
   q.push(t);
   //�ڶ���QI�в�����ڵ������ʼ������ 
   QI.push(Info(offset,0));

   // �����������̣�ֱ�����п� 
   while(!q.empty())
   {
      // �Ӷ�����ɾ��ǰ�˽ڵ㣬�����ʽڵ�
      currNode = q.front();
      q.pop();
      currInfo = QI.front();
      QI.pop(); 
      if( currInfo.yLevel != currlevel )
      {
           //������         
           cout<<"\n\n" ;     
          //���У���ʼλ��Ϊ0
          preX = 0;
          //��Ů�ڵ��ƫ����Ϊ �ϲ�ڵ��1/2  
          offset /= 2;   
          //���µ�ǰ�ڵ������� 
          currlevel = currInfo.yLevel;       
      }
      
      //����Ӧλ������ڵ����ͷ��Ԫ�ص�ֵ������ΪT��
      //���Ǽٶ�����T�����˺��ʵ�<<������ 
      cout<<setw((currInfo.xIndent-preX)*dataWidth)
          <<currNode->data;  
      
      if( currNode->left != NULL )
      {
          //���ӽڵ����
          q.push(currNode->left) ;
          //���ӽڵ�λ����Ϣ���
          QI.push(Info(currInfo.xIndent-offset,currInfo.yLevel+1));
      }
      if( currNode->right != NULL )
      {
          //���ӽڵ����
          q.push(currNode->right) ;
          //���ӽڵ�λ����Ϣ���
          QI.push(Info(currInfo.xIndent+offset,currInfo.yLevel+1));
      }      
      preX = currInfo.xIndent;
   } //whileѭ��
}
	
#endif   // TREE_LIBRARY_FUNCTIONS

