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
using Smilla.Net.NNTPClient;
using Iesi.Collections;
using System.Collections.Generic;
using System.Collections;

/// <summary>Summary description for NNTPImporter</summary>
internal class NNTPImporter : Importer
{
  public NNTPImporter()
  {
	_type.DefaultPort = 119;
	_type.Name = "nntp";
	_type.Description = "News groups protocol retriever";
  }

  protected override void _updateFeed(Feed feed)
  {
	Session session = new Session(feed.Fils, feed.FilsPort);

	NewsGroupCollection	groups = session.GetNewsGroups();

	if (feed.Chans == null)
	  feed.Chans = new ArrayList();

	Dictionary<string, Chan> chanMap = new Dictionary<string, Chan>();

	foreach (Chan chan in feed.iChans)
	  chanMap[chan.Title] = chan;

	foreach (string groupname in groups)
	{
	  if (chanMap.ContainsKey(groupname))
		continue;

	  NewsGroup group = groups[groupname];

	  Chan chan = new Chan();
	  chan.Title = group.Name;

	  feed.iChans.Add(chan);
	}
  }

  protected override void _updateChan(Chan chan)
  {
	Session session = new Session(chan.Feed.Fils, chan.Feed.FilsPort);
	NewsGroupCollection groups = session.GetNewsGroups();

	//////////////////////////////////////////////////////////////////////////

	foreach (string groupname in groups)
	{
	  if (chan.Title != groupname)
		continue;

	  NewsGroup group = groups[groupname];

	  ArticleCollection articles = group.GetArticles(true, 100);

	  chan.Description = group.Name;

	  if (chan.Items == null)
		chan.Items = new ArrayList();

	  Dictionary<string, Item> itemMap = new Dictionary<string, Item>();

	  foreach (Item item in chan.Items)
		itemMap[item.MessageID] = item;

	  Dictionary<string, Item> articleItem = new Dictionary<string, Item>();
	  foreach (string messageID in articles)
	  {
		if (itemMap.ContainsKey(articles[messageID].Header.MessageID))
		  continue;

		Item item = new Item();

		item.Chan = chan;

		item.MessageID = articles[messageID].Header.MessageID;
		item.Author = articles[messageID].Header.From;
		item.Date = articles[messageID].Header.Date;
		item.Title = articles[messageID].Header.Subject;
		item.Description = articles[messageID].Header.Summary;
		//item.Link = article.Header.Organization;

		//item.Content = articles[messageID].Body.ToString();

		if (articles[messageID].Header.References != null && articles[messageID].Header.References.Length > 0 &&
		  articleItem.ContainsKey(articles[messageID].Header.References[articles[messageID].Header.References.Length - 1]))
		  item.Parent = articleItem[articles[messageID].Header.References[articles[messageID].Header.References.Length - 1]];

		chan.Items.Add(item);
		articleItem[item.MessageID] = item;
	  }
	}
  }

  protected override void _updateItem(Item item)
  { 

  }
}