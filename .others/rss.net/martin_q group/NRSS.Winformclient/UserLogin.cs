using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using NRSS.Winformclient.NRSSServer;
using NRSS.Winformclient;
using System.Web.Services.Protocols;
using winformclient;

namespace NRSS.Winformclient
{
    public partial class UserLogin : Form
    {
        NRSS.Winformclient.NRSSServer.Service serviceAdd = new NRSS.Winformclient.NRSSServer.Service();
        public UserLogin()
        {
            InitializeComponent();
            if (Properties.Settings.Default.UserLogin.Length != 0 && Properties.Settings.Default.UserPasswd.Length != 0)
            {
                checkBox1.CheckState = CheckState.Checked;
                textBoxUser.Text = Properties.Settings.Default.UserLogin;
                textBoxPasswd.Text = Properties.Settings.Default.UserPasswd;
            }
        }

        private void buttonOk_Click(object sender, EventArgs e)
        {
            /// Verif user/passwd
            bool done = false;

            try
            {
                Form1.uid = serviceAdd.logon(textBoxUser.Text, textBoxPasswd.Text);
            }
            catch (SoapException)
            {
                labelError.Visible = true;
                labelError.Text = "Error: Invalid user or password";
            }
            if (Form1.uid.Length != 0)
            {
                if (checkBox1.CheckState == CheckState.Checked)
                {
                    Properties.Settings.Default.UserLogin = textBoxUser.Text;
                    Properties.Settings.Default.UserPasswd = textBoxPasswd.Text;
                    Properties.Settings.Default.Save();
                }
                else
                {
                    Properties.Settings.Default.UserLogin = "";
                    Properties.Settings.Default.UserPasswd = "";
                    Properties.Settings.Default.Save();
                }
                this.DialogResult = DialogResult.OK;
                Close();
            }
        }

        private void buttonCreateAccount_Click(object sender, EventArgs e)
        {
            CreateUser CreateUserDialog = new CreateUser();

            CreateUserDialog.ShowDialog();
        }
    }
}