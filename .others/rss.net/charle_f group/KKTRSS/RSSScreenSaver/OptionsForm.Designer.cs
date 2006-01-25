namespace RSSScreenSaver
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
            this.backgroundImageOpenFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.backgroundImageFolderBrowser = new System.Windows.Forms.FolderBrowserDialog();
            this.account_groupBox = new System.Windows.Forms.GroupBox();
            this.newAccount_button = new System.Windows.Forms.Button();
            this.testConn_button = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.pass_textBox = new System.Windows.Forms.TextBox();
            this.login_label = new System.Windows.Forms.Label();
            this.login_textBox = new System.Windows.Forms.TextBox();
            this.proxy_groupBox = new System.Windows.Forms.GroupBox();
            this.label4 = new System.Windows.Forms.Label();
            this.proxyPort_textBox = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.proxyUrl_textBox = new System.Windows.Forms.TextBox();
            this.useProxy_checkBox = new System.Windows.Forms.CheckBox();
            this.label2 = new System.Windows.Forms.Label();
            this.proxyPass_textBox = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.proxyLogin_textBox = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label6 = new System.Windows.Forms.Label();
            this.fade_numericUpDown = new System.Windows.Forms.NumericUpDown();
            this.account_groupBox.SuspendLayout();
            this.proxy_groupBox.SuspendLayout();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.fade_numericUpDown)).BeginInit();
            this.SuspendLayout();
            // 
            // okButton
            // 
            this.okButton.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.okButton.Location = new System.Drawing.Point(291, 260);
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
            this.cancelButton.Location = new System.Drawing.Point(210, 260);
            this.cancelButton.Margin = new System.Windows.Forms.Padding(1, 3, 3, 3);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(75, 23);
            this.cancelButton.TabIndex = 2;
            this.cancelButton.Text = "Cancel";
            this.cancelButton.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // backgroundImageFolderBrowser
            // 
            this.backgroundImageFolderBrowser.RootFolder = System.Environment.SpecialFolder.MyPictures;
            // 
            // account_groupBox
            // 
            this.account_groupBox.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.account_groupBox.Controls.Add(this.newAccount_button);
            this.account_groupBox.Controls.Add(this.testConn_button);
            this.account_groupBox.Controls.Add(this.label1);
            this.account_groupBox.Controls.Add(this.pass_textBox);
            this.account_groupBox.Controls.Add(this.login_label);
            this.account_groupBox.Controls.Add(this.login_textBox);
            this.account_groupBox.Location = new System.Drawing.Point(11, 1);
            this.account_groupBox.Name = "account_groupBox";
            this.account_groupBox.Size = new System.Drawing.Size(355, 77);
            this.account_groupBox.TabIndex = 5;
            this.account_groupBox.TabStop = false;
            this.account_groupBox.Text = "Compte";
            // 
            // newAccount_button
            // 
            this.newAccount_button.Location = new System.Drawing.Point(234, 43);
            this.newAccount_button.Name = "newAccount_button";
            this.newAccount_button.Size = new System.Drawing.Size(105, 23);
            this.newAccount_button.TabIndex = 6;
            this.newAccount_button.Text = "Nouveau compte";
            this.newAccount_button.UseVisualStyleBackColor = true;
            this.newAccount_button.Click += new System.EventHandler(this.newAccount_button_Click);
            // 
            // testConn_button
            // 
            this.testConn_button.Location = new System.Drawing.Point(234, 17);
            this.testConn_button.Name = "testConn_button";
            this.testConn_button.Size = new System.Drawing.Size(105, 23);
            this.testConn_button.TabIndex = 5;
            this.testConn_button.Text = "Tester";
            this.testConn_button.UseVisualStyleBackColor = true;
            this.testConn_button.Click += new System.EventHandler(this.testConn_button_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(26, 48);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(33, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "Pass:";
            // 
            // pass_textBox
            // 
            this.pass_textBox.Location = new System.Drawing.Point(85, 45);
            this.pass_textBox.Name = "pass_textBox";
            this.pass_textBox.PasswordChar = '*';
            this.pass_textBox.Size = new System.Drawing.Size(132, 20);
            this.pass_textBox.TabIndex = 3;
            // 
            // login_label
            // 
            this.login_label.AutoSize = true;
            this.login_label.Location = new System.Drawing.Point(26, 22);
            this.login_label.Name = "login_label";
            this.login_label.Size = new System.Drawing.Size(36, 13);
            this.login_label.TabIndex = 1;
            this.login_label.Text = "Login:";
            // 
            // login_textBox
            // 
            this.login_textBox.Location = new System.Drawing.Point(85, 19);
            this.login_textBox.Name = "login_textBox";
            this.login_textBox.Size = new System.Drawing.Size(132, 20);
            this.login_textBox.TabIndex = 0;
            // 
            // proxy_groupBox
            // 
            this.proxy_groupBox.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.proxy_groupBox.Controls.Add(this.label4);
            this.proxy_groupBox.Controls.Add(this.proxyPort_textBox);
            this.proxy_groupBox.Controls.Add(this.label5);
            this.proxy_groupBox.Controls.Add(this.proxyUrl_textBox);
            this.proxy_groupBox.Controls.Add(this.useProxy_checkBox);
            this.proxy_groupBox.Controls.Add(this.label2);
            this.proxy_groupBox.Controls.Add(this.proxyPass_textBox);
            this.proxy_groupBox.Controls.Add(this.label3);
            this.proxy_groupBox.Controls.Add(this.proxyLogin_textBox);
            this.proxy_groupBox.Enabled = false;
            this.proxy_groupBox.Location = new System.Drawing.Point(12, 87);
            this.proxy_groupBox.Name = "proxy_groupBox";
            this.proxy_groupBox.Size = new System.Drawing.Size(355, 100);
            this.proxy_groupBox.TabIndex = 6;
            this.proxy_groupBox.TabStop = false;
            this.proxy_groupBox.Text = "Proxy";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(165, 74);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(29, 13);
            this.label4.TabIndex = 10;
            this.label4.Text = "Port:";
            // 
            // proxyPort_textBox
            // 
            this.proxyPort_textBox.Location = new System.Drawing.Point(224, 71);
            this.proxyPort_textBox.Name = "proxyPort_textBox";
            this.proxyPort_textBox.Size = new System.Drawing.Size(123, 20);
            this.proxyPort_textBox.TabIndex = 9;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(165, 48);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(51, 13);
            this.label5.TabIndex = 8;
            this.label5.Text = "Url proxy:";
            // 
            // proxyUrl_textBox
            // 
            this.proxyUrl_textBox.Location = new System.Drawing.Point(224, 45);
            this.proxyUrl_textBox.Name = "proxyUrl_textBox";
            this.proxyUrl_textBox.Size = new System.Drawing.Size(123, 20);
            this.proxyUrl_textBox.TabIndex = 7;
            // 
            // useProxy_checkBox
            // 
            this.useProxy_checkBox.AutoSize = true;
            this.useProxy_checkBox.Location = new System.Drawing.Point(29, 19);
            this.useProxy_checkBox.Name = "useProxy_checkBox";
            this.useProxy_checkBox.Size = new System.Drawing.Size(103, 17);
            this.useProxy_checkBox.TabIndex = 6;
            this.useProxy_checkBox.Text = "Utiliser un proxy.";
            this.useProxy_checkBox.UseVisualStyleBackColor = true;
            this.useProxy_checkBox.CheckedChanged += new System.EventHandler(this.useProxy_checkBox_CheckedChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 74);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(33, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "Pass:";
            // 
            // proxyPass_textBox
            // 
            this.proxyPass_textBox.Location = new System.Drawing.Point(65, 71);
            this.proxyPass_textBox.Name = "proxyPass_textBox";
            this.proxyPass_textBox.PasswordChar = '*';
            this.proxyPass_textBox.Size = new System.Drawing.Size(85, 20);
            this.proxyPass_textBox.TabIndex = 3;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 48);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(36, 13);
            this.label3.TabIndex = 1;
            this.label3.Text = "Login:";
            // 
            // proxyLogin_textBox
            // 
            this.proxyLogin_textBox.Location = new System.Drawing.Point(65, 45);
            this.proxyLogin_textBox.Name = "proxyLogin_textBox";
            this.proxyLogin_textBox.Size = new System.Drawing.Size(85, 20);
            this.proxyLogin_textBox.TabIndex = 0;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.fade_numericUpDown);
            this.groupBox1.Location = new System.Drawing.Point(12, 197);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(355, 54);
            this.groupBox1.TabIndex = 7;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Divers";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(194, 23);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(79, 13);
            this.label6.TabIndex = 1;
            this.label6.Text = "Fade Time (ms)";
            // 
            // fade_numericUpDown
            // 
            this.fade_numericUpDown.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.fade_numericUpDown.Location = new System.Drawing.Point(41, 19);
            this.fade_numericUpDown.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.fade_numericUpDown.Minimum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.fade_numericUpDown.Name = "fade_numericUpDown";
            this.fade_numericUpDown.Size = new System.Drawing.Size(120, 20);
            this.fade_numericUpDown.TabIndex = 0;
            this.fade_numericUpDown.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            // 
            // OptionsForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(379, 295);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.account_groupBox);
            this.Controls.Add(this.proxy_groupBox);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.okButton);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "OptionsForm";
            this.Padding = new System.Windows.Forms.Padding(9);
            this.ShowIcon = false;
            this.Text = "Screen Saver Settings";
            this.Load += new System.EventHandler(this.OptionsForm_Load);
            this.account_groupBox.ResumeLayout(false);
            this.account_groupBox.PerformLayout();
            this.proxy_groupBox.ResumeLayout(false);
            this.proxy_groupBox.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.fade_numericUpDown)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button cancelButton;
        private System.Windows.Forms.Button okButton;
        private System.Windows.Forms.OpenFileDialog backgroundImageOpenFileDialog;
        private System.Windows.Forms.FolderBrowserDialog backgroundImageFolderBrowser;
        private System.Windows.Forms.GroupBox account_groupBox;
        private System.Windows.Forms.Label login_label;
        private System.Windows.Forms.TextBox login_textBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox pass_textBox;
        private System.Windows.Forms.GroupBox proxy_groupBox;
        private System.Windows.Forms.CheckBox useProxy_checkBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox proxyPass_textBox;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox proxyLogin_textBox;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox proxyPort_textBox;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox proxyUrl_textBox;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.NumericUpDown fade_numericUpDown;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button newAccount_button;
        private System.Windows.Forms.Button testConn_button;
    }
}