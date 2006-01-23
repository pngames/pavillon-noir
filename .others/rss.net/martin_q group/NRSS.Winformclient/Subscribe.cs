using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace NRSS.Winformclient
{
    public partial class Subscribe : Form
    {
        public Subscribe()
        {
            InitializeComponent();
            for (int i = 0; i != 5;  i++)
                checkedListBox1.Items.Add("Rss feed " + i.ToString(), CheckState.Unchecked);
        }

        private void checkedListBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            // Envoyer les modifs au serveur
            //checkedListBox1.CheckedItems.Count;
        }
    }
}