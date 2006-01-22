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
public class NNTPImporter : Importer
{
  public NNTPImporter()
  {
	_type.DefaultPort = 115;
	_type.Name = "nntp";
	_type.Description = "News groups protocol retriever";
  }

  protected override void _updateFeed(Feed feed)
  {
	Session session = new Session(feed.Fils, feed.FilsPort);

	NewsGroupCollection	groups = session.GetNewsGroups();

	if (feed.Chans == null)
	  feed.Chans = new ArrayList();
	feed.Chans.Clear();

	foreach (NewsGroup group in groups)
	{
	  Chan chan = new Chan();

	  chan.Feed = feed;

	  chan.Title = group.Name;
	  chan.Description = group.Name;

	  if (chan.Items == null)
		chan.Items = new ArrayList();
	  chan.Items.Clear();

	  Dictionary<string, Item> articleItem = new Dictionary<string, Item>();
	  foreach (Article article in group.GetArticles(false))
	  {
		Item item = new Item();

		item.Chan = chan;

		item.MessageID = article.Header.MessageID;
		item.Author = article.Header.From;
		item.Date = article.Header.Date;
		item.Title = article.Header.Subject;
		item.Description = article.Header.Summary;
		//item.Link = article.Header.Organization;

		item.Content = article.Body.ToString();

		if (article.Header.References != null && article.Header.References.Length > 0)
		  item.Parent = articleItem[article.Header.References[article.Header.References.Length-1]];

		chan.Items.Add(item);
		articleItem[item.MessageID] = item;
	  }

	  feed.Chans.Add(chan);
	}
  }
}