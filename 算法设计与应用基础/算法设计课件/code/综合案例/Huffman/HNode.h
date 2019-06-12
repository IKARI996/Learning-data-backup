#ifndef HUFFMAN
#define HUFFMAN

#include <iostream>
#include <iomanip>
#include <queue>
#include <vector>
#include <bitset>	

using namespace std;

// NIL ��ʾһ��������
const short NIL = -1;

// ѹ���ļ���Huffman���Ľڵ����
class DiskHuffNode
{
public:
	// �洢���ַ�
	unsigned char ch;
	// �ӽڵ��ָ�루������
	short left;
	short right;

	DiskHuffNode (unsigned char c = 0, short lptr = NIL, short rptr = NIL):
			ch(c), left(lptr), right(rptr)
	{}
};

// �����ַ������λ���С
const int MAXBITSIZE = 255;
typedef bitset<MAXBITSIZE> BitCode;

// ����Huffman���Ľڵ�
// ѹ���㷨ʹ����Щ�����Լ�����DiskHuffNode�����ڵ�
// �����е������ڽ�ѹ���㷨�в�����Ҫ
class HuffNode: public DiskHuffNode
{
public:
	int freq;				// f�ַ�ch�ĳ���Ƶ��
	int index;				// ����ڵ������е�����
	int parent;				// ����ڵ�ĸ��ڵ�
	int numberOfBits;		// ch��Huffman�����bit��Ŀ
	BitCode bits;			// ����Huffman���bitset����

	HuffNode (unsigned char c = 0, short lptr = NIL, short rptr = NIL,
		       int f = 0, int indx = NIL, int p = 0,
				 int numBits = 0, int maxSizeOfBits = MAXBITSIZE):
			DiskHuffNode(c, lptr, rptr), freq(f), index(indx),
			parent(p), numberOfBits(numBits), bits(0)
	{}

	// ��<���͡�>��������ǹ���������ȼ����к���С���ȼ����б����
	friend bool operator< (const HuffNode& lhs, const HuffNode& rhs)
	{
		return lhs.freq < rhs.freq;
	}
	friend bool operator> (const HuffNode& lhs, const HuffNode& rhs)
	{
		return lhs.freq > rhs.freq;
	}
};


// ��ֱ���������
void displayHuffmanTree (const vector<HuffNode>& tree);

// IMPLEMENTATION OF TREE DISPLAY

// record to hold the pointer value and x,y coordinates for a
// node used in displayHuffmanTree
class infoNode
{
	public:
		HuffNode value;						// node value
		int xPosition;							// x position on the line
		int yLevel;								// level (line) position
		infoNode *left, *right;

		infoNode ()
		{}
};

infoNode *createInfoNode(const vector<HuffNode>& tree, int i,
								 int& x, int y, int dataWidth)
{
	infoNode *newNode = NULL;
	int dx = dataWidth;

	if (i != NIL)
	{
		newNode = new infoNode;
		// allocate node for left child at next level in tree; attach node
		infoNode *newLeft = createInfoNode(tree, tree[i].left, x, y+1, dataWidth);
		newNode->left = newLeft;

		// initialize data members of new node
		newNode->value = tree[i];
		newNode->xPosition = x;
		newNode->yLevel = y;
		// update x to position dx characters to right of current position
		x+= dx;

		// allocate node for right child at next level in tree; attach node
		infoNode *newRight = createInfoNode(tree, tree[i].right, x, y+1, dataWidth);
		newNode->right = newRight;
	}
	return newNode;
}

// delete the shadow tree
void clearShadowTree(infoNode *t)
{
	if (t != NULL)
	{
		clearShadowTree(t->left);
		clearShadowTree(t->right);
		delete t;
	}
}

// output tree vertically
void displayHuffmanTree (const vector<HuffNode>& tree)
{
	const int dataWidth = 7;
   // set xPosition as 1 and the level at 0
	int x = 1, y = 0;
	infoNode *root;
	// launch the inorder scan; root is the base of the shadow tree
	root = createInfoNode(tree, tree.size()-1, x, y, dataWidth);
	infoNode *currNode, *prevNode;
	HuffNode h;

	// store siblings of each infoNode object in a queue so that
	// they are visited in order at the next level of the tree
   queue<infoNode *> q;

	// objects to maintain current print position on a line
	int i, currPosition = 0;

	cout.setf(ios::left,ios::adjustfield);

   // insert the root in the queue and initialize prevNode as root
   q.push(root);
	prevNode = root;

   // continue the iterative process until the queue is empty
   while(!q.empty())
   {
      // delete front node from queue and set as current node
      currNode = q.front();
		q.pop();

		// if current node on the next level, output newlines
		// reset currPosition (on line) back to 0
		if (prevNode->yLevel < currNode->yLevel)
		{
			cout << endl << endl;
			currPosition = 0;
		}

		// use spaces to scan from current position to x position of node
		for (i = currPosition; i < currNode->xPosition; i++)
			cout << " ";
		// output data value and update currPosition dataWidth chars
		h = currNode->value;
		if (h.left == NIL)
			if (h.ch >= ' ' && h.ch <= '~')
				cout << h.ch << ':' << setw(5) << h.freq;
			else
				cout << "x" << hex << setw(2) << int(h.ch)
					  << dec << ':' << setw(3) << h.freq;
		else
				cout << setw(7) << h.freq;
		currPosition = currNode->xPosition + dataWidth;
		// update prevNode for the next iteration
		prevNode = currNode;

		// if a left child exists, insert it in the queue
      if(currNode->left != NULL)
			q.push(currNode->left);
      // if a right child exists, insert next to its sibling
      if(currNode->right != NULL)
			q.push(currNode->right);
   }
	cout << endl;

	clearShadowTree(root);

	cout.setf(ios::right,ios::adjustfield);
}

#endif // HUFFMAN
