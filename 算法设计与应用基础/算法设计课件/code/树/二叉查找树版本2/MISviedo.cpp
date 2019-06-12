// FileName MISvideo.cpp
// С�������̵��������ϵͳ
// ���Video��洢��Ӱ���ƺ͸�����Ŀ�����ṩ�����Ĳ����ӿ�
// Video�����������Ƚϲ�������������Ϊ�����������������������
// ����ܹ����£�
// ���ȣ�����setupInventory()��"films.dat"�ļ���ȡ��Ӱ���ƣ�����Video����
//       ������Щ���������BinSearchTree����inventory��
//       �г�inventory�е�����ӰƬ
// ֮�󣬽���һ������ѭ������Ա����˿�����rentӰƬ��returnӰƬ
//       ��������Done�Խ���һ�칤��
//       �������裬�����rentalTransaction()
//       ����ǹ黹�������returnTransaction()

#include <iostream>
#include <fstream>
#include <string>
#include <utility>				// for pair class

#include "BinSearchTree.h"		// BinSearchTree class
#include "Video.h"				// Video class


using namespace std;

// ���ļ�"films.dat"��ʼ��inventory��
void setupInventory(BinSearchTree<Video>& inventory);

// ����ӰƬ�黹����
void returnTransaction(BinSearchTree<Video>& inventory,
			  BinSearchTree<Video>& rentals, const string& filmName);

// ����ӰƬ�������
void rentalTransaction(BinSearchTree<Video>& inventory,
			  BinSearchTree<Video>& rentals, const string& filmName);

//�����������������
template <typename T>
void writeBSTree(const BinSearchTree<T>& t, const string& separator);

int main()
{
	// ���ͳ����嵥
	BinSearchTree<Video> inventory, rentals;
	// find()�ķ���ֵ��ֵ��filmIter
	BinSearchTree<Video>::iterator filmIter;
	// ���Ե�Ա�����룺��������
	// transactionType = "Rent", "Return",�� "Done"
	string transactionType;

	// �˿�����ĵ�Ӱ
	string filmName;

	// ���벢�������ļ�
	setupInventory(inventory);
	cout << "��ʼ����嵥:" << endl;
	writeBSTree(inventory, "\n");
	cout << endl;

	// ���ݵ���˿͵���������"Rental" �� "Return" ��ӰƬ���ƣ�
	// �����롰Done������ֹ����
	// ���� "Rent"����, ����渱����Ŀ����1�������ӵ�������ݿ�
	// ����"Return"����,�������Ƴ�������ݿ⣬���ĸ�������1
	cout << "�������������� (Rent, Return, Done)�����Կո�" << endl;
	cout << "����������ӰƬ���ƣ��������س�ȷ��" << endl << endl;
	while (true)
	{
		// �����������ͣ��������ͱ����Կո���ֹ
		cout << "����: ";
		getline(cin, transactionType, ' ');
		// ����� "Done", ��ֹѭ��
		if (transactionType == "Done")
			break;

		// ��ȡӰƬ����
		getline(cin, filmName,'\n');

		if (transactionType == "Return")
			returnTransaction(inventory, rentals, filmName);
		else
			rentalTransaction(inventory, rentals, filmName);
	}
	cout << endl;

	// ������յĽ����Ӱ�Ϳ���嵥
	cout << "�ѽ���ĵ�Ӱ: " << endl << endl;
	writeBSTree(rentals, "\n");
	cout << endl;
	cout << "�����ڿ���еĵ�Ӱ:" << endl << endl;
	writeBSTree(inventory, "\n");

	system("pause");
	return 0;
}

void setupInventory(BinSearchTree<Video>& inventory)
{
	ifstream filmFile;		// ������
	string filmName;		// ���ڼ�¼��Ӱ����
	// ��BinSearchTree insert()һ��ʹ��
	pair<BinSearchTree<Video>::iterator, bool> p;

	// ���ļ� "films.dat"
	filmFile.open("films.dat");
	if (!filmFile)
	{
		cerr << "�ļ�'films.dat'δ�ҵ�!" << endl;
		exit(1);
	}

	// ��ȡ����ֱ������EOF��
	// ��inventory�б��в����Ӱ����
	while(true)
	{
		getline(filmFile,filmName,'\n');
		if (!filmFile)
			break;

		// ���Բ��룬������ȡĬ��ֵ1
		p = inventory.insert(Video(filmName));
		// �鿴Video�����Ƿ��Ѵ���inventory��
		if (p.second == false)
			// �Ѿ���inventory�У�����������1
			(*(p.first)).updateCopies(1);
	}
}

void returnTransaction(BinSearchTree<Video>& inventory,
			  BinSearchTree<Video>& rentals, const string& filmName)
{
	BinSearchTree<Video>::iterator filmIter;

	// locate the film in the return database
	filmIter = rentals.find(Video(filmName));
	// if there is only 1 copy left, erase the entry;
	// otherwise, decrease the number of rented copies
	// by 1
	if ((*filmIter).getCopies() == 1)
		rentals.erase(filmIter);
	else
		(*filmIter).updateCopies(-1);

	// locate the film in the inventory and increase the
	// number of copies available by 1
	filmIter = inventory.find(Video(filmName));
	(*filmIter).updateCopies(1);
	cout << "ӰƬ ��" << filmName << "���ɹ��黹" << endl ;

}

void rentalTransaction(BinSearchTree<Video>& inventory,
			  BinSearchTree<Video>& rentals, const string& filmName)
{
	BinSearchTree<Video>::iterator filmIter;
	// pObj��BinSearchTree��insert()һ��ʹ��
	pair<BinSearchTree<Video>::iterator,bool> pObj;

	// ӰƬ�ɽ�ô?
	filmIter = inventory.find(Video(filmName));
	if ( filmIter == inventory.end())
	{
		// ӰƬ�����̵�Ŀ���嵥��
		cout << "ӰƬ ��" << filmName << "�������̵����嵥�С���" 
		 << "�˴����ʧ��" << endl;
	}
	else if ((*filmIter).getCopies() == 0)
	{
		// ���и������ѱ����
		cout << "ӰƬ ��" << filmName << "�������и��������������" 
			<< "�˴����ʧ��" << endl;
	}
	else
	{
		// ������еĸ�����Ŀ��1
		(*filmIter).updateCopies(-1);
		// ���Խ�ӰƬ����rentalList
		// ����ɹ����룬��rental���ⲿӰƬ��������ĿΪ1
		pObj = rentals.insert(Video(filmName));
		// ���δ���룬���ѽ��������Ŀ��1
		if (pObj.second == false)
			(*(pObj.first)).updateCopies(1);
		cout << "ӰƬ ��"<< filmName << "���ɹ����" << endl;
	}
}


//�����������������
template <typename T>
void writeBSTree(const BinSearchTree<T>& t, const string& separator = "  ")
{
	BinSearchTree<T>::const_iterator iter = t.begin();

	while (iter != t.end())
	{
		cout << *iter << separator;
		iter++;
	}
}
/*
Run:

Initial inventory list:
Frequency (1)
Gladiator (2)
Lord of the Rings (4)
U-571 (2)

Transactions: Enter type (Rent, Return, Done)
followed by film name or space if done

Transaction: Rent Gladiator
Transaction: Rent Frequency
Transaction: Rent Shaft
Film Shaft is not in inventory
Transaction: Rent Frequency
All copies of Frequency are checked out
Transaction: Done

Rented Films:

Frequency (1)
Gladiator (1)

Films Remaining in Inventory:

Frequency (0)
Gladiator (1)
Lord of the Rings (4)
U-571 (2)
*/
