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
using System.Threading;


namespace RSSReader
{
    public delegate void DelegateVocalThreadFinished();

    public partial class RSSReaderMain : Form
    {
        #region Private Var

        private KKTRSS_service.Service _mainWebService = new KKTRSS_service.Service();

        private string _sessionID = "";
        private Connexion connexionWin = new Connexion();
        private bool _isConnected = false;
        private SpVoice mainVoice = new SpVoice();
        private string _fluxUrl = "http://bluegloup.free.fr/news.xml";

        private ListViewItem _lastSelectedFlux = null;
        private ListViewItem _lastSelectedNews = null;

        private NotifyWindow nw = null;

        private RssFeed _rssFeed = new RssFeed();
        private RssFeed _previousFeed = new RssFeed();

        private List<fluxItem> _fluxList = new List<fluxItem>();
        private bool _isUpdating = false;
        private bool _readStop = false;

        public bool IsConnected
        {
            get { return _isConnected; }
            set { _isConnected = value; }
        }
        public string SessionID
        {
            get { return _sessionID; }
            set { _sessionID = value; }
        }
        public KKTRSS_service.Service MainWebService
        {
            get { return _mainWebService; }
            set { _mainWebService = value; }
        }
        #endregion


        public RSSReaderMain()
        {
           
            InitializeComponent();
            Properties.Settings.Default.Reset();
        }

        private void updateOptions()
        {
            useSystray();
            //main_timer.Interval = Properties.Settings.Default.updateTime * 60 * 1000;
            main_timer.Interval = Properties.Settings.Default.updateTime * 10 * 1000;
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

            if (_isConnected == true)
            {
                statusCnx_toolStripLabel.Text = Properties.Settings.Default.login;
                update_toolStripButton.Enabled = true;
                ListFluxToolStripMenuItem.Enabled = true;

           
                main_timer.Tick += new EventHandler(Timer_Tick);
                main_timer.Start();

               

                updateFluxList();
            }
        }

        private void setFluxIsRead()
        {
            bool returnVal = false;

            foreach (RssChannel chan in _rssFeed.Channels)
            {
                returnVal = true;
                foreach (RssItem item in chan.Items)
                {
                    if (item.IsRead == false)
                        returnVal = false;
                }
                if (returnVal == true)
                    chan.IsRead = true;
            }
        }

        private void fillRSSFeed()
        {
            HttpWebRequest request = null;
            bool err = true;
            int tried = 0;

            string tmp = _mainWebService.GetMyRssFeed(_sessionID);
            _previousFeed = _rssFeed;
            if (tmp != "")
                _rssFeed = RssFeed.ReadFromString(tmp);
            setFluxIsRead();
            useTooltipMSN();
          //  if (err == true)
           //      System.Windows.Forms.MessageBox.Show("Erreur dans la mise a jour des flux.", "RssReader", System.Windows.Forms.MessageBoxButtons.OK, System.Windows.Forms.MessageBoxIcon.Error);
        }

    
        private void RSSReaderMain_Shown(object sender, EventArgs e)
        {

        }

        public bool connectionToServer(string login, string mdp)
        {
           _sessionID = _mainWebService.Login(login, mdp);
            if (_sessionID == null || _sessionID == "")
                return false;
            else
            {
                _isConnected = true;
                Properties.Settings.Default.login = login;
                Properties.Settings.Default.pass = mdp;
                Properties.Settings.Default.Save();
              
                return true;
            }
        }

        public void Timer_Tick(object sender, EventArgs eArgs)
        {
            if (sender == main_timer && _isConnected == true)
            {
                updateFluxList();
                if (_lastSelectedFlux != null)
                    updateNewsList(_lastSelectedFlux);

          
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

        public void updateFluxList()
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
            news_listView.Items.Clear();
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

                    if (_mainWebService.MarkAsRead(_sessionID, itemSel.HashID) == true)
                    {
                        item.Font = new Font("Microsoft Sans Serif", 8.25f, FontStyle.Regular);
                        itemSel.IsRead = true;
                    }
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

        private void selFluxAndItemByItem(RssItem itemToSel)
        {
            lock (this)
            {
                RssChannel chanToSel = new RssChannel();
                chanToSel = getChannelOfItem(itemToSel);

                foreach (ListViewItem items in flux_listView.Items)
                {
                    if ((RssChannel)items.Tag == chanToSel)
                        items.Selected = true;
                    else
                        items.Selected = false;
                }
                foreach (ListViewItem items in news_listView.Items)
                {
                    if ((RssItem)items.Tag == itemToSel)
                        items.Selected = true;
                    else
                        items.Selected = false;
                }
            }
        }

        # region Systeme de reduction dans la systray

        private RssItem getLastArrivedItem()
        {
            RssItem lastPrevItem = new RssItem();
            DateTime prevDate = new DateTime();

            RssItem lastCurItem = new RssItem();
            DateTime curDate = new DateTime();

            foreach (RssChannel chan in _previousFeed.Channels)
            {
                foreach (RssItem item in chan.Items)
                {
                    if (item.PubDate > prevDate)
                    {
                        lastPrevItem = item;
                        prevDate = item.PubDate;
                    }
                }
            }
            foreach (RssChannel chan in _rssFeed.Channels)
            {
                foreach (RssItem item in chan.Items)
                {
                    if (item.PubDate > curDate)
                    {
                        lastCurItem = item;
                        curDate = item.PubDate;
                    }
                }
            }

            if (curDate >= prevDate)
                return lastCurItem;
            else
                return null;
        }

        private void useTooltipMSN()
        {
            if (Properties.Settings.Default.systray == true && Properties.Settings.Default.tooltip == true && this.WindowState == FormWindowState.Minimized)
            {
                RssItem item = new RssItem();
                item = getLastArrivedItem();
                if (getLastArrivedItem() != null)
                {
                    nw = new NotifyWindow("Nouvelle news", item.Title);
                    nw.WaitTime = 1000;
                    nw.Tag = item;
                    nw.TextClicked += new System.EventHandler(nwTextClick);
                    nw.TitleClicked += new System.EventHandler(nwTextClick);
                    nw.Notify();
                }
            }
        }

        private void nwTextClick(object sender, System.EventArgs e)
        {
            this.ShowInTaskbar = true;
            this.Show();
            this.WindowState = FormWindowState.Normal;

            RssItem selItem = (RssItem)nw.Tag;
            selFluxAndItemByItem(selItem);
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
            lock (this)
            {
                foreach (RssChannel chan in _rssFeed.Channels)
                {
                    foreach (RssItem items in chan.Items)
                    {
                        if (items == item)
                        {
                            return chan;
                        }
                    }
                }
                return null;
            }
        }

        private RssChannel getNextChannel(RssChannel chan)
        {
            lock (this)
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
        }

        private RssItem getNextItem(RssItem item)
        {
            lock (this)
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


        Thread m_WorkerThread;
        ManualResetEvent m_EventStopThread;
        ManualResetEvent m_EventThreadStopped;
        public DelegateVocalThreadFinished m_DelegateThreadFinished;

        private RssItem _itemToRead = new RssItem();
        private bool _continueToRead = false;


        private void stop_VocalSynth_toolStripButton_Click(object sender, EventArgs e)
        {
            _continueToRead = false;
            if (m_WorkerThread != null && m_WorkerThread.IsAlive)  // thread is active
            {
                m_EventStopThread.Set();
                while (m_WorkerThread.IsAlive)
                {
                    if (WaitHandle.WaitAll((new ManualResetEvent[] { m_EventThreadStopped }), 10, true))
                        break;
                    Application.DoEvents();
                }
            }
            stop_VocalSynth_toolStripButton.Enabled = false;
            newsRead_toolStripButton.Enabled = true;
            main_timer.Start();
        }

        private void stop_Thread()
        {
            if (m_WorkerThread != null && m_WorkerThread.IsAlive)  // thread is active
            {
                m_EventStopThread.Set();
                while (m_WorkerThread.IsAlive)
                {
                    if (WaitHandle.WaitAll((new ManualResetEvent[] { m_EventThreadStopped }), 10, true))
                        break;
                    Application.DoEvents();
                }
            }
           
        }
    
        private void WorkerThreadFunction()
        {
            VocalThread vocalThread;
            vocalThread = new VocalThread(m_EventStopThread, m_EventThreadStopped, this, _itemToRead);
            vocalThread.run();
        }

        private void ThreadFinished()
        {
           /* lock (this)
            {*/
                if (Properties.Settings.Default.nextNewsRead == true && _continueToRead == true)
                {
                    _itemToRead = getNextItem(_itemToRead);
                    selFluxAndItemByItem(_itemToRead);
                    m_EventStopThread.Reset();
                    m_EventThreadStopped.Reset();

                    m_WorkerThread = new Thread(new ThreadStart(this.WorkerThreadFunction));
                    m_WorkerThread.Name = "Vocal thread";
                    m_WorkerThread.Start();

                }
                else if (Properties.Settings.Default.nextNewsRead == false && _continueToRead == true)
                {
                    _continueToRead = false;
                    main_timer.Start();
                }
           // }
        }

        private void vocal_ParseNews(ListView.SelectedListViewItemCollection newsSel)
        {
             if (newsSel.Count == 1 )
             {
                 stop_VocalSynth_toolStripButton.Enabled = true;
                 newsRead_toolStripButton.Enabled = false;

                 main_timer.Stop();
                 _continueToRead = true;
                 _itemToRead = (RssItem)newsSel[0].Tag;

                 m_DelegateThreadFinished = new DelegateVocalThreadFinished(this.ThreadFinished);


                 m_EventStopThread = new ManualResetEvent(false);
                 m_EventThreadStopped = new ManualResetEvent(false);


                 m_EventStopThread.Reset();
                 m_EventThreadStopped.Reset();


                 m_WorkerThread = new Thread(new ThreadStart(this.WorkerThreadFunction));
                 m_WorkerThread.Name = "Vocal thread";
                 //  while (_continueToRead == true)
                 m_WorkerThread.Start();
             }

        /*    if (newsSel.Count == 1 && Properties.Settings.Default.nextNewsRead == true)
            {

               _itemToRead = (RssItem)newsSel[0].Tag;
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
            }*/
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

            statusCnx_toolStripLabel.Text = Properties.Settings.Default.login;
            update_toolStripButton.Enabled = true;
            ListFluxToolStripMenuItem.Enabled = true;
            updateFluxList();
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
            ListView.SelectedListViewItemCollection fluxCol = flux_listView.SelectedItems;
            foreach (ListViewItem flux in fluxCol)
            {
                flux.Font = new Font("Microsoft Sans Serif", 8.25f, FontStyle.Regular);
                RssChannel tmpFlux = (RssChannel)flux.Tag;
                tmpFlux.IsRead = true;
                foreach (RssItem item in tmpFlux.Items)
                {
                    // TODO get listViewItem by RssItem
                    //item.Font = new Font("Microsoft Sans Serif", 8.25f, FontStyle.Regular);
                    if (item.IsRead == false)
                    {
                        item.IsRead = true;
                        _mainWebService.MarkAsRead(_sessionID, item.HashID);
                    }
                }
            }

        }

        private void newsRead_toolStripButton_Click(object sender, EventArgs e)
        {
            ListView.SelectedListViewItemCollection itemCol = news_listView.SelectedItems;

            foreach (ListViewItem item in itemCol)
            {
                // TODO tester toutes les news affichees et si elles sont toutes lues marquer le flux comme lu 
                item.Font = new Font("Microsoft Sans Serif", 8.25f, FontStyle.Regular);
                RssItem tmpItem = (RssItem)item.Tag;
                if (tmpItem.IsRead == false)
                {
                    tmpItem.IsRead = true;
                    _mainWebService.MarkAsRead(_sessionID, tmpItem.HashID);
                }
            }
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

        private void RSSReaderMain_FormClosed(object sender, FormClosedEventArgs e)
        {
            stop_Thread();
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