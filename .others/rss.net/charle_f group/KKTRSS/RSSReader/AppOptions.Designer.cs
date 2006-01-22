namespace RSSReader
{
    partial class AppOptions
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
            this.systray_checkBox = new System.Windows.Forms.CheckBox();
            this.label1 = new System.Windows.Forms.Label();
            this.valid_button = new System.Windows.Forms.Button();
            this.tooltip_checkBox = new System.Windows.Forms.CheckBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.update_numericUpDown = new System.Windows.Forms.NumericUpDown();
            this.Proxy = new System.Windows.Forms.GroupBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.proxyPort_textBox = new System.Windows.Forms.TextBox();
            this.proxyPass_textBox = new System.Windows.Forms.TextBox();
            this.proxyUrl_textBox = new System.Windows.Forms.TextBox();
            this.proxyLogin_textBox = new System.Windows.Forms.TextBox();
            this.useProxy_checkBox = new System.Windows.Forms.CheckBox();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.update_numericUpDown)).BeginInit();
            this.Proxy.SuspendLayout();
            this.SuspendLayout();
            // 
            // systray_checkBox
            // 
            this.systray_checkBox.AutoSize = true;
            this.systray_checkBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.systray_checkBox.Location = new System.Drawing.Point(27, 33);
            this.systray_checkBox.Name = "systray_checkBox";
            this.systray_checkBox.Size = new System.Drawing.Size(158, 17);
            this.systray_checkBox.TabIndex = 0;
            this.systray_checkBox.Text = "Réduire dans la systray";
            this.systray_checkBox.UseVisualStyleBackColor = true;
            this.systray_checkBox.CheckedChanged += new System.EventHandler(this.systray_checkBox_CheckedChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(133, 33);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(189, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Fréquence des update (minutes)";
            // 
            // valid_button
            // 
            this.valid_button.Location = new System.Drawing.Point(310, 260);
            this.valid_button.Name = "valid_button";
            this.valid_button.Size = new System.Drawing.Size(75, 23);
            this.valid_button.TabIndex = 3;
            this.valid_button.Text = "Valider";
            this.valid_button.UseVisualStyleBackColor = true;
            this.valid_button.Click += new System.EventHandler(this.valid_button_Click);
            // 
            // tooltip_checkBox
            // 
            this.tooltip_checkBox.AutoSize = true;
            this.tooltip_checkBox.Enabled = false;
            this.tooltip_checkBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tooltip_checkBox.Location = new System.Drawing.Point(203, 33);
            this.tooltip_checkBox.Name = "tooltip_checkBox";
            this.tooltip_checkBox.Size = new System.Drawing.Size(156, 17);
            this.tooltip_checkBox.TabIndex = 4;
            this.tooltip_checkBox.Text = "Utiliser un tooltip (msn)";
            this.tooltip_checkBox.UseVisualStyleBackColor = true;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.systray_checkBox);
            this.groupBox1.Controls.Add(this.tooltip_checkBox);
            this.groupBox1.Location = new System.Drawing.Point(12, 2);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(373, 69);
            this.groupBox1.TabIndex = 5;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Systray";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.update_numericUpDown);
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Location = new System.Drawing.Point(12, 77);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(373, 71);
            this.groupBox2.TabIndex = 6;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Update";
            // 
            // update_numericUpDown
            // 
            this.update_numericUpDown.Location = new System.Drawing.Point(27, 31);
            this.update_numericUpDown.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.update_numericUpDown.Name = "update_numericUpDown";
            this.update_numericUpDown.Size = new System.Drawing.Size(100, 20);
            this.update_numericUpDown.TabIndex = 3;
            this.update_numericUpDown.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // Proxy
            // 
            this.Proxy.Controls.Add(this.label5);
            this.Proxy.Controls.Add(this.label4);
            this.Proxy.Controls.Add(this.label3);
            this.Proxy.Controls.Add(this.label2);
            this.Proxy.Controls.Add(this.proxyPort_textBox);
            this.Proxy.Controls.Add(this.proxyPass_textBox);
            this.Proxy.Controls.Add(this.proxyUrl_textBox);
            this.Proxy.Controls.Add(this.proxyLogin_textBox);
            this.Proxy.Controls.Add(this.useProxy_checkBox);
            this.Proxy.Location = new System.Drawing.Point(12, 154);
            this.Proxy.Name = "Proxy";
            this.Proxy.Size = new System.Drawing.Size(373, 100);
            this.Proxy.TabIndex = 7;
            this.Proxy.TabStop = false;
            this.Proxy.Text = "Proxy";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(200, 77);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(32, 13);
            this.label5.TabIndex = 13;
            this.label5.Text = "Port :";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(199, 45);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(59, 13);
            this.label4.TabIndex = 12;
            this.label4.Text = "Password :";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 74);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(69, 13);
            this.label3.TabIndex = 11;
            this.label3.Text = "Url du proxy :";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 45);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(39, 13);
            this.label2.TabIndex = 10;
            this.label2.Text = "Login :";
            // 
            // proxyPort_textBox
            // 
            this.proxyPort_textBox.Location = new System.Drawing.Point(267, 74);
            this.proxyPort_textBox.Name = "proxyPort_textBox";
            this.proxyPort_textBox.Size = new System.Drawing.Size(100, 20);
            this.proxyPort_textBox.TabIndex = 9;
            // 
            // proxyPass_textBox
            // 
            this.proxyPass_textBox.Location = new System.Drawing.Point(267, 42);
            this.proxyPass_textBox.Name = "proxyPass_textBox";
            this.proxyPass_textBox.PasswordChar = '*';
            this.proxyPass_textBox.Size = new System.Drawing.Size(100, 20);
            this.proxyPass_textBox.TabIndex = 8;
            // 
            // proxyUrl_textBox
            // 
            this.proxyUrl_textBox.Location = new System.Drawing.Point(85, 74);
            this.proxyUrl_textBox.Name = "proxyUrl_textBox";
            this.proxyUrl_textBox.Size = new System.Drawing.Size(100, 20);
            this.proxyUrl_textBox.TabIndex = 7;
            // 
            // proxyLogin_textBox
            // 
            this.proxyLogin_textBox.Location = new System.Drawing.Point(85, 42);
            this.proxyLogin_textBox.Name = "proxyLogin_textBox";
            this.proxyLogin_textBox.Size = new System.Drawing.Size(100, 20);
            this.proxyLogin_textBox.TabIndex = 6;
            // 
            // useProxy_checkBox
            // 
            this.useProxy_checkBox.AutoSize = true;
            this.useProxy_checkBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.useProxy_checkBox.Location = new System.Drawing.Point(27, 19);
            this.useProxy_checkBox.Name = "useProxy_checkBox";
            this.useProxy_checkBox.Size = new System.Drawing.Size(117, 17);
            this.useProxy_checkBox.TabIndex = 5;
            this.useProxy_checkBox.Text = "Utiliser un proxy";
            this.useProxy_checkBox.UseVisualStyleBackColor = true;
            this.useProxy_checkBox.CheckedChanged += new System.EventHandler(this.useProxy_checkBox_CheckedChanged);
            // 
            // AppOptions
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(406, 292);
            this.Controls.Add(this.Proxy);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.valid_button);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "AppOptions";
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Options";
            this.Load += new System.EventHandler(this.AppOptions_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.update_numericUpDown)).EndInit();
            this.Proxy.ResumeLayout(false);
            this.Proxy.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.CheckBox systray_checkBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button valid_button;
        private System.Windows.Forms.CheckBox tooltip_checkBox;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.NumericUpDown update_numericUpDown;
        private System.Windows.Forms.GroupBox Proxy;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox proxyPort_textBox;
        private System.Windows.Forms.TextBox proxyPass_textBox;
        private System.Windows.Forms.TextBox proxyUrl_textBox;
        private System.Windows.Forms.TextBox proxyLogin_textBox;
        private System.Windows.Forms.CheckBox useProxy_checkBox;
    }
}