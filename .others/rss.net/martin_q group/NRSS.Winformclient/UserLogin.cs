using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace NRSS.Winformclient
{
    public partial class UserLogin : Form
    {
        public UserLogin()
        {
            InitializeComponent();
        }

        private void buttonOk_Click(object sender, EventArgs e)
        {
            /// Verif user/passwd

            if (textBoxPasswd.Text.Length == 0 || textBoxUser.Text.Length == 0)
            {
                labelError.Visible = true;
            }
            else
            {
                this.DialogResult = DialogResult.OK;
                Close();
            }
        }
    }
}