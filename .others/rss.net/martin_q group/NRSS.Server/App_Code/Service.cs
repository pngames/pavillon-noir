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
  
  [WebMethod]
  public string HelloWorld()
  {
	SchemaUtility.ExportSchema();

	/*BaseDataAccess mgr = new BaseDataAccess();

	DBUser user = new DBUser();
	user.Id = "joe_cool";
	user.UserName = "Joseph Cool";
	user.Password = "abc123";
	user.EmailAddress = "joe@cool.com";
	user.LastLogon = DateTime.Now;

	try
	{
	  mgr.Save(user);
	}
	catch (Exception)
	{

	  //throw;
	}

	/*foreach (DBUser user in mgr.Get(typeof(DBUser)))
	{
	  
	}*/

	return "Hello World";
  }

  [WebMethod]
  public void TestRSS()
  {
	SchemaUtility.ExportSchema();

	//////////////////////////////////////////////////////////////////////////
	
	RSSImporter	importer = new RSSImporter();

	Feed  feed = new Feed();

	feed.Type = "rss";
	feed.Fils = "http://www.lemonde.fr/rss/sequence/0,2-3208,1-0,0.xml";

	//////////////////////////////////////////////////////////////////////////
	
	Importer.updateFeed(feed);

	//////////////////////////////////////////////////////////////////////////

	BaseDataAccess mgr = new BaseDataAccess();
	mgr.Save(feed);
  }

  [WebMethod]
  public User testSerializationUser()
  {
	User toto = new User();

	toto.Groups = new ArrayList();

	toto.Groups.Add(15);

	return toto;
  }

  //////////////////////////////////////////////////////////////////////////



  //////////////////////////////////////////////////////////////////////////

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

  [WebMethod]
  public ArrayList createUser(User user)
  {
	user.Id = Guid.NewGuid();

	//////////////////////////////////////////////////////////////////////////

	BaseDataAccess mgr = new BaseDataAccess();
	mgr.Save(user);

	//////////////////////////////////////////////////////////////////////////
	
	//envoyer un mail

	return new ArrayList();
  }

  [WebMethod]
  public void validateUser(string hash)
  {
	BaseDataAccess mgr = new BaseDataAccess();

	User user = mgr.Get(typeof(User), "Id", new Guid(hash)) as User;

	//////////////////////////////////////////////////////////////////////////

	if (user == null)
	  throw new NRSSException("La chaine ne correspond a aucun utilisateur");

	//////////////////////////////////////////////////////////////////////////

	if (user.Confirmed)
	  throw new NRSSException("La compte utilisateur est deja valide");

	user.Confirmed = true;

	mgr.Save(user);
  }
}