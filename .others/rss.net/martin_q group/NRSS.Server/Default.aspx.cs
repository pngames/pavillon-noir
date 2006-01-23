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
using NRSS.Server.DataAccess;
using NRSS.mapping;

public partial class _Default : System.Web.UI.Page
{
  protected void Page_Load(object sender, EventArgs e)
  {
    if (!Page.IsPostBack)
    {
      NRSS.Server.DataAccess.BaseDataAccess db = new NRSS.Server.DataAccess.BaseDataAccess();
      foreach (NRSS.mapping.Group g in db.Get(typeof(NRSS.mapping.Group)))
        ListBox1.Items.Add(g.Name);
      ListBox1.SelectedIndex = 0;
    }
  }

  protected void AddNewGroup(Object sender, EventArgs E)
  {
    BaseDataAccess BDA = new BaseDataAccess();
    bool already = false;

    IList groups = BDA.Get(typeof(Group));
    foreach (Group g in groups)
      if (g.Name == NewGroup.Value)
        already = true;
    if (!already)
    {
      Group group = new Group();
      group.Name = NewGroup.Value;
      BDA.Save(group);
      ListBox1.Items.Add(group.Name);
      ListBox1.SelectedIndex = 0;
    }
  }
  protected void GroupSuppr(object sender, EventArgs e)
  {
    BaseDataAccess BDA = new BaseDataAccess();
    foreach (Group g in BDA.Get(typeof(Group)))
      if (ListBox1.SelectedItem.Text == g.Name)
      {
        BDA.Delete(g);
        ListBox1.Items.Clear();
        NRSS.Server.DataAccess.BaseDataAccess db = new NRSS.Server.DataAccess.BaseDataAccess();
        foreach (NRSS.mapping.Group gg in db.Get(typeof(NRSS.mapping.Group)))
          ListBox1.Items.Add(gg.Name);
        if (ListBox1.Items.Count > 0)
          ListBox1.SelectedIndex = 0;
        break;
      }
  }
}
