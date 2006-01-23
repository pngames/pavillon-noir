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
            this.valid_button = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.flux_listView = new System.Windows.Forms.ListView();
            this.SuspendLayout();
            // 
            // valid_button
            // 
            this.valid_button.Location = new System.Drawing.Point(113, 404);
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
            this.label1.Location = new System.Drawing.Point(67, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(178, 13);
            this.label1.TabIndex = 5;
            this.label1.Text = "Flux disponibles sur le serveur";
            // 
            // flux_listView
            // 
            this.flux_listView.CheckBoxes = true;
            this.flux_listView.Location = new System.Drawing.Point(12, 25);
            this.flux_listView.Name = "flux_listView";
            this.flux_listView.Size = new System.Drawing.Size(294, 373);
            this.flux_listView.TabIndex = 6;
            this.flux_listView.UseCompatibleStateImageBehavior = false;
            this.flux_listView.View = System.Windows.Forms.View.List;
            // 
            // ModifyFluxList
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(318, 439);
            this.Controls.Add(this.flux_listView);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.valid_button);
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

        private System.Windows.Forms.Button valid_button;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ListView flux_listView;
    }
}