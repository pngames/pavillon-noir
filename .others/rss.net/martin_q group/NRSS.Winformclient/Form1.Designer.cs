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
        System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
        
        /* Test */
        //////////////////////////////////////////////////////////////////////////
        System.Windows.Forms.TreeNode treeNode1 = new System.Windows.Forms.TreeNode("RSS Test 1");
        System.Windows.Forms.TreeNode treeNode2 = new System.Windows.Forms.TreeNode("RSS Test 2");
        System.Windows.Forms.TreeNode treeNode3 = new System.Windows.Forms.TreeNode("RSS Test 3");
        System.Windows.Forms.TreeNode treeNode4 = new System.Windows.Forms.TreeNode("RSS Feeds", new System.Windows.Forms.TreeNode[] {
            treeNode1,
            treeNode2,
            treeNode3});
        System.Windows.Forms.ListViewItem listViewItem1 = new System.Windows.Forms.ListViewItem(new string[] {
            "Sujet",
            "From:",
            "25/02/2006"}, -1);
        //////////////////////////////////////////////////////////////////////////
        
        
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
        this.treeView1 = new System.Windows.Forms.TreeView();
        this.splitContainer2 = new System.Windows.Forms.SplitContainer();
        this.listView1 = new System.Windows.Forms.ListView();
        this.columnSubject = new System.Windows.Forms.ColumnHeader();
        this.columnSender = new System.Windows.Forms.ColumnHeader();
        this.columnDate = new System.Windows.Forms.ColumnHeader();
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
        this.splitContainer1.Panel1.Controls.Add(this.treeView1);
        // 
        // splitContainer1.Panel2
        // 
        this.splitContainer1.Panel2.Controls.Add(this.splitContainer2);
        this.splitContainer1.Size = new System.Drawing.Size(866, 646);
        this.splitContainer1.SplitterDistance = 251;
        this.splitContainer1.TabIndex = 2;
        // 
        // treeView1
        // 
        this.treeView1.Dock = System.Windows.Forms.DockStyle.Fill;
        this.treeView1.Location = new System.Drawing.Point(0, 0);
        this.treeView1.Name = "treeView1";
        treeNode1.Name = "RSSTest1";
        treeNode1.Text = "RSS Test 1";
        treeNode2.Name = "RSSTest2";
        treeNode2.Text = "RSS Test 2";
        treeNode3.Name = "RSSTest3";
        treeNode3.Text = "RSS Test 3";
        treeNode4.Name = "RssFeeds";
        treeNode4.Text = "RSS Feeds";
        this.treeView1.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
            treeNode4});
        this.treeView1.Size = new System.Drawing.Size(251, 646);
        this.treeView1.TabIndex = 0;
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
        this.splitContainer2.Panel1.Controls.Add(this.listView1);
        // 
        // splitContainer2.Panel2
        // 
        this.splitContainer2.Panel2.Controls.Add(this.webBrowser1);
        this.splitContainer2.Size = new System.Drawing.Size(611, 646);
        this.splitContainer2.SplitterDistance = 251;
        this.splitContainer2.TabIndex = 0;
        // 
        // listView1
        // 
        this.listView1.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnSubject,
            this.columnSender,
            this.columnDate});
        this.listView1.Dock = System.Windows.Forms.DockStyle.Fill;
        this.listView1.Items.AddRange(new System.Windows.Forms.ListViewItem[] {
            listViewItem1});
        this.listView1.Location = new System.Drawing.Point(0, 0);
        this.listView1.Name = "listView1";
        this.listView1.Size = new System.Drawing.Size(607, 247);
        this.listView1.TabIndex = 0;
        this.listView1.UseCompatibleStateImageBehavior = false;
        this.listView1.View = System.Windows.Forms.View.Details;
        // 
        // columnSubject
        // 
        this.columnSubject.Name = "columnSubject";
        this.columnSubject.Text = "Subject";
        this.columnSubject.Width = 70;
        // 
        // columnSender
        // 
        this.columnSender.Name = "columnSender";
        this.columnSender.Text = "Sender";
        this.columnSender.Width = 244;
        // 
        // columnDate
        // 
        this.columnDate.Name = "columnDate";
        this.columnDate.Text = "Date";
        this.columnDate.Width = 189;
        // 
        // webBrowser1
        // 
        this.webBrowser1.AllowNavigation = false;
        this.webBrowser1.Dock = System.Windows.Forms.DockStyle.Fill;
        this.webBrowser1.Location = new System.Drawing.Point(0, 0);
        this.webBrowser1.MinimumSize = new System.Drawing.Size(20, 20);
        this.webBrowser1.Name = "webBrowser1";
        this.webBrowser1.Size = new System.Drawing.Size(607, 387);
        this.webBrowser1.TabIndex = 0;
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
      private System.Windows.Forms.TreeView treeView1;
      private System.Windows.Forms.ListView listView1;
      private System.Windows.Forms.ColumnHeader columnSubject;
      private System.Windows.Forms.ColumnHeader columnSender;
      private System.Windows.Forms.ColumnHeader columnDate;

}
}

