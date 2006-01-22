using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace NewsForms
{
	/// <summary>
	/// Summary description for frmGetGroups.
	/// </summary>
	public class StatusWindow : System.Windows.Forms.Form
	{
		internal System.Windows.Forms.ProgressBar progressBar;
		internal System.Windows.Forms.Timer tmrGetGroups;
		private System.ComponentModel.IContainer components;
		private System.Windows.Forms.Label lblStatus;
		private frmMain ParentFrm;

		public StatusWindow()
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
			this.lblStatus = new System.Windows.Forms.Label();
			this.progressBar = new System.Windows.Forms.ProgressBar();
			this.tmrGetGroups = new System.Windows.Forms.Timer(this.components);
			this.SuspendLayout();
			// 
			// lblStatus
			// 
			this.lblStatus.AutoSize = true;
			this.lblStatus.Location = new System.Drawing.Point(28, 20);
			this.lblStatus.Name = "lblStatus";
			this.lblStatus.Size = new System.Drawing.Size(161, 13);
			this.lblStatus.TabIndex = 0;
			this.lblStatus.Text = "Receiving groups from server...";
			// 
			// progressBar
			// 
			this.progressBar.Location = new System.Drawing.Point(28, 44);
			this.progressBar.Name = "progressBar";
			this.progressBar.Size = new System.Drawing.Size(260, 23);
			this.progressBar.TabIndex = 1;
			// 
			// tmrGetGroups
			// 
			this.tmrGetGroups.Tick += new System.EventHandler(this.tmrGetGroups_Tick);
			// 
			// StatusWindow
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(316, 91);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.progressBar,
																		  this.lblStatus});
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "StatusWindow";
			this.Text = "Receiving groups";
			this.Load += new System.EventHandler(this.frmGetGroups_Load);
			this.ResumeLayout(false);

		}
		#endregion

		private void tmrGetGroups_Tick(object sender, System.EventArgs e)
		{
			if (!ParentFrm.ready)
			{
				if (progressBar.Value != progressBar.Maximum)
					progressBar.PerformStep();
				else
					progressBar.Value = 0;
			}
			else
				this.Close();
		}

		private void frmGetGroups_Load(object sender, System.EventArgs e)
		{
			ParentFrm = (frmMain)this.Owner;
			tmrGetGroups.Enabled = true;
		}

		public string StatusMessage
		{
			get
			{
				return lblStatus.Text;
			}
			set
			{
				lblStatus.Text = value;
			}
		}
	}
}
