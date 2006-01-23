using System;
using System.Data;
using System.Configuration;
using KKTRSS.Server.Helpers.Persistance;
using Iesi.Collections;
using System.Collections;
using System.IO;
using System.Net;
using Rss;
using System.Xml.Serialization;


/// <summary>
/// Summary description for RssFeedRef
/// </summary>
namespace KKTRSS.Server.Model
{
    public class RssFeedRef : APersistant
    {
        public RssFeedRef()
        {
            //
            // TODO: Add constructor logic here
            //
        }
        /*********************************************************************/
        private string _name;

        public string Name
        {
            get { return _name; }
            set { _name = value; }
        }
        /*********************************************************************/
        private string _url;

        public string Url
        {
            get { return _url; }
            set { _url = value; }
        }
        /*********************************************************************/
        private Group _group;

        public Group Group
        {
            get { return _group; }
            set { _group = value; }
        }
        /*********************************************************************/
        private IList _accounts;
        [XmlIgnore]
        public IList Accounts
        {
            get { return _accounts; }
            set { _accounts = value; }
        }
        /*********************************************************************/
        private string _rssCache = null;

        public string RssCache
        {
            get { return _rssCache; }
            set { _rssCache = value; }
        }

        public override NHibernate.LifecycleVeto OnSave(NHibernate.ISession s)
        {
            RssCache = ImportRssFeed(Url);
            if (Name == null || Name == "")
            {
                Name = Url;
            }
            return base.OnSave(s);
        }

        public override NHibernate.LifecycleVeto OnUpdate(NHibernate.ISession s)
        {
            RssCache = ImportRssFeed(Url);
            return base.OnUpdate(s);
        }

        public string ImportRssFeed(string url)
        {
            HttpWebRequest request = null;
            Rss.RssFeed rss = null;
            bool err = true;
            int tried = 0;

            while (err == true)
            {
                try
                {
                    request = (HttpWebRequest)WebRequest.Create(new Uri(url));
                    /*  if (Properties.Settings.Default.useProxy == true)
                      {*/
                    WebProxy proxy = new WebProxy("proxies.epitech.net", 3128);
                    #region
                    proxy.Credentials = new NetworkCredential("dupert_s", "0EbPuiA6");

                    #endregion
                    request.Proxy = proxy;
                    //                }

                    rss = RssFeed.Read(request);
                    err = false;
                }
                catch (Exception ex)
                {
                    err = true;
                }
                if (tried > 10)
                    break;
                tried++;
            }

            rss.Write(@""+Name+"temp.file");
            StreamReader sr = new StreamReader(@"" + Name + "temp.file", System.Text.Encoding.GetEncoding("ISO-8859-1"));
            MemoryStream ms = new MemoryStream();
            rss.Write(ms);
            string line = sr.ReadLine();
            while (sr.EndOfStream == false)
            {
                line += sr.ReadLine();
            }

            sr.Close();

            return line;

        }

    }
}