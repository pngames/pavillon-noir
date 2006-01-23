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

namespace KKTRSS.Web
{

public partial class src_showfeed : System.Web.UI.Page
{

  /* QS Parameters */
  static public string DSP_NB_ITEMS = "dspnbitems";
  static public string DSP_ONLY_UNREAD = "dsponlyunread";
  static public string FEED_ID = "feedid";
  static public string PROXY_MODE = "proxymode";
  static public string UID = "uid";

  /* QS values */
  protected int dspnbitems = 0;
  protected Boolean dsponlyread = false;
  protected Boolean proxymode = true;
 
  /* proxy variables */
  string _proxy_url = "proxies.epitech.net";
  int _proxy_port = 3128;
  string _proxy_user = "valy_m"; 
  string _proxy_pass = "pufCjnc[";
  string _proxy_output_file = @"c:\output-showfeed.aspx.txt";

  private static Hashtable feedsmap; // source feeds
  private Rss.RssFeed currentfeed;
  protected ArrayList readitems;

  protected Rss.RssFeed myfeed;
  private Rss.RssFeed currentfeed;
  protected System.Collections.Specialized.NameValueCollection qs;
  protected kktserver.Service service = new kktserver.Service();
  protected string uid = null;
  
  # region Accessors
	[AjaxPro.AjaxProperty]
	protected Boolean Dsponlyread
	{
	  get { return dsponlyread; }
	  set { dsponlyread = value; }
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
    protected Rss.RssFeed Currentfeed
    {
        get { return currentfeed; }
        set { currentfeed = value; }
    }
    protected System.Collections.Specialized.NameValueCollection Qs
    {
        get { return qs; }
        set { qs = value; }
    }
  #endregion
  

  protected void Page_Load(object sender, EventArgs e)
  {
	qs = Request.QueryString; 
	if (qs != null)
	{
	  uid = qs[UID];
	  dspnbitems = (qs[DSP_NB_ITEMS] != null ? Convert.ToInt32(qs[DSP_NB_ITEMS]) : dspnbitems);
	  dsponlyread = (qs[DSP_ONLY_UNREAD] != null ? Convert.ToBoolean(qs[DSP_ONLY_UNREAD]) : dsponlyread);
	  proxymode = (qs[PROXY_MODE] != null ? Convert.ToBoolean(qs[PROXY_MODE]) : proxymode);
	}

	if (uid != null)
	{
	  myfeed = RssFeed.ReadFromString(service.GetMyRssFeed());
	  HttpWebRequest request = null;
	}
	else
	{
	  Response.Redirect("login.aspx");
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
		currentfeed = RssFeed.Read(request);
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

  [AjaxPro.AjaxMethod()]
  public void markItemRead(string id)
  {
	readitems.Add(id);
	System.Console.WriteLine("id is " + id);
  }

  [AjaxPro.AjaxMethod()]
  public void markItemNotRead(string id)
  {
	readitems.Remove(id);
  }
  [AjaxPro.AjaxMethod()]
  public int gettest()
  {
	return (dsponlyread ? 1 : 0);
  }
}

}