namespace RSSReader
{
    partial class RSSReaderMain
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(RSSReaderMain));
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            this.main_timer = new System.Windows.Forms.Timer(this.components);
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fichierToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.connexionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.deconnexionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ListFluxToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.quitter_ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.optionsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.vocalOptions_ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.appOptions_ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.about_ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.news_listView = new System.Windows.Forms.ListView();
            this.sujet_columnHeader = new System.Windows.Forms.ColumnHeader();
            this.date_columnHeader = new System.Windows.Forms.ColumnHeader();
            this.auteur_columnHeader = new System.Windows.Forms.ColumnHeader();
            this.notifyIcon1 = new System.Windows.Forms.NotifyIcon(this.components);
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.statusCnx_toolStripLabel = new System.Windows.Forms.ToolStripLabel();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.update_toolStripButton = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.fluxRead_toolStripButton = new System.Windows.Forms.ToolStripButton();
            this.newsRead_toolStripButton = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.vocalSynthNews_toolStripButton = new System.Windows.Forms.ToolStripButton();
            this.stop_VocalSynth_toolStripButton = new System.Windows.Forms.ToolStripButton();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.flux_listView = new System.Windows.Forms.ListView();
            this.flux_columnHeader = new System.Windows.Forms.ColumnHeader();
            this.webBrowser1 = new System.Windows.Forms.WebBrowser();
            this.panel1 = new System.Windows.Forms.Panel();
            this.status_label = new System.Windows.Forms.Label();
            this.main_progressBar = new System.Windows.Forms.ProgressBar();
            this.newsFrom_label = new System.Windows.Forms.Label();
            this.newsWebSite_linkLabel = new System.Windows.Forms.LinkLabel();
            this.newsDate_label = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.newsSubject_label = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.splitter1 = new System.Windows.Forms.Splitter();
            this.BottomToolStripPanel = new System.Windows.Forms.ToolStripPanel();
            this.TopToolStripPanel = new System.Windows.Forms.ToolStripPanel();
            this.RightToolStripPanel = new System.Windows.Forms.ToolStripPanel();
            this.LeftToolStripPanel = new System.Windows.Forms.ToolStripPanel();
            this.ContentPanel = new System.Windows.Forms.ToolStripContentPanel();
            this.menuStrip1.SuspendLayout();
            this.toolStrip1.SuspendLayout();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // imageList1
            // 
            this.imageList1.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList1.ImageStream")));
            this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
            this.imageList1.Images.SetKeyName(0, "rss.bmp");
            // 
            // main_timer
            // 
            this.main_timer.Enabled = true;
            this.main_timer.Interval = 100000;
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fichierToolStripMenuItem,
            this.optionsToolStripMenuItem,
            this.toolStripMenuItem1});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.ShowItemToolTips = true;
            this.menuStrip1.Size = new System.Drawing.Size(1100, 24);
            this.menuStrip1.TabIndex = 8;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fichierToolStripMenuItem
            // 
            this.fichierToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.connexionToolStripMenuItem,
            this.deconnexionToolStripMenuItem,
            this.ListFluxToolStripMenuItem,
            this.quitter_ToolStripMenuItem});
            this.fichierToolStripMenuItem.Name = "fichierToolStripMenuItem";
            this.fichierToolStripMenuItem.Size = new System.Drawing.Size(50, 20);
            this.fichierToolStripMenuItem.Text = "Fichier";
            // 
            // connexionToolStripMenuItem
            // 
            this.connexionToolStripMenuItem.Name = "connexionToolStripMenuItem";
            this.connexionToolStripMenuItem.Size = new System.Drawing.Size(222, 22);
            this.connexionToolStripMenuItem.Text = "Connexion / Ajout utilisateur";
            this.connexionToolStripMenuItem.Click += new System.EventHandler(this.connexionToolStripMenuItem_Click);
            // 
            // deconnexionToolStripMenuItem
            // 
            this.deconnexionToolStripMenuItem.Name = "deconnexionToolStripMenuItem";
            this.deconnexionToolStripMenuItem.Size = new System.Drawing.Size(222, 22);
            this.deconnexionToolStripMenuItem.Text = "Deconnexion";
            this.deconnexionToolStripMenuItem.Click += new System.EventHandler(this.deconnexionToolStripMenuItem_Click);
            // 
            // ListFluxToolStripMenuItem
            // 
            this.ListFluxToolStripMenuItem.Name = "ListFluxToolStripMenuItem";
            this.ListFluxToolStripMenuItem.Size = new System.Drawing.Size(222, 22);
            this.ListFluxToolStripMenuItem.Text = "Modifier la liste des flux";
            this.ListFluxToolStripMenuItem.Click += new System.EventHandler(this.ListFluxToolStripMenuItem_Click);
            // 
            // quitter_ToolStripMenuItem
            // 
            this.quitter_ToolStripMenuItem.Name = "quitter_ToolStripMenuItem";
            this.quitter_ToolStripMenuItem.ShortcutKeyDisplayString = "";
            this.quitter_ToolStripMenuItem.Size = new System.Drawing.Size(222, 22);
            this.quitter_ToolStripMenuItem.Text = "Quitter";
            this.quitter_ToolStripMenuItem.Click += new System.EventHandler(this.quitter_ToolStripMenuItem_Click);
            // 
            // optionsToolStripMenuItem
            // 
            this.optionsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.vocalOptions_ToolStripMenuItem,
            this.appOptions_ToolStripMenuItem});
            this.optionsToolStripMenuItem.Name = "optionsToolStripMenuItem";
            this.optionsToolStripMenuItem.Size = new System.Drawing.Size(56, 20);
            this.optionsToolStripMenuItem.Text = "Options";
            // 
            // vocalOptions_ToolStripMenuItem
            // 
            this.vocalOptions_ToolStripMenuItem.Name = "vocalOptions_ToolStripMenuItem";
            this.vocalOptions_ToolStripMenuItem.Size = new System.Drawing.Size(249, 22);
            this.vocalOptions_ToolStripMenuItem.Text = "Preferences du synthetiseur vocal";
            this.vocalOptions_ToolStripMenuItem.Click += new System.EventHandler(this.vocalOptions_ToolStripMenuItem_Click);
            // 
            // appOptions_ToolStripMenuItem
            // 
            this.appOptions_ToolStripMenuItem.Name = "appOptions_ToolStripMenuItem";
            this.appOptions_ToolStripMenuItem.Size = new System.Drawing.Size(249, 22);
            this.appOptions_ToolStripMenuItem.Text = "Preferences de l\'application";
            this.appOptions_ToolStripMenuItem.Click += new System.EventHandler(this.appOptions_ToolStripMenuItem_Click);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.about_ToolStripMenuItem});
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(24, 20);
            this.toolStripMenuItem1.Text = "?";
            // 
            // about_ToolStripMenuItem
            // 
            this.about_ToolStripMenuItem.Name = "about_ToolStripMenuItem";
            this.about_ToolStripMenuItem.Size = new System.Drawing.Size(140, 22);
            this.about_ToolStripMenuItem.Text = "A propos...";
            this.about_ToolStripMenuItem.Click += new System.EventHandler(this.about_ToolStripMenuItem_Click);
            // 
            // news_listView
            // 
            this.news_listView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.sujet_columnHeader,
            this.date_columnHeader,
            this.auteur_columnHeader});
            this.news_listView.Dock = System.Windows.Forms.DockStyle.Top;
            this.news_listView.FullRowSelect = true;
            this.news_listView.HideSelection = false;
            this.news_listView.Location = new System.Drawing.Point(0, 0);
            this.news_listView.Name = "news_listView";
            this.news_listView.ShowItemToolTips = true;
            this.news_listView.Size = new System.Drawing.Size(893, 237);
            this.news_listView.TabIndex = 0;
            this.news_listView.UseCompatibleStateImageBehavior = false;
            this.news_listView.View = System.Windows.Forms.View.Details;
            this.news_listView.Enter += new System.EventHandler(this.news_listView_Enter);
            this.news_listView.SelectedIndexChanged += new System.EventHandler(this.news_listView_SelectedIndexChanged);
            this.news_listView.Leave += new System.EventHandler(this.news_listView_Leave);
            // 
            // sujet_columnHeader
            // 
            this.sujet_columnHeader.Name = "sujet_columnHeader";
            this.sujet_columnHeader.Text = "Sujet";
            this.sujet_columnHeader.Width = 400;
            // 
            // date_columnHeader
            // 
            this.date_columnHeader.Name = "date_columnHeader";
            this.date_columnHeader.Text = "Date";
            this.date_columnHeader.Width = 200;
            // 
            // auteur_columnHeader
            // 
            this.auteur_columnHeader.Name = "auteur_columnHeader";
            this.auteur_columnHeader.Text = "Auteur";
            this.auteur_columnHeader.Width = 200;
            // 
            // notifyIcon1
            // 
            this.notifyIcon1.Icon = ((System.Drawing.Icon)(resources.GetObject("notifyIcon1.Icon")));
            this.notifyIcon1.Text = "RSSReader : double click pour agrandir";
            this.notifyIcon1.DoubleClick += new System.EventHandler(this.notifyIcon1_DoubleClick);
            // 
            // toolStrip1
            // 
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.statusCnx_toolStripLabel,
            this.toolStripSeparator1,
            this.update_toolStripButton,
            this.toolStripSeparator2,
            this.fluxRead_toolStripButton,
            this.newsRead_toolStripButton,
            this.toolStripSeparator3,
            this.vocalSynthNews_toolStripButton,
            this.stop_VocalSynth_toolStripButton});
            this.toolStrip1.Location = new System.Drawing.Point(0, 24);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(1100, 36);
            this.toolStrip1.TabIndex = 0;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // statusCnx_toolStripLabel
            // 
            this.statusCnx_toolStripLabel.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.statusCnx_toolStripLabel.Name = "statusCnx_toolStripLabel";
            this.statusCnx_toolStripLabel.Size = new System.Drawing.Size(71, 33);
            this.statusCnx_toolStripLabel.Text = "Pas connecté";
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 36);
            // 
            // update_toolStripButton
            // 
            this.update_toolStripButton.Enabled = false;
            this.update_toolStripButton.Image = ((System.Drawing.Image)(resources.GetObject("update_toolStripButton.Image")));
            this.update_toolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.update_toolStripButton.Name = "update_toolStripButton";
            this.update_toolStripButton.Size = new System.Drawing.Size(46, 33);
            this.update_toolStripButton.Text = "Update";
            this.update_toolStripButton.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.update_toolStripButton.Click += new System.EventHandler(this.update_toolStripButton_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(6, 36);
            // 
            // fluxRead_toolStripButton
            // 
            this.fluxRead_toolStripButton.Enabled = false;
            this.fluxRead_toolStripButton.Image = ((System.Drawing.Image)(resources.GetObject("fluxRead_toolStripButton.Image")));
            this.fluxRead_toolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.fluxRead_toolStripButton.Name = "fluxRead_toolStripButton";
            this.fluxRead_toolStripButton.Size = new System.Drawing.Size(55, 33);
            this.fluxRead_toolStripButton.Text = "Flux lu(s)";
            this.fluxRead_toolStripButton.TextAlign = System.Drawing.ContentAlignment.BottomCenter;
            this.fluxRead_toolStripButton.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.fluxRead_toolStripButton.Click += new System.EventHandler(this.fluxRead_toolStripButton_Click);
            // 
            // newsRead_toolStripButton
            // 
            this.newsRead_toolStripButton.Enabled = false;
            this.newsRead_toolStripButton.Image = ((System.Drawing.Image)(resources.GetObject("newsRead_toolStripButton.Image")));
            this.newsRead_toolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.newsRead_toolStripButton.Name = "newsRead_toolStripButton";
            this.newsRead_toolStripButton.Size = new System.Drawing.Size(67, 33);
            this.newsRead_toolStripButton.Text = "News lue(s)";
            this.newsRead_toolStripButton.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.newsRead_toolStripButton.Click += new System.EventHandler(this.newsRead_toolStripButton_Click);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(6, 36);
            // 
            // vocalSynthNews_toolStripButton
            // 
            this.vocalSynthNews_toolStripButton.Enabled = false;
            this.vocalSynthNews_toolStripButton.Image = ((System.Drawing.Image)(resources.GetObject("vocalSynthNews_toolStripButton.Image")));
            this.vocalSynthNews_toolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.vocalSynthNews_toolStripButton.Name = "vocalSynthNews_toolStripButton";
            this.vocalSynthNews_toolStripButton.Size = new System.Drawing.Size(57, 33);
            this.vocalSynthNews_toolStripButton.Text = "Lire News";
            this.vocalSynthNews_toolStripButton.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.vocalSynthNews_toolStripButton.Click += new System.EventHandler(this.vocalSynthNews_toolStripButton_Click);
            // 
            // stop_VocalSynth_toolStripButton
            // 
            this.stop_VocalSynth_toolStripButton.Image = ((System.Drawing.Image)(resources.GetObject("stop_VocalSynth_toolStripButton.Image")));
            this.stop_VocalSynth_toolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.stop_VocalSynth_toolStripButton.Name = "stop_VocalSynth_toolStripButton";
            this.stop_VocalSynth_toolStripButton.Size = new System.Drawing.Size(33, 33);
            this.stop_VocalSynth_toolStripButton.Text = "Stop";
            this.stop_VocalSynth_toolStripButton.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.stop_VocalSynth_toolStripButton.ToolTipText = "Stop";
            this.stop_VocalSynth_toolStripButton.Click += new System.EventHandler(this.stop_VocalSynth_toolStripButton_Click);
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 60);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.flux_listView);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.webBrowser1);
            this.splitContainer1.Panel2.Controls.Add(this.panel1);
            this.splitContainer1.Panel2.Controls.Add(this.splitter1);
            this.splitContainer1.Panel2.Controls.Add(this.news_listView);
            this.splitContainer1.Size = new System.Drawing.Size(1100, 734);
            this.splitContainer1.SplitterDistance = 203;
            this.splitContainer1.TabIndex = 12;
            // 
            // flux_listView
            // 
            this.flux_listView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.flux_columnHeader});
            this.flux_listView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.flux_listView.FullRowSelect = true;
            this.flux_listView.HideSelection = false;
            this.flux_listView.Location = new System.Drawing.Point(0, 0);
            this.flux_listView.Name = "flux_listView";
            this.flux_listView.ShowItemToolTips = true;
            this.flux_listView.Size = new System.Drawing.Size(203, 734);
            this.flux_listView.TabIndex = 10;
            this.flux_listView.UseCompatibleStateImageBehavior = false;
            this.flux_listView.View = System.Windows.Forms.View.Details;
            this.flux_listView.SelectedIndexChanged += new System.EventHandler(this.flux_listView_SelectedIndexChanged);
            // 
            // flux_columnHeader
            // 
            this.flux_columnHeader.Name = "flux_columnHeader";
            this.flux_columnHeader.Text = "Flux";
            this.flux_columnHeader.Width = 204;
            // 
            // webBrowser1
            // 
            this.webBrowser1.AllowWebBrowserDrop = false;
            this.webBrowser1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.webBrowser1.IsWebBrowserContextMenuEnabled = false;
            this.webBrowser1.Location = new System.Drawing.Point(0, 311);
            this.webBrowser1.MinimumSize = new System.Drawing.Size(20, 20);
            this.webBrowser1.Name = "webBrowser1";
            this.webBrowser1.Size = new System.Drawing.Size(893, 423);
            this.webBrowser1.TabIndex = 11;
            this.webBrowser1.Url = new System.Uri("about:blank", System.UriKind.Absolute);
            this.webBrowser1.WebBrowserShortcutsEnabled = false;
            this.webBrowser1.ProgressChanged += new System.Windows.Forms.WebBrowserProgressChangedEventHandler(this.webBrowser1_ProgressChanged);
            // 
            // panel1
            // 
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1.Controls.Add(this.status_label);
            this.panel1.Controls.Add(this.main_progressBar);
            this.panel1.Controls.Add(this.newsFrom_label);
            this.panel1.Controls.Add(this.newsWebSite_linkLabel);
            this.panel1.Controls.Add(this.newsDate_label);
            this.panel1.Controls.Add(this.label5);
            this.panel1.Controls.Add(this.label4);
            this.panel1.Controls.Add(this.label3);
            this.panel1.Controls.Add(this.newsSubject_label);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel1.Location = new System.Drawing.Point(0, 240);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(893, 71);
            this.panel1.TabIndex = 12;
            // 
            // status_label
            // 
            this.status_label.AutoSize = true;
            this.status_label.Location = new System.Drawing.Point(786, 49);
            this.status_label.Name = "status_label";
            this.status_label.Size = new System.Drawing.Size(103, 13);
            this.status_label.TabIndex = 10;
            this.status_label.Text = "Status : en attente...";
            // 
            // main_progressBar
            // 
            this.main_progressBar.Location = new System.Drawing.Point(789, 2);
            this.main_progressBar.Name = "main_progressBar";
            this.main_progressBar.Size = new System.Drawing.Size(100, 13);
            this.main_progressBar.TabIndex = 9;
            this.main_progressBar.Visible = false;
            // 
            // newsFrom_label
            // 
            this.newsFrom_label.AutoSize = true;
            this.newsFrom_label.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.newsFrom_label.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.newsFrom_label.Location = new System.Drawing.Point(84, 21);
            this.newsFrom_label.Name = "newsFrom_label";
            this.newsFrom_label.Size = new System.Drawing.Size(0, 13);
            this.newsFrom_label.TabIndex = 8;
            // 
            // newsWebSite_linkLabel
            // 
            this.newsWebSite_linkLabel.AutoSize = true;
            this.newsWebSite_linkLabel.Location = new System.Drawing.Point(84, 49);
            this.newsWebSite_linkLabel.Name = "newsWebSite_linkLabel";
            this.newsWebSite_linkLabel.Size = new System.Drawing.Size(0, 13);
            this.newsWebSite_linkLabel.TabIndex = 7;
            this.newsWebSite_linkLabel.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.newsWebSite_linkLabel_LinkClicked);
            // 
            // newsDate_label
            // 
            this.newsDate_label.AutoSize = true;
            this.newsDate_label.Location = new System.Drawing.Point(84, 35);
            this.newsDate_label.Name = "newsDate_label";
            this.newsDate_label.Size = new System.Drawing.Size(0, 13);
            this.newsDate_label.TabIndex = 5;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(7, 49);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(67, 13);
            this.label5.TabIndex = 4;
            this.label5.Text = "Site Web :";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(32, 35);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(42, 13);
            this.label4.TabIndex = 3;
            this.label4.Text = "Date :";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(43, 21);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(31, 13);
            this.label3.TabIndex = 2;
            this.label3.Text = "De :";
            // 
            // newsSubject_label
            // 
            this.newsSubject_label.AutoSize = true;
            this.newsSubject_label.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.newsSubject_label.Location = new System.Drawing.Point(84, 7);
            this.newsSubject_label.Name = "newsSubject_label";
            this.newsSubject_label.Size = new System.Drawing.Size(0, 13);
            this.newsSubject_label.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(30, 7);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(44, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Sujet :";
            // 
            // splitter1
            // 
            this.splitter1.Dock = System.Windows.Forms.DockStyle.Top;
            this.splitter1.Location = new System.Drawing.Point(0, 237);
            this.splitter1.Name = "splitter1";
            this.splitter1.Size = new System.Drawing.Size(893, 3);
            this.splitter1.TabIndex = 10;
            this.splitter1.TabStop = false;
            // 
            // BottomToolStripPanel
            // 
            this.BottomToolStripPanel.Location = new System.Drawing.Point(0, 0);
            this.BottomToolStripPanel.Name = "BottomToolStripPanel";
            this.BottomToolStripPanel.Orientation = System.Windows.Forms.Orientation.Horizontal;
            this.BottomToolStripPanel.RowMargin = new System.Windows.Forms.Padding(3, 0, 0, 0);
            this.BottomToolStripPanel.Size = new System.Drawing.Size(0, 0);
            // 
            // TopToolStripPanel
            // 
            this.TopToolStripPanel.Location = new System.Drawing.Point(0, 0);
            this.TopToolStripPanel.Name = "TopToolStripPanel";
            this.TopToolStripPanel.Orientation = System.Windows.Forms.Orientation.Horizontal;
            this.TopToolStripPanel.RowMargin = new System.Windows.Forms.Padding(3, 0, 0, 0);
            this.TopToolStripPanel.Size = new System.Drawing.Size(0, 0);
            // 
            // RightToolStripPanel
            // 
            this.RightToolStripPanel.Location = new System.Drawing.Point(0, 0);
            this.RightToolStripPanel.Name = "RightToolStripPanel";
            this.RightToolStripPanel.Orientation = System.Windows.Forms.Orientation.Horizontal;
            this.RightToolStripPanel.RowMargin = new System.Windows.Forms.Padding(3, 0, 0, 0);
            this.RightToolStripPanel.Size = new System.Drawing.Size(0, 0);
            // 
            // LeftToolStripPanel
            // 
            this.LeftToolStripPanel.Location = new System.Drawing.Point(0, 0);
            this.LeftToolStripPanel.Name = "LeftToolStripPanel";
            this.LeftToolStripPanel.Orientation = System.Windows.Forms.Orientation.Horizontal;
            this.LeftToolStripPanel.RowMargin = new System.Windows.Forms.Padding(3, 0, 0, 0);
            this.LeftToolStripPanel.Size = new System.Drawing.Size(0, 0);
            // 
            // ContentPanel
            // 
            this.ContentPanel.Size = new System.Drawing.Size(150, 175);
            // 
            // RSSReaderMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1100, 794);
            this.Controls.Add(this.splitContainer1);
            this.Controls.Add(this.toolStrip1);
            this.Controls.Add(this.menuStrip1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "RSSReaderMain";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "RSSReader";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.RSSReaderMain_FormClosed);
            this.Resize += new System.EventHandler(this.RSSReaderMain_Resize);
            this.Shown += new System.EventHandler(this.RSSReaderMain_Shown);
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.RSSReaderMain_FormClosing);
            this.Load += new System.EventHandler(this.RSSReaderMain_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ImageList imageList1;
        private System.Windows.Forms.Timer main_timer;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ListView news_listView;
        private System.Windows.Forms.NotifyIcon notifyIcon1;
        private System.Windows.Forms.ToolStripMenuItem optionsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem fichierToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem quitter_ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem vocalOptions_ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem about_ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem appOptions_ToolStripMenuItem;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.Splitter splitter1;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripLabel statusCnx_toolStripLabel;
        private System.Windows.Forms.ToolStripButton update_toolStripButton;
        private System.Windows.Forms.ColumnHeader sujet_columnHeader;
        private System.Windows.Forms.ColumnHeader date_columnHeader;
        private System.Windows.Forms.ColumnHeader auteur_columnHeader;
        private System.Windows.Forms.WebBrowser webBrowser1;
        private System.Windows.Forms.ToolStripMenuItem connexionToolStripMenuItem;
        private System.Windows.Forms.ToolStripButton vocalSynthNews_toolStripButton;
        private System.Windows.Forms.ToolStripMenuItem ListFluxToolStripMenuItem;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label newsSubject_label;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.LinkLabel newsWebSite_linkLabel;
        private System.Windows.Forms.Label newsDate_label;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label newsFrom_label;
        private System.Windows.Forms.ListView flux_listView;
        private System.Windows.Forms.ColumnHeader flux_columnHeader;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripButton fluxRead_toolStripButton;
        private System.Windows.Forms.ToolStripButton newsRead_toolStripButton;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripPanel BottomToolStripPanel;
        private System.Windows.Forms.ToolStripPanel TopToolStripPanel;
        private System.Windows.Forms.ToolStripPanel RightToolStripPanel;
        private System.Windows.Forms.ToolStripPanel LeftToolStripPanel;
        private System.Windows.Forms.ToolStripContentPanel ContentPanel;
        private System.Windows.Forms.ToolStripMenuItem deconnexionToolStripMenuItem;
        private System.Windows.Forms.ProgressBar main_progressBar;
        private System.Windows.Forms.Label status_label;
        private System.Windows.Forms.ToolStripButton stop_VocalSynth_toolStripButton;


    }
}