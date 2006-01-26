using Rss;
using System;
using System.IO;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using System.Net;
using System.Threading;
using kktserver;
using System.Collections.Generic;


namespace KKTRSS.Web
{

public partial class src_showfeed : System.Web.UI.Page
{

  /* QS Parameters */
  static public string ACTION = "action";
  static public string DSP_NB_ITEMS = "dspnbitems";
  static public string DSP_ONLY_UNREAD = "dsponlyunread";
  static public string CHANNEL_ID = "channelid";
  static public string FEED_ID = "feedid";
  static public string ITEM_ID = "itemid";
  static public string PROXY_MODE = "proxymode";
  static public string UID = "uid";

  /* QS values */
  protected int dspnbitems = 0;
  protected Boolean dsponlyunread = false;
  protected Boolean proxymode = true;
  protected string channelid = "0";
  protected string action = "show";
  protected long feed_id = -1;
  protected long item_id = -1;
 
  /* proxy variables */
  string _proxy_url = "proxies.epitech.net";
  int _proxy_port = 3128;
  string _proxy_user = "valy_m"; 
  string _proxy_pass = "pufCjnc[";
  string _proxy_output_file = @"c:\output-showfeed.aspx.txt";

  private static Hashtable feedsmap;

  protected Rss.RssFeed myfeed;
  protected Rss.RssChannel current_channel;
  protected System.Collections.Specialized.NameValueCollection qs;
  protected kktserver.Service service = new kktserver.Service();
  protected string uid = null;
  
  protected IList availableFeeds = null;
  protected IList suscribedFeeds = null;
  protected IList unsuscribedFeeds = null;
  
  # region Accessors
	protected Boolean Dsponlyunread
	{
	  get { return dsponlyunread; }
	  set { dsponlyunread = value; }
	}
	protected int Dspnbitems
	{
	  get { return dspnbitems; }
	  set { dspnbitems = value; }
	}
	protected Boolean Proxymode
	{
	  get { return proxymode; }
	  set { proxymode = value; }
	}
	protected static Hashtable Feedsmap
	{
        get { return src_showfeed.feedsmap; }
        set { src_showfeed.feedsmap = value; }
    }
    protected System.Collections.Specialized.NameValueCollection Qs
    {
        get { return qs; }
        set { qs = value; }
    }
  #endregion
  

  protected void Page_Load(object sender, EventArgs e)
  {
	string query_channelid = (Request.Form["querystring_" + CHANNEL_ID] != null ? Request.Form["querystring_" + CHANNEL_ID].ToString() : "0");
	string query_action = (Request.Form["querystring_" + ACTION] != null ? Request.Form["querystring_" + ACTION].ToString() : "show");
	Boolean query_proxymode = (Request.Form["querystring_" + PROXY_MODE] != null ? Convert.ToBoolean(Request.Form["querystring_" + PROXY_MODE].ToString()) : proxymode);
	Boolean query_dsponlyunread = (Request.Form["querystring_" + DSP_ONLY_UNREAD] != null ? Convert.ToBoolean(Request.Form["querystring_" + DSP_ONLY_UNREAD].ToString()) : dsponlyunread);
	
	qs = Request.QueryString; 
	if (qs != null)
	{ // First we get the informations from the QueryString
	  uid = qs[UID];
	  action = (qs[ACTION] != null ? qs[ACTION] : query_action);
	  channelid = (qs[CHANNEL_ID] != null ? qs[CHANNEL_ID] : query_channelid);
	  dspnbitems = (qs[DSP_NB_ITEMS] != null ? Convert.ToInt32(qs[DSP_NB_ITEMS]) : dspnbitems);
	  dsponlyunread = (qs[DSP_ONLY_UNREAD] != null ? Convert.ToBoolean(qs[DSP_ONLY_UNREAD]) : dsponlyunread);
	  proxymode = (qs[PROXY_MODE] != null ? Convert.ToBoolean(qs[PROXY_MODE]) : query_proxymode);
	  feed_id = (qs[FEED_ID] != null ? Convert.ToInt32(qs[FEED_ID]) : feed_id);
	  item_id = (qs[ITEM_ID] != null ? Convert.ToInt32(qs[ITEM_ID]) : item_id);
	}

	if (action.Equals("submit"))
		submitFeed(Request.Form["submit_feed_url"].ToString(), Request.Form["submit_feed_name"].ToString());
    else if (action.Equals("suscribe") && feed_id != -1)
		suscribe(feed_id);
    else if (action.Equals("unsuscribe") && feed_id != -1)
		unsuscribe(feed_id);
    else if (action.Equals("markread") && item_id != -1)
		markItemRead(item_id.ToString());

	if (uid != null)
	{ // Then we fetch informations from the server, build lists, set current items ...
	  HttpWebRequest request = null;
	  checkFeeds();
	  myfeed = RssFeed.ReadFromString(service.GetMyRssFeed(uid));
	  if (channelid != "0")
		foreach (Rss.RssChannel c in  myfeed.Channels)
		  if (c.HashID.Equals(channelid))
			current_channel = c;
	  else
		current_channel = null;
	}
	else
	{
	  Response.Redirect("../login.aspx");
	}
  }

  protected string getFavico(string url) 
  {
	Uri uri = new Uri(url);
	uri = new Uri("http://" + uri.Host + "/favicon.ico");
	string favico = null;

	WebRequest request = WebRequest.Create(uri);
	if (proxymode)
	{
	  WebProxy proxy = new WebProxy(_proxy_url, _proxy_port);
	  proxy.Credentials = new NetworkCredential(_proxy_user, _proxy_pass);
	  request.Proxy = proxy;
	}
	try
	{
	  request.Timeout = 2000;
	  WebResponse response = request.GetResponse();
	  favico = uri.ToString();
	}
	catch (WebException exp)
	{
	  favico = "/KKTRSS.Web/rss.png";
	}

	return favico;
  }

  protected void checkFeeds() 
  {
	suscribedFeeds = service.ListSubscribedRssFeeds(uid);
	unsuscribedFeeds = new List<RssFeedRef>();
	availableFeeds = service.ListAvailableRssFeeds(uid);

	foreach (RssFeedRef a in availableFeeds)
	{
	  Boolean inlist = false;
	  foreach (RssFeedRef s in suscribedFeeds)
		if (a.Id.Equals(s.Id))
		  inlist = true;
	  if (!inlist)
		unsuscribedFeeds.Add(a);
	}
  }

  protected void submitFeed(string feedurl, string feedname)
  {
	service.ImportRssFeed(uid, feedurl, feedname, "", false);
  }

  protected void suscribe(long feed_id_)
  {
	service.RssFeedSubscribe(uid, feed_id_);
  }

  protected void unsuscribe(long feed_id_)
  {
	service.RssFeedUnsubscribe(uid, feed_id_);
  }

  // --- unused

  private HttpWebRequest getFeed(string feedid, HttpWebRequest request)
  {
	// Fetches the feed
	KKTFeed kktfeed = (KKTFeed)feedsmap[feedid];
	string feedurl = kktfeed.Url; 
	request = (HttpWebRequest)WebRequest.Create(new Uri(feedurl));

	// Proxy stuffs
	bool err = true;
	FileStream file = new FileStream(_proxy_output_file, FileMode.Create, FileAccess.Write);
	StreamWriter sw = new StreamWriter(file);
	int error_nb = 0;

	while (err == true)
	{
	  try
	  {
		if (proxymode)
		{
		  WebProxy proxy = new WebProxy(_proxy_url, _proxy_port);
		  proxy.Credentials = new NetworkCredential(_proxy_user, _proxy_pass);
		  request.Proxy = proxy;
		}
		//currentfeed = RssFeed.Read(request);
		err = false;
	  }
	  catch (Exception ex)
	  {
		if (proxymode)
		{
		  sw.Write("Proxy error number " + error_nb.ToString() + "\r\n");
		  sw.Write("  proxymode=" + proxymode.ToString() + ";_proxy_url=" + _proxy_url + "\r\n");
		  sw.Write("  ex=" + ex.Message + "\r\n");
		  sw.Flush();
		  error_nb += 1;
		  Thread.Sleep(1000);
		}
		err = true;
	  }
	}
	sw.Close();
	file.Close();

	return request;
  }

  public void markItemRead(string id)
  {
	service.MarkAsRead(uid, id);
  }

  public void markItemNotRead(string id)
  {
  }

  public int gettest()
  {
	return (dsponlyunread ? 1 : 0);
  }
}

}