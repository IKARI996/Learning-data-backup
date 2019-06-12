import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.net.*;
import java.io.*;

public class ConversionApplet extends JApplet
{
	JLabel jl1=new JLabel("X509֤���ļ���");
	JTextField jf1=new JTextField(20);
	JButton jb1=new JButton("ѡ���ļ�...");
	JPanel jp1=new JPanel();

	JLabel jl2=new JLabel("��Կ�ļ�(DER����)��");
	JTextField jf2=new JTextField(20);
	JButton jb2=new JButton("ѡ���ļ�...");
	JPanel jp2=new JPanel();

	JLabel funjl1=new JLabel("��;��");
	JComboBox jcb1=new JComboBox(new String[]{"����/����","ǩ��/��֤"});
	JButton convertBtn1=new JButton("����PKCS12��ʽ�ļ�");
	JPanel jpb1=new JPanel();

	JLabel splitLabel=new JLabel("");	

	JLabel jl3=new JLabel("PKCS12�ļ���");
	JTextField jf3=new JTextField(20);
	JButton jb3=new JButton("ѡ���ļ�...");
	JPanel jp3=new JPanel();

	JLabel funjl2=new JLabel("��;��");
	JComboBox jcb2=new JComboBox(new String[]{"����/����","ǩ��/��֤"});
	JButton convertBtn2=new JButton("����X509֤���ļ���DER�������Կ�ļ�");
	JPanel jpb2=new JPanel();

	String[] funcStr={"_forEncryp&Decrypt","_forSign&Verify"};

	public void init()
	{
		
	}

	public void start()
	{
		jp1.setLayout(new FlowLayout(FlowLayout.LEFT));jp1.add(jl1);jp1.add(jf1);jp1.add(jb1);
		jp2.setLayout(new FlowLayout(FlowLayout.LEFT));jp2.add(jl2);jp2.add(jf2);jp2.add(jb2);
		jpb1.setLayout(new FlowLayout(FlowLayout.LEFT));jpb1.add(funjl1);jpb1.add(jcb1);jpb1.add(convertBtn1);
		jp3.setLayout(new FlowLayout(FlowLayout.LEFT));jp3.add(jl3);jp3.add(jf3);jp3.add(jb3);
		jpb2.setLayout(new FlowLayout(FlowLayout.LEFT));jpb2.add(funjl2);jpb2.add(jcb2);jpb2.add(convertBtn2);

		getContentPane().setLayout(new GridLayout(6,1));
		getContentPane().add(jp1);
		getContentPane().add(jp2);
		getContentPane().add(jpb1);
		getContentPane().add(splitLabel);
		getContentPane().add(jp3);
		getContentPane().add(jpb2);

		jb1.addActionListener(new MySelectListener());
		jb2.addActionListener(new MySelectListener());
		jb3.addActionListener(new MySelectListener());

		convertBtn1.addActionListener(new ConvertListener());
		convertBtn2.addActionListener(new ConvertListener());

	}

	public class MySelectListener implements ActionListener
	{
		public void actionPerformed(ActionEvent ae)
		{
			String userFilename=null;
			String[] filterStr=null;
			JTextField  tempJf=null;

			if(ae.getSource()==jb1)	
				{ filterStr=new String[]{"cer","X.509֤��"}; tempJf=jf1;}
			if(ae.getSource()==jb2)	
				{ filterStr=new String[]{"pem", "DER�����ʽ��˽Կ�ļ�"}; tempJf=jf2;}
			if(ae.getSource()==jb3)	
				{ filterStr=new String[]{"pfx","PKCS12�����ʽ�ļ�"}; tempJf=jf3;}

			JFileChooser openChooser = new JFileChooser();
   			ExampleFileFilter filefilter = new ExampleFileFilter(filterStr[0], filterStr[1]);
   			openChooser.addChoosableFileFilter(filefilter);
			openChooser.setDialogTitle("��ѡ���ļ���");
   			int returnVal = openChooser.showOpenDialog(null);
   			if(returnVal == JFileChooser.APPROVE_OPTION) 
			{
				File  chosenFile=openChooser.getSelectedFile();
				tempJf.setText(chosenFile.toString());
				return;
			}
			else return;

		}
	}

	public class ConvertListener implements ActionListener
	{
		public void actionPerformed(ActionEvent ae)
		{
			if(ae.getSource()==convertBtn1)	
			{
				String certFile=jf1.getText();
				String pvkFile=jf2.getText();
				String pkcs12File=null;
				String password=null;
			
				JFileChooser saveChooser = new JFileChooser();
   				ExampleFileFilter filefilter = new ExampleFileFilter("pfx","PKCS12�����ʽ�ļ�");
   				saveChooser.addChoosableFileFilter(filefilter);
				saveChooser.setDialogTitle("��ѡ�񱣴浽��PKCS12�ļ���");
   				int returnVal = saveChooser.showSaveDialog(null);
   				if(returnVal == JFileChooser.APPROVE_OPTION) 
				{
					File  chosenFile=saveChooser.getSelectedFile();
					pkcs12File=chosenFile.toString();
					password = JOptionPane.showInputDialog("��������Ҫ���浽��PKCS12�ļ������루�ɿգ���\n��ȡ����ʾ������\n���벻�ܳ���6λ");
					if(password==null) password="";

					X2P x2p=new X2P(certFile,pvkFile,pkcs12File,password,funcStr[jcb1.getSelectedIndex()]);
					int result=x2p.convert();
					if(result==0)
						JOptionPane.showMessageDialog(null, "�ļ��Ѿ���ת���ɹ������棡", "ת�����", JOptionPane.INFORMATION_MESSAGE); 				
					else if(result==-1)	
						JOptionPane.showMessageDialog(null, "�Բ���ת��ʧ�ܣ�\n��������ѡ���֤���ļ��Ƿ���ȷ��", "ת��ʧ��", JOptionPane.ERROR_MESSAGE); 						
					else if(result==-2)	
						JOptionPane.showMessageDialog(null, "�Բ���ת��ʧ�ܣ�\n��������ѡ���˽Կ�ļ��Ƿ���ȷ��", "ת��ʧ��", JOptionPane.ERROR_MESSAGE); 						
					else if(result==-3)	
						JOptionPane.showMessageDialog(null, "�Բ��𣬱���ʧ�ܣ�\n�������Ƿ���Ȩ�ޱ����ļ�������������������", "����ʧ��", JOptionPane.ERROR_MESSAGE); 						
				}				

			}
			else if(ae.getSource()==convertBtn2)	
			{
				String certFile=null;
				String pvkFile=null;
				String pkcs12File=jf3.getText();
				String password=null;

				password = JOptionPane.showInputDialog("�������PKCS12�ļ������룺(��ȡ����ʾ������)");
				if(password==null) password="";	
		
				JFileChooser saveChooser1 = new JFileChooser();
   				ExampleFileFilter filefilter1 = new ExampleFileFilter("cer","X.509֤��");
   				saveChooser1.addChoosableFileFilter(filefilter1);
				saveChooser1.setDialogTitle("��ѡ����Ҫ���浽��X509֤���ļ���");
   				int returnVal1 = saveChooser1.showSaveDialog(null);
   				if(returnVal1 == JFileChooser.APPROVE_OPTION) 
				{
					File  chosenFile=saveChooser1.getSelectedFile();
					certFile=chosenFile.toString();
				}
				else
				{
					//JOptionPane.showMessageDialog(null, "", "", JOptionPane.INFORMATION_MESSAGE); 				
					return;
				}

   				JFileChooser saveChooser2 = new JFileChooser();
   				ExampleFileFilter filefilter2 = new ExampleFileFilter("pem", "DER�����ʽ��˽Կ�ļ�");
   				saveChooser2.addChoosableFileFilter(filefilter2);
				saveChooser2.setDialogTitle("��ѡ����Ҫ���浽��˽Կ�ļ���");
   				int returnVal2 = saveChooser2.showSaveDialog(null);
   				if(returnVal2 == JFileChooser.APPROVE_OPTION) 
				{
					File  chosenFile=saveChooser2.getSelectedFile();
					pvkFile=chosenFile.toString();
				}
				else
				{
					//JOptionPane.showMessageDialog(null, "", "", JOptionPane.INFORMATION_MESSAGE); 				
					return;
				}

				P2X p2x=new P2X(certFile,pvkFile,pkcs12File,password,funcStr[jcb2.getSelectedIndex()]);
				int result=p2x.convert();
				if(result==0)
					JOptionPane.showMessageDialog(null, "ԭPKCS12�ļ��Ѿ����ֱ𱣴�Ϊһ��X509֤���ļ���һ����Կ�ļ���", "ת�����", JOptionPane.INFORMATION_MESSAGE); 				
				else if(result==-1)	
					JOptionPane.showMessageDialog(null, "�Բ���ԭPKCS12�ļ�ת��ʧ�ܣ�\n��������ѡ���PKCS12�ļ��Ƿ���ȷ�����Ƿ������˴�������롣", "ת��ʧ��", JOptionPane.ERROR_MESSAGE); 						
				else if(result==-2)	
					JOptionPane.showMessageDialog(null, "�Բ��𣬱���X509֤���ļ�ʧ�ܣ�\n�������Ƿ���Ȩ�ޱ����ļ���", "����ʧ��", JOptionPane.ERROR_MESSAGE); 						
				else if(result==-3)	
					JOptionPane.showMessageDialog(null, "�Բ��𣬱�����Կʧ�ܣ�\n�������Ƿ���Ȩ�ޱ����ļ���", "����ʧ��", JOptionPane.ERROR_MESSAGE); 						
									
			}
		}
	}

}