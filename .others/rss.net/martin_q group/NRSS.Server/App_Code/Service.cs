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
  public string testCreateUser()
  {
	User user = new User();

	user.Email = "ttttt";
	user.Passwd = "ppppp";

	return createUser(user);
  }

  [WebMethod]
  public void testAbonnement()
  {
	
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
  public string createUser(User user)
  {
	return UserManager.Instance.createUser(user);
  }

  [WebMethod]
  public void validateUser(string hash)
  {
	UserManager.Instance.activate(hash);
  }

  [WebMethod]
  public User logon(string user, string pass)
  {
	return UserManager.Instance.logon(user, pass);
  }

  //////////////////////////////////////////////////////////////////////////

  [WebMethod]
  [XmlInclude(typeof(Chan)), XmlInclude(typeof(Item))]
  public List<Feed> getFeeds(string uid)
  {
	List<Feed> feeds = new List<Feed>();

	UserManager.Instance.validate(uid);

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
}