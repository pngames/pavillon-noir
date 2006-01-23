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

namespace NRSS.Winformclient
{
    public partial class UserLogin : Form
    {
        NRSS.Winformclient.NRSSServer.Service serviceAdd = new NRSS.Winformclient.NRSSServer.Service();
        public UserLogin()
        {
            InitializeComponent();
        }

        private void buttonOk_Click(object sender, EventArgs e)
        {
            /// Verif user/passwd
            bool done = false;
            User user = new User();

            try
            {
                user = serviceAdd.logon(textBoxUser.Text, textBoxPasswd.Text);
            }
            catch (SoapException)
            {
                labelError.Visible = true;
                labelError.Text = "Error: Invalid user or password";
            }
                if (user.Confirmed == true)
                {
                    this.DialogResult = DialogResult.OK;
                    Close();
                }
        }

        private void buttonCreateAccount_Click(object sender, EventArgs e)
        {
            CreateUser CreateUserDialog = new CreateUser();

            CreateUserDialog.ShowDialog();

            //this.DialogResult = DialogResult.OK;
        }
    }
}