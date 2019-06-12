#include <iostream>
#include "AES.h"
#include "Base64.h"
using namespace std;

const char original_key[17] = "16337341zhuzhiru";
const char original_iv[17] = "123";

string EncryptionAES(const string& strSrc) { //AES����
	size_t length = strSrc.length();
	int block_num = length / BLOCK_SIZE + 1;
	//����
	char* szDataIn = new char[block_num * BLOCK_SIZE + 1];
	memset(szDataIn, 0x00, block_num * BLOCK_SIZE + 1);

#pragma warning(disable:4996)
	strcpy(szDataIn, strSrc.c_str());

	//����PKCS7Padding��䡣
	int k = length % BLOCK_SIZE;
	int j = length / BLOCK_SIZE;
	int padding = BLOCK_SIZE - k;
	for (int i = 0; i < padding; i++)
		szDataIn[j * BLOCK_SIZE + k + i] = padding;
	szDataIn[block_num * BLOCK_SIZE] = '\0';

	//���ܺ������
	char *szDataOut = new char[block_num * BLOCK_SIZE + 1];
	memset(szDataOut, 0, block_num * BLOCK_SIZE + 1);

	//���н���AES��CBCģʽ����
	AES aes;
	aes.MakeKey(original_key, original_iv, 16, 16);
	aes.Encrypt(szDataIn, szDataOut, block_num * BLOCK_SIZE, AES::CBC);
	string str = base64_encode((unsigned char*)szDataOut,
		block_num * BLOCK_SIZE);
	delete[] szDataIn;
	delete[] szDataOut;
	return str;
}

string DecryptionAES(const string& strSrc) { //AES����
	string strData = base64_decode(strSrc);
	size_t length = strData.length();
	//����
	char *szDataIn = new char[length + 1];
	memcpy(szDataIn, strData.c_str(), length + 1);
	//����
	char *szDataOut = new char[length + 1];
	memcpy(szDataOut, strData.c_str(), length + 1);

	//����AES��CBCģʽ����
	AES aes;
	aes.MakeKey(original_key, original_iv, 16, 16);
	aes.Decrypt(szDataIn, szDataOut, length, AES::CBC);

	//ȥPKCS7Padding���
	if (0x00 < szDataOut[length - 1] <= 0x16) {
		int tmp = szDataOut[length - 1];
		for (int i = length - 1; i >= (length - tmp); i--) {
			if (szDataOut[i] != tmp) {
				memset(szDataOut, 0, length);
				cout << "ȥ���ʧ�ܣ����ܳ�����" << endl;
				break;
			}
			else
				szDataOut[i] = 0;
		}
	}
	string strDest(szDataOut);
	delete[] szDataIn;
	delete[] szDataOut;
	return strDest;
}

string input_P() {
	cout << "���������ģ�" << endl;
	string temp;
	getline(cin, temp);
	return temp;
}

string input_C() {
	cout << "���������ģ�" << endl;
	string temp;
	getline(cin, temp);
	return temp;
}

char EnterNum() {
	string temp;
	getline(cin, temp);
	if (temp == "1") return '1';
	else if (temp == "2") return '2';
	else return '0';
}

void main_loop() {
	bool flag = true;
	while (flag) {
		char result = EnterNum();
		if (result == '1') {
			string str1 = input_P();
			string str2 = EncryptionAES(str1);
			cout << "���ܺ�:" << str2 << endl;
			flag = false;
		}
		else if (result == '2') {
			string str2 = input_C();
			string str3 = DecryptionAES(str2);
			cout << "���ܺ�:" << str3 << endl;
			flag = false;
		}
		else if (result == '0')
			cout << "����������������룺";
	}
}


int main()
{
	while (true) {
		cout << endl << "ָ�1.��������	2.��������" << endl << "�����룺";
		main_loop();
	loop:
		cout << "�����Ƿ������1.����  2.�˳�	";
		char Continue_index = EnterNum();
		if (Continue_index == '1') continue;
		else if (Continue_index == '2') break;
		else if (Continue_index == '0') {
			cout << "����������������룺";
			goto loop;
		}
	}
	return 0;
}

