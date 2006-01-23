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
using System.Collections.Generic;
using NRSSService;


public partial class Home : System.Web.UI.Page
{
    /*public Feed _feed;*/
    NRSSService.Service NRSSS;
    public Feed rssFeed;

    protected void Page_Load(object sender, EventArgs e)
    {
        NRSSS = new NRSSService.Service();
        rssFeed = NRSSS.testRSS();

        doItemTree();
    }
   
    protected void doItemTree()
    {
        int i = 0;
        foreach (Chan chan in rssFeed.Chans)
        {
            TreeNode x = new TreeNode();
            x = new TreeNode();
            x.Text = chan.Title;
            ItemTree.Nodes.AddAt(0, x);
            foreach (Item item in chan.Items)
            {
                TreeNode xx = new TreeNode();
                xx.Text = item.Title;
                xx.NavigateUrl = "javascript:toggleItem('item" + i.ToString() + "');";
                x.ChildNodes.Add(xx);
                i++;
            }
        }
    }

}
