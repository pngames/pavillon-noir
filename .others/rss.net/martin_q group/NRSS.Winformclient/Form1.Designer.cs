namespace winformclient
{
  partial class Form1
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
        System.Windows.Forms.TreeNode treeNode1 = new System.Windows.Forms.TreeNode("RSS Test 1");
        System.Windows.Forms.TreeNode treeNode2 = new System.Windows.Forms.TreeNode("RSS Test 2");
        System.Windows.Forms.TreeNode treeNode3 = new System.Windows.Forms.TreeNode("RSS Test 3");
        System.Windows.Forms.TreeNode treeNode4 = new System.Windows.Forms.TreeNode("RSS", new System.Windows.Forms.TreeNode[] {
            treeNode1,
            treeNode2,
            treeNode3});
        System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
        this.LeftTreeMenu = new System.Windows.Forms.TreeView();
        this.menuStrip1 = new System.Windows.Forms.MenuStrip();
        this.fichierToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        this.newFeedToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        this.rSSFeedToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        this.nNTPToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        this.editionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        this.selectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        this.allMessagesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        this.optionsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        this.preferencesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        this.aboutNRSSToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        this.splitContainer1 = new System.Windows.Forms.SplitContainer();
        this.splitContainer2 = new System.Windows.Forms.SplitContainer();
        this.RightListView = new System.Windows.Forms.ListView();
        this.columnSubject = new System.Windows.Forms.ColumnHeader();
        this.columnSender = new System.Windows.Forms.ColumnHeader();
        this.columnDate = new System.Windows.Forms.ColumnHeader();
        this.columnDescription = new System.Windows.Forms.ColumnHeader();
        this.columnLink = new System.Windows.Forms.ColumnHeader();
        this.splitContainer3 = new System.Windows.Forms.SplitContainer();
        this.labelTitleContent = new System.Windows.Forms.Label();
        this.labelFromContent = new System.Windows.Forms.Label();
        this.labelDateContent = new System.Windows.Forms.Label();
        this.linkLabel = new System.Windows.Forms.LinkLabel();
        this.labelLink = new System.Windows.Forms.Label();
        this.labelDate = new System.Windows.Forms.Label();
        this.labelFrom = new System.Windows.Forms.Label();
        this.labelTitle = new System.Windows.Forms.Label();
        this.webBrowser1 = new System.Windows.Forms.WebBrowser();
        this.ToolBar = new System.Windows.Forms.ToolStrip();
        this.ReadText = new System.Windows.Forms.ToolStripButton();
        this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
        this.menuStrip1.SuspendLayout();
        this.splitContainer1.Panel1.SuspendLayout();
        this.splitContainer1.Panel2.SuspendLayout();
        this.splitContainer1.SuspendLayout();
        this.splitContainer2.Panel1.SuspendLayout();
        this.splitContainer2.Panel2.SuspendLayout();
        this.splitContainer2.SuspendLayout();
        this.splitContainer3.Panel1.SuspendLayout();
        this.splitContainer3.Panel2.SuspendLayout();
        this.splitContainer3.SuspendLayout();
        this.ToolBar.SuspendLayout();
        this.SuspendLayout();
        // 
        // LeftTreeMenu
        // 
        this.LeftTreeMenu.Dock = System.Windows.Forms.DockStyle.Fill;
        this.LeftTreeMenu.Location = new System.Drawing.Point(0, 0);
        this.LeftTreeMenu.Name = "LeftTreeMenu";
        treeNode1.Name = "RSSTest1";
        treeNode1.Text = "RSS Test 1";
        treeNode2.Name = "RSSTest2";
        treeNode2.Text = "RSS Test 2";
        treeNode3.Name = "RSSTest3";
        treeNode3.Text = "RSS Test 3";
        treeNode4.Name = "RssFeeds";
        treeNode4.Text = "RSS";
        this.LeftTreeMenu.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
            treeNode4});
        this.LeftTreeMenu.Size = new System.Drawing.Size(215, 646);
        this.LeftTreeMenu.TabIndex = 0;
        this.LeftTreeMenu.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.LeftTreeMenu_AfterSelect);
        // 
        // menuStrip1
        // 
        this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fichierToolStripMenuItem,
            this.editionToolStripMenuItem,
            this.optionsToolStripMenuItem,
            this.helpToolStripMenuItem});
        this.menuStrip1.Location = new System.Drawing.Point(0, 0);
        this.menuStrip1.Name = "menuStrip1";
        this.menuStrip1.Size = new System.Drawing.Size(866, 24);
        this.menuStrip1.TabIndex = 0;
        this.menuStrip1.Text = "menuStrip1";
        // 
        // fichierToolStripMenuItem
        // 
        this.fichierToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newFeedToolStripMenuItem});
        this.fichierToolStripMenuItem.Name = "fichierToolStripMenuItem";
        this.fichierToolStripMenuItem.Size = new System.Drawing.Size(38, 20);
        this.fichierToolStripMenuItem.Text = "File";
        // 
        // newFeedToolStripMenuItem
        // 
        this.newFeedToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.rSSFeedToolStripMenuItem,
            this.nNTPToolStripMenuItem});
        this.newFeedToolStripMenuItem.Name = "newFeedToolStripMenuItem";
        this.newFeedToolStripMenuItem.Size = new System.Drawing.Size(109, 22);
        this.newFeedToolStripMenuItem.Text = "New";
        // 
        // rSSFeedToolStripMenuItem
        // 
        this.rSSFeedToolStripMenuItem.Name = "rSSFeedToolStripMenuItem";
        this.rSSFeedToolStripMenuItem.Size = new System.Drawing.Size(138, 22);
        this.rSSFeedToolStripMenuItem.Text = "RSS feed";
        // 
        // nNTPToolStripMenuItem
        // 
        this.nNTPToolStripMenuItem.Name = "nNTPToolStripMenuItem";
        this.nNTPToolStripMenuItem.Size = new System.Drawing.Size(138, 22);
        this.nNTPToolStripMenuItem.Text = "NNTP";
        // 
        // editionToolStripMenuItem
        // 
        this.editionToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.selectToolStripMenuItem});
        this.editionToolStripMenuItem.Name = "editionToolStripMenuItem";
        this.editionToolStripMenuItem.Size = new System.Drawing.Size(40, 20);
        this.editionToolStripMenuItem.Text = "Edit";
        // 
        // selectToolStripMenuItem
        // 
        this.selectToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.allMessagesToolStripMenuItem});
        this.selectToolStripMenuItem.Name = "selectToolStripMenuItem";
        this.selectToolStripMenuItem.Size = new System.Drawing.Size(120, 22);
        this.selectToolStripMenuItem.Text = "Select";
        // 
        // allMessagesToolStripMenuItem
        // 
        this.allMessagesToolStripMenuItem.Name = "allMessagesToolStripMenuItem";
        this.allMessagesToolStripMenuItem.Size = new System.Drawing.Size(160, 22);
        this.allMessagesToolStripMenuItem.Text = "All messages";
        // 
        // optionsToolStripMenuItem
        // 
        this.optionsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.preferencesToolStripMenuItem});
        this.optionsToolStripMenuItem.Name = "optionsToolStripMenuItem";
        this.optionsToolStripMenuItem.Size = new System.Drawing.Size(62, 20);
        this.optionsToolStripMenuItem.Text = "Options";
        // 
        // preferencesToolStripMenuItem
        // 
        this.preferencesToolStripMenuItem.Name = "preferencesToolStripMenuItem";
        this.preferencesToolStripMenuItem.Size = new System.Drawing.Size(153, 22);
        this.preferencesToolStripMenuItem.Text = "Preferences";
        // 
        // helpToolStripMenuItem
        // 
        this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aboutNRSSToolStripMenuItem});
        this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
        this.helpToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
        this.helpToolStripMenuItem.Text = "Help";
        // 
        // aboutNRSSToolStripMenuItem
        // 
        this.aboutNRSSToolStripMenuItem.Name = "aboutNRSSToolStripMenuItem";
        this.aboutNRSSToolStripMenuItem.Size = new System.Drawing.Size(154, 22);
        this.aboutNRSSToolStripMenuItem.Text = "About NRSS";
        // 
        // splitContainer1
        // 
        this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
        this.splitContainer1.Location = new System.Drawing.Point(0, 49);
        this.splitContainer1.Name = "splitContainer1";
        // 
        // splitContainer1.Panel1
        // 
        this.splitContainer1.Panel1.Controls.Add(this.LeftTreeMenu);
        // 
        // splitContainer1.Panel2
        // 
        this.splitContainer1.Panel2.Controls.Add(this.splitContainer2);
        this.splitContainer1.Size = new System.Drawing.Size(866, 646);
        this.splitContainer1.SplitterDistance = 215;
        this.splitContainer1.TabIndex = 2;
        // 
        // splitContainer2
        // 
        this.splitContainer2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
        this.splitContainer2.Cursor = System.Windows.Forms.Cursors.Default;
        this.splitContainer2.Dock = System.Windows.Forms.DockStyle.Fill;
        this.splitContainer2.Location = new System.Drawing.Point(0, 0);
        this.splitContainer2.Name = "splitContainer2";
        this.splitContainer2.Orientation = System.Windows.Forms.Orientation.Horizontal;
        // 
        // splitContainer2.Panel1
        // 
        this.splitContainer2.Panel1.Controls.Add(this.RightListView);
        // 
        // splitContainer2.Panel2
        // 
        this.splitContainer2.Panel2.Controls.Add(this.splitContainer3);
        this.splitContainer2.Size = new System.Drawing.Size(647, 646);
        this.splitContainer2.SplitterDistance = 197;
        this.splitContainer2.TabIndex = 0;
        // 
        // RightListView
        // 
        this.RightListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnSubject,
            this.columnSender,
            this.columnDate,
            this.columnDescription,
            this.columnLink});
        this.RightListView.Dock = System.Windows.Forms.DockStyle.Fill;
        this.RightListView.FullRowSelect = true;
        this.RightListView.Location = new System.Drawing.Point(0, 0);
        this.RightListView.MultiSelect = false;
        this.RightListView.Name = "RightListView";
        this.RightListView.Size = new System.Drawing.Size(643, 193);
        this.RightListView.TabIndex = 0;
        this.RightListView.UseCompatibleStateImageBehavior = false;
        this.RightListView.View = System.Windows.Forms.View.Details;
        this.RightListView.SelectedIndexChanged += new System.EventHandler(this.RightListView_SelectedIndexChanged);
        // 
        // columnSubject
        // 
        this.columnSubject.Name = "columnSubject";
        this.columnSubject.Text = "Author";
        this.columnSubject.Width = 70;
        // 
        // columnSender
        // 
        this.columnSender.Name = "columnSender";
        this.columnSender.Text = "Title";
        this.columnSender.Width = 114;
        // 
        // columnDate
        // 
        this.columnDate.Name = "columnDate";
        this.columnDate.Text = "Date";
        this.columnDate.Width = 113;
        // 
        // columnDescription
        // 
        this.columnDescription.Name = "columnDescription";
        this.columnDescription.Text = "Description";
        this.columnDescription.Width = 190;
        // 
        // columnLink
        // 
        this.columnLink.Name = "columnLink";
        this.columnLink.Text = "Link";
        this.columnLink.Width = 149;
        // 
        // splitContainer3
        // 
        this.splitContainer3.Dock = System.Windows.Forms.DockStyle.Fill;
        this.splitContainer3.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
        this.splitContainer3.Location = new System.Drawing.Point(0, 0);
        this.splitContainer3.Name = "splitContainer3";
        this.splitContainer3.Orientation = System.Windows.Forms.Orientation.Horizontal;
        // 
        // splitContainer3.Panel1
        // 
        this.splitContainer3.Panel1.Controls.Add(this.labelTitleContent);
        this.splitContainer3.Panel1.Controls.Add(this.labelFromContent);
        this.splitContainer3.Panel1.Controls.Add(this.labelDateContent);
        this.splitContainer3.Panel1.Controls.Add(this.linkLabel);
        this.splitContainer3.Panel1.Controls.Add(this.labelLink);
        this.splitContainer3.Panel1.Controls.Add(this.labelDate);
        this.splitContainer3.Panel1.Controls.Add(this.labelFrom);
        this.splitContainer3.Panel1.Controls.Add(this.labelTitle);
        // 
        // splitContainer3.Panel2
        // 
        this.splitContainer3.Panel2.Controls.Add(this.webBrowser1);
        this.splitContainer3.Size = new System.Drawing.Size(643, 441);
        this.splitContainer3.SplitterDistance = 70;
        this.splitContainer3.TabIndex = 0;
        // 
        // labelTitleContent
        // 
        this.labelTitleContent.AutoSize = true;
        this.labelTitleContent.Location = new System.Drawing.Point(45, 5);
        this.labelTitleContent.Name = "labelTitleContent";
        this.labelTitleContent.Size = new System.Drawing.Size(27, 13);
        this.labelTitleContent.TabIndex = 7;
        this.labelTitleContent.Text = "N/A";
        // 
        // labelFromContent
        // 
        this.labelFromContent.AutoSize = true;
        this.labelFromContent.Location = new System.Drawing.Point(45, 21);
        this.labelFromContent.Name = "labelFromContent";
        this.labelFromContent.Size = new System.Drawing.Size(27, 13);
        this.labelFromContent.TabIndex = 6;
        this.labelFromContent.Text = "N/A";
        // 
        // labelDateContent
        // 
        this.labelDateContent.AutoSize = true;
        this.labelDateContent.Location = new System.Drawing.Point(45, 38);
        this.labelDateContent.Name = "labelDateContent";
        this.labelDateContent.Size = new System.Drawing.Size(27, 13);
        this.labelDateContent.TabIndex = 5;
        this.labelDateContent.Text = "N/A";
        // 
        // linkLabel
        // 
        this.linkLabel.AutoSize = true;
        this.linkLabel.CausesValidation = false;
        this.linkLabel.Location = new System.Drawing.Point(46, 55);
        this.linkLabel.Name = "linkLabel";
        this.linkLabel.Size = new System.Drawing.Size(27, 13);
        this.linkLabel.TabIndex = 4;
        this.linkLabel.TabStop = true;
        this.linkLabel.Text = "N/A";
        // 
        // labelLink
        // 
        this.labelLink.AutoSize = true;
        this.labelLink.Font = new System.Drawing.Font("Garamond", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
        this.labelLink.Location = new System.Drawing.Point(3, 55);
        this.labelLink.Name = "labelLink";
        this.labelLink.Size = new System.Drawing.Size(36, 14);
        this.labelLink.TabIndex = 3;
        this.labelLink.Text = "Link:";
        // 
        // labelDate
        // 
        this.labelDate.AutoSize = true;
        this.labelDate.Font = new System.Drawing.Font("Garamond", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
        this.labelDate.Location = new System.Drawing.Point(3, 38);
        this.labelDate.Name = "labelDate";
        this.labelDate.Size = new System.Drawing.Size(36, 14);
        this.labelDate.TabIndex = 2;
        this.labelDate.Text = "Date:";
        // 
        // labelFrom
        // 
        this.labelFrom.AutoSize = true;
        this.labelFrom.Font = new System.Drawing.Font("Garamond", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
        this.labelFrom.Location = new System.Drawing.Point(3, 21);
        this.labelFrom.Name = "labelFrom";
        this.labelFrom.Size = new System.Drawing.Size(41, 14);
        this.labelFrom.TabIndex = 1;
        this.labelFrom.Text = "From:";
        // 
        // labelTitle
        // 
        this.labelTitle.AutoSize = true;
        this.labelTitle.Font = new System.Drawing.Font("Garamond", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
        this.labelTitle.Location = new System.Drawing.Point(3, 4);
        this.labelTitle.Name = "labelTitle";
        this.labelTitle.Size = new System.Drawing.Size(37, 14);
        this.labelTitle.TabIndex = 0;
        this.labelTitle.Text = "Title:";
        // 
        // webBrowser1
        // 
        this.webBrowser1.Dock = System.Windows.Forms.DockStyle.Fill;
        this.webBrowser1.Location = new System.Drawing.Point(0, 0);
        this.webBrowser1.MinimumSize = new System.Drawing.Size(20, 20);
        this.webBrowser1.Name = "webBrowser1";
        this.webBrowser1.Size = new System.Drawing.Size(643, 367);
        this.webBrowser1.TabIndex = 1;
        // 
        // ToolBar
        // 
        this.ToolBar.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ReadText,
            this.toolStripSeparator1});
        this.ToolBar.Location = new System.Drawing.Point(0, 24);
        this.ToolBar.Name = "ToolBar";
        this.ToolBar.Size = new System.Drawing.Size(866, 25);
        this.ToolBar.TabIndex = 1;
        this.ToolBar.Text = "toolStrip1";
        // 
        // ReadText
        // 
        this.ReadText.CheckOnClick = true;
        this.ReadText.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
        this.ReadText.Image = ((System.Drawing.Image)(resources.GetObject("ReadText.Image")));
        this.ReadText.ImageTransparentColor = System.Drawing.Color.Magenta;
        this.ReadText.Name = "ReadText";
        this.ReadText.Size = new System.Drawing.Size(23, 22);
        this.ReadText.Text = "Start/Stop text reading";
        this.ReadText.ToolTipText = "Start/Stop text reading";
        this.ReadText.Click += new System.EventHandler(this.toolStripButton1_Click);
        // 
        // toolStripSeparator1
        // 
        this.toolStripSeparator1.Name = "toolStripSeparator1";
        this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
        // 
        // Form1
        // 
        this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
        this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
        this.ClientSize = new System.Drawing.Size(866, 695);
        this.Controls.Add(this.splitContainer1);
        this.Controls.Add(this.ToolBar);
        this.Controls.Add(this.menuStrip1);
        this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
        this.MainMenuStrip = this.menuStrip1;
        this.Name = "Form1";
        this.Text = "NRSS Client";
        this.Load += new System.EventHandler(this.Form1_Load);
        this.menuStrip1.ResumeLayout(false);
        this.menuStrip1.PerformLayout();
        this.splitContainer1.Panel1.ResumeLayout(false);
        this.splitContainer1.Panel2.ResumeLayout(false);
        this.splitContainer1.ResumeLayout(false);
        this.splitContainer2.Panel1.ResumeLayout(false);
        this.splitContainer2.Panel2.ResumeLayout(false);
        this.splitContainer2.ResumeLayout(false);
        this.splitContainer3.Panel1.ResumeLayout(false);
        this.splitContainer3.Panel1.PerformLayout();
        this.splitContainer3.Panel2.ResumeLayout(false);
        this.splitContainer3.ResumeLayout(false);
        this.ToolBar.ResumeLayout(false);
        this.ToolBar.PerformLayout();
        this.ResumeLayout(false);
        this.PerformLayout();

	}

	#endregion

      private System.Windows.Forms.MenuStrip menuStrip1;
      private System.Windows.Forms.ToolStripMenuItem fichierToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem editionToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem optionsToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem newFeedToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem rSSFeedToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem nNTPToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem selectToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem allMessagesToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem aboutNRSSToolStripMenuItem;
      private System.Windows.Forms.ToolStripMenuItem preferencesToolStripMenuItem;
      private System.Windows.Forms.SplitContainer splitContainer1;
      private System.Windows.Forms.SplitContainer splitContainer2;
      private System.Windows.Forms.ListView RightListView;
      private System.Windows.Forms.ColumnHeader columnAuthor;
      private System.Windows.Forms.ColumnHeader columnTitle;
      private System.Windows.Forms.ColumnHeader columnDate;
      private System.Windows.Forms.ColumnHeader columnDescription;
      private System.Windows.Forms.ColumnHeader columnLink;
      private System.Windows.Forms.TreeView LeftTreeMenu;
      private System.Windows.Forms.ColumnHeader columnSubject;
      private System.Windows.Forms.ColumnHeader columnSender;
      private System.Windows.Forms.SplitContainer splitContainer3;
      private System.Windows.Forms.ToolStrip ToolBar;
      private System.Windows.Forms.WebBrowser webBrowser1;
      private System.Windows.Forms.ToolStripButton ReadText;
      private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
      private System.Windows.Forms.Label labelTitle;
      private System.Windows.Forms.Label labelDate;
      private System.Windows.Forms.Label labelFrom;
      private System.Windows.Forms.Label labelLink;
      private System.Windows.Forms.LinkLabel linkLabel;
      private System.Windows.Forms.Label labelTitleContent;
      private System.Windows.Forms.Label labelFromContent;
      private System.Windows.Forms.Label labelDateContent;

}
}

