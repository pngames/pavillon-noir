using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using SpeechLib;
using Rss;

namespace RSSReader
{
    class VocalThread
    {
#region Members
        private RSSReaderMain _mainForm;
        private RssFeed _rssFeed;
        private RssItem _firstItem;
        private SpVoice mainVoice = new SpVoice();

#endregion

        private string readNewsItem(RssItem rssItem)
        {
            string sentence = "";
            if (rssItem.Title != "")
                sentence += "Titre " + System.Web.HttpUtility.HtmlDecode(rssItem.Title) + ". ";
            if (rssItem.Author != "")
                sentence += "Auteur " + System.Web.HttpUtility.HtmlDecode(rssItem.Author) + ". ";
            if (rssItem.Description != "")
                sentence += "Description " + System.Web.HttpUtility.HtmlDecode(rssItem.Description) + ". ";
            if (rssItem.PubDate.ToString() != "")
                sentence += "Date " + rssItem.PubDate.ToShortDateString() + ". ";
            return sentence;
        }

        private void vocal_SpellText(string text)
        {
            try
            {
                SpeechVoiceSpeakFlags flags = SpeechVoiceSpeakFlags.SVSFlagsAsync | SpeechVoiceSpeakFlags.SVSFPurgeBeforeSpeak;
                mainVoice.Volume = Properties.Settings.Default.synthVolume;
                mainVoice.Speak(text, flags);

                int lngHandle = mainVoice.SpeakCompleteEvent();
                bool lngRtn = mainVoice.WaitUntilDone(System.Threading.Timeout.Infinite);

            }
            catch
            {
            }
        }

        public VocalThread(RSSReaderMain mainForm, RssFeed rssFeed, RssItem item)
        {
            _mainForm = mainForm;
            _rssFeed = rssFeed;
            _firstItem = item;
        }
    }
}
