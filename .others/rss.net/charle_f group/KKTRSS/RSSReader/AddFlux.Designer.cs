namespace RSSReader
{
    partial class AddFlux
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
            this.urlFlux_textBox = new System.Windows.Forms.TextBox();
            this.nomFlux_textBox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // valid_button
            // 
            this.valid_button.Location = new System.Drawing.Point(164, 71);
            this.valid_button.Name = "valid_button";
            this.valid_button.Size = new System.Drawing.Size(75, 23);
            this.valid_button.TabIndex = 0;
            this.valid_button.Text = "Valider";
            this.valid_button.UseVisualStyleBackColor = true;
            this.valid_button.Click += new System.EventHandler(this.valid_button_Click);
            // 
            // urlFlux_textBox
            // 
            this.urlFlux_textBox.Location = new System.Drawing.Point(88, 6);
            this.urlFlux_textBox.Name = "urlFlux_textBox";
            this.urlFlux_textBox.Size = new System.Drawing.Size(338, 20);
            this.urlFlux_textBox.TabIndex = 1;
            // 
            // nomFlux_textBox
            // 
            this.nomFlux_textBox.Location = new System.Drawing.Point(88, 36);
            this.nomFlux_textBox.Name = "nomFlux_textBox";
            this.nomFlux_textBox.Size = new System.Drawing.Size(225, 20);
            this.nomFlux_textBox.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(68, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Url du Flux";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(3, 39);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(77, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "Nom du Flux";
            // 
            // AddFlux
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(438, 106);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.nomFlux_textBox);
            this.Controls.Add(this.urlFlux_textBox);
            this.Controls.Add(this.valid_button);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "AddFlux";
            this.Text = "Ajout Flux";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button valid_button;
        private System.Windows.Forms.TextBox urlFlux_textBox;
        private System.Windows.Forms.TextBox nomFlux_textBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
    }
}