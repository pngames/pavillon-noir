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
using KKTRSS_server;

public partial class Admin : System.Web.UI.Page
{
    private static string _sessionID = "";
    private static KKTRSS_server.Service _mainServer = new KKTRSS_server.Service();
    private static IList _groupList = null;
    private static IList _rssFeedInGroup = null;
    private static IList _AccountInGroup = null;
  


    protected void Page_Load(object sender, EventArgs e)
    {
        if (Page.IsPostBack == false)
        {
            _sessionID = _mainServer.Login("default", "kkt");
            _groupList = _mainServer.GetGroupList(_sessionID);
            foreach (Group item in _groupList)
            {
                ListItem listItem = new ListItem(item.Name, Convert.ToString(item.Id));
                group_ListBox.Items.Add(listItem);
            }

            IList _rssFeedGlobal = _mainServer.ListAvailableRssFeedsInGroup(_sessionID, ((Group)_groupList[0]).Id);
            foreach (RssFeedRef feed in _rssFeedGlobal)
            {
                ListItem listItem = new ListItem(feed.Name, Convert.ToString(feed.Id));
                globalFlux_ListBox.Items.Add(listItem);
            }

            IList _accountGlobal = _mainServer.ListAccountInGroup(_sessionID, ((Group)_groupList[0]).Id);
            foreach (Account acc in _accountGlobal)
            {
                ListItem listItem = new ListItem(acc.Email, Convert.ToString(acc.Id));
                globalUser_ListBox.Items.Add(listItem);
            }

        }
     
    }


    protected void refreshALL()
    {
        group_ListBox.Items.Clear();
        user_ListBox.Items.Clear();
        flux_ListBox.Items.Clear();
        globalFlux_ListBox.Items.Clear();
        globalUser_ListBox.Items.Clear();
        gpgeName_TextBox.Text = "";
        globalLogin_TextBox.Text = "";
        globalPass_TextBox.Text = "";
        globalUrl_TextBox.Text = "";
        globalName_TextBox.Text = "";

        _groupList = _mainServer.GetGroupList(_sessionID);
        if (_groupList != null)
        {
            foreach (Group item in _groupList)
            {
                ListItem listItem = new ListItem(item.Name, Convert.ToString(item.Id));
                group_ListBox.Items.Add(listItem);
            }
            IList _rssFeedGlobal = _mainServer.ListAvailableRssFeeds(_sessionID);
            if (_rssFeedGlobal != null)
                foreach (RssFeedRef feed in _rssFeedGlobal)
                {
                    ListItem listItem = new ListItem(feed.Name, Convert.ToString(feed.Id));
                    globalFlux_ListBox.Items.Add(listItem);
                }

            IList _accountGlobal = _mainServer.ListAccountInGroup(_sessionID, ((Group)_groupList[0]).Id);
            if (_accountGlobal != null)
                foreach (Account acc in _accountGlobal)
                {
                    ListItem listItem = new ListItem(acc.Email, Convert.ToString(acc.Id));
                    globalUser_ListBox.Items.Add(listItem);
                }
        }
       
    }

    protected void addGpe_Button_Click(object sender, EventArgs e)
    {
        if (gpgeName_TextBox.Text != "")
        {
            _mainServer.AddGroup(_sessionID, gpgeName_TextBox.Text, false);
            refreshALL();
        }
    }

    protected void delGpe_Button_Click(object sender, EventArgs e)
    {
        //faire gaffe ici
        if (group_ListBox.SelectedItem.Selected == true && group_ListBox.SelectedItem.Text != "default")
        {
            _mainServer.DelGroup(_sessionID, Convert.ToInt32(group_ListBox.SelectedItem.Value));
            refreshALL();
        }
    }

    protected void addUser_Button_Click(object sender, EventArgs e)
    {
        if (group_ListBox.SelectedItem.Selected == true && globalUser_ListBox.SelectedItem.Selected == true &&
            group_ListBox.SelectedItem.Text != "default" && globalUser_ListBox.SelectedItem.Text != "default")
        {
            _mainServer.AddAccountToGroup(_sessionID, Convert.ToInt32(group_ListBox.SelectedItem.Value), Convert.ToInt32(globalUser_ListBox.SelectedItem.Value));
            refreshALL();
        }
    }

    protected void delUser_Button_Click(object sender, EventArgs e)
    {
        //faire gaffe ici
        if (user_ListBox.SelectedItem.Selected == true && group_ListBox.SelectedItem.Selected == true && user_ListBox.SelectedItem.Text != "default")
        {
            _mainServer.DelAccountFromGroup(_sessionID, Convert.ToInt32(group_ListBox.SelectedItem.Value), Convert.ToInt32(user_ListBox.SelectedItem.Value));
            refreshALL();
        }
    }

    protected void addFlux_Button_Click(object sender, EventArgs e)
    {
        if (group_ListBox.SelectedItem.Selected == true && globalFlux_ListBox.SelectedItem.Selected == true)
        {
            IList tmp = _mainServer.ListAvailableRssFeeds(_sessionID);
            foreach(RssFeedRef feed in tmp)
            {
                if (feed.Id == Convert.ToInt32(globalFlux_ListBox.SelectedItem.Value))
                {
                    _mainServer.ImportRssFeed(_sessionID, feed.Url, feed.Name, group_ListBox.SelectedItem.Value, false);
                    refreshALL();
                }
            }
        }
    }
    protected void fluxDel_Button_Click(object sender, EventArgs e)
    {
        //////////////////////////////////////////////////////////////////////////
        //TODO
/*        if (flux_ListBox.SelectedItem.Selected == true && group_ListBox.SelectedItem.Selected == true && flux_ListBox.SelectedItem.Text != "default")
        {
            _mainServer.de (_sessionID, Convert.ToInt32(group_ListBox.SelectedItem.Value), Convert.ToInt32(user_ListBox.SelectedItem.Value));
            refreshALL();
        }*/
    }

    protected void globalAddFlux_Button_Click(object sender, EventArgs e)
    {
        if (globalUrl_TextBox.Text != "" && globalName_TextBox.Text != "")
        {
            _mainServer.ImportRssFeed(_sessionID, globalUrl_TextBox.Text, globalName_TextBox.Text, "", false);
            refreshALL();
        }
    }
    protected void globalAddAcount_Button_Click(object sender, EventArgs e)
    {
        if (globalLogin_TextBox.Text != "" && globalPass_TextBox.Text != "")
        {
            _mainServer.Register(globalLogin_TextBox.Text, globalPass_TextBox.Text);
            refreshALL();
        }
    }
    protected void group_ListBox_SelectedIndexChanged(object sender, EventArgs e)
    {
        if (group_ListBox.SelectedItem.Selected == true)
        {
            _rssFeedInGroup = _mainServer.ListAvailableRssFeedsInGroup(_sessionID, Convert.ToInt32(group_ListBox.SelectedItem.Value));
            _AccountInGroup = _mainServer.ListAccountInGroup(_sessionID, Convert.ToInt32(group_ListBox.SelectedItem.Value));
            if (_rssFeedInGroup != null)
            {
                flux_ListBox.Items.Clear();
                foreach (RssFeedRef item in _rssFeedInGroup)
                {
                    ListItem listItem = new ListItem(item.Name, Convert.ToString(item.Id));
                    flux_ListBox.Items.Add(listItem);
                }
            }
            if (_AccountInGroup != null)
            {
                user_ListBox.Items.Clear();
                foreach (Account item in _AccountInGroup)
                {
                    ListItem listItem = new ListItem(item.Email, Convert.ToString(item.Id));
                    user_ListBox.Items.Add(listItem);
                }
            }
        }
    }
 
}
