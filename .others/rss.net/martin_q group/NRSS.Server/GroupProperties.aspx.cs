using System;
using System.Collections;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Web;
using System.Web.Mobile;
using System.Web.SessionState;
using System.Web.UI;
using System.Web.UI.MobileControls;
using System.Web.UI.WebControls;
using System.Web.UI.HtmlControls;
using NRSS.Server.DataAccess;
using NRSS.mapping;

public partial class _GroupProperties : System.Web.UI.Page
{
  private Group group;
  protected void Page_Load(object sender, EventArgs e)
  {
    if (!Page.IsPostBack)
    {
      
      BaseDataAccess bda = new BaseDataAccess();
      string groupName = Request.Params["group"].Substring(0, Request.Params["group"].Length - 1);
      group = bda.Get(typeof(Group), "Name", groupName) as Group;
      IList userList = bda.Get(typeof(User));
      foreach (User u in userList)
      {
        //foreach (Attribute att in UserList.SelectedItem.Attributes)
          //Response.Write(att.GetType());
        UserList.Items.Add(u.Email);
      }
    }
  }
}
