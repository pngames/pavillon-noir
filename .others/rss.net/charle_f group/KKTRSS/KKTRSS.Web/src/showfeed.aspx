<%@ Page Language="C#" AutoEventWireup="true" CodeFile="showfeed.aspx.cs" Inherits="src_showfeed" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >

<head runat="server">
    <title>KKTRSS.Feeds</title>
    <link rel="stylesheet" type="text/css" media="screen" href="../css/style.css"/>
</head>

<body>

<!-- #Include File="Header.inc" -->

  <form id="form1" runat="server">
	<atlas:ScriptManager runat="server" id="scriptManager" />
	<div id="content">

	  <!-- Navigation-->
      <div id="nav">
		<ul id="menunav">
		  <li><a href="/KKTRSS.Web/Default.aspx">Home</a></li>
		  <li id="sep_1" class="separator">::</li>
		  <li><a href="/KKTRSS.Web/src/admin.aspx">Administration</a></li>
		  <li id="Li1" class="separator">::</li>
		  <li><a href="/KKTRSS.Web/login.aspx?logout=true">Logout</a></li>
		</ul>
      </div>
			
	  
	  <!-- Channels box -->	  
	  <div id="channelsbox">
		<h3 id="channelslabel">
		  <span id="minus">-</span><span id="plus" class="invisible">&#43;</span> Channels
		</h3>
		<ul id="channelslist">
				<% foreach (DictionaryEntry de in Feedsmap)
				   {
				     KKTFeed kktfeed = (KKTFeed)de.Value;
					 string name = kktfeed.Name;
                     string feedid = (string)de.Key;
                     string qs_str = "?" +
                           FEED_ID + "=" + feedid + "&" +
						   PROXY_MODE + "=" + proxymode.ToString() + "&" +
						   DSP_NB_ITEMS + "=" + dspnbitems.ToString() + "&" +
						   DSP_ONLY_UNREAD + "=" + dsponlyread.ToString();                          
				%>
		  <li class="channelsinbox"><a href="showfeed.aspx<%= qs_str %>" title="<%= name %>"><%= name%></a></li>
				<% } %>
		</ul>
	  </div>
	  
	  
	  <!-- FEED -->
	  <div class="feed">

		<!-- CHANNELS -->
		<% foreach (Rss.RssChannel current_channel in Currentfeed.Channels) { %>
		<div class="channel">
		  <h3><a class="name" href="<%= current_channel.Link %>"><%= current_channel.Title %> (<%= current_channel.Items.Count %>)</a></h3>
  
		  <!-- ITEMS -->
		  <% foreach (Rss.RssItem current_item in current_channel.Items) { 
			  string item_id = getItemID(current_item);
			  if (!dsponlyread || (dsponlyread && !readitems.Contains(item_id))) {
		  %>
		  <div class="item">
			<h4> <!-- Title of the item with + and - signs -->
			  <span id="minus_<%= item_id %>">&#45;</span>
			  <span id="plus_<%= item_id %>" class="invisible">&#43;</span>
			  <a href="<%= current_item.Link %>"><%= current_item.Title %></a>
			</h4>
			<ul id="infos_<%= item_id %>" class="infos">
			  <li>Date: <%= current_item.PubDate %></li>
			  <li>Author: <%= current_item.Author %></li>
			</ul>
			<div id="desc_<%= item_id %>" class="desc">
			  <%= current_item.Description %>
			</div>
			<ul id="actions">
			  <li><a href="<%= current_item.Link %>">Read more</a></li>
			  <li><a href="#">Mark as read</a></li>
			  <li><a href="#">Tag</a></li>
			</ul>
			
			<!-- ATLAS stuffs -->
			<script type="text/xml-script">
			  <page xmlns:script="http://schemas.microsoft.com/xml-script/2005">
				<components>
				  <!-- Hide channelslist -->
		  					  
				  <button targetElement="minus_<%= item_id %>">
					<click> <!-- Hide desc and minus sign, show plus sign -->
<!--					  <invokeMethod target="desc_<%= item_id %>" method="addCssClass">
						<parameters className="invisible"/>
					  </invokeMethod>
					  <invokeMethod target="desc_<%= item_id %>" method="removeCssClass">
						<parameters className="visible"/>
					  </invokeMethod>-->
					  <invokeMethod target="minus_<%= item_id %>" method="addCssClass">
						<parameters className="invisible"/>
					  </invokeMethod>
					  <invokeMethod target="minus_<%= item_id %>" method="removeCssClass">
						<parameters className="visible"/>
					  </invokeMethod>
					  <invokeMethod target="plus_<%= item_id %>" method="addCssClass">
						<parameters className="visible"/>
					  </invokeMethod>
					  <invokeMethod target="plus_<%= item_id %>" method="removeCssClass">
						<parameters className="invisible"/>
					  </invokeMethod>
<!--					  <invokeMethod target="infos_<%= item_id %>" method="addCssClass">
						<parameters className="invisible"/>
					  </invokeMethod>
					  <invokeMethod target="infos_<%= item_id %>" method="removeCssClass">
						<parameters className="visible"/>
					  </invokeMethod>-->
					</click>
				  </button>
		  					  
				  <button targetElement="plus_<%= item_id %>">
					<click>
<!--					  <invokeMethod target="desc_<%= item_id %>" method="addCssClass">
						<parameters className="visible"/>
					  </invokeMethod>
					  <invokeMethod target="desc_<%= item_id %>" method="removeCssClass">
						<parameters className="invisible"/>
					  </invokeMethod>-->
					  <invokeMethod target="minus_<%= item_id %>" method="addCssClass">
						<parameters className="visible"/>
					  </invokeMethod>
					  <invokeMethod target="minus_<%= item_id %>" method="removeCssClass">
						<parameters className="invisible"/>
					  </invokeMethod>
					  <invokeMethod target="plus_<%= item_id %>" method="addCssClass">
						<parameters className="invisible"/>
					  </invokeMethod>
					  <invokeMethod target="plus_<%= item_id %>" method="removeCssClass">
						<parameters className="visible"/>
					  </invokeMethod>
					</click>
				  </button>
							  
				</components>
			  </page>
			</script>
    
		  </div> <!-- !item -->
		<% } // if : DSP_ONLY_UNREAD 
		  string color = "#000000";
		  if (readitems.Contains(item_id)) color = "#FF0000";
		 %>
		 <span class="itemid" style="color:<%= color %>">id=<%= item_id %></span><br/>
		<%  } // for : items
		 } // for : channels %>
		</div> <!-- !channel -->
                
	  </div> <!-- !feed -->
            
	  </div> <!-- !content -->

  </form>
    
    <!-- AJAX code for ChannelsBox starts here -->
    <script type="text/xml-script">
	  <page xmlns:script="http://schemas.microsoft.com/xml-script/2005">
		<components>
		  
		  <!-- Operations on channelslist -->
		  <control targetElement="channelslist"/>
		  
		  <!-- Show channelslist -->
		  <button targetElement="plus">
			<click>
			  <invokeMethod target="plus" method="addCssClass">
				<parameters className="invisible"/>
              </invokeMethod>
              <invokeMethod target="plus" method="removeCssClass">
				<parameters className="visible"/>
              </invokeMethod>
              <invokeMethod target="minus" method="removeCssClass">
                <parameters className="invisible"/>
              </invokeMethod>
              <invokeMethod target="minus" method="addCssClass">
                <parameters className="visible"/>
              </invokeMethod>
              <invokeMethod target="channelslist" method="removeCssClass">
                <parameters className="invisible"/>
              </invokeMethod>
              <invokeMethod target="channelslist" method="addCssClass">
                <parameters className="visible"/>
              </invokeMethod>
			</click>
		  </button>
		  
		  <!-- Hide channelslist -->
		  <button targetElement="minus">
			<click>
			  <invokeMethod target="minus" method="addCssClass">
				<parameters className="invisible"/>
              </invokeMethod>
              <invokeMethod target="minus" method="removeCssClass">
                <parameters className="visible"/>
              </invokeMethod>
              <invokeMethod target="plus" method="removeCssClass">
                <parameters className="invisible"/>
              </invokeMethod>
              <invokeMethod target="plus" method="addCssClass">
                <parameters className="visible"/>
              </invokeMethod>
              <invokeMethod target="channelslist" method="addCssClass">
                <parameters className="invisible"/>
              </invokeMethod>
              <invokeMethod target="channelslist" method="removeCssClass">
                <parameters className="visible"/>
              </invokeMethod>
			</click>
		  </button>

		</components>
	  </page>
	</script>
    
<!-- #Include File="Footer.inc" -->

</body>
</html>
