namespace RSSReader
{
    partial class Connexion
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Connexion));
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.mdp_textBox = new System.Windows.Forms.TextBox();
            this.email_textBox = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.load_button = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label3 = new System.Windows.Forms.Label();
            this.register_button = new System.Windows.Forms.Button();
            this.rememberMe_checkBox = new System.Windows.Forms.CheckBox();
            this.label4 = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.rememberMe_checkBox);
            this.groupBox1.Controls.Add(this.mdp_textBox);
            this.groupBox1.Controls.Add(this.email_textBox);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.load_button);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(256, 190);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Utilisateur existant";
            // 
            // mdp_textBox
            // 
            this.mdp_textBox.Location = new System.Drawing.Point(109, 78);
            this.mdp_textBox.Name = "mdp_textBox";
            this.mdp_textBox.PasswordChar = '*';
            this.mdp_textBox.Size = new System.Drawing.Size(141, 20);
            this.mdp_textBox.TabIndex = 1;
            // 
            // email_textBox
            // 
            this.email_textBox.Location = new System.Drawing.Point(109, 40);
            this.email_textBox.Name = "email_textBox";
            this.email_textBox.Size = new System.Drawing.Size(141, 20);
            this.email_textBox.TabIndex = 0;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(12, 82);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(91, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Mot de passe :";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(12, 47);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(45, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Email :";
            // 
            // load_button
            // 
            this.load_button.Location = new System.Drawing.Point(67, 161);
            this.load_button.Name = "load_button";
            this.load_button.Size = new System.Drawing.Size(118, 23);
            this.load_button.TabIndex = 2;
            this.load_button.Text = "Charger mes flux";
            this.load_button.UseVisualStyleBackColor = true;
            this.load_button.Click += new System.EventHandler(this.load_button_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.register_button);
            this.groupBox2.Location = new System.Drawing.Point(274, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(256, 190);
            this.groupBox2.TabIndex = 1;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Nouvel utilisateur";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(33, 42);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(200, 52);
            this.label3.TabIndex = 6;
            this.label3.Text = "S\'enregistrer permet d\'accéder à ses flux \r\npersonnalisés depuis n\'importe quel\r\n" +
                "ordinateur en utilisant son adresse email \r\net son mot de passe.";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // register_button
            // 
            this.register_button.CausesValidation = false;
            this.register_button.Location = new System.Drawing.Point(96, 161);
            this.register_button.Name = "register_button";
            this.register_button.Size = new System.Drawing.Size(75, 23);
            this.register_button.TabIndex = 3;
            this.register_button.Text = "S\'enregistrer";
            this.register_button.UseVisualStyleBackColor = true;
            this.register_button.Click += new System.EventHandler(this.register_button_Click);
            // 
            // rememberMe_checkBox
            // 
            this.rememberMe_checkBox.AutoSize = true;
            this.rememberMe_checkBox.Location = new System.Drawing.Point(170, 117);
            this.rememberMe_checkBox.Name = "rememberMe_checkBox";
            this.rememberMe_checkBox.Size = new System.Drawing.Size(15, 14);
            this.rememberMe_checkBox.TabIndex = 3;
            this.rememberMe_checkBox.UseVisualStyleBackColor = true;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(12, 118);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(123, 13);
            this.label4.TabIndex = 4;
            this.label4.Text = "Se souvenir de moi :";
            // 
            // Connexion
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(537, 214);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Connexion";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Connexion";
            this.Load += new System.EventHandler(this.Connexion_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox mdp_textBox;
        private System.Windows.Forms.TextBox email_textBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button load_button;
        private System.Windows.Forms.Button register_button;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.CheckBox rememberMe_checkBox;
    }
}

