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

  bool	validate(string validationString)
  {
	return false;
  }

  string validate(string user, string pass)
  {
	return null;
  }

  void activate(string hash)
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
