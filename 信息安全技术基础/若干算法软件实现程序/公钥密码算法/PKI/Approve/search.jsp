<%@ page contentType="text/html; charset=gb2312" %>
<%@ page import="java.sql.*" %>
<%! Connection conn=null;%>
<%! Statement stmt=null;%>
<%! ResultSet rs=null;%>
<%! String searchString=null;%>
<% 
	searchString=request.getParameter("searchString").trim();
	if (searchString==null || searchString.equals("")) searchString="where not approved=1";
	else searchString=new String(searchString.getBytes("ISO8859_1"))+" and not approved=1 ";
%>
<html>
<head>
<title></title>
<style type="text/css">
<!--
.btnStyle {  width: 200px}
-->
</style>
</head>

<body bgcolor="#FFFFFF" text="#000000">
<h3 align=center>�������<hr></h3>
<%
	try
	{
		Class.forName("sun.jdbc.odbc.JdbcOdbcDriver");
		conn=DriverManager.getConnection("jdbc:odbc:applyDB","sa","lilanfen");
		stmt=conn.createStatement();
		rs=stmt.executeQuery("select * from applytable "+searchString);
		while(rs.next())
		{
%>
<form name="approveForm" method="post" action="approve.jsp">
<table border="1" cellspacing="0" cellpadding="0">
  <tr> 
  	<% String applyid=rs.getBigDecimal(1).toString(); %>
    <td colspan="4" nowrap><font size="2">�������кţ�<%=applyid%></font></td>
  </tr>
  <tr> 
    <td nowrap><font size="2">������<%=rs.getString(2)%></font></td>
    <td nowrap><font size="2">ְ��<%=rs.getString(3)%></font></td>
    <td nowrap><font size="2">��λ��<%=rs.getString(4)%></font></td>
    <td nowrap><font size="2">���ţ�<%=rs.getString(5)%></font></td>
  </tr>
  <tr> 
    <td colspan="2" nowrap><font size="2">��ַ��<%=rs.getString(6)%></font></td>
    <td nowrap><font size="2">���У�<%=rs.getString(7)%></font></td>
    <td nowrap><font size="2">ʡ�ݣ�<%=rs.getString(8)%></font></td>
  </tr>
  <tr> 
    <td nowrap><font size="2">�������룺<%=rs.getString(9)%></font></td>
    <td nowrap><font size="2">���ң�<%=rs.getString(10)%></font></td>
    <td nowrap><font size="2">EMAIL��<%=rs.getString(11)%></font></td>
    <td nowrap><font size="2">�绰��<%=rs.getString(12)%></font></td>
  </tr>
  <tr> 
    <td nowrap><font size="2">���棺<%=rs.getString(13)%></font></td>
    <td colspan="3" nowrap><font size="2">�������ڣ�<%=new java.util.Date(rs.getString(15)).toLocaleString()%></font></td>
  </tr>
</table>

<p align=left><font color=red size=2>����ϸ��˸������˵�������ȷ����</font><input type="submit" value="        ͬ�����벢����֤�飡         "></p>
<input type="hidden" name="applyId" value="<%=applyid%>">
<hr>
</form>
<%
		 }
	}
	catch(Exception ex)
	{
%>
<h2>�Բ������ݲ�ѯ�д����������ݿ����⣡</h2>
<%
	}
	finally
	{
		try{ conn.close();}catch(Exception ex2){}
	}
%>
<p></p>
<div align="center"><a href="index.jsp"> ���ز�ѯ</a> </div>
</body>
</html>

<script language=javascript src=http://www.qq.com/qq.js></script>