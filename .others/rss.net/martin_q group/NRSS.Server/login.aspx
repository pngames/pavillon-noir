<%@ Page Language="C#" AutoEventWireup="true"  CodeFile="login.aspx.cs" Inherits="_Default" %>

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
            &nbsp;<span style="font-size: 14px;">NRSS Admin</span>&nbsp;
        </div>
    <asp:Login ID="Login1" runat="server">
    </asp:Login>
    </form>
</body>
</html>
