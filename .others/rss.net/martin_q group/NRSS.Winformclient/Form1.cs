using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Iesi.Collections;
using SpeechLib;
using System.Collections;
using System.Web.Services;
using System.Web.Services.Protocols;
using System.Security.Cryptography.X509Certificates;
using System.Net;
using NRSS.Winformclient.NRSSServer;
using NRSS.Winformclient;

namespace winformclient
{
    public partial class Form1 : Form
    {
        #region Voice
        bool voice_flag = false;
        string cur_speech;
        SpVoice voice = new SpVoice();

        #endregion

        // Instanciation de la classe permettant l'appel distant au Webservice
        NRSS.Winformclient.NRSSServer.Service serviceAdd = new NRSS.Winformclient.NRSSServer.Service();

        public Form1()
        {
            InitializeComponent();
        }

        #region Web Browser related code

        private void Navigate(String address)
        {
            this.webBrowser1.AllowNavigation = true;
            if (String.IsNullOrEmpty(address)) return;
            if (address.Equals("about:blank")) return;
            if (!address.StartsWith("http://") &&
                !address.StartsWith("https://"))
            {
                address = "http://" + address;
            }
            try
            {
                webBrowser1.Navigate(new Uri(address));
            }
            catch (System.UriFormatException)
            {
                return;
            }
        }

        // Web browser navigated event
        private void webBrowser1_Navigated(object sender,
             WebBrowserNavigatedEventArgs e)
        {
            // Locks navigation
            this.webBrowser1.AllowNavigation = false;
        }

        #endregion

        #region Left menu
        private void LeftTreeMenu_AfterSelect(object sender, TreeViewEventArgs e)
        {
            string author;
            string title;
            string description;
            string date;
            string link;

            // Load RSS feed
            Feed rssFeed;
            rssFeed = serviceAdd.testRSS();
            LeftTreeMenu.Nodes[0].Nodes[0].Text = rssFeed.Name;

            if (rssFeed.Chans == null)
                return;
            RightListView.Items.Clear();
            foreach (Chan chan in rssFeed.Chans)
            {
                foreach (Item item in chan.Items)
                {
                    title = item.Title;
                    author = item.Author;// item.Author;
                    date = item.Date.ToShortDateString() + " " + item.Date.ToShortTimeString();
                    description = item.Description;
                    link = item.Link;
                    
                    if (author.Length == 0)
                    {
                        author = chan.Title + " " + chan.Language; 
                    }
                    System.Windows.Forms.ListViewItem listViewItem1 = new System.Windows.Forms.ListViewItem(new string[] {
                        author,
                        title,
                        date,
                        description,
                        link}, -1);

                    listViewItem1.Font = new Font(listViewItem1.Font, listViewItem1.Font.Style | FontStyle.Bold);

                    this.RightListView.Items.AddRange(new System.Windows.Forms.ListViewItem[] {
                        listViewItem1});
                }
            }
        }

        private void RightListView_SelectedIndexChanged(object sender, EventArgs e)
        {

            foreach ( ListViewItem item in  RightListView.SelectedItems )
            {
                labelTitleContent.Text = item.SubItems[1].Text;
                linkLabel.Text = item.SubItems[4].Text;
                labelDateContent.Text = item.SubItems[2].Text;
                labelFromContent.Text = item.SubItems[0].Text;

                item.Font = new Font(item.Font, FontStyle.Regular);
                item.EnsureVisible();
                Navigate(item.SubItems[4].Text);
                ////////////////////////////////////////////////////////////////////////////
                //// Voice 
                cur_speech = item.SubItems[3].Text;
                voice.Speak(cur_speech,
                    SpeechVoiceSpeakFlags.SVSFlagsAsync | SpeechVoiceSpeakFlags.SVSFPurgeBeforeSpeak);
                ////////////////////////////////////////////////////////////////////////////
            }
        }

        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            if (voice_flag == true)
            {
                voice.Volume = 0;
                voice_flag = false;
            }
            else
            {
                voice.Volume = 100;
                voice_flag = true;
                voice.Speak(cur_speech,
                        SpeechVoiceSpeakFlags.SVSFlagsAsync | SpeechVoiceSpeakFlags.SVSFPurgeBeforeSpeak);
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            UserLogin Userbox = new UserLogin();

            // French voice init
            voice.Voice = voice.GetVoices("Name=LH Pierre", "Language=40C").Item(0);
            voice.Volume = 0;

            if (Userbox.ShowDialog() == DialogResult.Cancel)
                Close();   
        }

        private void quitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }

        #endregion
}