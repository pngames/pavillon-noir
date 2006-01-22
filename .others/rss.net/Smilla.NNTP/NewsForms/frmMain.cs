using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using Smilla.Net.NNTPClient;
using System.Threading;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;

namespace NewsForms
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class frmMain : System.Windows.Forms.Form
	{
		private System.Windows.Forms.Panel pnlAddressBar;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.TextBox txtServerName;
		private System.Windows.Forms.Button btnConnect;
		private System.Windows.Forms.ToolBar Toolbar;
		internal System.Windows.Forms.ImageList imageList;
		private System.Windows.Forms.ToolBarButton btnPostArticle;
		private System.Windows.Forms.Panel panel1;
		private System.Windows.Forms.TreeView trvGroups;
		private System.Windows.Forms.Splitter splitter1;
		private System.Windows.Forms.StatusBar statusBar;
		private System.Windows.Forms.StatusBarPanel statusMain;
		private System.Windows.Forms.Splitter splitter2;
		private System.Windows.Forms.Panel panel2;
		private System.Windows.Forms.ListView lvArticles;
		private AxSHDocVw.AxWebBrowser axWebBrowser;
		private System.ComponentModel.IContainer components;

		internal Session session;
		internal NewsGroupCollection groups;
		internal bool ready = false;
		private System.Windows.Forms.ColumnHeader colSubject;
		private System.Windows.Forms.ColumnHeader colFrom;
		private System.Windows.Forms.ColumnHeader colDate;

		private Hashtable articleCollections = new Hashtable();
		private string currentGroup;
		private System.Windows.Forms.ToolBarButton btnRefreshArticles;
		private ArticleCollection currentArticles;
		string srcPath = Application.StartupPath + @"\Temp";

		public frmMain()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			System.Resources.ResourceManager resources = new System.Resources.ResourceManager(typeof(frmMain));
			this.pnlAddressBar = new System.Windows.Forms.Panel();
			this.btnConnect = new System.Windows.Forms.Button();
			this.txtServerName = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.Toolbar = new System.Windows.Forms.ToolBar();
			this.btnPostArticle = new System.Windows.Forms.ToolBarButton();
			this.btnRefreshArticles = new System.Windows.Forms.ToolBarButton();
			this.imageList = new System.Windows.Forms.ImageList(this.components);
			this.panel1 = new System.Windows.Forms.Panel();
			this.lvArticles = new System.Windows.Forms.ListView();
			this.colSubject = new System.Windows.Forms.ColumnHeader();
			this.colFrom = new System.Windows.Forms.ColumnHeader();
			this.colDate = new System.Windows.Forms.ColumnHeader();
			this.splitter1 = new System.Windows.Forms.Splitter();
			this.trvGroups = new System.Windows.Forms.TreeView();
			this.statusBar = new System.Windows.Forms.StatusBar();
			this.statusMain = new System.Windows.Forms.StatusBarPanel();
			this.splitter2 = new System.Windows.Forms.Splitter();
			this.panel2 = new System.Windows.Forms.Panel();
			this.axWebBrowser = new AxSHDocVw.AxWebBrowser();
			this.pnlAddressBar.SuspendLayout();
			this.panel1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.statusMain)).BeginInit();
			this.panel2.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.axWebBrowser)).BeginInit();
			this.SuspendLayout();
			// 
			// pnlAddressBar
			// 
			this.pnlAddressBar.Controls.AddRange(new System.Windows.Forms.Control[] {
																						this.btnConnect,
																						this.txtServerName,
																						this.label1});
			this.pnlAddressBar.Dock = System.Windows.Forms.DockStyle.Top;
			this.pnlAddressBar.Location = new System.Drawing.Point(0, 39);
			this.pnlAddressBar.Name = "pnlAddressBar";
			this.pnlAddressBar.Size = new System.Drawing.Size(624, 32);
			this.pnlAddressBar.TabIndex = 18;
			this.pnlAddressBar.Paint += new System.Windows.Forms.PaintEventHandler(this.pnlAddressBar_Paint);
			// 
			// btnConnect
			// 
			this.btnConnect.Anchor = (System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right);
			this.btnConnect.Location = new System.Drawing.Point(544, 4);
			this.btnConnect.Name = "btnConnect";
			this.btnConnect.TabIndex = 2;
			this.btnConnect.Text = "Connect";
			this.btnConnect.Click += new System.EventHandler(this.btnConnect_Click);
			// 
			// txtServerName
			// 
			this.txtServerName.Anchor = ((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
				| System.Windows.Forms.AnchorStyles.Right);
			this.txtServerName.Location = new System.Drawing.Point(44, 5);
			this.txtServerName.Name = "txtServerName";
			this.txtServerName.Size = new System.Drawing.Size(496, 20);
			this.txtServerName.TabIndex = 1;
			this.txtServerName.Text = "msnews.microsoft.com";
			this.txtServerName.KeyDown += new System.Windows.Forms.KeyEventHandler(this.txtServerName_KeyDown);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(4, 9);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(41, 13);
			this.label1.TabIndex = 0;
			this.label1.Text = "Server:";
			// 
			// Toolbar
			// 
			this.Toolbar.Appearance = System.Windows.Forms.ToolBarAppearance.Flat;
			this.Toolbar.Buttons.AddRange(new System.Windows.Forms.ToolBarButton[] {
																					   this.btnPostArticle,
																					   this.btnRefreshArticles});
			this.Toolbar.DropDownArrows = true;
			this.Toolbar.ImageList = this.imageList;
			this.Toolbar.Name = "Toolbar";
			this.Toolbar.ShowToolTips = true;
			this.Toolbar.Size = new System.Drawing.Size(624, 39);
			this.Toolbar.TabIndex = 19;
			this.Toolbar.ButtonClick += new System.Windows.Forms.ToolBarButtonClickEventHandler(this.Toolbar_ButtonClick);
			// 
			// btnPostArticle
			// 
			this.btnPostArticle.ImageIndex = 0;
			this.btnPostArticle.Text = "New Post";
			// 
			// btnRefreshArticles
			// 
			this.btnRefreshArticles.ImageIndex = 1;
			this.btnRefreshArticles.Text = "Refresh";
			// 
			// imageList
			// 
			this.imageList.ColorDepth = System.Windows.Forms.ColorDepth.Depth8Bit;
			this.imageList.ImageSize = new System.Drawing.Size(16, 16);
			this.imageList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList.ImageStream")));
			this.imageList.TransparentColor = System.Drawing.Color.Transparent;
			// 
			// panel1
			// 
			this.panel1.Controls.AddRange(new System.Windows.Forms.Control[] {
																				 this.lvArticles,
																				 this.splitter1,
																				 this.trvGroups});
			this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
			this.panel1.Location = new System.Drawing.Point(0, 71);
			this.panel1.Name = "panel1";
			this.panel1.Size = new System.Drawing.Size(624, 189);
			this.panel1.TabIndex = 20;
			// 
			// lvArticles
			// 
			this.lvArticles.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
																						 this.colSubject,
																						 this.colFrom,
																						 this.colDate});
			this.lvArticles.Dock = System.Windows.Forms.DockStyle.Fill;
			this.lvArticles.FullRowSelect = true;
			this.lvArticles.HideSelection = false;
			this.lvArticles.Location = new System.Drawing.Point(248, 0);
			this.lvArticles.MultiSelect = false;
			this.lvArticles.Name = "lvArticles";
			this.lvArticles.Size = new System.Drawing.Size(376, 189);
			this.lvArticles.SmallImageList = this.imageList;
			this.lvArticles.TabIndex = 20;
			this.lvArticles.View = System.Windows.Forms.View.Details;
			this.lvArticles.Click += new System.EventHandler(this.lvArticles_Click);
			this.lvArticles.ItemActivate += new System.EventHandler(this.lvArticles_ItemActivate);
			this.lvArticles.SelectedIndexChanged += new System.EventHandler(this.lvArticles_SelectedIndexChanged);
			// 
			// colSubject
			// 
			this.colSubject.Text = "Subject";
			this.colSubject.Width = 203;
			// 
			// colFrom
			// 
			this.colFrom.Text = "From";
			this.colFrom.Width = 111;
			// 
			// colDate
			// 
			this.colDate.Text = "Date";
			// 
			// splitter1
			// 
			this.splitter1.Location = new System.Drawing.Point(244, 0);
			this.splitter1.Name = "splitter1";
			this.splitter1.Size = new System.Drawing.Size(4, 189);
			this.splitter1.TabIndex = 19;
			this.splitter1.TabStop = false;
			// 
			// trvGroups
			// 
			this.trvGroups.Dock = System.Windows.Forms.DockStyle.Left;
			this.trvGroups.HideSelection = false;
			this.trvGroups.ImageIndex = -1;
			this.trvGroups.Name = "trvGroups";
			this.trvGroups.SelectedImageIndex = -1;
			this.trvGroups.Size = new System.Drawing.Size(244, 189);
			this.trvGroups.TabIndex = 18;
			this.trvGroups.DoubleClick += new System.EventHandler(this.trvGroups_DoubleClick);
			this.trvGroups.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.trvGroups_AfterSelect);
			// 
			// statusBar
			// 
			this.statusBar.Location = new System.Drawing.Point(0, 407);
			this.statusBar.Name = "statusBar";
			this.statusBar.Panels.AddRange(new System.Windows.Forms.StatusBarPanel[] {
																						 this.statusMain});
			this.statusBar.ShowPanels = true;
			this.statusBar.Size = new System.Drawing.Size(624, 22);
			this.statusBar.TabIndex = 21;
			this.statusBar.Text = "statusBar1";
			// 
			// statusMain
			// 
			this.statusMain.AutoSize = System.Windows.Forms.StatusBarPanelAutoSize.Spring;
			this.statusMain.Text = "Disconnected";
			this.statusMain.Width = 608;
			// 
			// splitter2
			// 
			this.splitter2.Dock = System.Windows.Forms.DockStyle.Top;
			this.splitter2.Location = new System.Drawing.Point(0, 260);
			this.splitter2.Name = "splitter2";
			this.splitter2.Size = new System.Drawing.Size(624, 4);
			this.splitter2.TabIndex = 23;
			this.splitter2.TabStop = false;
			// 
			// panel2
			// 
			this.panel2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.panel2.Controls.AddRange(new System.Windows.Forms.Control[] {
																				 this.axWebBrowser});
			this.panel2.Dock = System.Windows.Forms.DockStyle.Fill;
			this.panel2.Location = new System.Drawing.Point(0, 264);
			this.panel2.Name = "panel2";
			this.panel2.Size = new System.Drawing.Size(624, 143);
			this.panel2.TabIndex = 24;
			// 
			// axWebBrowser
			// 
			this.axWebBrowser.ContainingControl = this;
			this.axWebBrowser.Dock = System.Windows.Forms.DockStyle.Fill;
			this.axWebBrowser.Enabled = true;
			this.axWebBrowser.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axWebBrowser.OcxState")));
			this.axWebBrowser.Size = new System.Drawing.Size(620, 139);
			this.axWebBrowser.TabIndex = 0;
			// 
			// frmMain
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(624, 429);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.panel2,
																		  this.splitter2,
																		  this.statusBar,
																		  this.panel1,
																		  this.pnlAddressBar,
																		  this.Toolbar});
			this.Name = "frmMain";
			this.Text = "Smilla News Reader";
			this.Load += new System.EventHandler(this.frmMain_Load);
			this.pnlAddressBar.ResumeLayout(false);
			this.panel1.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.statusMain)).EndInit();
			this.panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.axWebBrowser)).EndInit();
			this.ResumeLayout(false);

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new frmMain());
		}

		private void btnConnect_Click(object sender, System.EventArgs e)
		{
			this.Connect();
		}

		private void Connect()
		{
			try
			{
				statusMain.Text = "Connecting";
				articleCollections.Clear();
				session = new Session(txtServerName.Text);
				StatusWindow getGroups = new StatusWindow();
				this.ready = false;
				ThreadPool.QueueUserWorkItem(new WaitCallback(this.GetGroups));
				getGroups.ShowDialog(this);
				lvArticles.Items.Clear();
				ClearBrowser();
				FillNewsGroups(this.groups);
				statusMain.Text = "Connected";
			}
			catch 
			{
				MessageBox.Show(this, "Cannot connect to the specified server!", "Connection failed", MessageBoxButtons.OK, MessageBoxIcon.Error);
			}
		}

		private void GetArticles(object groupName)
		{
			ArticleCollection articles = groups[(string)groupName].GetArticles(true, 100);
			articleCollections[groupName] = articles;
			this.ready = true;
		}

		private void FillArticles(ArticleCollection articles)
		{
//			lvArticles.Clear();
			lvArticles.Items.Clear();
			lvArticles.BeginUpdate();
			foreach (string messageID in articles)
			{
				ListViewItem item = new ListViewItem(new string[] {articles[messageID].Header.Subject, articles[messageID].Header.From, articles[messageID].Header.Date.ToLocalTime().ToString()}, (articles[messageID].Body == null)?2:3);
				item.Tag = messageID;
				lvArticles.Items.Add(item);
			}
			lvArticles.EndUpdate();
		}

		private void GetGroups(object state)
		{
			groups = session.GetNewsGroups();
			this.ready = true;
		}

		private void FillNewsGroups(NewsGroupCollection news)
		{
			trvGroups.Nodes.Clear();
			trvGroups.BeginUpdate();
			trvGroups.Nodes.Add(txtServerName.Text);
			foreach (string name in news)
			{
				trvGroups.Nodes[0].Nodes.Add(name);
			}
			trvGroups.EndUpdate();
		}

		private void txtServerName_KeyDown(object sender, System.Windows.Forms.KeyEventArgs e)
		{
			if (e.KeyCode == Keys.Return)
				this.Connect();
		}

		private void trvGroups_AfterSelect(object sender, System.Windows.Forms.TreeViewEventArgs e)
		{
			if (trvGroups.SelectedNode != null && trvGroups.SelectedNode.Parent != null)
			{
				currentGroup = trvGroups.SelectedNode.Text;
				if (articleCollections[trvGroups.SelectedNode.Text] == null)
				{
					ReceiveArticles();
				}
				currentArticles = (ArticleCollection)articleCollections[currentGroup];
				FillArticles(currentArticles);
				this.Text = String.Format("{0} - Smilla News Reader", trvGroups.SelectedNode.Text);
			}
		}

		private void trvGroups_DoubleClick(object sender, System.EventArgs e)
		{
//			if (trvGroups.SelectedNode != null && trvGroups.SelectedNode.Parent != null)
//			{
//				currentGroup = trvGroups.SelectedNode.Text;
//				if (articleCollections[trvGroups.SelectedNode.Text] == null)
//				{
//					ReceiveArticles();
//				}
//				currentArticles = (ArticleCollection)articleCollections[currentGroup];
//				FillArticles(currentArticles);
//				this.Text = String.Format("{0} - Smilla News Reader", trvGroups.SelectedNode.Text);
//			}
		}

		private void ReceiveArticles()
		{
			StatusWindow waitArticles = new StatusWindow();
			waitArticles.StatusMessage = "Receiving articles from server...";
			waitArticles.Text = "Receiving articles";
			this.ready = false;
			ThreadPool.QueueUserWorkItem(new WaitCallback(this.GetArticles), currentGroup);
			waitArticles.ShowDialog(this);
		}

		private void lvArticles_SelectedIndexChanged(object sender, System.EventArgs e)
		{
//			if (lvArticles.SelectedItems.Count > 0)
//			{
//				Article article = currentArticles[lvArticles.SelectedItems[0].Tag.ToString()];
//				if (article.Body == null)
//				{
//					this.Cursor = Cursors.WaitCursor;
//					article.RetrieveBody();
//					lvArticles.SelectedItems[0].ImageIndex = 3;
//					this.Cursor = Cursors.Default;
//				}
//				if (article.Body.HtmlBodyPart != null)
//					WriteHtmlToBrowser(article.Body.HtmlBodyPart.DecodedText);
//				else
//					WriteTextToBrowser(article.Body.TextBodyPart.DecodedText);
//			}
		}

		private void ClearBrowser()
		{
			mshtml.IHTMLDocument2 doc = (mshtml.IHTMLDocument2)axWebBrowser.Document;
			doc.write("");
			doc.close();
		}

		private void WriteHtmlToBrowser(string text)
		{
			mshtml.IHTMLDocument2 doc = (mshtml.IHTMLDocument2)axWebBrowser.Document;
			doc.write("");
			doc.close();
			doc.write(text);
			doc.body.style.fontFamily = "Verdana";
		}

		private void WriteTextToBrowser(string text)
		{
			mshtml.IHTMLDocument2 doc = (mshtml.IHTMLDocument2)axWebBrowser.Document;
			doc.write("");
			doc.close();
			doc.writeln("<pre>");
			doc.writeln(text);
			doc.writeln("</pre>");
			doc.body.style.fontFamily = "Verdana";
		}

		private void frmMain_Load(object sender, System.EventArgs e)
		{
			string blankUrl = "about:blank";
			object nullObj = null;
			axWebBrowser.Navigate(blankUrl,ref nullObj,ref nullObj,ref nullObj,ref nullObj);
		}

		private void Toolbar_ButtonClick(object sender, System.Windows.Forms.ToolBarButtonClickEventArgs e)
		{
			if (e.Button == btnRefreshArticles)
			{
				this.ReceiveArticles();
				currentArticles = (ArticleCollection)articleCollections[currentGroup];
				FillArticles(currentArticles);
				return;
			}
			if (e.Button == btnPostArticle)
			{
				PostingForm postingForm = new PostingForm();
				if (currentGroup != "")
					postingForm.txtNewsgroups.Text = currentGroup;
				postingForm.ParentFrm = this;
				postingForm.Show();
				return;
			}
		}

		private void lvArticles_ItemActivate(object sender, System.EventArgs e)
		{
//			if (lvArticles.SelectedItems.Count > 0)
//			{
//				Article article = currentArticles[lvArticles.SelectedItems[0].Tag.ToString()];
//				if (article.Body == null)
//				{
//					this.Cursor = Cursors.WaitCursor;
//					article.RetrieveBody();
//					lvArticles.SelectedItems[0].ImageIndex = 3;
//					this.Cursor = Cursors.Default;
//				}
//				if (article.Body.HtmlBodyPart != null)
//					WriteHtmlToBrowser(article.Body.HtmlBodyPart.DecodedText);
//				else
//					WriteTextToBrowser(article.Body.TextBodyPart.DecodedText);
//			}		
		}

		private void pnlAddressBar_Paint(object sender, System.Windows.Forms.PaintEventArgs e)
		{
			ControlPaint.DrawBorder3D(e.Graphics, e.ClipRectangle, Border3DStyle.Etched, Border3DSide.Top | Border3DSide.Bottom);		
		}

		private void lvArticles_Click(object sender, System.EventArgs e)
		{
			if (lvArticles.SelectedItems.Count > 0)
			{
				Article article = currentArticles[lvArticles.SelectedItems[0].Tag.ToString()];
				if (article.Body == null)
				{
					this.Cursor = Cursors.WaitCursor;
					article.RetrieveBody();
					lvArticles.SelectedItems[0].ImageIndex = 3;
					this.Cursor = Cursors.Default;
				}
				if (article.Body.HtmlBodyPart != null)
				{
					WriteHtmlToBrowser(ProcessLinkedFiles(article));
				}
				else
					WriteTextToBrowser(article.Body.TextBodyPart.DecodedText);
			}				
		}

		private string ProcessLinkedFiles(Article article)
		{
			IBodyPart htmlPart = article.Body.HtmlBodyPart;
			StringBuilder result = new StringBuilder(htmlPart.DecodedText);
			MatchCollection matches = Regex.Matches(htmlPart.DecodedText, "cid:([^\"]+)", RegexOptions.Multiline);
			if (!Directory.Exists(srcPath))
				Directory.CreateDirectory(srcPath);
			foreach (Match match in matches)
			{
				string srcURL = match.Value;
				string contentID = match.Groups[1].Value;
				IBodyPart dataPart = Utils.FindBodyPartsByContentID("<" + contentID + ">", (IBodyPart)article.Body);
				string fileExt = "";
				switch (dataPart.ContentType)
				{
					case "image/jpeg":
						fileExt = ".jpeg";
						break;
					case "image/gif":
						fileExt = ".gif";
						break;
				}
				string fileName = srcPath + "\\" + contentID + fileExt;
				if (!File.Exists(fileName))
				{
					dataPart.Save(fileName);
				}
				result = result.Replace(srcURL, fileName);
			}
			return result.ToString();
		}
	}
}
