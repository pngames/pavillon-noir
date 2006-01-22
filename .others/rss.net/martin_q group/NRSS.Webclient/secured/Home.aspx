<%@ Page MasterPageFile="~/SiteMaster.master" CodeFile="Home.aspx.cs" Inherits="Home" Title="NRSS Home" %>

<asp:Content ID="Content1" ContentPlaceHolderID="ContentPlaceHolder1" runat="Server">
        <div class="leftcol">
            <div class="rssfeed"><div class="content"><div class="title">&nbsp;Flux</div>
                <a href=""><% Response.Write(this._feed.Name); %></a>
             </div></div>
        </div>
        <div class="rightcol">
            <div class="rssitem"><div class="content"><div class="title">&nbsp;Billets</div>
                <asp:TreeView ID="ItemTree" runat="server" ExpandDepth="1" ImageSet="News" NodeIndent="10" Width="100%">
                    <ParentNodeStyle Font-Bold="False" />
                    <HoverNodeStyle Font-Underline="True" />
                    <SelectedNodeStyle Font-Underline="True" HorizontalPadding="0px" VerticalPadding="0px" />
                    <NodeStyle Font-Names="Tahoma" Font-Size="10px" ForeColor="Black" HorizontalPadding="5px"
                        NodeSpacing="0px" VerticalPadding="0px" />
                </asp:TreeView>
             </div></div>
             <div class="itemcontent" style="margin-top: 10px;"><div class="content">
                test<br/>
                test<br/>
             </div></div>
        </div>
        <div class="spacer"></div>
</asp:Content>

