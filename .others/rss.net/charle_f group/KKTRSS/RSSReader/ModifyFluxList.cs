using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Collections;
using Rss;
using RSSReader.KKTRSS_service;


namespace RSSReader
{
    public partial class ModifyFluxList : Form
    {
        private RSSReaderMain frmParent;
        private IList _SuscribeFeedsList;

        public RSSReaderMain FormParent
        {
            get { return frmParent; }
            set { frmParent = value; }
        }

        public ModifyFluxList()
        {
            InitializeComponent();
        }

        private bool isInSuscribeList(RssFeedRef feedRef)
        {
            foreach (RssFeedRef feeds in _SuscribeFeedsList)
            {
                if (feedRef.Id == feeds.Id)
                    return true;
            }
            return false;
        }

        private void ModifyFluxList_Load(object sender, EventArgs e)
        {
            updateFluxList();
        }

        public void updateFluxList()
        {
            flux_listView.Items.Clear();
            IList AllFeedsList = frmParent.MainWebService.ListAvailableRssFeeds(frmParent.SessionID);
            _SuscribeFeedsList = frmParent.MainWebService.ListSubscribedRssFeeds(frmParent.SessionID);

            foreach (RssFeedRef feedRef in AllFeedsList)
            {
                ListViewItem item = new ListViewItem(feedRef.Name);
                item.Tag = feedRef;
                if (isInSuscribeList(feedRef) == true)
                    item.Checked = true;
                flux_listView.Items.Add(item);
            }
        }


        private void valid_button_Click(object sender, EventArgs e)
        {
            foreach (ListViewItem item in flux_listView.Items)
            {
                if (item.Checked == true && isInSuscribeList((RssFeedRef)item.Tag) == false)
                {
                    frmParent.MainWebService.RssFeedSubscribe(frmParent.SessionID, ((RssFeedRef)item.Tag).Id);
                }
            }
           /* foreach (ListViewItem item in flux_listView.Items)
            {
                if (item.Checked == false && isInSuscribeList((RssFeedRef)item.Tag) == true)
                {
                    frmParent.MainWebService.RssFeedUnSubscribe(frmParent.SessionID, ((RssFeedRef)item.Tag).Id);
                }
            }*/
            
            this.Close();
        }

        private void addFlux_button_Click(object sender, EventArgs e)
        {
            AddFlux addFluxWin = new AddFlux();
            addFluxWin.FormParent = this;
            addFluxWin.ShowDialog();
        }

      
    }
}