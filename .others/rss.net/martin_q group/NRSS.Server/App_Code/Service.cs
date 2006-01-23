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
using NHibernate;

[WebService(Namespace = "http://nrss.org/")]
[WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
public class Service : System.Web.Services.WebService
{
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

	user.Email = "user";
	user.Passwd = "pass";

	createUser(user);
  }

  [WebMethod]
  public List<Feed> testGetAllFeeds()
  {
	return getAllFeeds("a2e75e11-d05f-49da-b8d3-e156d50b723d");
  }
  #endregion

  //////////////////////////////////////////////////////////////////////////
  // User management

  #region users
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

	return user.AutoLog;
  }

  [WebMethod]
  public User getUser(string hash)
  {
	ITransaction tx = null;

	try
	{
	  tx = NHibernateHttpModule.CurrentSession.BeginTransaction();

	  tx.Commit();
	}
	catch (Exception ex)
	{
	  if (tx != null)
		tx.Rollback();

	  throw ex;
	}

	return UserManager.Instance.getUser(hash);
  }
  #endregion

  //////////////////////////////////////////////////////////////////////////
  // Feeds

  #region feeds
  #region gets
  [WebMethod]
  [XmlInclude(typeof(Chan)), XmlInclude(typeof(Item))]
  public List<Feed> getFeeds(string uid)
  {
	UserManager.Instance.validate(uid);

	//////////////////////////////////////////////////////////////////////////

	ITransaction tx = null;
	List<Feed> feedsToSend = new List<Feed>();

	BaseDataAccess mgr = new BaseDataAccess();

	try
	{
	  tx = NHibernateHttpModule.CurrentSession.BeginTransaction();

	  //////////////////////////////////////////////////////////////////////////

	  feedsToSend = new List<Feed>();
	  IList feeds = mgr.Get(typeof(Feed));

	  User user = UserManager.Instance.getUser(uid);
	  IList mygroups = user.iGroups;

	  foreach (Feed feed in feeds)
	  {
		Importer.updateFeed(feed);

		if (feed.Groups == null || feed.Groups.Count == 0)
		  feedsToSend.Add(feed);
		else
		  foreach (Group group in feed.Groups)
		  {
			if (mygroups.Contains(group))
			{
			  feedsToSend.Add(feed);
			  break;
			}
		  }

		feed.Selected = user.Feeds != null && user.Feeds.Contains(feed);
	  }

	  tx.Commit();
	}
	catch (Exception ex)
	{
	  if (tx != null)
		tx.Rollback();

	  throw ex;
	}

	return feedsToSend;
  }

  #region add
  [WebMethod]
  public void addFeed(string uid, Feed feed)
  {
	UserManager.Instance.validate(uid);

	BaseDataAccess mgr = new BaseDataAccess();
	User user = UserManager.Instance.getUser(uid);
	Group mygroup = mgr.Get(typeof(Group), "Name", user.Email) as Group;

	feed.Groups = new ArrayList();
	feed.Groups.Add(mygroup);

	mgr.Save(feed);
  }

  [WebMethod]
  public void delFeed(string uid, Feed feed)
  {
	UserManager.Instance.validate(uid);

	BaseDataAccess mgr = new BaseDataAccess();
	feed = mgr.Get(typeof(Feed), "Id", feed.Id) as Feed;

	mgr.Delete(feed);
  }

  #endregion
  #endregion

  #region subscribing
  [WebMethod]
  [XmlInclude(typeof(Feed))]
  public List<Feed> getAllFeeds(string uid)
  {
	UserManager.Instance.validate(uid);

	//////////////////////////////////////////////////////////////////////////

	ITransaction tx = null;
	List<Feed> feedsToSend = new List<Feed>();

	BaseDataAccess mgr = new BaseDataAccess();

	try
	{
	  tx = NHibernateHttpModule.CurrentSession.BeginTransaction();

	  //////////////////////////////////////////////////////////////////////////

	  IList feeds = mgr.Get(typeof(Feed));

	  User user = UserManager.Instance.getUser(uid);
	  IList mygroups = user.iGroups;

	  foreach (Feed feed in feeds)
	  {
		Importer.updateFeed(feed);

		if (feed.Groups == null || feed.Groups.Count == 0)
		  feedsToSend.Add(feed);
		else
		  foreach (Group group in feed.Groups)
		  {
			if (mygroups.Contains(group))
			{
			  feedsToSend.Add(feed);
			  break;
			}
		  }

		feed.Selected = user.Feeds != null && user.Feeds.Contains(feed);
		feed.Chans = null;
	  }

	  tx.Commit();
	}
	catch (Exception ex)
	{
	  if (tx != null)
		tx.Rollback();

	  throw ex;
	}

	return feedsToSend;
  }

  [WebMethod]
  [XmlInclude(typeof(Feed))]
  public void updateFeedsSubscribe(string uid, ArrayList feeds)
  {
	UserManager.Instance.validate(uid);

	//////////////////////////////////////////////////////////////////////////

	Dictionary<string, Feed> feedMap = new Dictionary<string,Feed>();

	foreach (Feed feed in feeds)
	  feedMap[feed.Fils] = feed;

	BaseDataAccess mgr = new BaseDataAccess();
	User user = UserManager.Instance.getUser(uid);

	foreach (Feed feed in mgr.Get(typeof(Feed)))
	{
	  feed.Selected = feedMap[feed.Fils].Selected;

	  if (feed.Selected)
	  {
		if (feed.Users == null)
		  feed.Users = new ArrayList();
		feed.Users.Add(user);
	  }
	  else if (feed.Users != null && feed.Users.Contains(user))
	  {
		feed.Users.Remove(user);
	  }

	  mgr.Save(feed);
	}
  }
  #endregion
  #endregion

  //////////////////////////////////////////////////////////////////////////

  [WebMethod]
  public void setAsRead(string uid, Item item)
  {
	UserManager.Instance.validate(uid);

	//////////////////////////////////////////////////////////////////////////

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