<%@ Page Language="C#" AutoEventWireup="true"  CodeFile="Default.aspx.cs" Inherits="_Default" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head id="Head1" runat="server">
    <title>NRSS</title>
<style>
/* html */
body { font-family: tahoma; font-size: 12px}
hr { border: solid 1px #cdcdcd; }

/* master */
.leftcol { float: left; }
.rightcol { float: left; width: 75%; }
.spacer { clear: both; }
.content { border: solid 1px #cdcdcd; background-color: #ffffff;}
.title {width: 100%; background-color: #cdcdcd; color: #ffffff; line-height: 150%; font-weight: bold;}
.menu { margin: 5px 5px 5px 5px; background-color: cornflowerblue; border: solid 1px #cdcdcd; 
color: #add8e6; line-height: 150%; font-weight: bold;}
.logo { margin: 5px 5px 5px 5px; background-color: #33cc00; border: solid 1px #cdcdcd; 
color: white; line-height: 150%; font-weight: bold;}
.login {margin: 5px 5px 5px 5px; background-color: #000000;}
</style>
</head>
<body  bgColor="#ffffff" style="background-image: url(img/bg.gif)">
<form id="form1" runat="server">
    <div class="logo">
            &nbsp;<span style="font-size: 14px;">NRSS</span>&nbsp;
        </div>
        <div class="leftcol">
            <div class="login"><div class="content"><div class="title">&nbsp;Login</div>
       
            <table>
        <tr>
          <td>Email:</td>
          <td><input id="UserEmail" type="text" runat=server/></td>
          <td><ASP:RequiredFieldValidator ID="RequiredFieldValidator1" ControlToValidate="UserEmail" Display="Static" ErrorMessage="*" runat=server/></td>
        </tr>
        <tr>
          <td>Mot de passe:</td>
          <td><input id="UserPass" type=password runat=server/></td>
          <td><ASP:RequiredFieldValidator ID="RequiredFieldValidator2" ControlToValidate="UserPass" Display="Static" ErrorMessage="*" runat=server/></td>
        </tr>
        <tr>
          <td>Se rappeller de moi:</td>
          <td><ASP:CheckBox id="PersistCookie" runat="server" /> </td>
          <td></td>
        </tr>
      </table>

      <asp:button ID="Button1" text="Login" OnClick="Login_Click" runat=server/>

      <asp:Label id="Msg" ForeColor="red" Font-Names="Tahoma" Font-Size="8" runat=server />
        
 </div></div>
    </form>
</body>
</html>
