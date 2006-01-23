using System;
using System.Web;
using System.Web.Services;
using System.Web.Services.Protocols;
using NRSS.Server.DataAccess;
using NRSS.mapping;
using System.IO;
using System.Collections.Generic;
using System.Collections;
using Iesi.Collections;
using System.Configuration;
using NRSS;
using NRSS.errors;
using System.Xml.Serialization;

[WebService(Namespace = "http://nrss.org/")]
[WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
public class Service : System.Web.Services.WebService
{
  public AuthHeader Authentication;

  public class AuthHeader : SoapHeader
  {
	public string Username;
	public string Password;
  }

  public Service()
  { }

  //////////////////////////////////////////////////////////////////////////

  #region tests
  [WebMethod]
  [XmlInclude(typeof(Chan)), SoapInclude(typeof(Item))]
  public Feed testRSS()
  {
	Feed  feed = new Feed();

	feed.Type = "rss";
	feed.Fils = "http://www.lemonde.fr/rss/sequence/0,2-3208,1-0,0.xml";

	//////////////////////////////////////////////////////////////////////////
	
	Importer.updateFeed(feed);

	BaseDataAccess mgr = new BaseDataAccess();
	mgr.Save(feed);

	return feed;
  }

  [WebMethod]
  public void testCreateUser()
  {
	User user = new User();

	user.Email = "ttttt";
	user.Passwd = "ppppp";

	createUser(user);
  }
  #endregion

  //////////////////////////////////////////////////////////////////////////
  // Supported types

  [WebMethod]
  public List<ImportType> getSupportedTypes()
  {
	List<ImportType> types = new List<ImportType>();

	foreach (KeyValuePair<string, Importer> pair in Importer.Importers)
	{
	  types.Add(pair.Value.Type);
	}

	return types;
  }

  //////////////////////////////////////////////////////////////////////////
  // User management

  [WebMethod]
  public void createUser(User user)
  {
	UserManager.Instance.createUser(user);
  }

  [WebMethod]
  public void validateUser(string hash)
  {
	UserManager.Instance.activate(hash);
  }

  [WebMethod]
  public string logon(string email, string pass)
  {
	User user = UserManager.Instance.logon(email, pass);

	if (user.iGroups != null)
	  foreach (Group group in user.iGroups)
		group.iUsers = null;

	return user.AutoLog;
  }

  [WebMethod]
  public User getUser(string hash)
  {
	return UserManager.Instance.getUser(hash);
  }

  //////////////////////////////////////////////////////////////////////////
  // Feeds

  [WebMethod]
  [XmlInclude(typeof(Chan)), XmlInclude(typeof(Item))]
  public List<Feed> getFeeds(string uid)
  {
	UserManager.Instance.validate(uid);

	List<Feed> feeds = new List<Feed>();

	User user = UserManager.Instance.getUser(uid);

	foreach (Group group in user.Groups)
	{
	  foreach (Feed feed in group.Feeds)
	  {
		if (!feeds.Contains(feed))
		{
		  Importer.updateFeed(feed);
		  feeds.Add(feed);

		  foreach (Chan chan in feed.Chans)
			foreach (Item item in chan.Items)
			{
			  item.Read = item.ReaderUsers.Contains(user);
			}
		}
	  }
	}

	return feeds;
  }

  [WebMethod]
  [XmlInclude(typeof(Feed))]
  public IList getAllFeeds(string uid)
  {
	UserManager.Instance.validate(uid);

	BaseDataAccess mgr = new BaseDataAccess();
	IList feeds = mgr.Get(typeof(Feed));

	User user = UserManager.Instance.getUser(uid);
	IList mygroups = user.iGroups;

	foreach (Feed feed in feeds)
	{
	  Importer.updateFeed(feed);

	  #region chans
	  foreach (Chan chan in feed.iChans)
	  {
		foreach (Group group in chan.Groups)
		{
		  if (mygroups.Contains(group))
		  {
			chan.Selected = true;
			break;
		  }

		  chan.Selected = false;
		}

		chan.iItems = null;
	  }
	  #endregion

	  foreach (Group group in feed.Groups)
	  {
		if (mygroups.Contains(group))
		{
		  feed.Selected = true;
		  break;
		}

		feed.Selected = false;
	  }
	}

	return feeds;
  }

  [WebMethod]
  [XmlInclude(typeof(Feed))]
  public void updateFeedsSubscibe(string uid, ArrayList feeds)
  {
	UserManager.Instance.validate(uid);

	Dictionary<string, Feed> feedMap = new Dictionary<string,Feed>();
	Dictionary<string, Chan> chanMap = new Dictionary<string, Chan>();

	foreach (Feed feed in feeds)
	{
	  if (feed.Chans != null)
		foreach (Chan chan in feed.Chans)
		  chanMap[chan.Title] = chan;

	  feedMap[feed.Fils] = feed;
	}

	BaseDataAccess mgr = new BaseDataAccess();
	User user = UserManager.Instance.getUser(uid);
	Group mygroup = mgr.Get(typeof(Group), "Name", user.Email) as Group;
	IList myfeeds = mgr.Get(typeof(Feed));

	foreach (Feed feed in myfeeds)
	{
	  Importer.updateFeed(feed);

	  #region chans
	  foreach (Chan chan in feed.iChans)
	  {
		if (chan.Selected)
		{
		  if (chan.Groups == null)
			chan.Groups = new ArrayList();
		  chan.Groups.Add(mygroup);
		}
		else if (chan.Groups != null && chan.Groups.Contains(mygroup))
		{
		  chan.Groups.Remove(mygroup);
		}
	  }
	  #endregion

	  if (feed.Selected)
	  {
		if (feed.Groups == null)
		  feed.Groups = new ArrayList();
		feed.Groups.Add(mygroup);
	  }
	  else if (feed.Groups != null && feed.Groups.Contains(mygroup))
	  {
		feed.Groups.Remove(mygroup);
	  }
	}
  }

  //////////////////////////////////////////////////////////////////////////

  [WebMethod]
  public void setAsRead(string uid, Item item)
  {
	UserManager.Instance.validate(uid);

	User user = UserManager.Instance.getUser(uid);

	BaseDataAccess mgr = new BaseDataAccess();
	item = mgr.Get(typeof(Item), "Id", item.Id) as Item;

	if (item.Read && !user.ReadItems.Contains(item))
	  user.ReadItems.Add(item);
	else if (!item.Read && user.ReadItems.Contains(item))
	  user.ReadItems.Remove(item);

	mgr.Save(user);
  }

  //////////////////////////////////////////////////////////////////////////

  /*[WebMethod]
  public List<Feed> setAsRead(string uid, Item item)
  { 

  }*/

  //////////////////////////////////////////////////////////////////////////
}