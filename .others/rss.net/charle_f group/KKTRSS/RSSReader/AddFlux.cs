using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace RSSReader
{
    public partial class AddFlux : Form
    {
        private ModifyFluxList frmParent;
        public ModifyFluxList FormParent
        {
            get { return frmParent; }
            set { frmParent = value; }
        }

        public AddFlux()
        {
            InitializeComponent();
        }

        private void valid_button_Click(object sender, EventArgs e)
        {
            if (urlFlux_textBox.Text != "" && nomFlux_textBox.Text != "")
            {
                frmParent.FormParent.MainWebService.ImportRssFeed(frmParent.FormParent.SessionID, urlFlux_textBox.Text, nomFlux_textBox.Text, "", false);
                frmParent.updateFluxList();
                this.Close();
            }
        }
    }
}