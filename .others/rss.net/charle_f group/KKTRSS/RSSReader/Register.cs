using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace RSSReader
{
    public partial class Register : Form
    {
        private RSSReaderMain frmParent;
        public RSSReaderMain FormParent
        {
            get { return frmParent; }
            set { frmParent = value; }
        }

        public Register()
        {
            InitializeComponent();
        }

        private void Register_Load(object sender, EventArgs e)
        {
            
        }

        private void valid_button_Click(object sender, EventArgs e)
        {
            bool err = false;

            if (email_textBox.Text == "")
            {
                email_textBox.Focus();
                err = true;
            }
            else if (mdp_textBox.Text == "")
            {
                mdp_textBox.Focus();
                err = true;
            }
            else if (mdp2_textBox.Text == "")
            {
                mdp2_textBox.Focus();
                err = true;
            }

            if (email_textBox.Text != "" && mdp_textBox.Text != "" && mdp2_textBox.Text != "")
            {

                if (mdp_textBox.Text != mdp2_textBox.Text)
                {
                    mdp_textBox.Focus();
                    err = true;
                }
                else if (mdp_textBox.Text.Length < 6)
                {
                    mdp_textBox.Focus();
                    err = true;
                }
            }

            if (err == false)
            {
                Configuration.Instance.IsConnected = true;
                this.Close();
            }
        }
    }
}