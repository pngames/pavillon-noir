<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Default.aspx.cs" Inherits="_Default" MasterPageFile="~/SiteMaster.master" %>

<asp:Content ID="Content1" ContentPlaceHolderID="ContentPlaceHolder1" runat="Server">
    <form id="form1" runat="server">
    <input name="group" type="hidden" id="groupe" value="">
    <div style="font-weight: bold">
      <table>
        <tr>
          <td>Ajouter un groupe:</td>
          <td><input id="NewGroup" type="text" runat=server/></td>
          <td><asp:button ID="AddButton" text="Ajouter !" OnClick="AddNewGroup" runat=server/></td>
        </tr>
      </table>
        <br />
        Liste des groupes:<br />
    </div>

    <asp:ListBox ID="ListBox1" runat="server" Height="178px" Width="168px">
    </asp:ListBox>&nbsp;&nbsp;<asp:Button ID="Editer" runat=server Text="Editer" OnClick="GroupEdit" />
    <asp:Button ID="Supprimer" runat=server Text="Supprimer" OnClick="GroupSuppr" />
    
    
    </form>    
</asp:Content>