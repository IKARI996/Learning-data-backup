/**for Stream tools*/
import java.io.*;	
/**for ArrayList*/
import java.util.*;

/** ��Ϣϵͳ��ȫ����
 *<P> ��������ڼ���.
 * @author ���ѧԺ �ⵤ 00234015 
 * @version 1.0
*/
class enCipher 
{
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
	
	/**�����㷨:
	 *<P>1,�ȶ�����ܵ�Ŀ���ļ��͹�Կ
	 *<P>2,��RSA�㷨��Ŀ���ļ����м���(ÿ8��bitΪһ�飬�����long��¼).
	 *<P>3,������ܽ��
	 *<P>pre:none
	 *<P>post:���ļ�����
	*/
	enCipher()
	{
		String filename;
		ArrayList mem_buffer=new ArrayList();
		try{

			BufferedReader in1=new BufferedReader(
				new InputStreamReader(System.in));
			System.out.println("������Ҫ�����ļ����ļ�����(·��):");
			filename=in1.readLine();
			DataInputStream infile=new DataInputStream(
				new BufferedInputStream(
					new FileInputStream(filename)));
			System.out.println("�����빫Կ���ļ���(·��)");
			filename=in1.readLine();
			DataInputStream key=new DataInputStream(
				new BufferedInputStream(
					new FileInputStream(filename)));
			long e=key.readLong();
			long n=key.readLong();

			while(infile.available()>0)
			{
				byte temp=infile.readByte();
				long c=powMod(temp,e,n);
				mem_buffer.add(new Long(c));
			}
			System.out.println("��ȡ���.");
			System.out.println("���������ĵĴ���ļ���(·��):");
			filename=in1.readLine();

			DataOutputStream out1=new DataOutputStream(
				new BufferedOutputStream(
					new FileOutputStream(filename)));
			for(int i=0;i<mem_buffer.size();i++)
				out1.writeLong(((Long)mem_buffer.get(i)).longValue());
			System.out.println("�������");

		}catch(EOFException e){
			System.out.println("�ļ�д�����!");
		}
		catch(IOException e){
			System.err.println("�ļ���ȡд����������ļ����������Ƿ���ȷ�����ļ��Ƿ���ڣ�\n ��ȷ��ʽ��data.dat��c:\\data.dat");
			
		}
	}

	public static void main(String[] args) 
	{
		new enCipher();
	}
}
