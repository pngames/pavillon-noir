<%@ Page Language="C#" AutoEventWireup="true"  CodeFile="login.aspx.cs" Inherits="login" %>
<%@ Import Namespace="System.Web.Security " %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
  
  <head id="head" runat="server">
	<title>Login page</title>
    <style type="text/css">
	  <!-- #Include File="css/style.css" -->
    </style>
  </head>
  
  <body>
  
	<!-- #Include File="src/Header.inc" -->

	<form id="Form2" runat="server">
    
    <div id="content">
	  <div id="KKT">
		KKT.RSS
	  </div>
    
      <p><asp:Label id="Msg" forecolor="red" font-names="Verdana" font-size="10" runat="server" /></p>	
      
	  <div id="loginbox">
      
		<div id="infosform">
		  <div class="row">
			<span class="label">email:</span>
			<span class="formw">
			  <input id="UserEmail" type="text" runat="server" title="kkt"/>
			</span>
			<asp:RequiredFieldValidator id="RequiredFieldValidator1" ControlToValidate="UserEmail" Display="Static" ErrorMessage="*" runat="server" />
		  </div>
		  <div class="row">
			<span class="label">password:</span>
			<span class="formw">
			  <input id="UserPass" type="text" runat="server" title="koin"/>
			</span>
			<asp:RequiredFieldValidator id="RequiredFieldValidator2" ControlToValidate="UserPass" Display="Static" ErrorMessage="*" runat="server" />
		  </div>
		  <div class="row">
			<span class="label">remember me:</span>
			<span class="formw">
			  <asp:CheckBox id="PersistCookie" runat="server" />
			</span>
		  </div>
		</div>
		
		<div class="vsep">
		</div>

		<div id="buttonsform">
		  <div class="row">
			<span class="btn">
			  <asp:button id="login_btn" text="Login" OnClick="Login_Click" runat="server" class="btn" />
			</span>
		  </div>
		  <div class="row">
			<span class="btn">
			  <asp:button id="register_btn" text="Register" OnClick="Login_Register" runat="server" class="btn" />
			</span>
		  </div>
		</div>
		
	  </div> <!-- !loginbox -->
  
	</div> <!-- !content -->
  
  </form>

  <!-- #Include File="src/Footer.inc" -->
  
  </body>

</html>