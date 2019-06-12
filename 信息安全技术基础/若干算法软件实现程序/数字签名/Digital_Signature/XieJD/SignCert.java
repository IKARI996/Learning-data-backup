
import java.io.*;

import java.security.*;

import java.security.cert.*;

import java.util.*;

import java.math.*;

import sun.security.x509.*;

/**
* <p>Description: �ó������ǩ���ߣ�CA����֤����Ϣ����CA��˽Կ�����Ա�ǩ����
* <p/>
* ��֤�����ǩ�������̼���ʹ��CA��֤��ͱ�ǩ֤�����ع��γ�һ���µ�֤��</p>
*
* @author abnerchai
* @version 1.0
*/

public class SignCert {

public static void main(String[] args) throws Exception {

char[] storepass = "100200".toCharArray();//���CA֤��ͱ�ǩ֤���֤���ķ�������

char[] cakeypass = "200100".toCharArray();//CA����֤����Ŀ�ķ�������

String alias = "rootCA";//CA֤����֤����еı��������CA��֤������ǩ��������֤��

String name = "rootCALib";//���CA֤��ͱ�ǩ֤���֤��������

String newLib = "SignedLib";//��֤�������֣������Ҫ��ǩ�����֤������¿⣬�����¿������

char[] newLibPass = "100200".toCharArray();//�����¿�ķ�������

String cerFileName = "eagleCA.cer";//��ǩ֤���֤���ļ���

String aliasName = "eagleCA";//��ǩ֤����֤����е�alias����

char[] namePass = "200100".toCharArray();//��ǩ֤�����Ŀ��֤����˽Կ����

int n = 3; //��ǩ֤�����Ч�ڣ�����Ϊ��λ���Ե�ǰʱ�俪ʼ����

int sn = 200406001;//���кſ��Լ����壬���ﶨ�������Ϊ2004��6��ǩ�����Ǳ����CAǩ���ĵڶ��ٸ���001���㣬Ҫ��Ψһ

String afteraliasName = "eagleCA_Signed"; //ǩ�����²����ı�ǩ������֤���ڿ��еı���

char[] afterNewPass = "100200".toCharArray(); //ǩ�����²����ı�ǩ������֤���ڿ����Ŀ��˽Կ������

//װ��֤���

FileInputStream in = new FileInputStream(name);

KeyStore ks = KeyStore.getInstance("JKS");//JKSΪ֤��������

ks.load(in, storepass);

//��֤����ж���ǩ���ߣ�CA����֤��

java.security.cert.Certificate cl = ks.getCertificate(alias);//����һ��CA֤��,�����l����ĸl����������1

PrivateKey privateKey = (PrivateKey) ks.getKey(alias, cakeypass);//���ݱ�����֤���������CA֤���˽Կ

in.close();

//��֤����ж�����ǩ����(CA)��֤������ȡǩ���ߵ���Ϣ

byte[] encodl = cl.getEncoded();//��ȡ֤��ı��룬��������ĸl����������1

X509CertImpl cimpl = new X509CertImpl(encodl);//��������ĸl����������1������֤��ı��봴��X509CertImpl���͵Ķ���

//��������Ķ�����X509CertInfo���͵Ķ��󣬸ö����װ��֤���ȫ�����ݡ�

X509CertInfo cinfo_first =

    (X509CertInfo) cimpl.get(X509CertImpl.NAME + "." + X509CertImpl.INFO);

//Ȼ����X500Name���͵�ǩ������Ϣ

X500Name issuer = (X500Name)

    cinfo_first.get(X509CertInfo.SUBJECT + "." + CertificateIssuerName.DN_NAME);

//��ȡ��ǩ����֤�飬����ȡ��ǩ���ߵ�֤�� 

//�ɴ���Կ���л�ȡ��Ҳ�ɴӵ�����֤���ļ��л�ȡ������������ַ�ʽ /////////////////////////////////////////////////////////////////////////////// 

//��ʽһ�����ôӵ�����cer�ļ��л�ȡ start 

/////////////////////////////////////////////////////////////////////////////// 

/*

CertificateFactory cf = CertificateFactory.getInstance("X.509");//X.509��ʹ������һ������֤���׼ 

FileInputStream in2 = new FileInputStream(cerFileName);//��ǩ֤���ļ� 

java.security.cert.Certificate c2 = cf.generateCertificate(in2);//������Ҫ��ǩ��֤�� 

in2.close(); 

byte[] encod2 = c2.getEncoded(); 

X509CertImpl cimp2 = new X509CertImpl(encod2); 

//��ñ�ǩ֤�����ϸ���ݣ�Ȼ��������֤��������֤�� 

X509CertInfo cinfo_second = 

(X509CertInfo)cimp2.get(X509CertImpl.NAME+"."+X509CertImpl.INFO); 


*/
/////////////////////////////////////////////////////////////////////////////// 

//end ��ʽһ 

/////////////////////////////////////////////////////////////////////////////// 

/////////////////////////////////////////////////////////////////////////////// 

//��ʽ������֤����ж�����ǩ��֤�� start 

///////////////////////////////////////////////////////////////////////////////

java.security.cert.Certificate c3 = ks.getCertificate(aliasName);//��֤����ж�����ǩ֤�飬Ȼ�������µ�֤��

byte[] encod3 = c3.getEncoded();

X509CertImpl cimp3 = new X509CertImpl(encod3);

X509CertInfo cinfo_second =

    (X509CertInfo) cimp3.get(X509CertImpl.NAME + "." + X509CertImpl.INFO); ///////////////////////////////////////////////////////////////////////////////

//end��ʽ�� 

/////////////////////////////////////////////////////////////////////////////// //������֤�����Ч�ڣ�ʹ֮Ϊ��ǰ���n����Ч����֤��� 

//��ֹ���ڲ��ܳ���CA֤�����Ч����

Date beginDate = new Date();

Calendar cal = Calendar.getInstance();

cal.setTime(beginDate);

cal.add(cal.YEAR, n);

Date endDate = cal.getTime();

CertificateValidity cv = new CertificateValidity(beginDate, endDate);

cinfo_second.set(X509CertInfo.VALIDITY, cv);

//������֤������к�

CertificateSerialNumber csn = new CertificateSerialNumber(sn);

cinfo_second.set(X509CertInfo.SERIAL_NUMBER, csn);

//������֤���ǩ����

cinfo_second.set(X509CertInfo.ISSUER + "." + CertificateIssuerName.DN_NAME,

    issuer);

//�µ�ǩ������CA��֤���ж������� 

//������֤����㷨��ָ��CAǩ����֤����ʹ�õ��㷨Ϊmd5WithRSA

AlgorithmId algorithm =

    new AlgorithmId(AlgorithmId.md5WithRSAEncryption_oid);

cinfo_second.set(CertificateAlgorithmId.NAME + "." +

    CertificateAlgorithmId.ALGORITHM, algorithm);

//�����µ�ǩ�����֤��

X509CertImpl newcert = new X509CertImpl(cinfo_second);

//ǩ��,ʹ��CA֤���˽Կ����ǩ����ǩ��ʹ�õ��㷨ΪMD5WithRSA

newcert.sign(privateKey, "MD5WithRSA");//������õ��˾���CAǩ�����֤��

//����֤�����֤��� 

//�������ɵ�֤�����һ���µ�֤��⣬Ҳ���Դ���ԭ֤��⣬ 

//������֤��⣬����֤����в�������ԭ֤����е�������Ŀ�� 

//������������һ����β�������Ŀ��ע�⣬��ʱ���²�����ǩ�����֤��ֻ 

//������Կ��������Ϣ��ǩ����Ϣ��������˽Կ��Ϣ������������ַ�ʽ�� 

/////////////////////////////////////////////////////////////////////////// 

//��ʽһ����������Կ�� 

/////////////////////////////////////////////////////////////////////////// 

KeyStore ks2 = KeyStore.getInstance("JKS");//JKSΪ֤��������

ks2.load(null, newLibPass);

PrivateKey prk = (PrivateKey) ks.getKey(aliasName, namePass);

java.security.cert.Certificate[] cchain = {newcert};

//����ԭ���Ŀ�,�ڶ�������Ϊԭ֤���˽Կ������������Ϊ��֤���˽Կ���룬����������Ϊ��֤��

ks2.setKeyEntry(afteraliasName, prk, afterNewPass, cchain); //������Կ���ԭ����û��ǩ����֤�������

FileOutputStream out = new FileOutputStream(newLib); 

//�����¿�signedLib���������¿�Ŀ�������� 

ks2.store(out,newLibPass); 

out.close(); 



/////////////////////////////////////////////////////////////////////////// 

//end ��ʽһ 

/////////////////////////////////////////////////////////////////////////// 

//Ҳ���Բ�������һ�ַ�ʽ������ԭ֤����� 

//����ԭ���У�����ԭ֤���������һ��֤�飬���֤����ԭ֤�龭��ǩ�����֤�� 

//�����֤�麬��˽Կ��˽Կ���� 

/////////////////////////////////////////////////////////////////////////// 

//��ʽ��������ԭ��Կ�� 

/////////////////////////////////////////////////////////////////////////// 
/*
//����ԭ���ж�����ǩ֤���˽Կ


PrivateKey prk = (PrivateKey) ks.getKey(aliasName, namePass);

java.security.cert.Certificate[] cchain = {newcert};

//����ԭ���Ŀ�,�ڶ�������Ϊԭ֤���˽Կ������������Ϊ��֤���˽Կ���룬����������Ϊ��֤��

ks.setKeyEntry(afteraliasName, prk, afterNewPass, cchain); //������Կ���ԭ����û��ǩ����֤�������

FileOutputStream out2 = new FileOutputStream(name);

ks.store(out2, storepass);//����ԭ���Ŀ��У��ڶ�������Ϊ�ÿ�ķ�������
*/
/////////////////////////////////////////////////////////////////////////// 

//end ��ʽ�� 

///////////////////////////////////////////////////////////////////////////

}

}

