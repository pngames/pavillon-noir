using System;
using System.Data;
using System.Configuration;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using NRSS.mapping;
using System.Net;
using Rss;
using System.Collections.Generic;
using System.Collections;
using Iesi.Collections;

/// <summary>Summary description for RSSImporter</summary>
internal class RSSImporter : Importer
{
  public RSSImporter()
  {
	_type.DefaultPort = 80;
	_type.Name = "rss";
	_type.Description = "RSS feeds protocol retriever";
  }

  protected override void _updateFeed(Feed feed)
  {
	HttpWebRequest request = null;

	request = (HttpWebRequest)WebRequest.Create(feed.Fils);

	if (NRSSConfProxy.Instance.ProxyEnabled)
	{
	  WebProxy proxy = new WebProxy(NRSSConfProxy.Instance.ProxyUrl, NRSSConfProxy.Instance.ProxyPort);
	  proxy.Credentials = new NetworkCredential(NRSSConfProxy.Instance.ProxyLogin, NRSSConfProxy.Instance.ProxyPass);
	  request.Proxy = proxy;
	}

	RssFeed rssFeed = RssFeed.Read(request);

	if (feed.Chans == null)
	  feed.Chans = new ArrayList();
	feed.Chans.Clear();

	foreach (RssChannel rsschan in rssFeed.Channels)
	{
	  Chan chan = new Chan();

	  chan.Feed = feed;

	  chan.Title = rsschan.Title;
	  chan.Description = rsschan.Description;

	  if (chan.Items == null)
		chan.Items = new ArrayList();
	  chan.Items.Clear();

	  foreach (RssItem rssitem in rsschan.Items)
	  {
		Item item = new Item();

		item.Chan = chan;

		item.Author = rssitem.Author;
		item.Date = rssitem.PubDate;
		item.Title = rssitem.Title;
		item.Description = rssitem.Description;
		item.Link = rssitem.Link;

		//item.Content = rssitem.;

		chan.Items.Add(item);
	  }

	  feed.Chans.Add(chan);
	}
  }
}