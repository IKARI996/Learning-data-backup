import java.io.*; 
import java.security.*; 
import javax.crypto.*; 
import javax.crypto.spec.*; 
public class MyMac { 
public static void main(String[] args) throws Exception{ 
//����һ����ϢժҪ�� 
String str="TestString"; 
//��ͬ����Կ���룬�������ͨ�������㷨������� 
byte[] kb={11,105,-119,50,4,-105,16,38,-14,-111,21,-95,70,-15,76,-74, 
67,-88,59,-71,55,-125,104,42}; 
//��ȡ��ͬ����Կ 
SecretKeySpec k = new SecretKeySpec(kb,"HMACSHA1"); 
//��ȡMac���� 
Mac m = Mac.getInstance("HmacMD5"); 
m.init(k); 
m.update(str.getBytes("UTF-8")); 
byte[] re = m.doFinal();//������Ϣ�� 
//�������Ϣ��ת��Ϊ�ַ��� 
String result = ""; 
for(int i=0;i<re.length;i++){ 
result += Integer.toHexString((0x000000ff&re[i])|0xffffff00).substring(6); 
} 
System.out.println(result); 
} 
} 
