using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace RSSReader
{
    public partial class AppOptions : Form
    {
        private RSSReaderMain frmParent;
        public RSSReaderMain FormParent
        {
            get { return frmParent; }
            set { frmParent = value; }
        }

        public AppOptions()
        {
            InitializeComponent();
        }

        private void AppOptions_Load(object sender, EventArgs e)
        {
            
            systray_checkBox.Checked = Properties.Settings.Default.systray;
            tooltip_checkBox.Checked = Properties.Settings.Default.tooltip;
            update_numericUpDown.Value = Properties.Settings.Default.updateTime;

            useProxy_checkBox.Checked = Properties.Settings.Default.useProxy;
            proxyLogin_textBox.Text = Properties.Settings.Default.proxyLogin;
            proxyPass_textBox.Text = Properties.Settings.Default.proxyPass;
            proxyPort_textBox.Text = Convert.ToString(Properties.Settings.Default.proxyPort);
            proxyUrl_textBox.Text = Properties.Settings.Default.proxyUrl;

            if (Configuration.Instance.UseProxy == true)
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

        private void valid_button_Click(object sender, EventArgs e)
        {
            Properties.Settings.Default.systray = systray_checkBox.Checked;
            Properties.Settings.Default.tooltip = tooltip_checkBox.Checked;
            //TODO : check si il ya qu'un int dans la textbox
            Properties.Settings.Default.updateTime = (int)update_numericUpDown.Value;

            Properties.Settings.Default.useProxy = useProxy_checkBox.Checked;
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
                    Properties.Settings.Default.proxyLogin = proxyLogin_textBox.Text;
                    Properties.Settings.Default.proxyPass = proxyPass_textBox.Text;
                    Properties.Settings.Default.proxyPort = Convert.ToInt32(proxyPort_textBox.Text);
                    Properties.Settings.Default.proxyUrl = proxyUrl_textBox.Text;
                }
                else
                {
                    MessageBoxButtons buttons = MessageBoxButtons.OK;
                    MessageBox.Show("Vous devez remplir tous les champs\npour le proxy.", "Erreur dans les champs proxy" , buttons);
                }
            }

            Properties.Settings.Default.Save();
           if (err == false)
            this.Close();

        }

        private void systray_checkBox_CheckedChanged(object sender, EventArgs e)
        {
            if (systray_checkBox.Checked == true)
                tooltip_checkBox.Enabled = true;
            if (systray_checkBox.Checked == false)
                tooltip_checkBox.Enabled = false;
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
    }
}