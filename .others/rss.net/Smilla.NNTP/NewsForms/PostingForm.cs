using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using Smilla.Net.NNTPClient;

namespace NewsForms
{
	/// <summary>
	/// Summary description for PostingForm.
	/// </summary>
	public class PostingForm : System.Windows.Forms.Form
	{
		private System.Windows.Forms.ToolBar ToolBar;
		internal System.Windows.Forms.ImageList imageList;
		private System.Windows.Forms.ToolBarButton btnSend;
		private System.Windows.Forms.Panel panel1;
		private System.Windows.Forms.Panel panel2;
		private System.Windows.Forms.StatusBar statusBar1;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.TextBox txtFrom;
		internal System.Windows.Forms.TextBox txtNewsgroups;
		private System.Windows.Forms.TextBox txtSubject;
		private System.Windows.Forms.TextBox txtArticleText;
		private System.ComponentModel.IContainer components;

		internal frmMain ParentFrm;
		internal string Newsgroups;


		public PostingForm()
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
				if(components != null)
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
			System.Resources.ResourceManager resources = new System.Resources.ResourceManager(typeof(PostingForm));
			this.ToolBar = new System.Windows.Forms.ToolBar();
			this.btnSend = new System.Windows.Forms.ToolBarButton();
			this.imageList = new System.Windows.Forms.ImageList(this.components);
			this.panel1 = new System.Windows.Forms.Panel();
			this.txtSubject = new System.Windows.Forms.TextBox();
			this.txtNewsgroups = new System.Windows.Forms.TextBox();
			this.txtFrom = new System.Windows.Forms.TextBox();
			this.label3 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.label1 = new System.Windows.Forms.Label();
			this.panel2 = new System.Windows.Forms.Panel();
			this.txtArticleText = new System.Windows.Forms.TextBox();
			this.statusBar1 = new System.Windows.Forms.StatusBar();
			this.panel1.SuspendLayout();
			this.panel2.SuspendLayout();
			this.SuspendLayout();
			// 
			// ToolBar
			// 
			this.ToolBar.Appearance = System.Windows.Forms.ToolBarAppearance.Flat;
			this.ToolBar.Buttons.AddRange(new System.Windows.Forms.ToolBarButton[] {
																					   this.btnSend});
			this.ToolBar.DropDownArrows = true;
			this.ToolBar.ImageList = this.imageList;
			this.ToolBar.Name = "ToolBar";
			this.ToolBar.ShowToolTips = true;
			this.ToolBar.Size = new System.Drawing.Size(576, 39);
			this.ToolBar.TabIndex = 0;
			this.ToolBar.ButtonClick += new System.Windows.Forms.ToolBarButtonClickEventHandler(this.ToolBar_ButtonClick);
			// 
			// btnSend
			// 
			this.btnSend.ImageIndex = 4;
			this.btnSend.Text = "Send";
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
																				 this.txtSubject,
																				 this.txtNewsgroups,
																				 this.txtFrom,
																				 this.label3,
																				 this.label2,
																				 this.label1});
			this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
			this.panel1.Location = new System.Drawing.Point(0, 39);
			this.panel1.Name = "panel1";
			this.panel1.Size = new System.Drawing.Size(576, 77);
			this.panel1.TabIndex = 1;
			this.panel1.Paint += new System.Windows.Forms.PaintEventHandler(this.panel1_Paint);
			// 
			// txtSubject
			// 
			this.txtSubject.Anchor = ((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
				| System.Windows.Forms.AnchorStyles.Right);
			this.txtSubject.Location = new System.Drawing.Point(88, 52);
			this.txtSubject.Name = "txtSubject";
			this.txtSubject.Size = new System.Drawing.Size(480, 20);
			this.txtSubject.TabIndex = 5;
			this.txtSubject.Text = "";
			// 
			// txtNewsgroups
			// 
			this.txtNewsgroups.Anchor = ((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
				| System.Windows.Forms.AnchorStyles.Right);
			this.txtNewsgroups.Location = new System.Drawing.Point(88, 28);
			this.txtNewsgroups.Name = "txtNewsgroups";
			this.txtNewsgroups.Size = new System.Drawing.Size(480, 20);
			this.txtNewsgroups.TabIndex = 4;
			this.txtNewsgroups.Text = "";
			// 
			// txtFrom
			// 
			this.txtFrom.Anchor = ((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
				| System.Windows.Forms.AnchorStyles.Right);
			this.txtFrom.Location = new System.Drawing.Point(88, 4);
			this.txtFrom.Name = "txtFrom";
			this.txtFrom.Size = new System.Drawing.Size(480, 20);
			this.txtFrom.TabIndex = 3;
			this.txtFrom.Text = "";
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(12, 56);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(45, 13);
			this.label3.TabIndex = 2;
			this.label3.Text = "Subject:";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(12, 32);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(70, 13);
			this.label2.TabIndex = 1;
			this.label2.Text = "Newsgroups:";
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(12, 8);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(34, 13);
			this.label1.TabIndex = 0;
			this.label1.Text = "From:";
			// 
			// panel2
			// 
			this.panel2.Controls.AddRange(new System.Windows.Forms.Control[] {
																				 this.txtArticleText,
																				 this.statusBar1});
			this.panel2.Dock = System.Windows.Forms.DockStyle.Fill;
			this.panel2.Location = new System.Drawing.Point(0, 116);
			this.panel2.Name = "panel2";
			this.panel2.Size = new System.Drawing.Size(576, 225);
			this.panel2.TabIndex = 2;
			// 
			// txtArticleText
			// 
			this.txtArticleText.Dock = System.Windows.Forms.DockStyle.Fill;
			this.txtArticleText.Multiline = true;
			this.txtArticleText.Name = "txtArticleText";
			this.txtArticleText.Size = new System.Drawing.Size(576, 203);
			this.txtArticleText.TabIndex = 1;
			this.txtArticleText.Text = "";
			// 
			// statusBar1
			// 
			this.statusBar1.Location = new System.Drawing.Point(0, 203);
			this.statusBar1.Name = "statusBar1";
			this.statusBar1.ShowPanels = true;
			this.statusBar1.Size = new System.Drawing.Size(576, 22);
			this.statusBar1.TabIndex = 0;
			this.statusBar1.Text = "statusBar1";
			// 
			// PostingForm
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(576, 341);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.panel2,
																		  this.panel1,
																		  this.ToolBar});
			this.Name = "PostingForm";
			this.Text = "New Message";
			this.panel1.ResumeLayout(false);
			this.panel2.ResumeLayout(false);
			this.ResumeLayout(false);

		}
		#endregion

		private void ToolBar_ButtonClick(object sender, System.Windows.Forms.ToolBarButtonClickEventArgs e)
		{
			if (e.Button == btnSend)
			{
				this.Cursor = Cursors.WaitCursor;
				DoPost();
				this.Cursor = Cursors.Default;
			}
		}

		private void DoPost()
		{
			if (txtNewsgroups.Text != "")
			{
				Article article = this.ParentFrm.session.CreateArticle();
				article.Header.From = txtFrom.Text;
				article.Header.Subject = txtSubject.Text;
				article.Header.NewsGroups = new String[] { txtNewsgroups.Text};
				article.Body.Text = txtArticleText.Text;
				this.ParentFrm.session.PostArticle(article);
				this.Close();
			}
			else
				MessageBox.Show(this, "You must specify one or more newsgroups to post to!", "The message couldn't be sent", MessageBoxButtons.OK, MessageBoxIcon.Error);
		}

		private void panel1_Paint(object sender, System.Windows.Forms.PaintEventArgs e)
		{
			ControlPaint.DrawBorder3D(e.Graphics, e.ClipRectangle, Border3DStyle.Etched, Border3DSide.Top | Border3DSide.Bottom);
		}
	}
}
