<%@ Page Language="C#" AutoEventWireup="true" MasterPageFile="~/SiteMaster.master" CodeFile="Home.aspx.cs" Inherits="Home" Title="NRSS Home" %>

<asp:Content ID="Content1" ContentPlaceHolderID="ContentPlaceHolder1" runat="Server">
        <div class="leftcol">
            <div class="rssfeed"><div class="content"><div class="title">&nbsp;Flux</div>
                <div style="margin:4px;">
                    <a href="">Le monde.fr</a>
                    <a href="">Le monde.fr</a>
                </div>
             </div></div>
        </div>
        <div class="rightcol">
            <div class="rssitem"><div class="content"><div class="title">&nbsp;Billets</div>
                <div style="overflow:auto; height:180px;">
                <asp:TreeView ID="ItemTree" runat="server" ExpandDepth="1" ImageSet="News" NodeIndent="10" Width="95%">
                    <ParentNodeStyle Font-Bold="False" />
                    <HoverNodeStyle Font-Underline="False" Font-Bold="False" ForeColor="CornflowerBlue" />
                    <SelectedNodeStyle Font-Underline="False" HorizontalPadding="0px" VerticalPadding="0px" Font-Bold="True" />
                    <NodeStyle Font-Names="Tahoma" Font-Size="12px" ForeColor="Black" HorizontalPadding="5px"
                        NodeSpacing="2px" VerticalPadding="0px" />
                </asp:TreeView>
                </div>
             </div></div>
             <div class="itemcontent" style="margin-top: 10px;"><div class="content"><div class="title">&nbsp;Contenu du billet</div>
                <div style="padding:10px;">
                    <% 
                        int i = 0;
                        foreach (NRSSService.Chan chan in rssFeed.Chans)
                            foreach (NRSSService.Item item in chan.Items)
                            {
                                Response.Write("<div id=\"item");
                                Response.Write(i);
                                Response.Write("\" class=\"anitem\">");
                    %>
                                <div class="itemtitle"><span><% Response.Write(item.Title); %></span> <% Response.Write(item.Date.ToLongDateString()); %></div>
                                <div class="itemdesc"> <% Response.Write(item.Description); %></div>                                
                                <div class="itemlink"><a href="<% Response.Write(item.Link); %>"> <% Response.Write(item.Link); %></a></div>
                                <div class="itemcontent"> <% Response.Write(item.Content); %></div>
                    <%           
                                Response.Write("</div>");
                                Response.Write("");
                                i++;
                            }    
                    %>
                </div>
             </div></div>
        </div>
        <div class="spacer"></div>
</asp:Content>

