

#include<iostream.h>


void create_key()

{
	cout<<"RSA��Կ�Ƽ����㷨����ʾ����"<<endl<<endl;
	cout<<"�㷨�����ɹ�Կ��˽Կ��"<<endl;
	cout<<"�����������㹻���������";
	long int p,q;
	cin>>p >>q;

    long int n=p*q;
	long int m=(p-1)*(q-1);

	//����չ��Euclid�㷨��Կ��˽Կ
	bool select_again=true;
	while(select_again){
    	long int k,r,u,v,x,y,s,t;
     	long int a;
    	cout<<"������һ�������Ե���Կe ";
    	cin>> a;

	    k=a;
	    r=m;
    	u=1;
	    v=0;
    	x=0;
	    y=1;

	    while(r!=0){
		   q=k/r;
		   s=u-q*x;
		   t=v-q*y;
		   k=r;
		   r=a*s+m*t;
		   u=x;
		   v=y;
		   x=s;
		   y=t;
		}

	   if(k>1){
		   cout<<"���벻�Ϸ�,���������룺";

	   }
	   else{
		   select_again=false;
		   cout<<"��Կ:("<<a<<","<<n<<").˽Կ:"<<"d��";
		   if(u%m<0)cout<<u%m+m;
		   else cout<<u%m;
	   }
	   }

}

