/**for Stream tools*/
import java.io.*;	

/** ��Ϣϵͳ��ȫ������ҵ
 *<P> ��������ڲ�����Կ��˽Կ�������û�ָ�����ļ�.���㷨�������ɹ��캯��������������mothod��pre����none.
 * @author ���ѧԺ �ⵤ 00234015
 * @version 1.0
*/
class makeKey 
{
	/**RSA�㷨�е�����Ԫ��
	*pub_n->n
	*pub_q->q
	*pub_p->p
	*pub_e->e
	*pub_d->d
	*/
	long pub_n,pub_q,pub_p,pub_e,pub_d;

	
	/** witness�㷨(�������һ��Ԫ���Ƿ�������
	 *<P>pre:none.
	 *<P>post:dicide whether the number inputed is a element number.
	 *@param n the number to test.
	*/
	boolean witness(long n)
	{
		//���Դ����ļ�����
		int counter=0;
		//��n-1ת���̶������ַ���b
		String b=Long.toBinaryString(n-1);

		while(true)
		{
			//�������һ��a
			long a=(long)((n-1)*Math.random()+1);
			long d=1;
			
			for(int i=b.length()-1;i>=0;i--)
			{
				long x=d;
				d=(x*x)%n;
				if(d==1&&x!=1&&x!=n-1)
					return false;
			    /**���Դ���
				System.out.println("i="+i+" x="+x+" d="+d+" b"+i+"="+b.charAt(b.length()-1-i));
				*/
				if(b.charAt(b.length()-1-i)=='1')
					d=(d*a)%n;
			}
			if(d==1)
				counter++;
			else return false;

			//�������100��a��ͨ����⣬�����n��һ��������(�����������㷨��ȫ)
			//�����������ڹ��캯���л���һ�㱣��
			if(counter>=100)
				return true;
		}
	}
	
	/**����һ��ָ����С������(�������ӽ�)
	 *<P>pre:None.
	 *<P>post:return a element number that approximate the parameter.
	 *@param max_num to limit,or to say confin,the generating number.
	*/
	long eleGenerator(long max_num)
	{
		long p=(long)(Math.random()*max_num+1);
		//ʹpΪ����
		p=p%2==0?p+1:p;
		//��witness�㷨��p�Ƿ�Ϊ����
		while(!witness(p))
			p-=2;
		return p;
	}
	
	/**����RSA�е�p��q��n and e
	 *<P>pre:None.
	 *<P>post:generate "p��q��n��e" in RSA.
	*/
	void PQNEDGenerator()
	{
	//p�ķ�Χ����2^30���������(eleGenerator�ľ������ݼ���)
		pub_p=eleGenerator((long)(Math.random()*Math.pow(2,30)));
	//q�ķ�Χ����2^20���������,��p������4��ʮ�����Ա����ܵ�����(eleGenerator�ľ������ݼ���)
		pub_q=eleGenerator((long)(Math.random()*Math.pow(2,20)));
	//����n
		pub_n=pub_p*pub_q;
	//e������
		pub_e=(long)((pub_p-1)*(pub_q-1)*Math.random());
		//ʹeΪ����
		pub_e=pub_e%2==0?pub_e-1:pub_e;
		pub_d=stein(pub_e,(pub_p-1)*(pub_q-1));
		while(pub_d==-999)
		{
			pub_e-=2;
			pub_d=stein(pub_e,(pub_p-1)*(pub_q-1));
		}
	}

	/**Stein�㷨(����(e,m),����(e,m)=1����������e����ģm����Ԫ)
	 *<P>pre:none.
	 *<P>post:�ж�(e,m)�Ƿ����1�����������1����-999���������1����e����ģm����Ԫ��
	 *@param e Stein�㷨�е�"e".
	 *@param m Stein�㷨�е�"m".
	*/
	long stein(long e,long m)
	{
		long s0,s,r,r0,x,y,u,v;
		s0=s=e;
		r0=r=m;
		x=v=0;
		y=u=1;

		while(r!=0)
		{
			/**���Դ���
			System.out.println("r="+r);
			System.out.println("u="+u);
			*/
			if(r%2==1)
			{
				if(s>r)
				{
					long temp=s;s=r;r=temp;
					temp=x;x=u;u=temp;
					temp=y;y=v;v=temp;
				}
				r-=s;x-=u;y-=v;
			}
			else
				if(y%2==0)
				{
					r/=2;x/=2;y/=2;
				}
				else
				{
					if(y<0)
					{
						r/=2;
						y=(y+s0)/2;
						x=(x-r0)/2;
					}
					else
					{
						r/=2;
						y=(y-s0)/2;
						x=(x+r0)/2;
					}
				}
		}
		if(s==1)
			return u%m<0?u%m+m:u%m;
		else return -999;
	}
	/**�����п��������ģm�������ݵ��㷨
	 *<P>pre:none.
	 *<P>post:����a^t(mod n);
	 *@param a a^t(mod n)�е�a
	 *@param t a^t(mod n)�е�t
	 *@param n a^t(mod n)�е�n
	*/
	long powMod(long a,long t,long n)
	{
		long c=0;
		long d=1;
		String b=Long.toBinaryString(t);
		
		for(int i=b.length()-1;i>=0;i--)
		{
			c*=2;
			d=(d*d)%n;
			if(b.charAt((b.length()-1-i))=='1')
			{
				c+=1;
				d=(d*a)%n;
			}
			/**���Դ���
			System.out.print("i="+i);
			System.out.print(" c="+c);
			System.out.print(" d="+d);
			System.out.println();
			*/
		}
		return d;
	}
		

	/**���캯��
	 *<P>�����ǿ��Ƴ�������̣������������¹�����
	 *<P>1,ģ����ܽ���50�Σ��Է�ֹp,q��������(witness�㷨�Ĳ�����).
	 *<P>2,����RSA�㷨�е�p,q,r,s.
	 *<P>3,���湫Կ(e��n)��˽Կ(d��n).
	*/
	makeKey()
	{
		/**witness�����Ĳ��Դ���
		long test=(long)(Math.pow(2,13)-1);
		System.out.println(witness(test));
		*/

		/**elementGenerator�����Ĳ��Դ���
		long test=eleGenerator((long)(Math.random()*Math.pow(2,30)));
		System.out.println(test);
		System.out.println(witness(test));
		*/
		
		/**PQNEDGenerator�����Ĳ��Դ���
		PQNEDGenerator();
		System.out.println("p="+pub_p);
		System.out.println("q="+pub_q);
		System.out.println("n="+pub_n);
		System.out.println("e="+pub_e);
		System.out.println("d="+pub_d);
		*/
				
		/**stein�����Ĳ��Դ���
		System.out.println(stein(5,96));
		*/
		
		//ģ����ܽ���50�Σ��Է�ֹp,q��������(witness�㷨�Ĳ�����)
		boolean secure=false;
		while(!secure)
		{
			PQNEDGenerator();
			for(int i=0;i<50;i++)
			{
				long test=(long)(Math.pow(2,20)*Math.random());
				long c=powMod(test,pub_e,pub_n);
				long m=powMod(c,pub_d,pub_n);
				if(test==m)
				{
					secure=true;
				}
				else 
				{
					secure=false;
					break;
				}
			}
		}
		System.out.println("��Կ�ɹ�����");
		
		//�����Ǳ��湫Կ˽Կ��io����
		String filename=" ";
		try{
			BufferedReader in1=new BufferedReader(
				new InputStreamReader(System.in));

			System.out.println("�����빫Կ��ŵ��ļ���:");
			filename=in1.readLine();
			DataOutputStream key=new DataOutputStream(
				new BufferedOutputStream(
					new FileOutputStream(filename)));
			key.writeLong(pub_e);
			key.writeLong(pub_n);
			key.close();
			System.out.println("��Կ�ѱ���!");

			System.out.println("������˽Կ��ŵ��ļ���:");
			filename=in1.readLine();
			key=new DataOutputStream(
				new BufferedOutputStream(
					new FileOutputStream(filename)));
			key.writeLong(pub_d);
			key.writeLong(pub_n);
			key.close();

			System.out.println("��Կ��˽Կ�������");
		}
		catch(IOException e){
			System.err.println("�ļ�д��������������ʽ!\n��ȷ��ʽ��data.dat��c:\\data.dat");
		}
	}

	public static void main(String args[])
	{
		new makeKey();
	}
}
