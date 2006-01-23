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
	RssFeed rssFeed = null;
	int tries = 20;

  Retry:
	try
	{
	  HttpWebRequest request = (HttpWebRequest)WebRequest.Create(feed.Fils);

	  if (NRSSConfProxy.Instance.ProxyEnabled)
	  {
		WebProxy proxy = new WebProxy(NRSSConfProxy.Instance.ProxyUrl, NRSSConfProxy.Instance.ProxyPort);
		proxy.Credentials = new NetworkCredential(NRSSConfProxy.Instance.ProxyLogin, NRSSConfProxy.Instance.ProxyPass);
		request.Proxy = proxy;
	  }

	  rssFeed = RssFeed.Read(request);
	}
	catch (Exception)
	{
	  if (--tries > 0)
		goto Retry;
	  else
		return;
	}

	if (feed.iChans == null)
	  feed.iChans = new ArrayList();

	Dictionary<string, Chan> chanMap = new Dictionary<string, Chan>();

	foreach (Chan chan in feed.iChans)
	  chanMap[chan.Link] = chan;

	foreach (RssChannel rsschan in rssFeed.Channels)
	{
	  if (chanMap.ContainsKey(rsschan.Link.ToString()))
		continue;

	  Chan chan = new Chan();

	  chan.Feed = feed;

	  chan.Title = rsschan.Title;
	  chan.Description = rsschan.Description;
	  chan.Language = rsschan.Language;
	  chan.Link = rsschan.Link.ToString();

	  if (chan.iItems == null)
		chan.iItems = new ArrayList();

	  Dictionary<string, Item> itemMap = new Dictionary<string, Item>();

	  foreach (Item item in chan.iItems)
		itemMap[item.Link] = item;

	  foreach (RssItem rssitem in rsschan.Items)
	  {
		if (itemMap.ContainsKey(rssitem.Link.ToString()))
		  continue;

		Item item = new Item();

		item.Chan = chan;

		item.Author = rssitem.Author;
		item.Date = rssitem.PubDate;
		item.Title = rssitem.Title;
		item.Description = rssitem.Description;
		item.Link = rssitem.Link.ToString();

		//item.Content = rssitem.;

		chan.iItems.Add(item);
	  }

	  feed.iChans.Add(chan);
	}
  }

  protected override void _updateChan(Chan chan)
  {

  }

  protected override void _updateItem(Item item)
  {
  }
}