<%@ Page Language="C#" AutoEventWireup="true"  CodeFile="Default.aspx.cs" Inherits="_Default" %>
<%@ Import Namespace="System.Web.Security " %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">

  <head id="Head" runat="server">
    <title>Welcome</title>
    <link rel="stylesheet" type="text/css" media="screen" href="css/style.css"/>
  </head>
  
  <body>
  
  <!-- #Include File="src/Header.inc" -->
  
	<form id="form1" runat="server">
    <div id="content">
        <h2>Choose a feed:
        <%=
            qs["test"] == "" ? "TEST" : qs["test"]
        %>
        </h2>
        <ul class="feedslist">
            <li>With proxy</li>
            <% for (int i=1; i < 4; i++) { %>
            <li><a href="src/showfeed.aspx?feedid=<%= i %>&dspnbitems=0&dsponlyunread=false&proxymode=true"><%= i %></a></li>
            <% } %>

            <li>Without proxy</li>
            <% for (int i=1; i < 4; i++) { %>
            <li><a href="src/showfeed.aspx?feedid=<%= i %>&dspnbitems=0&dsponlyunread=false&proxymode=false"><%= i %></a></li>
            <% } %>

        </ul>
        
        <asp:button id="Button1" text="Signout" OnClick="Signout_Click" runat="server" />
	  
	  </div> <!-- !content -->  
    </form>
  
  </body>
  
<!-- #Include File="src/Footer.inc" -->

</html>

