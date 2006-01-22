namespace RSSReader
{
    partial class ModifyFluxList
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
            this.server_listBox = new System.Windows.Forms.ListBox();
            this.client_listBox = new System.Windows.Forms.ListBox();
            this.add_button = new System.Windows.Forms.Button();
            this.delete_button = new System.Windows.Forms.Button();
            this.valid_button = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // server_listBox
            // 
            this.server_listBox.FormattingEnabled = true;
            this.server_listBox.Location = new System.Drawing.Point(12, 26);
            this.server_listBox.Name = "server_listBox";
            this.server_listBox.Size = new System.Drawing.Size(202, 355);
            this.server_listBox.TabIndex = 0;
            this.server_listBox.Leave += new System.EventHandler(this.server_listBox_Leave);
            this.server_listBox.SelectedIndexChanged += new System.EventHandler(this.server_listBox_SelectedIndexChanged);
            // 
            // client_listBox
            // 
            this.client_listBox.FormattingEnabled = true;
            this.client_listBox.Location = new System.Drawing.Point(301, 26);
            this.client_listBox.Name = "client_listBox";
            this.client_listBox.Size = new System.Drawing.Size(202, 355);
            this.client_listBox.TabIndex = 1;
            this.client_listBox.Leave += new System.EventHandler(this.client_listBox_Leave);
            this.client_listBox.SelectedIndexChanged += new System.EventHandler(this.client_listBox_SelectedIndexChanged);
            // 
            // add_button
            // 
            this.add_button.Enabled = false;
            this.add_button.Location = new System.Drawing.Point(220, 136);
            this.add_button.Name = "add_button";
            this.add_button.Size = new System.Drawing.Size(75, 23);
            this.add_button.TabIndex = 2;
            this.add_button.Text = ">>";
            this.add_button.UseVisualStyleBackColor = true;
            this.add_button.Click += new System.EventHandler(this.add_button_Click);
            // 
            // delete_button
            // 
            this.delete_button.Enabled = false;
            this.delete_button.Location = new System.Drawing.Point(220, 184);
            this.delete_button.Name = "delete_button";
            this.delete_button.Size = new System.Drawing.Size(75, 23);
            this.delete_button.TabIndex = 3;
            this.delete_button.Text = "<<";
            this.delete_button.UseVisualStyleBackColor = true;
            this.delete_button.Click += new System.EventHandler(this.delete_button_Click);
            // 
            // valid_button
            // 
            this.valid_button.Location = new System.Drawing.Point(220, 401);
            this.valid_button.Name = "valid_button";
            this.valid_button.Size = new System.Drawing.Size(75, 23);
            this.valid_button.TabIndex = 4;
            this.valid_button.Text = "Valider";
            this.valid_button.UseVisualStyleBackColor = true;
            this.valid_button.Click += new System.EventHandler(this.valid_button_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(25, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(178, 13);
            this.label1.TabIndex = 5;
            this.label1.Text = "Flux disponibles sur le serveur";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(354, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(105, 13);
            this.label2.TabIndex = 6;
            this.label2.Text = "Flux selectionnés";
            // 
            // ModifyFluxList
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(518, 439);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.valid_button);
            this.Controls.Add(this.delete_button);
            this.Controls.Add(this.add_button);
            this.Controls.Add(this.client_listBox);
            this.Controls.Add(this.server_listBox);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "ModifyFluxList";
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Modifier la liste des flux";
            this.Load += new System.EventHandler(this.ModifyFluxList_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox server_listBox;
        private System.Windows.Forms.ListBox client_listBox;
        private System.Windows.Forms.Button add_button;
        private System.Windows.Forms.Button delete_button;
        private System.Windows.Forms.Button valid_button;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
    }
}