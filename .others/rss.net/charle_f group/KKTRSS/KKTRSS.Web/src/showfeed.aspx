<%@ Page Language="C#" AutoEventWireup="true" CodeFile="showfeed.aspx.cs" Inherits="KKTRSS.Web.src_showfeed" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >

  <head runat="server">
    <title>KKTRSS.Feeds</title>
    <link rel="stylesheet" type="text/css" media="screen" href="../css/style.css"/>
    
	<script type="text/javascript" defer="defer">
	<!--
	/*
	// AJAX stuffs
	vSar textLen = Class.create();
	textLen.prototype = {
	  initialize: function(ele) {
		this.ele = ele;
		this.display = document.getElementById(this.ele.id + "_display");
		addEvent(this.ele, "keyup", this.dosearch.bind(this));
	  },
	  dosearch: function() {
		ASP.WebUserControl1.GetLength(this.ele.value, this.ondata.bind(this));
	  },
	  ondata: function(res) {
		this.display.innerHTML = res.value;
	  }
	};
	function init() {
	  var x = new textLen(document.getElementById("<%=ClientID%>"));
	  x.ele.focus();
	}
	addEvent(window, "load", init);
	*/
	// -- 
	
	function markItemRead(item_id) {
	  //var item = document.getElementById("item_"+item_id);  
	  alert(KKTRSS.Web.src_showfeed.Dsponlyread);
	  alert(KKTRSS.Web.src_showfeed.gettest());
	  /*if (KKTRSS.Web.src_showfeed.dsponlyread == true)
		item.className = "invisible";
	  else
		item.className = "read";
	  KKTRSS.Web.src_showfeed.markItemRead(item_id);*/
	}
	
	// Show/Hide feed boxes
	function addFeeds() {
	  hideBox('channels_unsuscribe_box');
	  showBox('channels_suscribe_box');
	}
	function delFeeds() {
	  hideBox('channels_suscribe_box');
	  showBox('channels_unsuscribe_box');
	}
	
	// Suscribe/Unsuscribe to feeds
	function suscribe(chan_id) {
	  // TODO: add chan
	  document.getElementById('channels_suscribe_'+chan_id).style.background = "url('/KKTRSS.Web/img/accept.png') no-repeat left bottom";
	}
	function unsuscribe(chan_id) {
	  // TODO: remove chan
	  document.getElementById('channels_unsuscribe_'+chan_id).style.background = "url('/KKTRSS.Web/img/delete.png') no-repeat left bottom";
	}
	
	// Closes suscribe/unsuscribe box
	function closeBox(box) {
	  hideBox(box);
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

<body>

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
				<% foreach (DictionaryEntry de in Feedsmap)
				   {
				     KKTFeed kktfeed = (KKTFeed)de.Value;
					 string name = kktfeed.Name;
                     string feedid = (string)de.Key;
                     string qs_str = "?"+FEED_ID+"="+feedid+"&"+PROXY_MODE+"="+Proxymode.ToString()+"&"+
						   DSP_NB_ITEMS+"="+Dspnbitems.ToString()+"&"+DSP_ONLY_UNREAD+"="+Dsponlyread.ToString();                          
				%>
		  <li class="channelsinbox"><a href="showfeed.aspx<%= qs_str %>" title="<%= name %>"><%= name%></a></li>
				<% } %>
		</ul>
		
		<ul id="channels_actions">
		  <li id="chanact_add"><a href="#" onclick="javascript:addFeeds()"><img alt="add feed" title="add feed" src="/KKTRSS.Web/img/feed_add.png" /></a></li>
		  <li id="chanact_remove"><a href="#" onclick="javascript:delFeeds()"><img alt="remove feed" title="remove feed" src="/KKTRSS.Web/img/feed_delete.png" /></a></li>
		</ul>
		
		<div id="channels_suscribe_box">
		  <span class="boxtitle">Add feed</span>
		  <a href="#" onclick="javascript:closeBox('channels_suscribe_box')"><img alt="close" src="/KKTRSS.Web/img/cancel.png" class="chanact_cancel" title="close"/></a>
		  <ul id="channels_suscribe_list">
			<% foreach (DictionaryEntry de in Feedsmap) { 
			     KKTFeed kktfeed = (KKTFeed)de.Value;
				 string name = kktfeed.Name;
                 string feedid = (string)de.Key; 
			%>
			<li id="channels_suscribe_<%= feedid %>"><a href="#" onclick="javascript:suscribe('<%= feedid %>')"><%= name %></a></li>
			<% } %>
		  </ul>
		</div>

		<div id="channels_unsuscribe_box">
		  <h6 class="boxtitle">Remove feed</h6>
		  <a href="#" onclick="javascript:closeBox('channels_unsuscribe_box')"><img alt="close" src="/KKTRSS.Web/img/cancel.png" class="chanact_cancel" title="close"/></a>
		  <ul id="channels_unsuscribe_list">
			<% foreach (DictionaryEntry de in Feedsmap) { 
			     KKTFeed kktfeed = (KKTFeed)de.Value;
				 string name = kktfeed.Name;
                 string feedid = (string)de.Key; 
			%>
			<li id="channels_unsuscribe_<%= feedid %>"><a href="#" onclick="javascript:unsuscribe('<%= feedid %>')"><%= name %></a></li>
			<% } %>
		  </ul>
		</div>
		
	  </div>
	  
	  
	  <!-- FEED -->
	  <div class="feed">

		<!-- CHANNELS -->
		<% foreach (Rss.RssChannel current_channel in Currentfeed.Channels) { 
			string favico = getFavico(Currentfeed.Url); %>
		<div class="channel">
		  <h3>
			<img class="favico" src="<%= favico %>" alt="favico" />
			<a class="name" href="<%= current_channel.Link %>"><%= current_channel.Title %> (<%= current_channel.Items.Count %>)</a>
		  </h3>
  
		  <!-- ITEMS -->
		  <% 
			foreach (Rss.RssItem current_item in current_channel.Items) {		  
			  string item_id = current_item.HashID;
			  if (item_id.StartsWith("2"))
				markItemRead(item_id);
			  if (readitems.Contains(item_id)) 
				current_item.IsRead = true;
			  if (!Dsponlyread || (Dsponlyread && !current_item.IsRead)) {
		  %>
		  <div class="item" id="item_<%= item_id %>" ondblclick="javascript:markItemRead('<%=item_id%>')">
			<h4> <!-- Title of the item with + and - signs -->
			  <!--<img class="favico" src="<%= favico %>" alt="favico" />-->
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
			  <li><a href="#" onclick="javascript:markItemRead('<%=item_id%>')">Mark as read</a></li>
			</ul>
		  </div> <!-- !item -->
		  
		<% } // if : DSP_ONLY_UNREAD 
		  string color_ = "#999999";
		  if (current_item.IsRead) color_ = "#FF0000";
		 %>
		 <span class="itemid" style="color:<%= color_ %>">id=<%= item_id %></span><br/>
		<%  } // for : items
		 } // for : channels %>
		</div> <!-- !channel -->
                
	  </div> <!-- !feed -->
            
	  </div> <!-- !content -->

  </form>
    
<!-- #Include File="Footer.inc" -->

</body>
</html>
