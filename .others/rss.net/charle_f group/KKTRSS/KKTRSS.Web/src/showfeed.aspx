<%@ Page Language="C#" AutoEventWireup="true" CodeFile="showfeed.aspx.cs" Inherits="KKTRSS.Web.src_showfeed" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >

  <head runat="server">
    <title>KKTRSS.Feeds</title>
    <link rel="stylesheet" type="text/css" media="screen" href="../css/style.css"/>
    
	<script type="text/javascript" defer="defer">
	<!--
	function init(last_action) {
	  alert('init:'+last_action)
	  switch (last_action){
	  case 'suscribe':
		showBoxHideOthers('channels_suscribe_box');
		break;
	  case 'unsuscribe':
		showBoxHideOthers('channels_unsuscribe_box');
		break;
	  case 'submit':
		showBoxHideOthers('channel_submit_box');
		break;
	  case 'markread':
	  case 'show':
	  default : 
		break;
	  }
	}
	
	function markItemRead(item_id) {
	}
	
	// Show only one box, others are automatically hidden
	function showBoxHideOthers(toShow) {
	  var boxes = new Array('channel_submit_box', 'channels_suscribe_box', 'channels_unsuscribe_box');
	  for (var i = 0; i < boxes.length; i++)
		if (toShow == boxes[i])
		  showBox(boxes[i])
		else
		  hideBox(boxes[i])
	}
	
	// Suscribe/Unsuscribe to feeds
	function suscribe(chan_id, qs) {
	  alert('suscribe func ! chan_id='+chan_id)
	  document.getElementById('channels_suscribe_'+chan_id).style.background = "url('/KKTRSS.Web/img/accept.png') no-repeat left bottom";
	  document.location.href = qs+chan_id;
	}
	function unsuscribe(chan_id, qs) {
	  document.getElementById('channels_unsuscribe_'+chan_id).style.background = "url('/KKTRSS.Web/img/delete.png') no-repeat left bottom";
	  document.location.href = qs+chan_id;
	}
	
	// Closes submit/suscribe/unsuscribe boxes
	function closeBox(box) {
	  hideBox(box);
	  if (document.getElementById(box).hasChildNodes())
		for (var cur_node = document.getElementById(box).firstChild; cur_node != null; cur_node = cur_node.nextSibling)
		  if (cur_node.nodeName == "UL")
			for (var listelem = cur_node.firstChild; listelem != null; listelem = listelem.nextSibling)
			  if (listelem.nodeName == "LI")
				listelem.style.background= "none";
	}
	
	// Show/Hide boxes
	function showBox(box) {
	  document.getElementById(box).style.display = 'block';
	}
	function hideBox(box) {
	  document.getElementById(box).style.display = 'none';
	}
	//-->
	</script>

  </head>

<body onload="init('<%= action %>')">

<!-- #Include File="Header.inc" -->

  <form id="form1" runat="server">
	 <%--<atlas:ScriptManager runat="server" id="scriptManager" />--%>
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
	  <div id="channels_box">
		<h3 id="channels_label">Channels</h3>
		<ul id="channels_list">
				<% foreach (Rss.RssChannel channel in myfeed.Channels) {
                     string qs_str = "?"+CHANNEL_ID+"="+channel.HashID+"&"+PROXY_MODE+"="+Proxymode.ToString()+"&"+UID+"="+uid+"&"+
						   DSP_NB_ITEMS+"="+Dspnbitems.ToString()+"&"+DSP_ONLY_UNREAD+"="+Dsponlyunread.ToString()+"&"+ACTION+"=show";                         
				%>
		  <li class="channelsinbox"><a href="showfeed.aspx<%= qs_str %>" title="<%= channel.Title %>"><%= channel.Title %></a></li>
				<% } %>
		</ul> <!-- !channels_list -->
		
		<ul id="channels_actions" >
		  <li id="chanact_submit"><a href="#" onclick="javascript:showBoxHideOthers('channel_submit_box')"><img alt="submit new feed" title="submit new feed" src="/KKTRSS.Web/img/textfield_add.png" /></a></li>
		  <li id="chanact_add"><a href="#" onclick="javascript:showBoxHideOthers('channels_suscribe_box')"><img alt="add feed" title="add feed" src="/KKTRSS.Web/img/feed_add.png" /></a></li>
		  <li id="chanact_remove"><a href="#" onclick="javascript:showBoxHideOthers('channels_unsuscribe_box')"><img alt="remove feed" title="remove feed" src="/KKTRSS.Web/img/feed_delete.png" /></a></li>
		</ul> <!-- !channels_actions -->
		
		<div id="channel_submit_box" class="box">
		  <span class="boxtitle">Submit new feed</span>
		  <a href="#" onclick="javascript:closeBox('channel_submit_box')"><img alt="close" src="/KKTRSS.Web/img/cancel.png" class="chanact_cancel" title="close"/></a>
		  <% string qs_str_2 = "?"+CHANNEL_ID+"="+channelid+"&"+PROXY_MODE+"="+Proxymode.ToString()+"&"+UID+"="+uid+"&"+
						   DSP_NB_ITEMS + "=" + Dspnbitems.ToString() + "&" + DSP_ONLY_UNREAD + "=" + Dsponlyunread.ToString() + "&" + ACTION + "=submit"; 
			   
		  %>
		  <form action="showfeed.aspx" name="submit_feed" method="post">
			Name:<input type="text" id="submit_feed_name" name="submit_feed_name" size="8"/><br/>
			Url:<input type="text" id="submit_feed_url" name="submit_feed_url" size="15"/>
			<input type="submit" id="submit_feed_btn" name="submit_feed_btn" value="submit" />
			<input type="hidden" id="querystring_<%= PROXY_MODE %>" name="querystring_<%= PROXY_MODE %>" value="<%= Proxymode.ToString() %>" />
			<input type="hidden" id="querystring_<%= ACTION %>" name="querystring_<%= ACTION %>" value="submit" />
			<input type="hidden" id="querystring_<%= CHANNEL_ID %>" name="querystring_<%= CHANNEL_ID %>" value="<%= channelid %>" />
			<input type="hidden" id="Hidden1" name="querystring_<%= DSP_ONLY_UNREAD %>" value="<%= dsponlyunread %>" />
		  </form>
		</div> <!-- !channels_submit_box -->

		<div id="channels_suscribe_box" class="box">
		  <span class="boxtitle">Add feed</span>
		  <% string qs_str_3 = "?"+CHANNEL_ID+"="+channelid+"&"+PROXY_MODE+"="+Proxymode.ToString()+"&"+UID+"="+uid+"&"+
						   DSP_NB_ITEMS + "=" + Dspnbitems.ToString() + "&" + DSP_ONLY_UNREAD + "=" + Dsponlyunread.ToString() + "&" + ACTION + "=suscribe&" + FEED_ID + "="; %>
		  <a href="#" onclick="javascript:closeBox('channels_suscribe_box')"><img alt="close" src="/KKTRSS.Web/img/cancel.png" class="chanact_cancel" title="close"/></a>
		  <ul id="channels_suscribe_list">
			<% foreach (kktserver.RssFeedRef feed in unsuscribedFeeds) { %>
			<li id="channels_suscribe_<%= feed.Id %>"><a href="#" onclick="javascript:suscribe('<%= feed.Id %>', '<%= qs_str_3 %>')"><%= feed.Name %></a></li>
			<% } %>
		  </ul>
		</div> <!-- !channels_suscribe_box -->

		<div id="channels_unsuscribe_box" class="box">
		  <span class="boxtitle">Remove feed</span>
		  <% string qs_str_4 = "?"+CHANNEL_ID+"="+channelid+"&"+PROXY_MODE+"="+Proxymode.ToString()+"&"+UID+"="+uid+"&"+
						   DSP_NB_ITEMS + "=" + Dspnbitems.ToString() + "&" + DSP_ONLY_UNREAD + "=" + Dsponlyunread.ToString() + "&" + ACTION + "=unsuscribe&" + FEED_ID + "="; %>
		  <a href="#" onclick="javascript:closeBox('channels_unsuscribe_box')"><img alt="close" src="/KKTRSS.Web/img/cancel.png" class="chanact_cancel" title="close"/></a>
		  <ul id="channels_unsuscribe_list">
			<% foreach (kktserver.RssFeedRef feed in suscribedFeeds) { %>
			<li id="channels_unsuscribe_<%= feed.Id %>"><a href="#" onclick="javascript:unsuscribe('<%= feed.Id %>', '<%= qs_str_4 %>')"><%= feed.Name %></a></li>
			<% } %>
		  </ul>
		</div> <!-- !channels_unsuscribe_box -->
		
	  </div> <!-- !channels_box -->
	  
	  
	  <!-- FEED -->
	  <div class="feed">
		<% if (current_channel != null) { %>
		<!-- CHANNELS -->
		<div class="channel">
		<% string favico = getFavico(current_channel.Link.AbsoluteUri); %>
		  <h3 id="channel_title">
			<img class="favico" src="<%= favico %>" alt="favico" />
			<a class="name" href="<%= current_channel.Link %>"><%= current_channel.Title %> (<%= current_channel.Items.Count %>)</a>
		  </h3>

		  <!-- ITEMS -->
		  <%
			foreach (Rss.RssItem current_item in current_channel.Items) {
			  string item_id = current_item.HashID;
			  if (!Dsponlyunread || (Dsponlyunread && !current_item.IsRead)) {
				string qs_str_item = "?" + CHANNEL_ID + "=" + channelid + "&" + PROXY_MODE + "=" + Proxymode.ToString() + "&" + UID + "=" + uid + "&" + ITEM_ID + "=" + item_id + "&" +
										   DSP_NB_ITEMS + "=" + Dspnbitems.ToString() + "&" + DSP_ONLY_UNREAD + "=" + Dsponlyunread.ToString() + "&" + ACTION + "=markread";
		  %>
		  <div class="item" id="item_<%= item_id %>" ondblclick="javascript:markItemRead('<%=item_id%>')">
			<h4>
			  <%--<img class="favico" src="<%= favico %>" alt="favico" />--%>
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
			  <li><a href="showfeed.aspx<%= qs_str_item %>">Mark as read</a></li>
			</ul>
		  </div> <!-- !item -->
		  
		<% } // if : DSP_ONLY_UNREAD 
		  string color_ = "#999999";
		  if (current_item.IsRead) 
			color_ = "#FF0000"; %>
		 <span class="itemid" style="color:<%= color_ %>">id=<%= item_id %></span><br/>
		<%  } // foreach : items %>
		</div> <!-- !channel -->
		<%  } // if : current_channel %>
                
	  </div> <!-- !feed -->
            
	  </div> <!-- !content -->

  </form>
    
<!-- #Include File="Footer.inc" -->

</body>
</html>
