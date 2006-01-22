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

  protected void Page_Load(object sender, EventArgs e)
  {
	qs = Request.QueryString;
	signout = (qs["signout"] != "" ? Convert.ToBoolean(qs["signout"]) : false);

	if (signout)
	  Signout();
  }
  
  private void Signout()
  {
	FormsAuthentication.SignOut();
	Response.Redirect("login.aspx");
  }

  protected void Login_Click(Object sender, EventArgs E) 
  {
	// authenticate user: this samples accepts only one user with
    // a name of kkt and a password of 'koin'
    if ((UserEmail.Value == "kkt") && (UserPass.Value == "koin")) 
	{
	  FormsAuthentication.RedirectFromLoginPage(UserEmail.Value, PersistCookie.Checked);
    } 
	else 
	{
	  Msg.Text = "Invalid Credentials: Please try again";
    }
  }

  protected void Login_Register(Object sender, EventArgs E)
  {
	// authenticate user: this samples accepts only one user with
	// a name of kkt and a password of 'koin'
	if ((UserEmail.Value == "kkt") && (UserPass.Value == "koin"))
	{
	  FormsAuthentication.RedirectFromLoginPage(UserEmail.Value, PersistCookie.Checked);
	}
	else
	{
	  Msg.Text = "Invalid Credentials: Please try again";
	}
  }

  protected void Signout_Click(Object sender, EventArgs E)
  {
	Signout();
  }

}
