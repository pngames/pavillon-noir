namespace NRSS.Screensaver
{
  partial class OptionsForm : System.Windows.Forms.Form
  {
	/// <summary>
	/// Required designer variable.
	/// </summary>
	private System.ComponentModel.IContainer components = null;

	/// <summary>
	/// Clean up any resources being used.
	/// </summary>
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
      this.okButton = new System.Windows.Forms.Button();
      this.cancelButton = new System.Windows.Forms.Button();
      this.applyButton = new System.Windows.Forms.Button();
      this.imageGroupBox = new System.Windows.Forms.GroupBox();
      this.LoginTextBox = new System.Windows.Forms.TextBox();
      this.PasswordTextBox = new System.Windows.Forms.TextBox();
      this.label1 = new System.Windows.Forms.Label();
      this.backgroundImageLabel = new System.Windows.Forms.Label();
      this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
      this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
      this.imageGroupBox.SuspendLayout();
      this.tableLayoutPanel1.SuspendLayout();
      this.tableLayoutPanel2.SuspendLayout();
      this.SuspendLayout();
      // 
      // okButton
      // 
      this.okButton.Anchor = System.Windows.Forms.AnchorStyles.None;
      this.okButton.Location = new System.Drawing.Point(156, 3);
      this.okButton.Margin = new System.Windows.Forms.Padding(3, 3, 2, 3);
      this.okButton.Name = "okButton";
      this.okButton.Size = new System.Drawing.Size(75, 23);
      this.okButton.TabIndex = 1;
      this.okButton.Text = "OK";
      this.okButton.Click += new System.EventHandler(this.btnOK_Click);
      // 
      // cancelButton
      // 
      this.cancelButton.Anchor = System.Windows.Forms.AnchorStyles.None;
      this.cancelButton.Location = new System.Drawing.Point(74, 3);
      this.cancelButton.Margin = new System.Windows.Forms.Padding(1, 3, 3, 3);
      this.cancelButton.Name = "cancelButton";
      this.cancelButton.Size = new System.Drawing.Size(75, 23);
      this.cancelButton.TabIndex = 2;
      this.cancelButton.Text = "Cancel";
      this.cancelButton.Click += new System.EventHandler(this.btnCancel_Click);
      // 
      // applyButton
      // 
      this.applyButton.Anchor = System.Windows.Forms.AnchorStyles.None;
      this.applyButton.Location = new System.Drawing.Point(237, 3);
      this.applyButton.Name = "applyButton";
      this.applyButton.Size = new System.Drawing.Size(75, 23);
      this.applyButton.TabIndex = 3;
      this.applyButton.Text = "Apply";
      this.applyButton.Click += new System.EventHandler(this.btnApply_Click);
      // 
      // imageGroupBox
      // 
      this.imageGroupBox.Controls.Add(this.LoginTextBox);
      this.imageGroupBox.Controls.Add(this.PasswordTextBox);
      this.imageGroupBox.Controls.Add(this.label1);
      this.imageGroupBox.Controls.Add(this.backgroundImageLabel);
      this.imageGroupBox.Dock = System.Windows.Forms.DockStyle.Fill;
      this.imageGroupBox.Location = new System.Drawing.Point(3, 7);
      this.imageGroupBox.Name = "imageGroupBox";
      this.imageGroupBox.Size = new System.Drawing.Size(315, 128);
      this.imageGroupBox.TabIndex = 5;
      this.imageGroupBox.TabStop = false;
      this.imageGroupBox.Text = "Connection";
      // 
      // LoginTextBox
      // 
      this.LoginTextBox.BackColor = System.Drawing.SystemColors.Window;
      this.LoginTextBox.ForeColor = System.Drawing.Color.Black;
      this.LoginTextBox.Location = new System.Drawing.Point(7, 41);
      this.LoginTextBox.Name = "LoginTextBox";
      this.LoginTextBox.Size = new System.Drawing.Size(301, 20);
      this.LoginTextBox.TabIndex = 4;
      this.LoginTextBox.TextChanged += new System.EventHandler(this.LoginTextBox_TextChanged);
      // 
      // PasswordTextBox
      // 
      this.PasswordTextBox.BackColor = System.Drawing.SystemColors.Window;
      this.PasswordTextBox.ForeColor = System.Drawing.Color.Black;
      this.PasswordTextBox.Location = new System.Drawing.Point(7, 86);
      this.PasswordTextBox.Name = "PasswordTextBox";
      this.PasswordTextBox.PasswordChar = '*';
      this.PasswordTextBox.Size = new System.Drawing.Size(301, 20);
      this.PasswordTextBox.TabIndex = 3;
      this.PasswordTextBox.TextChanged += new System.EventHandler(this.PasswordTextBox_TextChanged);
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point(7, 66);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(59, 13);
      this.label1.TabIndex = 2;
      this.label1.Text = "Password :";
      // 
      // backgroundImageLabel
      // 
      this.backgroundImageLabel.AutoSize = true;
      this.backgroundImageLabel.Location = new System.Drawing.Point(7, 20);
      this.backgroundImageLabel.Name = "backgroundImageLabel";
      this.backgroundImageLabel.Size = new System.Drawing.Size(39, 13);
      this.backgroundImageLabel.TabIndex = 0;
      this.backgroundImageLabel.Text = "Login :";
      // 
      // tableLayoutPanel1
      // 
      this.tableLayoutPanel1.ColumnCount = 1;
      this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
      this.tableLayoutPanel1.Controls.Add(this.imageGroupBox, 0, 1);
      this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel2, 0, 2);
      this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
      this.tableLayoutPanel1.Location = new System.Drawing.Point(9, 9);
      this.tableLayoutPanel1.Name = "tableLayoutPanel1";
      this.tableLayoutPanel1.RowCount = 3;
      this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 3.305785F));
      this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 96.69421F));
      this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 35F));
      this.tableLayoutPanel1.Size = new System.Drawing.Size(321, 174);
      this.tableLayoutPanel1.TabIndex = 6;
      // 
      // tableLayoutPanel2
      // 
      this.tableLayoutPanel2.ColumnCount = 4;
      this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
      this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 81F));
      this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 81F));
      this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 81F));
      this.tableLayoutPanel2.Controls.Add(this.applyButton, 3, 0);
      this.tableLayoutPanel2.Controls.Add(this.cancelButton, 1, 0);
      this.tableLayoutPanel2.Controls.Add(this.okButton, 2, 0);
      this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
      this.tableLayoutPanel2.Location = new System.Drawing.Point(3, 141);
      this.tableLayoutPanel2.Name = "tableLayoutPanel2";
      this.tableLayoutPanel2.RowCount = 1;
      this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
      this.tableLayoutPanel2.Size = new System.Drawing.Size(315, 30);
      this.tableLayoutPanel2.TabIndex = 6;
      // 
      // OptionsForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(339, 192);
      this.Controls.Add(this.tableLayoutPanel1);
      this.Name = "OptionsForm";
      this.Padding = new System.Windows.Forms.Padding(9);
      this.ShowIcon = false;
      this.Text = "Screen Saver Settings";
      this.imageGroupBox.ResumeLayout(false);
      this.imageGroupBox.PerformLayout();
      this.tableLayoutPanel1.ResumeLayout(false);
      this.tableLayoutPanel2.ResumeLayout(false);
      this.ResumeLayout(false);

	}

	#endregion

	private System.Windows.Forms.Button applyButton;
	private System.Windows.Forms.Button cancelButton;
    private System.Windows.Forms.Button okButton;
    private System.Windows.Forms.GroupBox imageGroupBox;
    private System.Windows.Forms.Label backgroundImageLabel;
	private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
	private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
    private System.Windows.Forms.TextBox PasswordTextBox;
    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.TextBox LoginTextBox;
  }
}