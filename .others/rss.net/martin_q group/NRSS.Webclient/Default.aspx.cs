using System;
using System.Data;
using System.Configuration;
using System.Web;
using System.Text;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using NRSSService;

public partial class _Default : System.Web.UI.Page 
{
    NRSSService.Service NRSSS;

    protected void Page_Load(object sender, EventArgs e)
    {
        NRSSS = new NRSSService.Service();
    }

    protected void Login_Click(Object sender, EventArgs E)
    {
        try {
            NRSSS.logon(UserEmail.Value, UserPass.Value);
            Session.Add("UserEmail", UserEmail.Value);
            FormsAuthentication.RedirectFromLoginPage(UserEmail.Value, PersistCookie.Checked);
        }
        catch (System.Exception)
        {
            Msg.Text = "Echec de l'authentification";
        }
    }
}
