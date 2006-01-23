using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using NRSS.Winformclient.NRSSServer;
using winformclient;

namespace NRSS.Winformclient
{
    public partial class Subscribe : Form
    {
        NRSS.Winformclient.NRSSServer.Service serviceAdd = new NRSS.Winformclient.NRSSServer.Service();

        public Subscribe()
        {
            InitializeComponent();

            Feed[] feedslist = serviceAdd.getAllFeeds(Form1.uid);

            for (int i = 0; i != feedslist.Length; i++)
            {
                FeedContainer myFeedContainer = new FeedContainer(feedslist[i]);
                checkedListBox1.Items.Add(myFeedContainer, !feedslist[i].Selected ? CheckState.Unchecked : CheckState.Checked);
            }

            //checkedListBox1.Items.Add("Rss feed " + i.ToString(), CheckState.Unchecked);
        }

        private void checkedListBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            //checkedListBox1.CheckedItems.Count;
        }

        private void checkedListBox1_ItemCheck(object sender, ItemCheckEventArgs e)
        {
            FeedContainer tmpFeed = checkedListBox1.Items[e.Index] as FeedContainer;
            if (tmpFeed.MyFeed != null)
            {
                tmpFeed.MyFeed.Selected = e.NewValue == CheckState.Checked;
                serviceAdd.subscribe(Form1.uid, tmpFeed.MyFeed);
            }
        }
    }
    public class FeedContainer
    {
        private Feed myFeed;

        public Feed MyFeed
        {
            get { return myFeed; }
        }

        public FeedContainer(Feed newFeed)
        {
            myFeed = newFeed;
        }

        public override string ToString()
        {
            return myFeed.Fils;
        }
    }
}