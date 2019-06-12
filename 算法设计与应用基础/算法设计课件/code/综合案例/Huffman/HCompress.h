#ifndef HUFFMAN_COMPRESS
#define HUFFMAN_COMPRESS

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <queue>			//  For priority_queue
#include <functional>
#include <sstream>
#include <algorithm>

#include "HNode.h"			// Huffman node classes and node display

const int MAXCHARS = 256;
	// ASCII�ַ���Ŀ
typedef bitset<MAXBITSIZE> BitCode;		
	//����ַ�λ��
typedef vector<bool> bit_vector;
	//���ڴ�ű�ѹ���ļ�����


class HCompress
{
public:
	HCompress(const string& fname, bool v = false);
		// ���캯��������setFile() ��Դ�ļ�fname,
		// ���ɶ���������ļ�����Ӻ�׺".huf"��ʶ���κ���ǰ����չ�������滻
		// �߼���־vȷ���Ƿ����������Ϣ

	void setFile(const string& fname);
		// ��Դ�ļ�fname,���ɶ���������ļ���".huf"Ϊ��׺

	void compress();
		// ѹ���ļ�

	void dispCompRatio() const;		
		// ��ʾѹ����

	int size() const;
		// ����Huffman���нڵ���Ŀ

	void displayTree() const;
		// ��ʾHuffman��
		// ������Ļ�ߴ磬������С<= 11ʱ�Ƽ�������
private:
	fstream source;
	fstream dest;
		// ���������
	vector<int> charFreq, charLoc;
		// charFreq����ͳ���ַ�Ƶ��
		// charLocά���ļ����ֵ��ַ���Huffman���е��±�
	int numberLeaves;
		// numberLeaves������Ҷ�ڵ㣨�ַ��ڵ㣩��Ŀ
	short treeSize;
		// ѹ���ļ���Huffman���ڵ���Ŀ
	vector<HuffNode> tree;
		// �洢Huffman��
	bool verbose;
		// ���������Ϣ��
	unsigned long fileSize;
		// Դ�ļ��Ĵ�С
	unsigned long totalBits;
		// Դ�ļ���ѹ��������ʹ�õ���bits��Ŀ
	bool oneChar;
		// ������һ��Ψһ�ַ�ô��
	bool filesOpen;
		// Դ��Ŀ���ļ�����ô��

	void freqAnalysis();
		// �ж�Դ�ļ����ַ�Ƶ�Ȳ������Ǵ洢��charFreq
		// ͬʱȷ��numberLeaves�����г�fileSize
		// �������ǿ��Կ���ѹ���㷨��Ч��

	void buildTree();
		// ����Huffman�� 

	void generateCodes();
		// ��ÿ��Ҷ�ڵ㣬��Huffman��������ȷ��ÿ���ַ���Huffman�� 
		// �����㱻ѹ�����ݵ���λ��

	void writeCompressedData();
		// �ٴζ���Դ�ļ�
		// ��������Huffman��ָ����Huffman��д����dest��
	void mem_to_file(bit_vector& bv,fstream& ostr);
		// ��������bit���д��ڴ洫�ݵ��ļ���

	void treeData();
		// ���Huffman������
};

void HCompress::freqAnalysis()
{
	unsigned char ch;

	numberLeaves = 0;
	fileSize = 0;

	while (true)
	{
		ch = source.get();
		if (!source)
			break;

		// found 1 more char in the source file
		fileSize++;

		// count an occurrence of ch
		charFreq[ch]++;

		// if first time we have found ch, count it as a leaf
		if (charFreq[ch] == 1)
			numberLeaves++;
	}
	if (verbose)
		cout << "    �ļ���СΪ : " << fileSize << " ���ַ�" << endl
			  << "   ��ͬ�ַ�����ĿΪ: "
			  << numberLeaves << endl << endl;
}

void HCompress::buildTree()
{
	// ˳�����Huffman���ڵ�
	int i, nodeIndex;
	// ��׽�����ȼ������г����Ľڵ�
	HuffNode x, y;
	// ��С���ȼ����У����ڹ���Huffman��
	priority_queue<HuffNode, vector<HuffNode>, greater<HuffNode> > pq;

	// �����ļ�����һ�������ַ�����������
	if (numberLeaves == 1)
	{
		// ����Ҷ�ڵ���ĿΪ2��
		// ��������0��1λ�����1��Ҷ�ڵ�
		// ��Ϊ����Щλ�õ��ַ����������ļ���
		numberLeaves = 2;
		if (charFreq[0] != 0)
			charFreq[1] = 1;
		else
			charFreq[0] = 1;

		// ��¼�����Ѿ���������ڵ�
		oneChar = true;
	}
	else
		oneChar = false;

	// ���Ĵ�СΪ2*numberLeaves-1
	treeSize = 2*numberLeaves - 1;
	tree.resize(treeSize);

	// �������ǹ����е���
	nodeIndex = 0;

	// ��ʼ�������Ҷ�ڵ�
	//    value = char(i)
	//    left/right = NIL,
	//    frequency = charFreq[i]
	//    index = nodeIndex
	//	  parent, numberOfBits, maxSizeOfBits ΪĬ��ֵ
	// ��charLoc�м�¼Ҷ�ڵ��λ�ã����ڵ���뵽��С���ȼ�������
	for (i=0; i < MAXCHARS; i++)
		if (charFreq[i] != 0)
		{
			tree[nodeIndex] = HuffNode((unsigned char)(i), NIL, NIL,
				                        charFreq[i], nodeIndex);
			pq.push(tree[nodeIndex]);
			// ��¼��Ҷ�ڵ������������
			// writeCompressedData()����
			charLoc[i] = nodeIndex;
			// ׼��������һ���ڵ�
			nodeIndex++;
		}

	// ���� numberLeaves-1 �ε���, �Ƴ��ڵ��,
	// ���ɸ��ڵ�, �������ڵ��������
	for (i=1; i <= numberLeaves-1; i++)
	{
		// �Ƴ�Ƶ����͵������ڵ㡣�������������ж�Ӧ�ڵ�ĸ���
		// λ��Ϊx.index��y.index
		x = pq.top();
		pq.pop();
		y = pq.top();
		pq.pop();

		// ���ɸ��ڵ㣨�ڲ��ڵ㣩�������ӽڵ�
		// ���������е�����λ��Ϊx.index��y.index��
		// ����Ƶ��Ϊx��y��Ƶ�Ⱥ�
		// ����ڵ������ΪnodeIndex��
		// �丸�ڵ���ʱ��Ϊ0
		tree[nodeIndex] = HuffNode(char(0), x.index, y.index,
											x.freq + y.freq,
											nodeIndex, 0, 0, 0);

		// ʹ��x.index��y.index��
		// ��nodeIndex����Ϊx��y�ĸ��ڵ��Ա������ֵ
		tree[x.index].parent = nodeIndex;
		tree[y.index].parent = nodeIndex;

		// ���µĸ��ڵ���뵽���ȼ�����
		pq.push(tree[nodeIndex]);

		nodeIndex++;
	}
	if (verbose)
		cout << "   Huffman���Ľڵ���Ŀ: "
			  << treeSize << endl << endl;
}

void HCompress::generateCodes()
{
	int i, j;
	int bitNumber, current, parent;
	// use to compute each character's bit code
	BitCode bits;

	totalBits = 0;

	// the nodes tree[0], tree[1], ..., tree[numberLeaves-1] are
	// all leaf nodes. for each leaf, follow the parent index
	// up to the root and build the bit code for the character
	for (i=0; i < numberLeaves; i++)
	{
		// starting bit number of 0
		bitNumber = 0;
		// clear all the bits in the BitVector object bits
		bits.reset();
		// parent of our current leaf node
		parent = tree[i].parent;
		// identify the current node
		current = i;

		// continue generating bits until we hit the root,
		// whose parent is 0
		while (parent != 0)
		{
			// if the current node is the right child
			// of parent, add a 1 to bits at bitNumber.
			// otherwise, the bit is a 0, and bits
			// began with all zeros
			if (tree[parent].right == current)
				bits.set(bitNumber);
			// advance to the next bit number
			bitNumber++;
			// find the next parent
			current = parent;
			parent = tree[current].parent;
		}

		// the concluding value of bitNumber is the number of
		// bits in the Huffman code for tree[i].ch
		tree[i].numberOfBits = bitNumber;

		// copy the Huffman code from bits to tree[i].bits.
		// the order must be reversed
		for (j=bitNumber-1; j >= 0; j--)
			if (bits.test(j))
				tree[i].bits.set(bitNumber-1-j);

		// add the bit contribution of the character
		// to the total number of bits. in other words,
		// add the path weight of the leaf node to the
		// external path weight
		totalBits += bitNumber * tree[i].freq;
	}
}

void HCompress::mem_to_file(bit_vector& bv,fstream& ostr)
{
	// �����޷�ֱ�ӽ�������bit����vector<bool>���ݵ��ļ�
	// �����ַ�����ostringstream��λ��ת���������ݵ��ļ���
	ostringstream os;
	// λ�����а������ֽڵ�Ԫ���������β���������ֽڣ�
	// ����Ϊ���ֽ�
	int bytecnt = (bv.size()+7) >> 3;
	// bitset�������ת��Ϊunsigned long�ķ���
	bitset<8> btemp;
	for (int i = 0; i < bytecnt; i++)
	{
		// ������ÿ8λת��Ϊbitset<8>����
		// �ٽ�һ��ת��Ϊunsigned long
		for(int j=0; j<8; j++)
			btemp[j]= bv[8*i+j];
		char ch=btemp.to_ulong();
		ostr.put(ch);
	  		// ��������bit���д��ڴ洫�ݵ��ļ���
	}
}


void HCompress::writeCompressedData()
{
	// ��������ѹ���ļ�Huffman���λ����
	bit_vector compressedData(totalBits,false);
	int bitPos, i, j;
	unsigned char ch;

	// ΪԴ�ļ����end-of-file״̬���
	// �����ļ�ָ����Ϊ�ļ��Ŀ�ʼλ��
	source.clear();
	source.seekg(0, ios::beg);

	// bitPos���ڽ�bitsλ�����compressedData��
	bitPos = 0;

	// �ٴζ�ȡԴ�ļ�
	// ����compressedData������Huffman��
	while (true)
	{
		// ��ȡ��һ���ַ�
		ch = source.get();

		if (!source)
			break;

		// ����ch�����ڵ��index
		i = charLoc[ch];

		// ��tree[i].ch��λ�����λ������
		for (j=0;j < tree[i].numberOfBits; j++)
		{
			// ��tree[i].bits[j]Ϊ1ʱ��
			// ��compressedData��Ӧλ��λ
			if (tree[i].bits.test(j))
				compressedData[bitPos] = true;
			// һֱ��bitPos��ǰ�ƽ�
			bitPos++;
		}
	}

	// ��λ�����ڴ�compressedData��д�뵽�����ļ�
	mem_to_file(compressedData,dest);
}

void HCompress::treeData()
{
	int i, j;

	cout << "Huffman���� " << treeSize << " ��Ŀ, ���ڵ����� = "
		  << treeSize-1 << endl << endl;

	// table header
	cout <<  "����\t" << "����\t"
		  << "Ƶ��\t" << "���ڵ�\t"
		  << "���ӽڵ�\t" << "���ӽڵ�\t"
		  << "Bit��\t" << "bit��" << endl;

	// generate the table lines
	for (i=0;i < treeSize;i++)
	{
		cout << i << "\t";
		if (' ' <= tree[i].ch && tree[i].ch <= '~')
			cout << tree[i].ch << "\t";
		else if (i < numberLeaves)
		{
			cout << hex
				  << int(tree[i].ch) << "\t";
		}
		else
			cout << "Int"<< "\t";
		cout << tree[i].freq << "\t"
			  << tree[i].parent << "\t"
			  << tree[i].left<< "\t\t" << tree[i].right<< "\t\t";
		if (tree[i].numberOfBits != 0)
			  cout << tree[i].numberOfBits << "\t";
		for (j=0;j < tree[i].numberOfBits;j++)
			if (tree[i].bits[j])
				// only use setw(7) once
				//if (j == 0)
				//	cout << setw(7) << 1;
				//else
					cout << 1;
			else
				// only use setw(7) once
				//if (j == 0)
				//	cout << setw(7) << 0;
				//else
					cout << 0;
		cout << endl;
	}
	cout << endl;
}

// constructor must initialize charFreq and charLoc to
// have MAXCHARS characters
HCompress::HCompress(const string& fname, bool v):
	charFreq(MAXCHARS), charLoc(MAXCHARS), verbose(v), filesOpen(false)
{
	setFile(fname);
}

void HCompress::setFile(const string& fname)
{
	string ofname;
	int i;

	if (filesOpen)
	{
		source.close();
		dest.close();
	}

	// input using binary mode. we don't want the end of line
	// sequence translated to '\n'
	source.open(fname.c_str(), ios::in | ios::binary);
	ofname = fname;

	// if the original file name ends with an extension (".xxx"),
	// remove the extension. in any case, add the extension ".huf".

	// find the last occurrence of '.'
	if ((i = ofname.find_last_of('.')) != -1)
		// there is an extension. remove everything
		// from '.' to the end of the string
		ofname.erase(i);
	// add ".huf" as the extension
	ofname += ".huf";

	// open the compressed image file in binary mode
	dest.open(ofname.c_str(), ios::out | ios::binary | ios::trunc);
	filesOpen = true;
}

void HCompress::compress()
{
	int i;
	DiskHuffNode tmp;

	if (verbose)
		cout << "Դ�ļ��ַ���Ƶ�ȷ����� ..." << endl;
	// ִ��Ƶ�ȷ���
	freqAnalysis();

	if (verbose)
		cout << "����Huffman���� ..." << endl;
	// ����Huffman��
	buildTree();

	if (verbose)
		cout << "����Huffman���� ..." << endl << endl;
	// Ϊÿ���ַ�����Huffman�룬������ѹ���ַ��е����ַ���Ŀ
	generateCodes();

	// ���ѡ��verbose����ʱ�������ɣ��������������
	if (verbose)
		treeData();

	if (verbose)
		cout << "����ѹ���ļ��� ..." << endl << endl;
	// �������С
	dest.write((char *)&treeSize, sizeof(short));
	
	// �������ע������ֻ���HuffNode����Ļ��ಿ�֣�
	// ��ѹ��Huffman����Ҫ�Ľ����ַ����ӽڵ�ָ��
	for (i=0; i < treeSize; i++)
	{
		tmp = (DiskHuffNode)tree[i];
		dest.write((char *) &tmp, sizeof(DiskHuffNode));
	}
	// ���ڽ����е����ַ���Դ�ļ���
	// ɾ�����ڸ���Ҷ�ڵ�����ӵ�������۵Ķ���λ
	if (oneChar)
		totalBits--;
	// ���Huffmanѹ���ļ��ı�������Ŀ
	dest.write((char *)&totalBits, sizeof(unsigned long));
	// ��������Դ�ļ�����Huffman���в��Ҷ�Ӧÿ���ַ���Huffman��
	// д�뵽dest�ļ���
	writeCompressedData();

	// �ر�Դ�ļ���Ŀ���ļ�
	source.close();
	dest.close();

	filesOpen = false;
}

void HCompress::dispCompRatio() const
{
	double compRatio;
	//ѹ���ļ���С
	unsigned long out_bytecnt = sizeof(short) + treeSize*sizeof(DiskHuffNode) +
			 sizeof(unsigned long) + (totalBits+7)/8;

	// determine the ratio of the size of the compressed file
	// to the size of the orginal
	compRatio = double(fileSize)/out_bytecnt;
	cout << "Դ�ļ���С = "	<< fileSize << "��bytes��" << endl
		 << "ѹ���ļ���С = " << out_bytecnt << "��bytes��" << endl
		 <<	"ѹ���� = " << setprecision(3) << compRatio << endl << endl;
}

int HCompress::size() const
{
	return treeSize;
}

void HCompress::displayTree() const
{
	displayHuffmanTree(tree);
	cout << endl << endl << endl;
}

#endif	// HUFFMAN_COMPRESS
