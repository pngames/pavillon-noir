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



public partial class src_showfeed : System.Web.UI.Page
{

    /* QS Parameters */
    static public string DSP_NB_ITEMS = "dspnbitems";
    static public string DSP_ONLY_UNREAD = "dsponlyunread"; // true|false || 1|0
    static public string FEED_ID = "feedid";
    static public string PROXY_MODE = "proxymode";

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
    protected System.Collections.Specialized.NameValueCollection qs;
	protected ArrayList readitems;



    # region Accessors
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

		if (qs != null)
		{
		  dspnbitems = (qs[DSP_NB_ITEMS] != null ? Convert.ToInt32(qs[DSP_NB_ITEMS]) : dspnbitems);
		  dsponlyread = (qs[DSP_ONLY_UNREAD] != null ? Convert.ToBoolean(qs[DSP_ONLY_UNREAD]) : dsponlyread);
		  proxymode = (qs[PROXY_MODE] != null ? Convert.ToBoolean(qs[PROXY_MODE]) : proxymode);
		}
		
		readitems = new ArrayList();
		markItemRead("9304ebff1a1a96453a32de19df544c6f");
		markItemRead("856ba38c9e6c6d220d092dcbc81587d5");
		markItemRead("9dd698ecdb7b8c8cd5bf2e000aa9da38");
		markItemRead("310c8b8f792e9043e83ced4ccc7ca9cd");
		markItemRead("a202415de95b4ea4c79175c6cf82d90a");

		currentfeed = new RssFeed();
        initFeedsMap();

        qs = Request.QueryString;
        HttpWebRequest request = null;

        if (qs[FEED_ID] != null && feedsmap.Contains(qs[FEED_ID]))
        {
            try
            {
                request = getFeed(qs[FEED_ID], request);
            }
            catch (IndexOutOfRangeException ioore)
            {
                throw new Exception("unknown feed");
            }
        }


    }

    private static void initFeedsMap()
    {
        // Sets some feeds
        feedsmap = new Hashtable();
        feedsmap.Add("1", new KKTFeed("pcinpact.com", "http://www.pcinpact.com/include/news.xml"));
        feedsmap.Add("2", new KKTFeed("lemonde.fr", "http://www.lemonde.fr/rss/sequence/0,2-3208,1-0,0.xml"));
        feedsmap.Add("3", new KKTFeed("digg.com", "http://digg.com/rss/index.xml"));
    }

	protected string getItemID(RssItem item)
	{
	  string time = item.PubDate.ToUniversalTime().ToShortTimeString();
	  string data = item.Author + item.Description + item.PubDate.ToUniversalTime().ToShortTimeString() + item.Title;
	  
	  System.Security.Cryptography.MD5CryptoServiceProvider x = new System.Security.Cryptography.MD5CryptoServiceProvider();
	  byte[] bs = System.Text.Encoding.UTF8.GetBytes(data);
	  bs = x.ComputeHash(bs);
	  System.Text.StringBuilder s = new System.Text.StringBuilder();
	  foreach (byte b in bs)
		s.Append(b.ToString("x2").ToLower());
	  return s.ToString();
	}

  protected void markItemRead(string id)
  {
	readitems.Add(id);
  }

  protected void markItemNotRead(string id)
  {
	readitems.Remove(id);
  }


    private HttpWebRequest getFeed(string feedid, HttpWebRequest request)
    {
        // Fetches the feed
        KKTFeed kktfeed = (KKTFeed)feedsmap[feedid];
        string feedurl = kktfeed.Url; 
        request = (HttpWebRequest)WebRequest.Create(new Uri(feedurl));

        // Proxy stuffs
        Boolean proxy_mode = true;
		//Boolean proxy_mode = (qs[PROXY_MODE] == "" ? true : Convert.ToBoolean(qs[PROXY_MODE]));
        bool err = true;
        FileStream file = new FileStream(_proxy_output_file, FileMode.Create, FileAccess.Write);
        StreamWriter sw = new StreamWriter(file);
        int error_nb = 0;

        while (err == true)
        {
            try
            {
                if (proxy_mode)
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
                if (proxy_mode)
                {
                    sw.Write("Proxy error number " + error_nb.ToString() + "\r\n");
                    sw.Write("  proxy_mode=" + proxy_mode.ToString() + ";_proxy_url=" + _proxy_url + "\r\n");
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
}
