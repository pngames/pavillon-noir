using System;
using SpeechLib;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace RSSReader
{
    public partial class VocalOptions : Form
    {
        private RSSReaderMain frmParent;
        public RSSReaderMain FormParent
        {
            get { return frmParent; }
            set { frmParent = value; }
        }

        public VocalOptions()
        {
            InitializeComponent();
        }

        private void prononce_button_Click(object sender, EventArgs e)
        {
            if (prononce_textBox.Text != "")
            {
                try
                {
                    SpVoice voix = new SpVoice();
                    SpeechVoiceSpeakFlags flags = SpeechVoiceSpeakFlags.SVSFlagsAsync;
                   // voix.Voice = voix.GetVoices("", "").Item(Convert.ToInt32(voice_numericUpDown.Value));

                    voix.Speak(prononce_textBox.Text, flags);
                    voix.Volume = Convert.ToInt32(volume_numericUpDown.Value);
                }
                catch (Exception ex)
                {
                }
            }
        }

        private void valid_button_Click(object sender, EventArgs e)
        {
            Properties.Settings.Default.synthVolume = Convert.ToInt32(volume_numericUpDown.Value);
            Properties.Settings.Default.synthVoice = Convert.ToInt32(voice_numericUpDown.Value);
            Properties.Settings.Default.Save();
            this.Close();
        }

        private void VocalOptions_Load(object sender, EventArgs e)
        {
            volume_numericUpDown.Value = Properties.Settings.Default.synthVolume;
            voice_numericUpDown.Value = Properties.Settings.Default.synthVoice;
        }
    }
}