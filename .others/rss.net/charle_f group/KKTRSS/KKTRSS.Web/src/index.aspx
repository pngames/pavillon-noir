<%@ Page Language="C#" AutoEventWireup="true" CodeFile="index.aspx.cs" Inherits="src_index" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>myRSS : just for you</title>
    <link rel="stylesheet" type="text/css" media="screen" href="style.css"/>
</head>
<body>
<!-- #Include File="Header.inc" -->

    <form id="main_form" runat="server">
        <div id="content">
            Welcome \o/

            <div id="login_box">
                <form name="login_form" method="post" action="/login.aspx"> <!--id="login_form"-->
                    <div id="login_fields">
                        <input type="text" size="8" class="login_form" name="login" value="Login" />
                        <br />
                        <input type="password" size="8" class="login_form" name="passwd" value="Passwd" />
                    </div> <!-- !login_fields -->
                </form>
            </div> <!-- !login_box -->
        </div> <!-- !content -->
        
    </form>

<!-- #Include File="Footer.inc" -->
</body>
</html>
