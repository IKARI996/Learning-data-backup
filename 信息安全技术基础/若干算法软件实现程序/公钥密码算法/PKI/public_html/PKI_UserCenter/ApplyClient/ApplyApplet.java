import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.net.*;
import java.io.*;

import java.security.KeyPairGenerator;
import java.security.SecureRandom;
import java.security.KeyPair; 
import java.security.PrivateKey; 		
import java.security.PublicKey; 
import java.security.cert.Certificate;
import java.security.cert.CertificateFactory;
import javax.crypto.*;

import org.bouncycastle.jce.provider.*;

public class ApplyApplet extends JApplet
{
	JLabel[]  labels={
				new JLabel("�û�����"),	new JLabel("��λ��"),
				new JLabel("������λ��"),	new JLabel("�������ţ�"),
				new JLabel("��ַ��"),	new JLabel("���У�"),
				new JLabel("ʡ�ݣ�"),	new JLabel("�������룺"),
				new JLabel("���ң�"),		new JLabel("�������䣺"),
				new JLabel("�绰��"),	new JLabel("���棺")
			    };
	JTextField[]  fields=new JTextField[12];
	JPanel[]  jps=new JPanel[12];
	JPanel  centerPanel=new JPanel();
	JButton  accept=new JButton("������������ύ����");
	JPanel  btnPanel=new JPanel();
	
	public void init()
	{
		java.security.Security.addProvider(new BouncyCastleProvider());
	}

	public void start()
	{
		centerPanel.setLayout(new GridLayout(6,2));
		FlowLayout fl=new FlowLayout();
		fl.setAlignment(FlowLayout.RIGHT);
		for(int x=0;x<12;x++) 
		{	
			jps[x]=new JPanel();
			fields[x]=new JTextField(20);
			jps[x].setLayout(fl);
			jps[x].add(labels[x]);jps[x].add(fields[x]);
			centerPanel.add(jps[x]);
		}
		
		btnPanel.add(accept);
		Container c=getContentPane();
		c.add(centerPanel,BorderLayout.CENTER);
		c.add(btnPanel,BorderLayout.SOUTH);
		accept.addActionListener(new ApplyListener());
	}
	
	public void stop()
	{
	}
	
	public void destroy()
	{
	}

	class ApplyListener  implements ActionListener
	{
		public void actionPerformed(ActionEvent ae)
		{
			ApplySource as=new ApplySource();
			for(int x=0;x<12;x++)
			{
				as.source[x]=new String(fields[x].getText());
			}
			
			try{
				KeyPairGenerator kpg=KeyPairGenerator.getInstance("RSA","BC");
				SecureRandom rd=SecureRandom.getInstance("SHA1PRNG");
				rd.setSeed(new java.util.Date().getTime());
				kpg.initialize(1024,rd);
				KeyPair kp=kpg.genKeyPair();
				PrivateKey myPvk=kp.getPrivate();
				PublicKey myPbk=kp.getPublic();  
				//System.out.println(myPvk);
				//System.out.println(myPbk);

				as.applyPbk=myPbk;

				JOptionPane.showMessageDialog(null, "������ǩ���Ĺ�/˽Կ���Ѿ�����\n��[ȷ��]����ѡ�����ڼ�������������Ϣ�ĸ�CA֤��\n������Ļ�����û�и�֤�飬��������ҳ����", "ע��", JOptionPane.INFORMATION_MESSAGE); 				

				JFileChooser openChooser = new JFileChooser();
   				ExampleFileFilter filefilter = new ExampleFileFilter("cer", "X.509֤��");
   				openChooser.addChoosableFileFilter(filefilter);
				openChooser.setDialogTitle("��ѡ�����ڼ���������Ϣ�ĸ�CA֤�飺");
   				int returnVal = openChooser.showOpenDialog(null);
   				if(returnVal == JFileChooser.APPROVE_OPTION) 
				{
					File  chosenFile=openChooser.getSelectedFile();
    					System.out.println("You chose to open this file: "+chosenFile);

					DataInputStream dis=new DataInputStream(new FileInputStream(chosenFile));
					CertificateFactory cf=CertificateFactory.getInstance("X.509");
					byte[]  bytes=new byte[dis.available()];
					dis.readFully(bytes);
					ByteArrayInputStream bais=new ByteArrayInputStream(bytes);
					Certificate CAEncryptCert=cf.generateCertificate(bais);
					PublicKey  CAEncryptPbk=CAEncryptCert.getPublicKey();
					
					//System.out.println(CAEncryptPbk);

				
					Cipher cipher = Cipher.getInstance("DES","BC");
					KeyGenerator keygen = KeyGenerator.getInstance("DES","BC");
   					SecretKey desKey = keygen.generateKey();
					cipher.init(Cipher.ENCRYPT_MODE,desKey);		
					as.daytime=new java.util.Date();			
					SealedObject encryptedSource=new SealedObject(as,cipher);

					cipher=Cipher.getInstance("RSA","BC");
					cipher.init(Cipher.WRAP_MODE,CAEncryptPbk);
					byte[]  wrapedKey=cipher.wrap(desKey);
					

					boolean sendOk=ApplySender.send("127.0.0.1",8888,encryptedSource,wrapedKey);
					if(sendOk==true)
					{
					//	System.out.println("Send ok!");
						JOptionPane.showMessageDialog(null, "��������ǩ����֤��������Ѿ����ͳɹ�\n���¼���ķ���ʱ�䣺    \n"+as.daytime.toLocaleString()+"\n��[ȷ��]���������ǩ��˽Կ���浽�����ļ���", "ע��", JOptionPane.INFORMATION_MESSAGE); 				
	
						JFileChooser saveChooser = new JFileChooser();
 						filefilter = new ExampleFileFilter("pem", "DER�����ʽ��˽Կ");
   						saveChooser.addChoosableFileFilter(filefilter);
						saveChooser.setDialogTitle("�뱣������ǩ��˽Կ���ļ���");
						saveChooser.setSelectedFile(new File("pkiUser_Pvk_applyId("+Date2Id.change(as.daytime)+")_forSign&Verify"));
   						int returnSaveVal = saveChooser.showSaveDialog(null);
						if(returnSaveVal == JFileChooser.APPROVE_OPTION) 
						{
							File  chosenSaveFile=new File(saveChooser.getSelectedFile().toString()+".pem");
							DataOutputStream dos=new DataOutputStream(new FileOutputStream(chosenSaveFile));
							byte[] myPvkDer=myPvk.getEncoded();
							dos.write(myPvkDer, 0,myPvkDer.length);
							dos.flush();
							dos.close();
							JOptionPane.showMessageDialog(null, "����ǩ��˽Կ�Ѿ�����ɹ�\n�����Ʊ��ܺø��ļ������Ժ�ǩ������\n�������������и������ϵ�CAע������Թ����", "ע��", JOptionPane.INFORMATION_MESSAGE); 		
						}
						else
						{
							JOptionPane.showMessageDialog(null,"����ǩ��˽Կû�б���\n���ʹ���������֤��û������\n����������","�Բ���",JOptionPane.ERROR_MESSAGE);

						}
					}
					else
					{
						//System.out.println("NetWork Error!");
						JOptionPane.showMessageDialog(null,"�Բ�������֤������δ�ܷ��ͳɹ�\n������������������ݿ�������������\n����������","�Բ���",JOptionPane.ERROR_MESSAGE);
					}
				}
				
			}
			catch(Exception ex)
			{
				System.out.println(ex); ex.printStackTrace();
				JOptionPane.showMessageDialog(null,"�Բ�������֤������ʧ��\n�ܿ�������������ԭ��\n     ��ѡ������ڼ���������Ϣ�ĸ�CA֤�鲻��ȷ\n����������","�Բ���",JOptionPane.ERROR_MESSAGE);
			}
		}
			
		
	}

}