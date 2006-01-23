using System;
using System.Data;
using System.Configuration;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using NRSS.Server.DataAccess;
using NRSS.mapping;
using NRSS.errors;
using System.Collections;

/// <summary>Summary description for UserManager</summary>
public class UserManager
{
  #region singleton
  private static UserManager _instance = null;

  public static UserManager Instance
  {
	get
	{
	  if (UserManager._instance == null)
		UserManager._instance = new UserManager();

	  return UserManager._instance;
	}

	set { UserManager._instance = value; }
  }

  private UserManager()
  {

  }
  #endregion

  public string createUser(User user)
  {
	BaseDataAccess mgr = new BaseDataAccess();

	if (mgr.Get(typeof(User), "Email", user.Email) != null)
	  throw new NRSSException("L'utilisateur existe deja !");

	//////////////////////////////////////////////////////////////////////////

	user.AutoLog = Guid.NewGuid().ToString();
	mgr.Save(user);

	//////////////////////////////////////////////////////////////////////////

	//envoyer un mail

	return user.AutoLog;
  }

  public User logon(string email, string pass)
  {
	BaseDataAccess mgr = new BaseDataAccess();

	User user = mgr.Get(typeof(User), "Email", email, "Passwd", pass) as User;

	if (user == null)
	  throw new NRSSException("L'email ou le mot de passe n'existe pas !");

	if (!user.Confirmed)
	  throw new NRSSException("Le compte n'a pas ete active !");

	return user;
  }

  public void activate(string hash)
  {
	BaseDataAccess mgr = new BaseDataAccess();

	User user = mgr.Get(typeof(User), "AutoLog", hash) as User;

	//////////////////////////////////////////////////////////////////////////

	if (user == null)
	  throw new NRSSException("La chaine ne correspond a aucun utilisateur");

	//////////////////////////////////////////////////////////////////////////

	if (user.Confirmed)
	  throw new NRSSException("La compte utilisateur est deja valide");

	user.Confirmed = true;

	mgr.Save(user);
  }

  public void validate(string hash)
  {
	BaseDataAccess mgr = new BaseDataAccess();

	User user = mgr.Get(typeof(User), "Id", new Guid(hash)) as User;

	if (user == null)
	  throw new NRSSException("La validation de la chaine de connection automatique a echouee");
  }

  public User getUser(string hash)
  {
	BaseDataAccess mgr = new BaseDataAccess();

	return mgr.Get(typeof(User), "Id", new Guid(hash)) as User;
  }
}