using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace RSSScreenSaver
{
    public partial class Register : Form
    {
        private OptionsForm frmParent;
        public OptionsForm FormParent
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

        private void msgBoxGeneric(string head, string content)
        {

            MessageBoxButtons buttons = MessageBoxButtons.OK;
            MessageBox.Show(content, head, buttons);
        }

        private void valid_button_Click(object sender, EventArgs e)
        {
            bool err = false;

            if (email_textBox.Text == "")
            {
                msgBoxGeneric("Login.", "Champ non rempli.");
                email_textBox.Focus();
                err = true;
            }
            else if (mdp_textBox.Text == "")
            {
                msgBoxGeneric("Mot de passe.", "Champ non rempli.");
                mdp_textBox.Focus();
                err = true;
            }
            else if (mdp2_textBox.Text == "")
            {
                msgBoxGeneric("Mot de passe.", "Champ non rempli.");
                mdp2_textBox.Focus();
                err = true;
            }

            if (email_textBox.Text != "" && mdp_textBox.Text != "" && mdp2_textBox.Text != "")
            {

                if (mdp_textBox.Text != mdp2_textBox.Text)
                {
                    msgBoxGeneric("Mot de passe.", "Mots de passe non-identiques.");
                    mdp_textBox.Focus();
                    err = true;

               
                }
                else if (mdp_textBox.Text.Length < 6)
                {
                    msgBoxGeneric("Mot de passe.", "Votre mot de passe doit contenir\n au minimum 6 caracteres.");
                    mdp_textBox.Focus();
                    err = true;
                }
            }

            if (err == false)
            {
                if (frmParent.MainWebService.Register(email_textBox.Text, mdp_textBox.Text) != "")
                {
                    if (frmParent.connectionToServer(email_textBox.Text, mdp_textBox.Text) == false)
                    {
                        msgBoxGeneric("Compte non active.", "Votre compte n'est pas encore active.");
                    }
                    else
                        this.Close();
                }
            }
        }
    
    }
}