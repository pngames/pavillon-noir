<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Admin.aspx.cs" Inherits="Admin" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>Untitled Page</title>
</head>
<body>
    <form id="form1" runat="server">
        &nbsp; &nbsp;&nbsp;<table style="width: 828px; height: 150px">
            <tr>
                <td style="width: 150px; height: 70px">
        <asp:Label ID="Label4" runat="server" Text="Liste des groupes" Font-Bold="True"></asp:Label><br />
        <asp:ListBox ID="group_ListBox" runat="server" AutoPostBack="True" Height="228px"
            Width="174px" OnSelectedIndexChanged="group_ListBox_SelectedIndexChanged"></asp:ListBox><br />
                    &nbsp;&nbsp;
        <asp:Button ID="delGpe_Button" runat="server" Text="Deleter groupe" OnClick="delGpe_Button_Click" Width="141px" /></td>
                <td style="width: 65px; height: 70px">
                    <asp:Label ID="Label2" runat="server" Font-Bold="True" Text="Liste des comptes du groupe"
                        Width="195px"></asp:Label><asp:ListBox ID="user_ListBox" runat="server" Height="228px" Width="174px"></asp:ListBox><asp:Button ID="delUser_Button" runat="server" Text="Deleter compte du groupe" OnClick="delUser_Button_Click" Width="176px" /></td>
                <td style="width: 166px; height: 70px">
                    <asp:Label ID="Label3" runat="server" Text="Liste des flux du groupe" Font-Bold="True"></asp:Label><br />
        <asp:ListBox ID="flux_ListBox" runat="server" Height="228px" Width="168px"></asp:ListBox><br />
                    <asp:Button
            ID="fluxDel_Button" runat="server" Text="Deleter flux du groupe" OnClick="fluxDel_Button_Click" Width="143px" /></td>
            </tr>
        </table>
        &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp;<br />
        <br />
        <table style="width: 738px; height: 448px">
            <tr>
                <td style="width: 351px; height: 1px">
                    <asp:Label ID="Label1" runat="server" Text="Nom du groupe"></asp:Label>
                    <asp:TextBox ID="gpgeName_TextBox" runat="server"></asp:TextBox><br />
                    &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp;
                    &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp;<asp:Button ID="addGpe_Button" runat="server" Text="Ajouter groupe" OnClick="addGpe_Button_Click" /></td>
                <td style="width: 316px; height: 1px">
                </td>
                <td style="width: 303px; height: 1px">
                </td>
            </tr>
            <tr>
                <td style="width: 351px; height: 103px">
                    <asp:Label ID="Label5" runat="server" Font-Bold="True" Text="Liste des comptes" Width="155px"></asp:Label><br />
                    <asp:ListBox ID="globalUser_ListBox" runat="server" Height="117px" Width="157px"></asp:ListBox><br />
                    <asp:Button ID="addUser_Button" runat="server" Text="Ajouter compte au groupe" OnClick="addUser_Button_Click" Width="160px" /></td>
                <td style="width: 316px; height: 103px">
                    <asp:TextBox ID="globalLogin_TextBox" runat="server"></asp:TextBox>
                    <asp:Label ID="Label6" runat="server" Text="Login"></asp:Label>
                    <asp:TextBox ID="globalPass_TextBox" runat="server"></asp:TextBox>
                    <asp:Label ID="Label7" runat="server" Text="Password"></asp:Label><br />
                    <asp:Button ID="globalAddAcount_Button" runat="server" Text="Ajouter compte" OnClick="globalAddAcount_Button_Click" /></td>
                <td style="width: 303px; height: 103px">
                </td>
            </tr>
            <tr>
                <td style="width: 351px; height: 23px">
                    <asp:Label ID="Label8" runat="server" Font-Bold="True" Text="Liste des flux" Width="156px"></asp:Label><br />
                    <asp:ListBox
                        ID="globalFlux_ListBox" runat="server" Height="117px" Width="157px"></asp:ListBox><br />
                    <asp:Button
            ID="addFlux_Button" runat="server" Text="Ajouter flux au groupe" OnClick="addFlux_Button_Click" Width="158px" /></td>
                <td style="width: 316px; height: 23px">
                    <asp:TextBox ID="globalUrl_TextBox" runat="server"></asp:TextBox>
                    <asp:Label ID="Label9" runat="server" Text="Url"></asp:Label><br />
                    <asp:TextBox ID="globalName_TextBox" runat="server"></asp:TextBox>
                    <asp:Label ID="Label10" runat="server" Text="Nom"></asp:Label><br />
                    <asp:Button ID="globalAddFlux_Button" runat="server" Text="Ajouter flux" OnClick="globalAddFlux_Button_Click" /></td>
                <td style="width: 303px; height: 23px">
                </td>
            </tr>
        </table>
    </form>
</body>
</html>
