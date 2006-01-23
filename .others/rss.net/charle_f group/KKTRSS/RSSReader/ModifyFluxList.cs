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
    

        public RSSReaderMain FormParent
        {
            get { return frmParent; }
            set { frmParent = value; }
        }

        public ModifyFluxList()
        {
        

            InitializeComponent();
          
        }

        private void ModifyFluxList_Load(object sender, EventArgs e)
        {
            IList AllFeedsList = frmParent.MainWebService.ListAvailableRssFeeds(frmParent.SessionID);
            IList SuscribeFeedsList = frmParent.MainWebService.ListSubscribedRssFeeds(frmParent.SessionID);

            foreach (RssFeedRef test in AllFeedsList)
            {
                
                flux_listView.Items.Add(test.Name);
            }
       
        }

        private void refreshLists()
        {
       
        }

   

        private void valid_button_Click(object sender, EventArgs e)
        {
            //frmParent.MainWebService.RssFeedSubscribe(frmParent.SessionID);
            
        }

      
    }
}