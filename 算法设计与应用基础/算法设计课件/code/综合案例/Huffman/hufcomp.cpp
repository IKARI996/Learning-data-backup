// File: hcompress.cpp
// the program demonstrates Huffman compression. the user
// enters the name of a file to compress and indicates
// whether the verbose option is desired. after compressing
// the file, the program outputs the compression ratio.
// if the Huffman tree has no more than 11 nodes, the tree
// is displayed

#pragma warning(disable : 4267 4244)

#include <iostream>
#include <iomanip>			//For setpricision
#include <string>

#include "HCompress.h"		// HCompress class

using namespace std;

int main()
{
	string fileName;
	bool verbose;
	char response;

	// prompt for the source file name and whether
	// to use the verbose option for Huffman compression
	cout << "������Դ�ļ���: ";
	cin >> fileName;
	cout << "��ʾ����״̬��Ϣ�� (y or n): ";
	cin >> response;
	if (response == 'y')
		verbose = true;
	else
		verbose = false;

	cout << endl;

	// declare an HCompress object
	HCompress hc(fileName, verbose);

	// compress the file
	hc.compress();

	// output the compression ratio
	hc.dispCompRatio();

	if (hc.size() <= 11)
	{
		// display the Huffman tree if the tree is small
		cout << "Huffman ��Ϊ��" << endl;
		hc.displayTree();
	}
	system("pause");
	return 0;
}

/*
Run 1:

������Դ�ļ���: demo.dat
   (16000 'a'   4000 'b'   8000 'c'   6000 'd'   20000 'e'   3000 'f')
��ʾ����״̬��Ϣ�� (y or n): y

Դ�ļ��ַ���Ƶ�ȷ����� ...
   File size: 57000 characters
   Number of unique characters: 6

����Huffman���� ...
   Number of nodes in Huffman tree: 11

����Huffman���� ...

Huffman���� 11 ��Ŀ, ���ڵ����� = 10

����    ����    Ƶ��    ���ڵ�  ���ӽڵ�        ���ӽڵ�        Bit��   bit��
0       a       16000   9       -1              -1              2       10
1       b       4000    6       -1              -1              4       0111
2       c       8000    8       -1              -1              2       00
3       d       6000    7       -1              -1              3       010
4       e       20000   9       -1              -1              2       11
5       f       3000    6       -1              -1              4       0110
6       Int     7000    7       5               1
7       Int     13000   8       3               6
8       Int     21000   10      2               7
9       Int     36000   10      0               4
10      Int     57000   0       8               9

����ѹ���ļ��� ...

Դ�ļ���С = 57000��bytes��
ѹ���ļ���С = 16822��bytes��
ѹ���� = 3.39

                                                  57000

        21000                                                   36000

 c:8000               13000                              a:16000       e:20000

               d:6000               7000

                             f:3000        b:4000



Run 2:


������Դ�ļ���: webster.dict
��ʾ����״̬��Ϣ�� (y or n): n

Դ�ļ���С = 2486904��bytes��
ѹ���ļ���С = 1355712��bytes��
ѹ���� = 1.83


Run 3:


������Դ�ļ���: mspaint.exe
��ʾ����״̬��Ϣ�� (y or n): n

Դ�ļ���С = 344064��bytes��
ѹ���ļ���С = 253663��bytes��
ѹ���� = 1.36

*/
