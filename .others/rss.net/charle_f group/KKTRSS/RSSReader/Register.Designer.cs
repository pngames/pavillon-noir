namespace RSSReader
{
    partial class Register
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
            this.valid_button = new System.Windows.Forms.Button();
            this.email_textBox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.mdp_textBox = new System.Windows.Forms.TextBox();
            this.mdp2_textBox = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // valid_button
            // 
            this.valid_button.Location = new System.Drawing.Point(174, 112);
            this.valid_button.Name = "valid_button";
            this.valid_button.Size = new System.Drawing.Size(75, 23);
            this.valid_button.TabIndex = 3;
            this.valid_button.Text = "S\'enregistrer";
            this.valid_button.UseVisualStyleBackColor = true;
            this.valid_button.Click += new System.EventHandler(this.valid_button_Click);
            // 
            // email_textBox
            // 
            this.email_textBox.BackColor = System.Drawing.SystemColors.Window;
            this.email_textBox.Location = new System.Drawing.Point(195, 18);
            this.email_textBox.Name = "email_textBox";
            this.email_textBox.Size = new System.Drawing.Size(146, 20);
            this.email_textBox.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(31, 21);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(93, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Adresse email :";
            // 
            // mdp_textBox
            // 
            this.mdp_textBox.Location = new System.Drawing.Point(195, 44);
            this.mdp_textBox.Name = "mdp_textBox";
            this.mdp_textBox.PasswordChar = '*';
            this.mdp_textBox.Size = new System.Drawing.Size(100, 20);
            this.mdp_textBox.TabIndex = 1;
            // 
            // mdp2_textBox
            // 
            this.mdp2_textBox.Location = new System.Drawing.Point(195, 70);
            this.mdp2_textBox.Name = "mdp2_textBox";
            this.mdp2_textBox.PasswordChar = '*';
            this.mdp2_textBox.Size = new System.Drawing.Size(100, 20);
            this.mdp2_textBox.TabIndex = 2;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(31, 47);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(91, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "Mot de passe :";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(31, 73);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(158, 13);
            this.label3.TabIndex = 6;
            this.label3.Text = "Vérification mot de passe :";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.ForeColor = System.Drawing.Color.Gray;
            this.label4.Location = new System.Drawing.Point(313, 47);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(111, 13);
            this.label4.TabIndex = 7;
            this.label4.Text = "au moins 6 caractères";
            // 
            // Register
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(441, 140);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.mdp2_textBox);
            this.Controls.Add(this.mdp_textBox);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.email_textBox);
            this.Controls.Add(this.valid_button);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Register";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Nouvel utilisateur";
            this.Load += new System.EventHandler(this.Register_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button valid_button;
        private System.Windows.Forms.TextBox email_textBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox mdp_textBox;
        private System.Windows.Forms.TextBox mdp2_textBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
    }
}