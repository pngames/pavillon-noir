using System;
using System.Data;
using System.Configuration;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;

public partial class _Default : System.Web.UI.Page 
{
  protected System.Collections.Specialized.NameValueCollection qs;

  protected void Page_Load(object sender, EventArgs e)
  {
    qs = Request.QueryString;
  }

  protected void Signout_Click(Object sender, EventArgs E)
  {
	FormsAuthentication.SignOut();
	Response.Redirect("login.aspx");
  }

}
