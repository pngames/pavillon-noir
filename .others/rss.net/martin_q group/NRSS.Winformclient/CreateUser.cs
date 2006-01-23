using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using NRSS.Winformclient.NRSSServer;

namespace NRSS.Winformclient
{
    public partial class CreateUser : Form
    {
        NRSS.Winformclient.NRSSServer.Service serviceAdd = new NRSS.Winformclient.NRSSServer.Service();

        public CreateUser()
        {
            InitializeComponent();
        }

        private void buttonOk_Click(object sender, EventArgs e)
        {
            User newUser = new User();

            newUser.Email = textBoxEmail.Text;
            if (textBoxPasswd1.Text == textBoxPasswdConf.Text)
            {
                newUser.Passwd = textBoxPasswd1.Text;
                try
                {
                    serviceAdd.createUser(newUser);
                }
                catch (Exception)
                {
                    labelError.Visible = true;
                    labelError.Text = "Error: Cannot create account";
                }
                this.Close();
            }
            else {
                labelError.Text = "Error: Passwords are different";
                labelError.Visible = true;
            }
        }
    }
}