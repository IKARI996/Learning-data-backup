#ifndef HUFFMAN_DECOMPRESS
#define HUFFMAN_DECOMPRESS

#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <vector>
#include "HNode.h"					// DiskHuffNode class

typedef vector<bool> bit_vector;	//���ڴ�ű�ѹ���ļ�����

class HDecompress
{
public:
	HDecompress(const string& cname, const string& uname);
		// ���캯��������setFiles()��Huffmanѹ���ļ�cname
		// ��ָ������ļ���uname

	void setFiles(const string& cname, const string& uname);
		// ��Huffmanѹ���ļ�cname
		// ��ָ������ļ���uname
		// throws the fileOpenError exception if a file
		// cannot be opened
	void decompress();
		// �ļ���ѹ��

private:

	fstream source;
	fstream dest;
		// �������������
	void file_to_mem(bit_vector& bv,fstream& istr, unsigned long totalBits);
	// ��������bit���д��ڴ洫�ݵ��ļ���
	bool filesOpen;
		// Դ�ļ���Ŀ���ļ��Ƿ�򿪣�
};

HDecompress::HDecompress(const string& cname,
								 const string& uname): filesOpen(false)
{
	setFiles(cname, uname);
}

void HDecompress::setFiles(const string& cname, const string& uname)
{
	if (filesOpen)
	{
		source.close();
		dest.close();
	}

	// a Huffman compressed file is a binary file
	source.open(cname.c_str(), ios::in | ios::binary);
	// output using binary mode. we don't want '\n' expanded
	// to an end of line sequence. if the output file is a
	// textfile, its end of line characters were compressed
	// individually
	dest.open(uname.c_str(), ios::out | ios::binary | ios::trunc);
	filesOpen = true;
}


void HDecompress::file_to_mem(bit_vector &bv, 
							  std::fstream &istr, 
							  unsigned long totalBits)
{
	// λ�����е����ֽ���Ŀ��
	// ��������ĩ���ܵĲ������ֽڵ�β��λ��
	unsigned long bytecnt = totalBits>>3;
	// �������ֽڵ�β��λ������
	unsigned short retail = totalBits % 8;
	// ���ڽ��ֽڱ�ʾת��Ϊλ��ʾ
	typedef bitset<8> bitproxy;

	// ����bit����bv��С�����ɱ���bit����
	bv.resize(totalBits);
	// ���λ���ж���ĵ�ǰλ��
	unsigned long bitPos = 0;
	for(unsigned int i=0; i<bytecnt; i++)
	{
		// ���ֽڶ���Դ�ļ�
		char ch=istr.get();
		// ��ch���ֽڱ�ʾת��Ϊbit��ʾ
		bitproxy bp(ch);
		// ��ch��λ���Ƶ�λ������
		for(int j=0;j<8;j++,bitPos++)
		{
			bv[bitPos]=bp[j];
		}
	}
	if(retail)
	{	//���λ���д���β�����֣���������
		char ch=istr.get();
		bitproxy bp(ch);
		int i=0;
		while(bitPos<totalBits)
			bv[bitPos++]=bp[i++];
	}
}




void HDecompress::decompress()
{
	unsigned int i, bitPos;

	// ��ѹ���ļ��ж�ȡtreeSize��Huffman����С��
	// ��totalBits������λ���С��
	short treeSize;
	unsigned long totalBits;
	// ��ѹ���ļ��ж�ȡHuffman��������tree����������
	vector<DiskHuffNode> tree;
	// ��ѹ���ļ��ж�ȡtotalBits��bitλ����bitsλ������
	bit_vector bits;	
	// ����Huffman���Ĵ�С
	source.read((char *)&treeSize, sizeof(short));

	// �����洢Huffman����������С��
	// ��������
	tree.resize(treeSize);
	source.read((char *)&tree[0], sizeof(DiskHuffNode) * treeSize);

	// ����Huffman����λ������λ��
	source.read((char *)&totalBits, sizeof(unsigned long));

	// ��Huffman����λ���д��ļ������ڴ����ڽ�ѹ��
	file_to_mem(bits, source, totalBits);
	
	// ����Huffman������������������Ӧ�ַ�
	// �Ӷ��ָ�ԭʼ�ļ�
	bitPos = 0;
	while (bitPos < totalBits)
	{
		// �����ڵ�������λ��treeSize-1��
		i = treeSize-1;
		// ����bitsλ��Huffman�������»����±���
		// ֱ�����ǵ���Ҷ�ڵ㣬��ʼ�µĴӸ��ڵ�ı���
		while (tree[i].left != -1)
		{
			// �����ǰbitΪ0�����󣬷�������
			if (bits[bitPos] == 0)
				i = tree[i].left;
			else
				i = tree[i].right;
			// ��ǰλʹ����ϣ��ƽ�����һλ
			bitPos++;
		}
		// ����Ҷ�ڵ㣬����ַ����ļ�
		dest.put(tree[i].ch);
	}

	// �ر���������ļ���
	source.close();
	dest.close();

	filesOpen = false;
}

#endif	// HUFFMAN_DECOMPRESS
