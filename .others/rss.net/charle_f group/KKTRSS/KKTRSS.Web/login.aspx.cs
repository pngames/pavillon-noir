using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;

public partial class login : System.Web.UI.Page
{
  
  protected System.Collections.Specialized.NameValueCollection qs;
  protected Boolean signout = false;
  protected kktserver.Service service = new kktserver.Service();
  protected string uid = null;

  protected void Page_Load(object sender, EventArgs e)
  {
	qs = Request.QueryString;
	signout = (qs["signout"] != "" ? Convert.ToBoolean(qs["signout"]) : false);

	if (signout)
	  Signout();
  }
  
  private void Signin(string uid)
  {
	if (uid != "")
	  FormsAuthentication.RedirectFromLoginPage(UserEmail.Value, PersistCookie.Checked);
	else
	  Msg.Text = "Invalid Identifiers: Please try again";
  }
  
  private void Signout()
  {
	FormsAuthentication.SignOut();
	Response.Redirect("login.aspx");
  }

  protected void Login_Click(Object sender, EventArgs E) 
  {
	uid = service.Login(UserEmail.Value, UserPass.Value);
	Signin(uid);
  }

  protected void Login_Register(Object sender, EventArgs E)
  {
	uid = service.Register(UserEmail.Value, UserPass.Value);
	Signin(uid);
  }

  protected void Signout_Click(Object sender, EventArgs E)
  {
	Signout();
  }

}
