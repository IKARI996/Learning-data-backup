#include <iostream>
#include <cmath>
using namespace std;

class Base

{

protected:

       double result, a, b, step;//result����ֵ��a�������ޣ�b�������ޣ�step��������ʽ�У�step=(b-a)/n

       int n;//����������ʽ�е�n

public:

       virtual double fun(double x) = 0;//��������������Ϊ���麯��������������

       virtual void integrate(){}

       Base(double aa=0, double bb=0, int nn=100):a(aa),b(bb),n(nn),result(0.0){}

       void print()

       {

              cout<<result<<endl;

       }

};

class Rectangle:public Base
{
public:
	Rectangle(double aa=0, double bb=0, int nn=100):Base(aa,bb,nn){}
	virtual double fun(double x) {
		return sin(x);
	}
	virtual void integrate(){
		double step = (b - a) / n,i,j,ans;
		j = fun(a);
		for(i = 0;i <= n;i++){
			j += fun(a + step * i);
		}
		ans = step * j;
		result = ans;
	}
};

class Ladder:public Base
{
public:
	Ladder(double aa=0, double bb=0, int nn=100):Base(aa,bb,nn){}
	virtual double fun(double x) {
		return sin(x);
	}
	virtual void integrate(){
		double step = (b - a) / n,i,j,ans;
		j = fun(a) + fun(b);
		for(i = 0;i < n;i++) {
			j += fun(a + step * i) * 2;
		}
		ans = step * j / 2;
		result = ans;
	}
};

class Simpson:public Base
{
public:
	Simpson(double aa=0, double bb=0, int nn=100):Base(aa,bb,nn){}
	virtual double fun(double x) {
		return sin(x);
	}
	virtual void integrate(){
		double step = (b - a) / n,i,j,ans1 = ans2 = 0,ans;
		j = fun(a) + fun(b);
		for(i = 1;i <=n - 1;i += 2)
			ans1 += fun(a + step * i);
		ans1 *= 4;
		for(i = 2;i <= n - 2;i += 2)
			ans2 += fun(a + step * i);
		ans2 *= 2;
		ans = step / 3 * (j + ans1 + ans2);
		result = ans;
	}
};
