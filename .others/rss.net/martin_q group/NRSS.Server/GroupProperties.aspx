<%@ Page Language="C#" AutoEventWireup="true" CodeFile="GroupProperties.aspx.cs" Inherits="_GroupProperties" MasterPageFile="~/SiteMaster.master" %>

<asp:Content ID="Content1" ContentPlaceHolderID="ContentPlaceHolder1" runat="Server">
<form id="groupproperties" runat="server">&nbsp;&nbsp;&nbsp;
    <br />
    <strong>Feeds:</strong><br />
<asp:CheckBoxList ID="FeedList" runat="server">
    </asp:CheckBoxList><br />
    <strong>Users:</strong><br />
    <asp:CheckBoxList ID="UserList" runat="server">
        <asp:ListItem>awdr</asp:ListItem>
        <asp:ListItem>awd</asp:ListItem>
    </asp:CheckBoxList></form>
</asp:Content>