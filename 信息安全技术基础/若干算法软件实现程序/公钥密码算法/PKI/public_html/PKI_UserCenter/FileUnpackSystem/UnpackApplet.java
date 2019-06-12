import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.net.*;
import java.io.*;

public class UnpackApplet extends JApplet
{
	int fileSelectedFlag=1;

	JLabel  jl1=new JLabel("���ͷ���������֤��ǩ����֤�飺");
	JTextField jf1=new JTextField(20);
	JButton jb1=new JButton("ѡ���ļ�...");
	JPanel jp1=new JPanel();
	JButton jb1c1=new JButton("������֤��֤��");	
	JButton jb1c2=new JButton("��������֤��֤���Ƿ񱻳���");
	JPanel jpc1=new JPanel();

 	JRadioButton jrb2=new JRadioButton("�ֱ�ѡ�����ڽ��ܵ�˽Կ��֤�飺",true);

	JLabel  jl21=new JLabel("���Ľ���˽Կ�ļ���");
	JTextField jf21=new JTextField(20);
	JButton jb21=new JButton("ѡ���ļ�...");
	JPanel jp21=new JPanel();
	JLabel  jl22=new JLabel("��Ӧ�ļ���֤�飺");
	JTextField jf22=new JTextField(20);
	JButton jb22=new JButton("ѡ���ļ�...");
	JPanel jp22=new JPanel();
	JButton jb2c1=new JButton("������֤��֤��");
	JButton jb2c2=new JButton("��������֤��֤���Ƿ񱻳���");
	JPanel jpc2=new JPanel();

 	JRadioButton jrb3=new JRadioButton("ѡ�����ڽ��ܵ�PKCS12�ļ����ں�˽Կ����");

	JLabel  jl3=new JLabel("����PKCS12�ļ���");
	JTextField jf3=new JTextField(20);
	JButton jb3=new JButton("ѡ���ļ�...");
	JPanel jp3=new JPanel();
	JButton jb3c1=new JButton("������֤��֤��");
	JButton jb3c2=new JButton("��������֤��֤���Ƿ񱻳���");
	JPanel jpc3=new JPanel();

	ButtonGroup bg=new ButtonGroup();

	JLabel  jl4=new JLabel("Ҫ���ܽ�����ļ���");
	JTextField jf4=new JTextField(20);
	JButton jb4=new JButton("ѡ���ļ�...");	
	JPanel jp4=new JPanel();
	
	JButton unpackBtn=new JButton("���ܽ��");

	JDialog processDialog=new JDialog();
	
	public void init()
	{
		processDialog.getContentPane().setLayout(new BorderLayout());
		processDialog.getContentPane().add(new JLabel("�����У����Ժ�......"));
		processDialog.setTitle("������");
		processDialog.setSize(300,150);
		processDialog.setLocation(300,150);
	}

	public void start()
	{
		jp1.add(jl1);jp1.add(jf1);jp1.add(jb1);
		jpc1.add(jb1c1);jpc1.add(jb1c2);

		jp21.add(jl21);jp21.add(jf21);jp21.add(jb21);
		jp22.add(jl22);jp22.add(jf22);jp22.add(jb22);
		jpc2.add(jb2c1);jpc2.add(jb2c2);

		jp3.add(jl3);jp3.add(jf3);jp3.add(jb3);
		jpc3.add(jb3c1);jpc3.add(jb3c2);

		bg.add(jrb2);bg.add(jrb3);

		jp4.add(jl4);jp4.add(jf4);jp4.add(jb4);	jp4.add(unpackBtn);

		getContentPane().setLayout(new GridLayout(10,1));
		getContentPane().add(jp1);
		getContentPane().add(jpc1);
		getContentPane().add(jrb2);
		getContentPane().add(jp21);
		getContentPane().add(jp22);
		getContentPane().add(jpc2);
		getContentPane().add(jrb3);
		getContentPane().add(jp3);
		getContentPane().add(jpc3);
		getContentPane().add(jp4);

		fileSelectedFlag=1;
		jl3.setEnabled(false);jf3.setEnabled(false);jb3.setEnabled(false);
		jb3c1.setEnabled(false);jb3c2.setEnabled(false);

		jrb2.addActionListener(new MyRadioListener());
		jrb3.addActionListener(new MyRadioListener());

		jb1.addActionListener(new MySelectListener());
		jb21.addActionListener(new MySelectListener());
		jb22.addActionListener(new MySelectListener());
		jb3.addActionListener(new MySelectListener());
		jb4.addActionListener(new MySelectListener());
		

		jb1c1.addActionListener(new MyLocalValidListener());
		jb2c1.addActionListener(new MyLocalValidListener());
		jb3c1.addActionListener(new MyLocalValidListener());

		unpackBtn.addActionListener(new FileUnpackListener());
		
	}
	
	public void stop()
	{
	}
	
	public void destroy()
	{
	}

	public class MyRadioListener implements ActionListener
	{
		public void actionPerformed(ActionEvent ae)
		{
			if(ae.getSource()==jrb2)
			{
				fileSelectedFlag=1;
				jl21.setEnabled(true);jf21.setEnabled(true);jb21.setEnabled(true);
				jl22.setEnabled(true);jf22.setEnabled(true);jb22.setEnabled(true);
				jb2c1.setEnabled(true);jb2c2.setEnabled(true);
				jl3.setEnabled(false);jf3.setEnabled(false);jb3.setEnabled(false);
				jb3c1.setEnabled(false);jb3c2.setEnabled(false);
			}
			else
			{
				fileSelectedFlag=2;
				jl21.setEnabled(false);jf21.setEnabled(false);jb21.setEnabled(false);
				jl22.setEnabled(false);jf22.setEnabled(false);jb22.setEnabled(false);
				jb2c1.setEnabled(false);jb2c2.setEnabled(false);
				jl3.setEnabled(true);jf3.setEnabled(true);jb3.setEnabled(true);
				jb3c1.setEnabled(true);jb3c2.setEnabled(true);
			}
		}
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
			if(ae.getSource()==jb21)	
				{ filterStr=new String[]{"pem", "DER�����ʽ��˽Կ�ļ�"}; tempJf=jf21;}
			if(ae.getSource()==jb22)	
				{ filterStr=new String[]{"cer","X.509֤��"}; tempJf=jf22;}
			if(ae.getSource()==jb3)	
				{ filterStr=new String[]{"pfx","PKCS12�����ʽ�ļ�"}; tempJf=jf3;}

			if(ae.getSource()==jb4)	
			{ 
				tempJf=jf4;					
				JFileChooser openChooser = new JFileChooser();
   				openChooser.setDialogTitle("��ѡ���κ�Ҫ������ļ���");
   				int returnVal = openChooser.showOpenDialog(null);
   				if(returnVal == JFileChooser.APPROVE_OPTION) 
				{
					File  chosenFile=openChooser.getSelectedFile();
					tempJf.setText(chosenFile.toString());
					return;
				}
				else return;
			}	

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

	public class MyLocalValidListener implements ActionListener
	{
		public void actionPerformed(ActionEvent ae)
		{
			int fileflag=1;
			String userFilename=null,caFilename=null;
			if(ae.getSource()==jb1c1)
				userFilename=jf1.getText();
			else if(ae.getSource()==jb2c1)
				userFilename=jf22.getText();
			else if(ae.getSource()==jb3c1)
				{ userFilename=jf3.getText(); fileflag=2;}
			else return;
		
			if(fileflag==1)
			{	
				JFileChooser openChooser = new JFileChooser();
   				ExampleFileFilter filefilter = new ExampleFileFilter("cer", "X.509֤��");
   				openChooser.addChoosableFileFilter(filefilter);
				openChooser.setDialogTitle("��ѡ����֤��֤��ĸ�CA֤�飺");
   				int returnVal = openChooser.showOpenDialog(null);
   				if(returnVal == JFileChooser.APPROVE_OPTION) 
				{
					File  chosenFile=openChooser.getSelectedFile();
						caFilename=chosenFile.toString();
					LocalValid  localvalid=new LocalValid(userFilename,caFilename);
					int validResult=localvalid.valid();
					if(validResult==0)
						JOptionPane.showMessageDialog(null, "��֤��ͨ���˱�����֤��", "��֤���", JOptionPane.INFORMATION_MESSAGE); 				
					else if(validResult==1)	
						JOptionPane.showMessageDialog(null, "��֤���Ѿ����ڣ�", "��֤���", JOptionPane.ERROR_MESSAGE); 						
					else if(validResult==2)
						JOptionPane.showMessageDialog(null, "��֤��δ��ͨ��CA֤�����֤��", "��֤���", JOptionPane.ERROR_MESSAGE); 				
					else if(validResult==-1)
						JOptionPane.showMessageDialog(null, "��֤����������ѡ���˴����ʽ���ļ���", "��֤����", JOptionPane.ERROR_MESSAGE); 				
				
				}
			}
			else if(fileflag==2)
			{	

				String password = JOptionPane.showInputDialog("�������PKCS12�ļ������룺");
				if(password==null) password="";
				JFileChooser openChooser = new JFileChooser();
   				ExampleFileFilter filefilter = new ExampleFileFilter("cer", "X.509֤��");
   				openChooser.addChoosableFileFilter(filefilter);
				openChooser.setDialogTitle("��ѡ����֤��֤��ĸ�CA֤�飺");
   				int returnVal = openChooser.showOpenDialog(null);
   				if(returnVal == JFileChooser.APPROVE_OPTION) 
				{
					File  chosenFile=openChooser.getSelectedFile();
						caFilename=chosenFile.toString();
					LocalValidPKCS12  localvalid=new LocalValidPKCS12(userFilename,caFilename,password);
					int validResult=localvalid.valid();
					if(validResult==0)
						JOptionPane.showMessageDialog(null, "��֤��ͨ���˱�����֤��", "��֤���", JOptionPane.INFORMATION_MESSAGE); 				
					else if(validResult==1)	
						JOptionPane.showMessageDialog(null, "��֤���Ѿ����ڣ�", "��֤���", JOptionPane.ERROR_MESSAGE); 						
					else if(validResult==2)
						JOptionPane.showMessageDialog(null, "��֤��δ��ͨ��CA֤�����֤��", "��֤���", JOptionPane.ERROR_MESSAGE); 				
					else if(validResult==-1)
						JOptionPane.showMessageDialog(null, "��֤����������ѡ���˴����ʽ���ļ����������˴�������롣", "��֤����", JOptionPane.ERROR_MESSAGE); 				
				
				}				
			}

		}
	}
	

	class FileUnpackListener implements ActionListener
	{
		public void actionPerformed(ActionEvent ae)
		{
			String filenameToUnpack=jf4.getText();
			String filenameAfterUnpack=null;
			String yourCertFilename=jf1.getText();
			String myPrivateFilename;

			if(fileSelectedFlag==1)
			{
				myPrivateFilename=jf21.getText();
			
				JFileChooser saveChooser = new JFileChooser();
				saveChooser.setDialogTitle("��ѡ����ܽ���󱣴浽���ļ���");
   				int returnVal = saveChooser.showSaveDialog(null);
   				if(returnVal == JFileChooser.APPROVE_OPTION) 
				{
					File  chosenFile=saveChooser.getSelectedFile();
					filenameAfterUnpack=chosenFile.toString();
					FileUnpack fu=new FileUnpack(filenameToUnpack,filenameAfterUnpack,yourCertFilename,myPrivateFilename);
					int unpackResult=fu.unpack();
					if(unpackResult==0)
						JOptionPane.showMessageDialog(null, "�ļ�: "+filenameToUnpack+"\n�Ѿ������ܽ��Ϊ:\n"+filenameAfterUnpack+"\n������֤ǩ���ɹ���", "�ɹ�", JOptionPane.INFORMATION_MESSAGE); 				
					else if(unpackResult==-1)	
						JOptionPane.showMessageDialog(null, "�Բ��𣬽��ܽ��ʧ�ܣ�\n��������ѡ����ļ��Ƿ���ȷ��", "���ʧ��", JOptionPane.ERROR_MESSAGE); 
					else if(unpackResult==-2)	
						JOptionPane.showMessageDialog(null, "�ļ�: "+filenameToUnpack+"\n�Ѿ������ܽ��Ϊ:\n"+filenameAfterUnpack+"\n������֤ǩ��ʧ�ܣ�", "��֤ǩ��ʧ��", JOptionPane.ERROR_MESSAGE); 
						
				}				
			}
			else if(fileSelectedFlag==2)
			{
				myPrivateFilename=jf3.getText();

				String password = JOptionPane.showInputDialog("�������PKCS12�ļ������룺");
				if(password==null) password="";

				JFileChooser saveChooser = new JFileChooser();
				saveChooser.setDialogTitle("��ѡ����ܽ���󱣴浽���ļ���");
   				int returnVal = saveChooser.showSaveDialog(null);
   				if(returnVal == JFileChooser.APPROVE_OPTION) 
				{
					File  chosenFile=saveChooser.getSelectedFile();
					filenameAfterUnpack=chosenFile.toString();
					FileUnpackPKCS12 fuPkcs12=new FileUnpackPKCS12(filenameToUnpack,filenameAfterUnpack,yourCertFilename,myPrivateFilename,password);
					int unpackResult=fuPkcs12.unpack();					
					if(unpackResult==0)
						JOptionPane.showMessageDialog(null, "�ļ�: "+filenameToUnpack+"\n�Ѿ������ܽ��Ϊ:\n"+filenameAfterUnpack+"\n������֤ǩ���ɹ���", "�ɹ�", JOptionPane.INFORMATION_MESSAGE); 				
					else if(unpackResult==-1)	
						JOptionPane.showMessageDialog(null, "�Բ��𣬽��ܽ��ʧ�ܣ�\n��������ѡ����ļ��Ƿ���ȷ�������������Ƿ����", "���ʧ��", JOptionPane.ERROR_MESSAGE); 
					else if(unpackResult==-2)	
						JOptionPane.showMessageDialog(null, "�ļ�: "+filenameToUnpack+"\n�Ѿ������ܽ��Ϊ:\n"+filenameAfterUnpack+"\n������֤ǩ��ʧ�ܣ�", "��֤ǩ��ʧ��", JOptionPane.ERROR_MESSAGE); 
				}				
			}
			
		}		
	}
	

}