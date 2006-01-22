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
        System.Windows.Forms.TreeNode treeNode5 = new System.Windows.Forms.TreeNode("RSS Test 1");
        System.Windows.Forms.TreeNode treeNode6 = new System.Windows.Forms.TreeNode("RSS Test 2");
        System.Windows.Forms.TreeNode treeNode7 = new System.Windows.Forms.TreeNode("RSS Test 3");
        System.Windows.Forms.TreeNode treeNode8 = new System.Windows.Forms.TreeNode("RSS", new System.Windows.Forms.TreeNode[] {
            treeNode5,
            treeNode6,
            treeNode7});
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
        this.toolStrip1 = new System.Windows.Forms.ToolStrip();
        this.newToolStripButton = new System.Windows.Forms.ToolStripButton();
        this.openToolStripButton = new System.Windows.Forms.ToolStripButton();
        this.saveToolStripButton = new System.Windows.Forms.ToolStripButton();
        this.toolStripSeparator = new System.Windows.Forms.ToolStripSeparator();
        this.cutToolStripButton = new System.Windows.Forms.ToolStripButton();
        this.copyToolStripButton = new System.Windows.Forms.ToolStripButton();
        this.pasteToolStripButton = new System.Windows.Forms.ToolStripButton();
        this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
        this.helpToolStripButton = new System.Windows.Forms.ToolStripButton();
        this.splitContainer1 = new System.Windows.Forms.SplitContainer();
        this.splitContainer2 = new System.Windows.Forms.SplitContainer();
        this.RightListView = new System.Windows.Forms.ListView();
        this.columnSubject = new System.Windows.Forms.ColumnHeader();
        this.columnSender = new System.Windows.Forms.ColumnHeader();
        this.columnDate = new System.Windows.Forms.ColumnHeader();
        this.columnDescription = new System.Windows.Forms.ColumnHeader();
        this.columnLink = new System.Windows.Forms.ColumnHeader();
        this.webBrowser1 = new System.Windows.Forms.WebBrowser();
        this.menuStrip1.SuspendLayout();
        this.toolStrip1.SuspendLayout();
        this.splitContainer1.Panel1.SuspendLayout();
        this.splitContainer1.Panel2.SuspendLayout();
        this.splitContainer1.SuspendLayout();
        this.splitContainer2.Panel1.SuspendLayout();
        this.splitContainer2.Panel2.SuspendLayout();
        this.splitContainer2.SuspendLayout();
        this.SuspendLayout();
        // 
        // LeftTreeMenu
        // 
        this.LeftTreeMenu.Dock = System.Windows.Forms.DockStyle.Fill;
        this.LeftTreeMenu.Location = new System.Drawing.Point(0, 0);
        this.LeftTreeMenu.Name = "LeftTreeMenu";
        treeNode5.Name = "RSSTest1";
        treeNode5.Text = "RSS Test 1";
        treeNode6.Name = "RSSTest2";
        treeNode6.Text = "RSS Test 2";
        treeNode7.Name = "RSSTest3";
        treeNode7.Text = "RSS Test 3";
        treeNode8.Name = "RssFeeds";
        treeNode8.Text = "RSS";
        this.LeftTreeMenu.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
            treeNode8});
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
        // toolStrip1
        // 
        this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripButton,
            this.openToolStripButton,
            this.saveToolStripButton,
            this.toolStripSeparator,
            this.cutToolStripButton,
            this.copyToolStripButton,
            this.pasteToolStripButton,
            this.toolStripSeparator1,
            this.helpToolStripButton});
        this.toolStrip1.Location = new System.Drawing.Point(0, 24);
        this.toolStrip1.Name = "toolStrip1";
        this.toolStrip1.Size = new System.Drawing.Size(866, 25);
        this.toolStrip1.TabIndex = 1;
        this.toolStrip1.Text = "toolStrip1";
        // 
        // newToolStripButton
        // 
        this.newToolStripButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
        this.newToolStripButton.Image = ((System.Drawing.Image)(resources.GetObject("newToolStripButton.Image")));
        this.newToolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
        this.newToolStripButton.Name = "newToolStripButton";
        this.newToolStripButton.Size = new System.Drawing.Size(23, 22);
        this.newToolStripButton.Text = "&New";
        // 
        // openToolStripButton
        // 
        this.openToolStripButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
        this.openToolStripButton.Image = ((System.Drawing.Image)(resources.GetObject("openToolStripButton.Image")));
        this.openToolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
        this.openToolStripButton.Name = "openToolStripButton";
        this.openToolStripButton.Size = new System.Drawing.Size(23, 22);
        this.openToolStripButton.Text = "&Open";
        // 
        // saveToolStripButton
        // 
        this.saveToolStripButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
        this.saveToolStripButton.Image = ((System.Drawing.Image)(resources.GetObject("saveToolStripButton.Image")));
        this.saveToolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
        this.saveToolStripButton.Name = "saveToolStripButton";
        this.saveToolStripButton.Size = new System.Drawing.Size(23, 22);
        this.saveToolStripButton.Text = "&Save";
        // 
        // toolStripSeparator
        // 
        this.toolStripSeparator.Name = "toolStripSeparator";
        this.toolStripSeparator.Size = new System.Drawing.Size(6, 25);
        // 
        // cutToolStripButton
        // 
        this.cutToolStripButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
        this.cutToolStripButton.Image = ((System.Drawing.Image)(resources.GetObject("cutToolStripButton.Image")));
        this.cutToolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
        this.cutToolStripButton.Name = "cutToolStripButton";
        this.cutToolStripButton.Size = new System.Drawing.Size(23, 22);
        this.cutToolStripButton.Text = "C&ut";
        // 
        // copyToolStripButton
        // 
        this.copyToolStripButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
        this.copyToolStripButton.Image = ((System.Drawing.Image)(resources.GetObject("copyToolStripButton.Image")));
        this.copyToolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
        this.copyToolStripButton.Name = "copyToolStripButton";
        this.copyToolStripButton.Size = new System.Drawing.Size(23, 22);
        this.copyToolStripButton.Text = "&Copy";
        // 
        // pasteToolStripButton
        // 
        this.pasteToolStripButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
        this.pasteToolStripButton.Image = ((System.Drawing.Image)(resources.GetObject("pasteToolStripButton.Image")));
        this.pasteToolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
        this.pasteToolStripButton.Name = "pasteToolStripButton";
        this.pasteToolStripButton.Size = new System.Drawing.Size(23, 22);
        this.pasteToolStripButton.Text = "&Paste";
        // 
        // toolStripSeparator1
        // 
        this.toolStripSeparator1.Name = "toolStripSeparator1";
        this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
        // 
        // helpToolStripButton
        // 
        this.helpToolStripButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
        this.helpToolStripButton.Image = ((System.Drawing.Image)(resources.GetObject("helpToolStripButton.Image")));
        this.helpToolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
        this.helpToolStripButton.Name = "helpToolStripButton";
        this.helpToolStripButton.Size = new System.Drawing.Size(23, 22);
        this.helpToolStripButton.Text = "He&lp";
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
        this.splitContainer2.Panel2.Controls.Add(this.webBrowser1);
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
        // 
        // webBrowser1
        // 
        this.webBrowser1.Dock = System.Windows.Forms.DockStyle.Fill;
        this.webBrowser1.Location = new System.Drawing.Point(0, 0);
        this.webBrowser1.MinimumSize = new System.Drawing.Size(20, 20);
        this.webBrowser1.Name = "webBrowser1";
        this.webBrowser1.Size = new System.Drawing.Size(643, 441);
        this.webBrowser1.TabIndex = 0;
        this.webBrowser1.Navigated += new System.Windows.Forms.WebBrowserNavigatedEventHandler(this.webBrowser1_Navigated);
        // 
        // Form1
        // 
        this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
        this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
        this.ClientSize = new System.Drawing.Size(866, 695);
        this.Controls.Add(this.splitContainer1);
        this.Controls.Add(this.toolStrip1);
        this.Controls.Add(this.menuStrip1);
        this.MainMenuStrip = this.menuStrip1;
        this.Name = "Form1";
        this.Text = "NRSS Client";
        this.menuStrip1.ResumeLayout(false);
        this.menuStrip1.PerformLayout();
        this.toolStrip1.ResumeLayout(false);
        this.toolStrip1.PerformLayout();
        this.splitContainer1.Panel1.ResumeLayout(false);
        this.splitContainer1.Panel2.ResumeLayout(false);
        this.splitContainer1.ResumeLayout(false);
        this.splitContainer2.Panel1.ResumeLayout(false);
        this.splitContainer2.Panel2.ResumeLayout(false);
        this.splitContainer2.ResumeLayout(false);
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
      private System.Windows.Forms.ToolStrip toolStrip1;
      private System.Windows.Forms.ToolStripButton newToolStripButton;
      private System.Windows.Forms.ToolStripButton openToolStripButton;
      private System.Windows.Forms.ToolStripButton saveToolStripButton;
      private System.Windows.Forms.ToolStripSeparator toolStripSeparator;
      private System.Windows.Forms.ToolStripButton cutToolStripButton;
      private System.Windows.Forms.ToolStripButton copyToolStripButton;
      private System.Windows.Forms.ToolStripButton pasteToolStripButton;
      private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
      private System.Windows.Forms.ToolStripButton helpToolStripButton;
      private System.Windows.Forms.SplitContainer splitContainer1;
      private System.Windows.Forms.SplitContainer splitContainer2;
      private System.Windows.Forms.WebBrowser webBrowser1;
      private System.Windows.Forms.ListView RightListView;
      private System.Windows.Forms.ColumnHeader columnAuthor;
      private System.Windows.Forms.ColumnHeader columnTitle;
      private System.Windows.Forms.ColumnHeader columnDate;
      private System.Windows.Forms.ColumnHeader columnDescription;
      private System.Windows.Forms.ColumnHeader columnLink;
      private System.Windows.Forms.TreeView LeftTreeMenu;
      private System.Windows.Forms.ColumnHeader columnSubject;
      private System.Windows.Forms.ColumnHeader columnSender;

}
}

