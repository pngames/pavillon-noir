using System;
using System.Configuration;
using System.Drawing;
using System.Windows.Forms;
//using RSSScreenSaver.Rss;


namespace RSSScreenSaver
{
    public partial class OptionsForm : Form
    {
        private KKTRSS_service.Service _mainWebService = new KKTRSS_service.Service();

        public KKTRSS_service.Service MainWebService
        {
            get { return _mainWebService; }
            set { _mainWebService = value; }
        }

        public OptionsForm()
        {
            InitializeComponent();

            // Load the text boxes from the current settings
            
        }



        // Apply all the changes since apply button was last pressed
        private bool ApplyChanges()
        {

            Properties.Settings.Default.Login = login_textBox.Text;
            Properties.Settings.Default.Pass = pass_textBox.Text;

            Properties.Settings.Default.FadeTime = Convert.ToInt32(fade_numericUpDown.Value);
            Properties.Settings.Default.UseProxy = useProxy_checkBox.Checked;
            bool err = false;
            if (useProxy_checkBox.Checked == true)
            {

                if (proxyLogin_textBox.Text == "")
                    err = true;
                if (proxyPass_textBox.Text == "")
                    err = true;
                if (proxyPort_textBox.Text == "")
                    err = true;
                if (proxyUrl_textBox.Text == "")
                    err = true;

                if (err == false)
                {
                    Properties.Settings.Default.ProxyLogin = proxyLogin_textBox.Text;
                    Properties.Settings.Default.ProxyPass = proxyPass_textBox.Text;
                    Properties.Settings.Default.ProxyPort = Convert.ToInt32(proxyPort_textBox.Text);
                    Properties.Settings.Default.ProxyUrl = proxyUrl_textBox.Text;
                }
                else
                {
                    MessageBoxButtons buttons = MessageBoxButtons.OK;
                    MessageBox.Show("Vous devez remplir tous les champs\npour le proxy.", "Erreur dans les champs proxy", buttons);
                }
            }
           if (err == false)
            Properties.Settings.Default.Save();
        return err;
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
           
           if (ApplyChanges() == false)
                Close();
          
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void OptionsForm_Load(object sender, EventArgs e)
        {

            login_textBox.Text = Properties.Settings.Default.Login;
            pass_textBox.Text = Properties.Settings.Default.Pass;
            fade_numericUpDown.Value = Properties.Settings.Default.FadeTime;


            useProxy_checkBox.Checked = Properties.Settings.Default.UseProxy;
            proxyLogin_textBox.Text = Properties.Settings.Default.ProxyLogin;
            proxyPass_textBox.Text = Properties.Settings.Default.ProxyPass;
            proxyPort_textBox.Text = Convert.ToString(Properties.Settings.Default.ProxyPort);
            proxyUrl_textBox.Text = Properties.Settings.Default.ProxyUrl;

            if (Properties.Settings.Default.UseProxy == true)
            {
                proxyLogin_textBox.Enabled = true;
                proxyPass_textBox.Enabled = true;
                proxyPort_textBox.Enabled = true;
                proxyUrl_textBox.Enabled = true;
                label2.Enabled = true;
                label3.Enabled = true;
                label4.Enabled = true;
                label5.Enabled = true;
            }
            else
            {
                proxyLogin_textBox.Enabled = false;
                proxyPass_textBox.Enabled = false;
                proxyPort_textBox.Enabled = false;
                proxyUrl_textBox.Enabled = false;
                label2.Enabled = false;
                label3.Enabled = false;
                label4.Enabled = false;
                label5.Enabled = false;
            }

        }

        private void useProxy_checkBox_CheckedChanged(object sender, EventArgs e)
        {
            if (useProxy_checkBox.Checked == true)
            {
                proxyLogin_textBox.Enabled = true;
                proxyPass_textBox.Enabled = true;
                proxyPort_textBox.Enabled = true;
                proxyUrl_textBox.Enabled = true;
                label2.Enabled = true;
                label3.Enabled = true;
                label4.Enabled = true;
                label5.Enabled = true;
            }
            else
            {
                proxyLogin_textBox.Enabled = false;
                proxyPass_textBox.Enabled = false;
                proxyPort_textBox.Enabled = false;
                proxyUrl_textBox.Enabled = false;
                label2.Enabled = false;
                label3.Enabled = false;
                label4.Enabled = false;
                label5.Enabled = false;
            }
        }

        private void testConn_button_Click(object sender, EventArgs e)
        {
            if (login_textBox.Text != "" && pass_textBox.Text != "")
            {
               
                if (_mainWebService.Login(login_textBox.Text, pass_textBox.Text) == "")
                {
                    string caption = "Information incorrecte.";
                    string message = "Votre Email est incorrect ou votre mot de passe ne correspond pas.";

                    MessageBoxButtons buttons = MessageBoxButtons.OK;
                    MessageBox.Show(message, caption, buttons);
                }
                else
                {
                    string caption = "Informations correctes.";
                    string message = "Votre compte marche correctement.";

                    MessageBoxButtons buttons = MessageBoxButtons.OK;
                    MessageBox.Show(message, caption, buttons);
                }
            }
        }

        private void newAccount_button_Click(object sender, EventArgs e)
        {
            Register registerWin = new Register();
            registerWin.FormParent = this;
            registerWin.ShowDialog();
        }

        public bool connectionToServer(string login, string pass)
        {
            if (_mainWebService.Login(login, pass) == "")
            {
                return false;
            }
            else
            {
                login_textBox.Text = login;
                pass_textBox.Text = pass;
                return true;
            }
        }
    }
}