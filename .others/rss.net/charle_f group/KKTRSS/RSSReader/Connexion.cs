using System;
using System.Configuration;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace RSSReader
{
    public partial class Connexion : Form
    {
        private RSSReaderMain frmParent;
        public RSSReaderMain FormParent
        {
            get { return frmParent; }
            set { frmParent = value; }
        }

        public Connexion()
        {
            InitializeComponent();
        }

        private void Connexion_Load(object sender, EventArgs e)
        {
            email_textBox.Text = Properties.Settings.Default.login;
            mdp_textBox.Text = Properties.Settings.Default.pass;
            rememberMe_checkBox.Checked =  Properties.Settings.Default.rememberMe;
        }        

        private void showMsgBoxInfoMiss(String chp)
        {
            string caption = "Information manquante.";
            string message = "Le champ " + chp + " n'est pas correctement rempli.";

            MessageBoxButtons buttons = MessageBoxButtons.OK;
            MessageBox.Show(message, caption, buttons);
        }

        public void load_button_Click(object sender, EventArgs e)
        {
            if (email_textBox.Text == "" && mdp_textBox.Text == "")
            {
                email_textBox.Focus();
                showMsgBoxInfoMiss("email");
            }
            else
            {
                if (email_textBox.Text == "")
                {
                    email_textBox.Focus();
                    showMsgBoxInfoMiss("email");
                }

                if (mdp_textBox.Text == "")
                {
                    mdp_textBox.Focus();
                    showMsgBoxInfoMiss("mot de passe");
                }
            }
           

            if (email_textBox.Text != "" && mdp_textBox.Text != "")
            {

                if (frmParent.connectionToServer(email_textBox.Text, mdp_textBox.Text) == false)
                {
                    string caption = "Information incorrecte.";
                    string message = "Votre Email est incorrect ou votre mot de passe ne correspond pas.";

                    MessageBoxButtons buttons = MessageBoxButtons.OK;
                    MessageBox.Show(message, caption, buttons);
                }
                else
                {
                    Properties.Settings.Default.rememberMe = rememberMe_checkBox.Checked;
                    Properties.Settings.Default.Save();
                    this.Close();
                }
            }
            
        }

        public void register_button_Click(object sender, EventArgs e)
        {
            //frmParent.showConnexionWin();  
            this.Hide();
            this.Close();
            Register registerWin = new Register();
            registerWin.FormParent = frmParent;
            registerWin.ShowDialog();
        }

    }
}