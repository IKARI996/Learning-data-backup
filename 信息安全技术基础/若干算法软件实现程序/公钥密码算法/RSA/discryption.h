#include<fstream.h>
#include<stdlib.h>//for exit()
#include<iostream.h>

void discryption()
{

 //ģm�������ݵļ���
//		cout<<"�����������Կ(d,n)";
		int e,n;
		cin>>e >>n;
	                	
		int array[20];        //��e�ö����Ʊ�ʾ
		for(int i=0;i<20;i++)
			array[i]=9;
		
		int temp;
		temp=e;

		int j=19;
		while(temp>0){
	    	array[j]=temp%2;
			temp=temp/2;
			j--;
		}
		
        int length=0;
		for(int k=0;k<20;k++)     //�����ݵ�λ��
			if(array[k]!=9){
			//	cout<<array[k];
				length++;
			}
			

		    
		cout<<endl<<endl;
	//	cout<<"length="<<length;
		cout<<endl<<endl;

	/*	for(int ii=length;ii>=1;ii--){
			
			cout<<array[19-ii+1];
		}*/

	ifstream in_file("en_text.txt");//   open file to read data
	if(!in_file){
		cout<<"error opening text.txt."<<endl;
		exit(1);
	}
	ofstream out_file("dis_en_text.txt"); // open file to write data,after encryption.
	if(!out_file){
		cout<<"error opening en_text.txt."<<endl;
		exit(1);
	}

	//char letter;
    int c_i;
	while(!in_file.eof()){        //get a letter from the reading file
		in_file >> c_i;
		//cout<< c_i ;
	    //c_i=int(letter);


    	int cc,dd;            //encrypt the letter,and write the en_letter to en_text.txt
		cc=0;
		dd=1;
		//int c_i=7;
		for(int ii=length;ii>=1;ii--){
			cc=2*cc;
			dd=(dd*dd)%n;
			if(array[20-ii]==1){  cc=cc+1;dd=(dd*c_i)%n;}
		}
		//cout<<"result is "<<dd;

	//	char en_letter= char(dd);
	//	cout<<" --> ";
	//	cout<< dd<<" --> "<<char(dd)<<endl;
		out_file<< char(dd);

		//cout<<c_i<<endl;
	}  
	in_file.close();
	out_file.close();
}
