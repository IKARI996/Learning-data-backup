#ifndef VIDEO_CLASS
#define VIDEO_CLASS

#include <iostream>
#include <string>

using namespace std;

class Video
{
public:
	// ���캯������ʼ��filmTitle��numCopies
	Video(const string& film = "", int copies = 1):
		filmTitle(film), numCopies(copies)
	{}

	// ������Ŀ��n��ע�⣺���n�Ǹ���������Ǽ�ȥ
	void updateCopies(int n)
	{
		numCopies += n;
	}
	
	// ����ӰƬ������Ŀ
	int getCopies()
	{
		return numCopies;
	}
	
	// �����Video��������ͬtitle�����������
	friend bool operator== (const Video& lhs, const Video& rhs)
	{
		return lhs.filmTitle == rhs.filmTitle;
	}

	// ��filmTitleΪ�ؼ���Ƚ�Video����
	friend bool operator< (const Video& lhs, const Video& rhs)
	{
		return lhs.filmTitle < rhs.filmTitle;
	}

	// ���Video����
	friend ostream& operator<< (ostream& ostr, const Video& obj)
	{ 
		ostr << obj.filmTitle << " (" << obj.numCopies << ")" ;
		return ostr;
	}
private:
	// ӰƬ����
	string filmTitle;
	// ������Ŀ(>= 0)
	int numCopies;
};

#endif	// VIDEO_CLASS
