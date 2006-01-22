namespace RSSReader
{
    partial class VocalOptions
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
            this.prononce_textBox = new System.Windows.Forms.TextBox();
            this.prononce_button = new System.Windows.Forms.Button();
            this.valid_button = new System.Windows.Forms.Button();
            this.volume_numericUpDown = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.voice_numericUpDown = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.volume_numericUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.voice_numericUpDown)).BeginInit();
            this.SuspendLayout();
            // 
            // prononce_textBox
            // 
            this.prononce_textBox.Location = new System.Drawing.Point(15, 30);
            this.prononce_textBox.Multiline = true;
            this.prononce_textBox.Name = "prononce_textBox";
            this.prononce_textBox.Size = new System.Drawing.Size(253, 98);
            this.prononce_textBox.TabIndex = 0;
            this.prononce_textBox.Text = "Hello, you are in the configuration window of the vocal synthetiseur.";
            // 
            // prononce_button
            // 
            this.prononce_button.Location = new System.Drawing.Point(288, 62);
            this.prononce_button.Name = "prononce_button";
            this.prononce_button.Size = new System.Drawing.Size(75, 23);
            this.prononce_button.TabIndex = 1;
            this.prononce_button.Text = "Prononcer";
            this.prononce_button.UseVisualStyleBackColor = true;
            this.prononce_button.Click += new System.EventHandler(this.prononce_button_Click);
            // 
            // valid_button
            // 
            this.valid_button.Location = new System.Drawing.Point(288, 105);
            this.valid_button.Name = "valid_button";
            this.valid_button.Size = new System.Drawing.Size(75, 23);
            this.valid_button.TabIndex = 2;
            this.valid_button.Text = "Valider";
            this.valid_button.UseVisualStyleBackColor = true;
            this.valid_button.Click += new System.EventHandler(this.valid_button_Click);
            // 
            // volume_numericUpDown
            // 
            this.volume_numericUpDown.Location = new System.Drawing.Point(162, 152);
            this.volume_numericUpDown.Name = "volume_numericUpDown";
            this.volume_numericUpDown.Size = new System.Drawing.Size(75, 20);
            this.volume_numericUpDown.TabIndex = 3;
            this.volume_numericUpDown.Value = new decimal(new int[] {
            50,
            0,
            0,
            0});
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(12, 14);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(137, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "Tester le synthetiseur :";
            // 
            // voice_numericUpDown
            // 
            this.voice_numericUpDown.Location = new System.Drawing.Point(15, 152);
            this.voice_numericUpDown.Maximum = new decimal(new int[] {
            3,
            0,
            0,
            0});
            this.voice_numericUpDown.Name = "voice_numericUpDown";
            this.voice_numericUpDown.Size = new System.Drawing.Size(75, 20);
            this.voice_numericUpDown.TabIndex = 5;
            this.voice_numericUpDown.Value = new decimal(new int[] {
            2,
            0,
            0,
            0});
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(159, 136);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(56, 13);
            this.label2.TabIndex = 6;
            this.label2.Text = "Volume :";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(12, 136);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(91, 13);
            this.label3.TabIndex = 7;
            this.label3.Text = "Voix à utiliser :";
            // 
            // VocalOptions
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(391, 191);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.voice_numericUpDown);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.volume_numericUpDown);
            this.Controls.Add(this.valid_button);
            this.Controls.Add(this.prononce_button);
            this.Controls.Add(this.prononce_textBox);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "VocalOptions";
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Options du synthetiseur vocal";
            this.Load += new System.EventHandler(this.VocalOptions_Load);
            ((System.ComponentModel.ISupportInitialize)(this.volume_numericUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.voice_numericUpDown)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox prononce_textBox;
        private System.Windows.Forms.Button prononce_button;
        private System.Windows.Forms.Button valid_button;
        private System.Windows.Forms.NumericUpDown volume_numericUpDown;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown voice_numericUpDown;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
    }
}