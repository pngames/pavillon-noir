using System;
using SpeechLib;
using System.Net;
using System.Configuration;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.Xml;
using Rss;


namespace RSSReader
{
    public partial class RSSReaderMain : Form
    {
        #region Private Var
       
    
        private Connexion connexionWin = new Connexion();
        private bool _isConnected = false;
        private SpVoice mainVoice = new SpVoice();

        public bool IsConnected
        {
            get { return _isConnected; }
            set { _isConnected = value; }
        }
     


        private string _fluxUrl = "http://bluegloup.free.fr/news.xml";

        private ListViewItem _lastSelectedFlux = null;
        private ListViewItem _lastSelectedNews = null;
     
        private RssFeed _rssFeed = new RssFeed();
        private List<fluxItem> _fluxList = new List<fluxItem>();
        private bool _isUpdating = false;
        private bool _readStop = false;
       
        #endregion


        public RSSReaderMain()
        {
           
            InitializeComponent();
            Properties.Settings.Default.Reset();
        }

        private void updateOptions()
        {
            useSystray();
            main_timer.Interval = Properties.Settings.Default.updateTime * 600 * 1000;
        }

        private void RSSReaderMain_Load(object sender, EventArgs e)
        {
            if (Properties.Settings.Default.rememberMe == true)
            {
                if (connectionToServer(Properties.Settings.Default.login, Properties.Settings.Default.pass) == false)
                {
                    connexionWin.FormParent = this;
                    connexionWin.ShowDialog();
                }
            }
            else
            {
                connexionWin.FormParent = this;
                connexionWin.ShowDialog();
            }
            updateOptions();
        }

        private void fillRSSFeed()
        {
            HttpWebRequest request = null;
            bool err = true;
            int tried = 0;

            while (err == true)
            {
                try
                {
                    request = (HttpWebRequest)WebRequest.Create(new Uri(_fluxUrl));
                    if (Properties.Settings.Default.useProxy == true)
                    {
                        WebProxy proxy = new WebProxy(Properties.Settings.Default.proxyUrl, Properties.Settings.Default.proxyPort);
                        proxy.Credentials = new NetworkCredential(Properties.Settings.Default.proxyLogin, Properties.Settings.Default.proxyPass);
                        request.Proxy = proxy;
                    }

                    _rssFeed = RssFeed.Read(request);
                    err = false;
                }
                catch (Exception ex)
                {
                    err = true;
                }
                if (tried > 10)
                    break;
                tried++;
            }

            if (err == true)
                 System.Windows.Forms.MessageBox.Show("Erreur dans la mise a jour des flux.", "RssReader", System.Windows.Forms.MessageBoxButtons.OK, System.Windows.Forms.MessageBoxIcon.Error);
        }

    
        private void RSSReaderMain_Shown(object sender, EventArgs e)
        {

        }

        public bool connectionToServer(string login, string mdp)
        {
            if ((login == "t" && mdp == "t") || (login == "a" && mdp == "a"))
            {
                _isConnected = true;
                Properties.Settings.Default.login = login;
                Properties.Settings.Default.pass = mdp;

                statusCnx_toolStripLabel.Text = Properties.Settings.Default.login;
                update_toolStripButton.Enabled = true;

                main_timer.Start();
                main_timer.Tick += new EventHandler(Timer_Tick);
                ListFluxToolStripMenuItem.Enabled = true;
                
                updateFluxList();
                return true;
            }
            else
            {
                return false;
            }
        }

        public void Timer_Tick(object sender, EventArgs eArgs)
        {
            if (sender == main_timer && _isConnected == true)
            {
                updateFluxList();
                if (_lastSelectedFlux != null)
                    updateNewsList(_lastSelectedFlux);

              //TODO : a appeler que si ya une nouvelle news
                useTooltipMSN();
               
            }
        }

        private string createFluxTooltip(RssChannel chan)
        {
            string text = "";

            if (chan.Title != "")
                text = "Nom du flux : " + System.Web.HttpUtility.HtmlDecode(chan.Title.ToString()) + "\n";
            if (chan.Description != "")
                text += "Description : " + System.Web.HttpUtility.HtmlDecode(chan.Description.ToString()) + "\n";

            if (chan.Generator != "")
                text += "Generateur : " + System.Web.HttpUtility.HtmlDecode(chan.Generator.ToString()) + "\n";
            if (chan.Language != "")
                text += "Langue : " + System.Web.HttpUtility.HtmlDecode(chan.Language.ToString()) + "\n";
            if (chan.Link.ToString() != "")
                text += "URL : " + chan.Link.ToString() + "\n";
            if (chan.ManagingEditor != "")
                text += "Mail : " + System.Web.HttpUtility.HtmlDecode(chan.ManagingEditor.ToString()) + "\n";
            if (chan.PubDate.ToString() != "")
                text += "Date : " + chan.PubDate.ToShortDateString() + "\n";
            if (chan.WebMaster != "")
                text += "Webmaster : " + System.Web.HttpUtility.HtmlDecode(chan.WebMaster.ToString()) + "\n";

            return text;
        }

        private void updateFluxList()
        {
            _isUpdating = true;
            Cursor.Current = Cursors.WaitCursor;
            status_label.Text = "Status : update...";
            fillRSSFeed();
            
             ListView.SelectedListViewItemCollection itemCol = flux_listView.SelectedItems;

             if (itemCol.Count == 1)
             {
                 _lastSelectedFlux = itemCol[0];
             }
           // news_listView.Items.Clear();
             flux_listView.Items.Clear();

            ListViewItem viewItem = null;
            foreach (RssChannel chan in _rssFeed.Channels)
            {
                viewItem = new ListViewItem();
                viewItem.ToolTipText = createFluxTooltip(chan);
                viewItem.Tag = chan;
                viewItem.Text = chan.Title.ToString();
                flux_listView.Items.Add(viewItem);

                if (chan.IsRead == true)
                    viewItem.Font = new Font("Microsoft Sans Serif", 8.25f, FontStyle.Regular);
                else
                    viewItem.Font = new Font("Microsoft Sans Serif", 8.25f, FontStyle.Bold);
            }
         //   flux_listView.Items[_lastSelectedFlux.Text].Selected = true;
            status_label.Text = "Status : en attente...";
            Cursor.Current = Cursors.Default;
            _isUpdating = false;
        }

        private void flux_listView_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (_isUpdating == false)
            {
                ListView.SelectedListViewItemCollection itemCol = flux_listView.SelectedItems;
                if (itemCol.Count == 1)
                {
                  
                    fluxRead_toolStripButton.Enabled = true;
                    updateNewsList((ListViewItem)itemCol[0]);
                }
                if (itemCol.Count > 1)
                {
                    news_listView.Items.Clear();
                    webBrowser1.Url = new Uri("about:blank");
                    newsSubject_label.Text = "";
                    newsDate_label.Text = "";
                    newsFrom_label.Text = "";
                    newsWebSite_linkLabel.Text = "";

                    vocalSynthNews_toolStripButton.Enabled = false;
               
                    newsRead_toolStripButton.Enabled = false;
                    fluxRead_toolStripButton.Enabled = true;
                }
                if (itemCol.Count == 0)
                {

                    news_listView.Items.Clear();
                    webBrowser1.Url = new Uri("about:blank");
                    newsSubject_label.Text = "";
                    newsDate_label.Text = "";
                    newsFrom_label.Text = "";
                    newsWebSite_linkLabel.Text = "";

                    vocalSynthNews_toolStripButton.Enabled = false;
                
                    newsRead_toolStripButton.Enabled = false;
                    fluxRead_toolStripButton.Enabled = false;
                }

                //ListViewItem listViewSel = flux_listView.SelectedNode;
                //_lastSelectedFlux = nodeSel;
                //updateNewsList(nodeSel);
            }
        }

        

        private void news_listView_Enter(object sender, EventArgs e)
        {
            
        }

        private void news_listView_Leave(object sender, EventArgs e)
        {
            
        }

        private void news_listView_SelectedIndexChanged(object sender, EventArgs e)
        {
            ListView.SelectedListViewItemCollection itemCol = news_listView.SelectedItems;

            if (itemCol.Count == 1)
            {
                RssItem itemSel = null;

                foreach (ListViewItem item in itemCol)
                {
                    itemSel = (RssItem)item.Tag;
                    _lastSelectedNews = item;

                    webBrowser1.Url = new Uri(itemSel.Link.ToString());
                    
                   
                    newsSubject_label.Text = itemSel.Title.ToString();
                    newsDate_label.Text = itemSel.PubDate.ToString();
                    newsFrom_label.Text = itemSel.Author.ToString();
                    newsWebSite_linkLabel.Text = itemSel.Link.ToString();
                    
                    item.Font = new Font("Microsoft Sans Serif", 8.25f, FontStyle.Regular);
                    itemSel.IsRead = true;
                }
                vocalSynthNews_toolStripButton.Enabled = true;
                newsRead_toolStripButton.Enabled = true;
            }
            if (itemCol.Count > 1)
            {
                webBrowser1.Url = new Uri("about:blank");
                newsSubject_label.Text = "";
                newsDate_label.Text = "";
                newsFrom_label.Text = "";
                newsWebSite_linkLabel.Text = "";
                vocalSynthNews_toolStripButton.Enabled = true;
                newsRead_toolStripButton.Enabled = true;

            }
            if (itemCol.Count == 0)
            {
                webBrowser1.Url = new Uri("about:blank");
                newsSubject_label.Text = "";
                newsDate_label.Text = "";
                newsFrom_label.Text = "";
                newsWebSite_linkLabel.Text = "";

                 vocalSynthNews_toolStripButton.Enabled = false;
                 newsRead_toolStripButton.Enabled = false;
            }

          /*  if (itemSel != null)
            {
                fluxItem flxItem = itemSel.parentFlux;
                bool allread = true;

                foreach (newsItem nwsItem in flxItem.newsList)
                {
                    if (nwsItem.isRead == false)
                        allread = false;
                }
                if (allread == true)
                {
                    flxItem.isRead = true;
                    flxItem.fluxTreeNode.NodeFont = new Font("Microsoft Sans Serif", 8.25f, FontStyle.Regular);
                }

                //TODO : Ameliorer le systeme de l'activation du bouton
                vocalSynth_toolStripButton.Enabled = true;
            }
            else
                vocalSynth_toolStripButton.Enabled = false;*/

        }

        private string createNewsTooltip(RssItem item)
        {
           
            string text = "";
            if (item.Title != "")
                text += "Titre : " + System.Web.HttpUtility.HtmlDecode(item.Title) + "\n";
            if (item.Author != "")
                text += "Auteur : " + System.Web.HttpUtility.HtmlDecode(item.Author) + "\n";
            if (item.Description != "")
                text += "Description : " + System.Web.HttpUtility.HtmlDecode(item.Description) + "\n";
            if (item.Comments != "")
                text += "Commentaires : " + System.Web.HttpUtility.HtmlDecode(item.Comments) + "\n";
            if (item.Link.ToString() != "")
                text += "Url : " + item.Link.ToString() + "\n";
            if (item.PubDate.ToString() != "")
                text += "Date : " + item.PubDate.ToShortDateString() + "\n";
            return text;
        }

        private void updateNewsList(ListViewItem fluxSel)
        {
            news_listView.Items.Clear();
            RssChannel fluxFeed = (RssChannel)fluxSel.Tag;

            foreach (RssItem nwsItem in fluxFeed.Items)
            {
                ListViewItem item1 = new ListViewItem(nwsItem.Title.ToString());
             //   nwsItem.newsListItem = item1;

                item1.SubItems.Add(nwsItem.PubDate.ToShortDateString());
                if (nwsItem.Author.ToString() != "")
                    item1.SubItems.Add(nwsItem.Author.ToString());
                else
                    item1.SubItems.Add("non renseigné");
                item1.ToolTipText = createNewsTooltip(nwsItem);
               if (nwsItem.IsRead == true)
                    item1.Font = new Font("Microsoft Sans Serif", 8.25f, FontStyle.Regular);
                else
                    item1.Font = new Font("Microsoft Sans Serif", 8.25f, FontStyle.Bold);

                item1.Tag = nwsItem;
                news_listView.Items.Add(item1);
            }
        }

        # region Systeme de reduction dans la systray

        private void useTooltipMSN()
        {
            if (Properties.Settings.Default.systray == true && Properties.Settings.Default.tooltip == true && this.WindowState == FormWindowState.Minimized)
            {
                NotifyWindow nw = new NotifyWindow("RSSReader !", "test value");
                nw.WaitTime = 10000;
                // nw.TextClicked += new System.EventHandler(textClick);
                nw.Notify();
            }
        }

        private void useSystray()
        {
            if (Properties.Settings.Default.systray == true)
            {
                notifyIcon1.Visible = true;
            }
            else
            {
                notifyIcon1.Visible = false;
            }
        }

        private void notifyIcon1_DoubleClick(object sender, System.EventArgs e)
        {
            this.ShowInTaskbar = true;
            this.Show();
            this.WindowState = FormWindowState.Normal;
        }

        private void RSSReaderMain_Resize(object sender, System.EventArgs e)
        {
            if (this.WindowState == FormWindowState.Minimized && Properties.Settings.Default.systray == true)
            {
                this.ShowInTaskbar = false;
                this.Hide();
            }
        }
        #endregion

        private void quitter_ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        #region Vocal synth
        private RssChannel getChannelOfItem(RssItem item)
        {
            foreach (RssChannel chan in _rssFeed.Channels)
            {
                foreach(RssItem items in chan.Items)
                {
                    if (items == item)
                    {
                        return chan;
                    }
                }
            }
            return null;
        }

        private RssChannel getNextChannel(RssChannel chan)
        {
            bool tmp = false;
            foreach (RssChannel chans in _rssFeed.Channels)
            {
                if (tmp == true)
                    return chans;
                if (chans == chan)
                {
                    tmp = true;
                }
            }
            return _rssFeed.Channels[0];
        }

        private RssItem getNextItem(RssItem item)
        {
            RssChannel chan = getChannelOfItem(item);
            bool tmp = false;
            foreach (RssItem items in chan.Items)
            {
                if (tmp == true)
                    return items;
                if (items == item)
                {
                    tmp = true;
                }
            }
             chan = getNextChannel(chan);
            return chan.Items[0];
        }

        private string readNewsItem(RssItem rssItem)
        {
            string sentence = "";
            if (rssItem.Title != "")
                sentence += "Titre " + System.Web.HttpUtility.HtmlDecode(rssItem.Title) + ". ";
            if (rssItem.Author != "")
                sentence += "Auteur " + System.Web.HttpUtility.HtmlDecode(rssItem.Author) + ". ";
            if (rssItem.Description != "")
                sentence += "Description " + System.Web.HttpUtility.HtmlDecode(rssItem.Description) + ". ";
            if (rssItem.PubDate.ToString() != "")
                sentence += "Date " + rssItem.PubDate.ToShortDateString() + ". ";
            return sentence;
        }

        private void vocal_ParseNews(ListView.SelectedListViewItemCollection newsSel)
        {
            string sentence = "";
            bool first = false;

            if (newsSel.Count == 1 && Properties.Settings.Default.nextNewsRead == true)
            {
                RssItem tmpItem = (RssItem)newsSel[0].Tag;
            //    System.Threading.Thread myThread = new System.Threading.Thread(new System.Threading.ThreadStart(vocal_SpellText(readNewsItem(tmpItem))));
            //    myThread.Start();
               // vocal_SpellText(readNewsItem(tmpItem));

                while (_readStop == false)
                {
                     vocal_SpellText(readNewsItem(getNextItem(tmpItem)));
                }
              
            }
            else
            {
                foreach (ListViewItem item in newsSel)
                {
                    RssItem rssItem = (RssItem)item.Tag;
                    if (first == true)
                        sentence += "News suivante. ";
                    sentence = readNewsItem(rssItem);
                    first = true;
                }

                vocal_SpellText(sentence);
            }
        }

        private void vocal_SpellText(string text)
        {
            try
            {
                SpeechVoiceSpeakFlags flags = SpeechVoiceSpeakFlags.SVSFlagsAsync | SpeechVoiceSpeakFlags.SVSFPurgeBeforeSpeak;
                mainVoice.Volume = Properties.Settings.Default.synthVolume;
                mainVoice.Speak(text, flags);

                int lngHandle = mainVoice.SpeakCompleteEvent();
                bool lngRtn = mainVoice.WaitUntilDone(System.Threading.Timeout.Infinite);
                
            }
            catch
            {
            }
        }

        private void vocalOptions_ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            VocalOptions opt = new VocalOptions();
            opt.FormParent = this;
            opt.ShowDialog();
        } 
        #endregion

        private void about_ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            RSSReaderAboutBox about = new RSSReaderAboutBox();
            about.Show();
        }

        private void appOptions_ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            AppOptions appopt = new AppOptions();
            appopt.FormParent = this;
            appopt.ShowDialog();

            updateOptions();
            Properties.Settings.Default.Save();
        }

        private void update_toolStripButton_Click(object sender, EventArgs e)
        {
            updateFluxList();
        }

        private void connexionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            connexionWin.FormParent = this;
            connexionWin.ShowDialog();
            
        }

        private void vocalSynth_toolStripButton_Click(object sender, EventArgs e)
        {
          /*   ListView.SelectedListViewItemCollection itemCol = news_listView.SelectedItems;

             foreach (ListViewItem item in itemCol)
             {
                 vocal_ParseNews((RssItem)item.Tag);
             }*/
        }

        private void ListFluxToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ModifyFluxList _modifyFluxListWin = new ModifyFluxList();
            _modifyFluxListWin.FormParent = this;
            _modifyFluxListWin.ShowDialog();
        }

        private void newsWebSite_linkLabel_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            Process myProcess = new Process();
            myProcess.StartInfo.FileName = newsWebSite_linkLabel.Text.ToString();
            myProcess.StartInfo.Verb = "Open";
            myProcess.StartInfo.CreateNoWindow = true;
            myProcess.Start();
        }

        private void webBrowser1_ProgressChanged(object sender, WebBrowserProgressChangedEventArgs e)
        {
        
            main_progressBar.Visible = true;
            main_progressBar.Maximum = (int)e.MaximumProgress;
            main_progressBar.Value = (int)e.CurrentProgress;

            if (e.CurrentProgress >= e.MaximumProgress)
                main_progressBar.Visible = false;
        }

        private void vocalSynthNews_toolStripButton_Click(object sender, EventArgs e)
        {
            ListView.SelectedListViewItemCollection itemCol = news_listView.SelectedItems;
            vocal_ParseNews(itemCol);
        }

      
        private void fluxRead_toolStripButton_Click(object sender, EventArgs e)
        {

        }

        private void newsRead_toolStripButton_Click(object sender, EventArgs e)
        {

        }

     

        private void RSSReaderMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (Properties.Settings.Default.rememberMe == false)
            {
                Properties.Settings.Default.pass = "";
                Properties.Settings.Default.login = "";
            }
            Properties.Settings.Default.Save();
        }

        private void deconnexionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            _isConnected = false;
            statusCnx_toolStripLabel.Text = "Pas connecté";
            update_toolStripButton.Enabled = false;
            fluxRead_toolStripButton.Enabled = false;
            newsRead_toolStripButton.Enabled = false;
           
            vocalSynthNews_toolStripButton.Enabled = false;
            webBrowser1.Url = new Uri("about:blank");
            newsSubject_label.Text = "";
            newsDate_label.Text = "";
            newsFrom_label.Text = "";
            newsWebSite_linkLabel.Text = "";
            flux_listView.Items.Clear();
            news_listView.Items.Clear();

        }
    }

    public class newsItem
    {
        public string newsName = "";
        public bool isRead = false;
        public string newsAuteur = "";
        public string dateNews = "";
        public string urlNews = "";
        public fluxItem parentFlux = null;
        public ListViewItem newsListItem = null;
    }

    public class fluxItem
    {
        public string fluxName = "";
        public bool isRead = false;
        public List<newsItem> newsList = new List<newsItem>();
        public TreeNode fluxTreeNode = null;
    }
}