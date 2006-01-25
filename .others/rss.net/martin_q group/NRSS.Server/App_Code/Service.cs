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
  public string testLogon()
  { 
	return logon("user", "pass");
  }

  [WebMethod]
  public List<Feed> testGetAllFeeds()
  {
	return getFeeds("081c3921-41cc-46ec-a24d-181958d24f95");
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

	  tx.Commit();

	  foreach (Feed feed in feeds)
	  {
		tx = NHibernateHttpModule.CurrentSession.BeginTransaction();
		if (feed.Groups == null || feed.Groups.Count == 0)
		{
		  if (user.Feeds != null && user.Feeds.Contains(feed))
		  {
			Importer.updateFeed(feed);
			feedsToSend.Add(feed);
		  }
		}
		else
		  foreach (Group group in feed.Groups)
		  {
			if (mygroups.Contains(group))
			{
			  if (user.Feeds != null && user.Feeds.Contains(feed))
			  {
				Importer.updateFeed(feed);
				feedsToSend.Add(feed);
			  }
			  break;
			}
		  }

		if (feed.iChans != null)
		  foreach (Chan chan in feed.iChans)
			if (chan.iItems != null)
			  foreach (Item item in chan.iItems)
			  {
				if (item.ReaderUsers != null && item.ReaderUsers.Contains(user))
				  item.Read = true;
			  }

		tx.Commit();

		mgr.Save(feed);
	  }
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
  [XmlInclude(typeof(Chan))]
  public Feed updateFeed(string uid, Feed oldFeed)
  {
	UserManager.Instance.validate(uid);

	//////////////////////////////////////////////////////////////////////////

	ITransaction tx = null;

	BaseDataAccess mgr = new BaseDataAccess();
	Feed feed = null;

	try
	{
	  tx = NHibernateHttpModule.CurrentSession.BeginTransaction();

	  feed = mgr.Get(typeof(Feed), oldFeed.Id) as Feed;

	  if (feed == null)
		return null;

	  Importer.updateFeed(feed);

	  tx.Commit();
	}
	catch (Exception ex)
	{
	  if (tx != null)
		tx.Rollback();

	  throw ex;
	}

	mgr.Save(feed);

	return feed;
  }

  [WebMethod]
  [XmlInclude(typeof(Chan))]
  public Chan updateChan(string uid, Chan oldChan)
  {
	UserManager.Instance.validate(uid);

	//////////////////////////////////////////////////////////////////////////

	ITransaction tx = null;

	BaseDataAccess mgr = new BaseDataAccess();
	Chan chan = null;

	try
	{
	  tx = NHibernateHttpModule.CurrentSession.BeginTransaction();

	  chan = mgr.Get(typeof(Chan), oldChan.Id) as Chan;

	  if (chan == null)
		return null;

	  Importer.updateChan(chan);

	  tx.Commit();
	}
	catch (Exception ex)
	{
	  if (tx != null)
		tx.Rollback();

	  throw ex;
	}

	return chan;
  }

  [WebMethod]
  [XmlInclude(typeof(Chan))]
  public Item updateItem(string uid, Item oldItem)
  {
	UserManager.Instance.validate(uid);

	//////////////////////////////////////////////////////////////////////////

	ITransaction tx = null;

	BaseDataAccess mgr = new BaseDataAccess();
	Item item = null;

	try
	{
	  tx = NHibernateHttpModule.CurrentSession.BeginTransaction();

	  item = mgr.Get(typeof(Item), oldItem.Id) as Item;

	  if (item == null)
		return null;

	  Importer.updateItem(item);

	  tx.Commit();
	}
	catch (Exception ex)
	{
	  if (tx != null)
		tx.Rollback();

	  throw ex;
	}

	return item;
  }
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

	ITransaction tx = null;

	BaseDataAccess mgr = new BaseDataAccess();

	try
	{
	  tx = NHibernateHttpModule.CurrentSession.BeginTransaction();

	  Dictionary<string, Feed> feedMap = new Dictionary<string, Feed>();

	  foreach (Feed feed in feeds)
		feedMap[feed.Fils] = feed;

	  User user = UserManager.Instance.getUser(uid);

	  foreach (Feed feed in mgr.Get(typeof(Feed)))
	  {
		feed.Selected = feedMap[feed.Fils].Selected;

		if (feed.Selected)
		{
		  if (feed.Users == null)
			feed.Users = new ArrayList();
		  if (!feed.Users.Contains(user))
			feed.Users.Add(user);
		}
		else if (feed.Users != null && feed.Users.Contains(user))
		{
		  feed.Users.Remove(user);
		}

		mgr.Save(feed);
	  }

	  tx.Commit();
	}
	catch (Exception ex)
	{
	  if (tx != null)
		tx.Rollback();

	  throw ex;
	}
  }

  [WebMethod]
  public void subscribe(string uid, Feed modifiedFeed)
  {
	UserManager.Instance.validate(uid);

	//////////////////////////////////////////////////////////////////////////

	ITransaction tx = null;

	BaseDataAccess mgr = new BaseDataAccess();
	Feed feed = null;

	try
	{
	  tx = NHibernateHttpModule.CurrentSession.BeginTransaction();

	  feed = mgr.Get(typeof(Feed), modifiedFeed.Id) as Feed;
	  User user = UserManager.Instance.getUser(uid);

	  if (feed == null)
		return;

	  if (modifiedFeed.Selected)
	  {
		if (feed.Users == null)
		  feed.Users = new ArrayList();
		if (!feed.Users.Contains(user))
		  feed.Users.Add(user);
	  }
	  else if (feed.Users != null && feed.Users.Contains(user))
	  {
		feed.Users.Remove(user);
	  }

	  tx.Commit();
	}
	catch (Exception ex)
	{
	  if (tx != null)
		tx.Rollback();

	  throw ex;
	}

	if (feed != null)
	  mgr.Save(feed);
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