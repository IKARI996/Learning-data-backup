import java.security.*; 
public class DigestPass { 
public static void main(String[] args) throws Exception{ 
String str="Hello,I sent to you 80 yuan."; 
MessageDigest md = MessageDigest.getInstance("MD5");//���õ���MD5,SHA�㷨�� 
md.update(str.getBytes("UTF-8"));//����ԭʼ�ִ� 
byte[] re = md.digest();//������ϢժҪ����byte������ 
//�������ϢժҪת��Ϊ�ַ��� 
String result = ""; 
for(int i=0;i<re.length;i++){ 
result += Integer.toHexString((0x000000ff&re[i])|0xffffff00).substring(6); 
} 
System.out.println(result); 
} 
} 
