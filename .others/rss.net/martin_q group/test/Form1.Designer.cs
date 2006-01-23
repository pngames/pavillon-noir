namespace test
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
	  this.button1 = new System.Windows.Forms.Button();
	  this.t_user = new System.Windows.Forms.TextBox();
	  this.t_pass = new System.Windows.Forms.TextBox();
	  this.t_hash = new System.Windows.Forms.TextBox();
	  this.t_id = new System.Windows.Forms.TextBox();
	  this.SuspendLayout();
	  // 
	  // button1
	  // 
	  this.button1.Location = new System.Drawing.Point(142, 119);
	  this.button1.Name = "button1";
	  this.button1.Size = new System.Drawing.Size(75, 23);
	  this.button1.TabIndex = 0;
	  this.button1.Text = "button1";
	  this.button1.UseVisualStyleBackColor = true;
	  this.button1.Click += new System.EventHandler(this.button1_Click);
	  // 
	  // t_user
	  // 
	  this.t_user.Location = new System.Drawing.Point(12, 12);
	  this.t_user.Name = "t_user";
	  this.t_user.Size = new System.Drawing.Size(100, 20);
	  this.t_user.TabIndex = 1;
	  // 
	  // t_pass
	  // 
	  this.t_pass.Location = new System.Drawing.Point(12, 38);
	  this.t_pass.Name = "t_pass";
	  this.t_pass.Size = new System.Drawing.Size(100, 20);
	  this.t_pass.TabIndex = 2;
	  // 
	  // t_hash
	  // 
	  this.t_hash.Location = new System.Drawing.Point(12, 64);
	  this.t_hash.Name = "t_hash";
	  this.t_hash.ReadOnly = true;
	  this.t_hash.Size = new System.Drawing.Size(100, 20);
	  this.t_hash.TabIndex = 3;
	  // 
	  // t_id
	  // 
	  this.t_id.Location = new System.Drawing.Point(180, 12);
	  this.t_id.Name = "t_id";
	  this.t_id.Size = new System.Drawing.Size(100, 20);
	  this.t_id.TabIndex = 4;
	  // 
	  // Form1
	  // 
	  this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
	  this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
	  this.ClientSize = new System.Drawing.Size(292, 273);
	  this.Controls.Add(this.t_id);
	  this.Controls.Add(this.t_hash);
	  this.Controls.Add(this.t_pass);
	  this.Controls.Add(this.t_user);
	  this.Controls.Add(this.button1);
	  this.Name = "Form1";
	  this.Text = "Form1";
	  this.ResumeLayout(false);
	  this.PerformLayout();

	}

	#endregion

	private System.Windows.Forms.Button button1;
	private System.Windows.Forms.TextBox t_user;
	private System.Windows.Forms.TextBox t_pass;
	private System.Windows.Forms.TextBox t_hash;
	private System.Windows.Forms.TextBox t_id;
  }
}

