using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using NRSS.Winformclient.NRSSServer;

namespace NRSS.Winformclient
{
    public partial class Subscribe : Form
    {
        NRSS.Winformclient.NRSSServer.Service serviceAdd = new NRSS.Winformclient.NRSSServer.Service();

        public Subscribe()
        {
            InitializeComponent();
            
            Feed[] feedslist = serviceAdd.getFeeds("9cc48a6f-8aeb-4d1e-9f15-da11d9bf14c7");

            for (int i = 0; i != feedslist.Length; i++ )
            {
                checkedListBox1.Items.Add(feedslist[i].Fils, CheckState.Unchecked);
            }

            //checkedListBox1.Items.Add("Rss feed " + i.ToString(), CheckState.Unchecked);
        }

        private void checkedListBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            //checkedListBox1.CheckedItems.Count;
        }
    }
}