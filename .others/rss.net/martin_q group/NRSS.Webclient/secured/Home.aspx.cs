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
using NRSS.mapping;
using System.Collections.Generic;
using Iesi.Collections;


public partial class Home : System.Web.UI.Page
{
    public Feed _feed;

    protected void Page_Load(object sender, EventArgs e)
    {
        _feed = new Feed();
        _feed.Name = "le nom de mon feed";
        _feed.Chans = new HashedSet();
        _feed.Chans.Clear();

        // premier chan

        Chan chan = new Chan();
        chan.Feed = _feed;

        chan.Title = "my test chan title";
        chan.Description = "my test description";

        chan.Items = new HashedSet();
        chan.Items.Clear();

        Item item = new Item();
        item.Chan = chan;
        item.Author = "auteur";
        item.Date = new DateTime();
        item.Title = "titre de l'item";
        item.Description = "description de l'item";
        item.Link = new Uri("http://perdu.com");
        chan.Items.Add(item);

        Item item1 = new Item();
        item1.Chan = chan;
        item1.Author = "auteur1";
        item1.Date = new DateTime();
        item1.Title = "titre de l'item1";
        item1.Description = "description de l'item1";
        item1.Link = new Uri("http://perdu.com");
        chan.Items.Add(item1);

        _feed.Chans.Add(chan);

        // deuxieme chan

        chan = new Chan();
        chan.Feed = _feed;

        chan.Title = "my test chan title";
        chan.Description = "my test description";

        chan.Items = new HashedSet();
        chan.Items.Clear();

        item = new Item();
        item.Chan = chan;
        item.Author = "auteur";
        item.Date = new DateTime();
        item.Title = "titre de l'item";
        item.Description = "description de l'item";
        item.Link = new Uri("http://perdu.com");
        chan.Items.Add(item);

        item1 = new Item();
        item1.Chan = chan;
        item1.Author = "auteur1";
        item1.Date = new DateTime();
        item1.Title = "titre de l'item1";
        item1.Description = "description de l'item1";
        item1.Link = new Uri("http://perdu.com");
        chan.Items.Add(item1);

        _feed.Chans.Add(chan);




        doItemTree();
    }

    protected void doItemTree()
    {
        foreach (NRSS.mapping.Chan chan in this._feed.Chans)
        {
            TreeNode x = new TreeNode();
            x = new TreeNode();
            x.Text = chan.Title;
            ItemTree.Nodes.AddAt(0, x);
            /*foreach (NRSS.mapping.Item item in chan.Items)
            {
                TreeNode xx;
                xx = new TreeNode();
                xx.Text = item.Title;
                xx.NavigateUrl = "http://www.eggheadcafe.com/";
                ItemTree.Nodes[0].Nodes.Add(xx);
            }*/
        }
    }

}
