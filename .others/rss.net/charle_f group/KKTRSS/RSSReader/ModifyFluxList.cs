using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace RSSReader
{
    public partial class ModifyFluxList : Form
    {
        private RSSReaderMain frmParent;
        private List<string> _serverList = new List<string>();
        private List<string> _clientList = new List<string>();

        public RSSReaderMain FormParent
        {
            get { return frmParent; }
            set { frmParent = value; }
        }

        public ModifyFluxList()
        {
            InitializeComponent();
            _serverList.Add("toto");
            _serverList.Add("tata");
            _clientList.Add("tutu");
            _clientList.Add("titi");
        }

        private void ModifyFluxList_Load(object sender, EventArgs e)
        {
            refreshLists();
        }

        private void refreshLists()
        {
            foreach (string fluxName in _serverList)
            {
                server_listBox.Items.Add(fluxName);
            }
            foreach (string fluxName in _clientList)
            {
                client_listBox.Items.Add(fluxName);
            }
        }

        private void add_button_Click(object sender, EventArgs e)
        {

        }

        private void delete_button_Click(object sender, EventArgs e)
        {

        }

        private void server_listBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (server_listBox.SelectedItem != null)
                add_button.Enabled = true;
            else
                add_button.Enabled = false;
        }

        private void client_listBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (client_listBox.SelectedItem != null)
                delete_button.Enabled = true;
            else
                delete_button.Enabled = false;
        }

        private void valid_button_Click(object sender, EventArgs e)
        {

        }

        private void server_listBox_Leave(object sender, EventArgs e)
        {
            
            add_button.Enabled = false;
        }

        private void client_listBox_Leave(object sender, EventArgs e)
        {
            delete_button.Enabled = false;
        }
    }
}