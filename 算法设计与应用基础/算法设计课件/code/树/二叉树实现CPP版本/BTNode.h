// FileName;BTNode.h
//������������ͷ�ļ� 

#ifndef BTNODE
#define BTNODE


// ��ʾ�������Ľڵ�
template <typename T>
class BTNode
{
   public:
		// BTNode �����ʵ�֣�ʹ�����ݳ�Ϊ���г�Ա�����ຯ���Ĺ��죬
		//���BTNode��Ӧ�ó��ϣ�����Υ������������ԭ��
		T data;
		BTNode<T> *left, *right;

		// Ĭ�Ϲ��캯����������δ����ʼ��������ָ��Ϊ�� 
		BTNode():left(NULL),right(NULL)
		{}

        // ��׼���캯������ʼ�����ݳ�Ա����������ָ���Ĭ�ϲ���ֵ��ΪNULL
		BTNode (const T& item, BTNode<T> *lptr = NULL, 
				 BTNode<T> *rptr = NULL):
					data(item), left(lptr), right(rptr)
		{}
};

#endif	// BTNODE
