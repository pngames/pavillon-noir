using System;
using System.Web;
using System.Web.Services;
using System.Web.Services.Protocols;
using KKTRSS.Server.Model;
using KKTRSS.Server.Helpers.DataAccess;
using NHibernate;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using Rss;
using System.Net;
using System.IO;


[WebService(Namespace = "http://tempuri.org/")]
[WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
public class Service : System.Web.Services.WebService
{
    public Service()
    {

        //Uncomment the following line if using designed components 
        //InitializeComponent(); 
    }


    private Boolean IsRegistered(string anAutologin)
    {
        Account acc = null;
        try
        {
            acc = (Account)NHibernateHttpModule.CurrentSession
                .CreateQuery("FROM Account acc WHERE acc.Autologin=?")
                .SetString(0, anAutologin)
                .UniqueResult();
        }
        catch (NHibernate.HibernateException e)
        {
            throw e;
        }
        return (acc != null);
    }

    private Account GetRegistered(string anAutologin)
    {
        Account acc = null;
        try
        {
            acc = (Account)NHibernateHttpModule.CurrentSession
                .CreateQuery("FROM Account acc WHERE acc.Autologin=?")
                .SetString(0, anAutologin)
                .UniqueResult();
        }
        catch (NHibernate.HibernateException e)
        {
            throw e;
        }
        return acc;
    }

    [WebMethod]
    public string GenerateShema()
    {
        KKTRSS.Server.Helpers.DataAccess.SchemaUtility.ExportSchema();
        Register("default", "kkt");

        return "Generation successfull";

    }

    [WebMethod]
    public string Register(string email, string password)
    {
        NHibernateHttpModule.BeginTranaction();
        Account acc = new Account();
        try
        {
            acc.Email = email;
            acc.Password = password;
            NHibernateHttpModule.CurrentSession.Save(acc);
            NHibernateHttpModule.CommitTranction();
        }
        catch (NHibernate.HibernateException e)
        {
            NHibernateHttpModule.RollbackTransaction();
            throw e;
        }
        return acc.Autologin;
    }

    [WebMethod]
    public string Login(string email, string password)
    {
        Account acc = null;
        IList list = null;
        try
        {
            acc = (Account)NHibernateHttpModule.CurrentSession
                .CreateQuery("FROM Account acc WHERE acc.Email=? AND acc.Password=?")
                .SetString(0, email)
                .SetString(1, password)
                .UniqueResult();
        }
        catch (NHibernate.HibernateException e)
        {
            throw e;
        }

        if (acc == null)
            return "";
        return acc.Autologin;
    }

    [WebMethod]
    public IList ListAvailableRssFeedsInGroup(string sessionId, int groupId)
    {
        int[] ret = { 1, 2 };
        return ret;
    }

    [WebMethod]
    [System.Xml.Serialization.XmlInclude(typeof(KKTRSS.Server.Model.RssFeedRef))]
    public IList ListAvailableRssFeeds(string sessionId)
    {
        if (IsRegistered(sessionId) == false)
            return null;
        IList feedList = null;
        feedList = NHibernateHttpModule.CurrentSession
        .CreateQuery("from RssFeedRef rfr where rfr.Group=?")
        .SetEntity(0, GetDefaultGroup())
        .List();
        foreach (RssFeedRef it in feedList)
        {
            it.RssCache = "";
        }
        return feedList;
    }

    [WebMethod]
    [System.Xml.Serialization.XmlInclude(typeof(KKTRSS.Server.Model.RssFeedRef))]
    public IList ListSubscribedRssFeeds(string sessionId)
    {
        Account acc = GetRegistered(sessionId);
        if (acc == null)
            return null;
        IList feedList = null;
        feedList = new ArrayList(acc.SubscribedRssFeeds);
        foreach (RssFeedRef it in feedList)
        {
            it.RssCache = "";
        }
        return feedList;
    }

    [WebMethod]
    public bool RssFeedSubscribe(string sessionId, long RssFeedId)
    {
        Account acc = GetRegistered(sessionId);
        if (acc == null)
            return false;
        try
        {

            NHibernateHttpModule.BeginTranaction();
            RssFeedRef rfr = new RssFeedRef();
            NHibernateHttpModule.CurrentSession.Load(rfr, RssFeedId);
            if (rfr == null)
            {
                NHibernateHttpModule.RollbackTransaction();
                return false;
            }
            acc.SubscribedRssFeeds.Add(rfr);
            NHibernateHttpModule.CurrentSession.Update(acc);
            NHibernateHttpModule.CommitTranction();
        }
        catch(HibernateException e)
        {
            NHibernateHttpModule.RollbackTransaction();
            return false;
        }
        return true;
    }

    [WebMethod]
    public string GetMyRssFeed(string sessionId)
    {
        Account acc = GetRegistered(sessionId);
        if (acc == null)
            return null;
        RssFeed MyFeed = new RssFeed();
        IList myRssFeeds = acc.SubscribedRssFeeds;
        foreach (RssFeedRef anRssfeedRef in myRssFeeds)
        {
            RssFeed feed = RssFeed.ReadFromString(anRssfeedRef.RssCache);
            foreach (RssChannel chan in feed.Channels)
            {
                foreach(RssItem it in chan.Items)
                {
                   if( NHibernateHttpModule.CurrentSession
                     .CreateQuery("from ReadRssItem rri where rri.HashCode=? and rri.Account=?")
                     .SetString(0, it.HashID)
                     .SetEntity(1, acc).List().Count > 0)
                   {
                       it.IsRead = true;
                   }
                }
                MyFeed.Channels.Add(chan);
            }
        }
        MyFeed.Write(@"" + acc.Autologin + "temp.file");
        StreamReader sr = new StreamReader(@"" + acc.Autologin + "temp.file");
        MemoryStream ms = new MemoryStream();
        MyFeed.Write(ms);
        string line = sr.ReadLine();
        while (sr.EndOfStream == false)
        {
            line += sr.ReadLine();
        }

        sr.Close();

        return line;

    }

    [WebMethod]
    [System.Xml.Serialization.XmlInclude(typeof(KKTRSS.Server.Model.Group))]
    public IList GetGroupList(string sessionId)
    {
        IList ret = null;
        if (IsRegistered(sessionId) == false)
            return ret;
        try
        {
            ret = NHibernateHttpModule.CurrentSession.CreateQuery("FROM Group").List();
        }
        catch (HibernateException e)
        {
            throw e;
        }
        return ret;
    }

    [WebMethod]
    [System.Xml.Serialization.XmlInclude(typeof(KKTRSS.Server.Model.Group))]
    public IList GetMyGroupList(string sessionId)
    {
        IList ret = null;
        Account acc = null;
        try
        {
            if ((acc = GetRegistered(sessionId)) == null)
                return ret;
            ret = new ArrayList(acc.Groups);
        }
        catch (HibernateException e)
        {
            throw e;
        }
        return ret;
    }

    [WebMethod]
    public string GetRssFeed(string sessionId, int RssFeedId)
    {
        string ret = "";
        return ret;
    }

    [WebMethod]
    public Boolean ImportRssFeed(string autologin, string url, string name, string grpId, Boolean isPrivate)
    {
        if (autologin == null || autologin == "" || url == null || url == "")
            return false;
        Account acc = null;
        RssFeedRef rssRef = new RssFeedRef();
        Group grp = null;
        try
        {
            NHibernateHttpModule.BeginTranaction();
            if (grpId == null || grpId == "")
            {
                acc = (Account)NHibernateHttpModule.CurrentSession
                  .CreateQuery("from Account acc where acc.Autologin=?")
                  .SetString(0, autologin)
                  .UniqueResult();

                if (isPrivate == false)
                {
                    grp = GetDefaultGroup();
                }
                else
                {
                    grp = GetMainUserGroup(acc.Email);
                }
            }
            else
            {
                grp = GetDefaultGroup();
            }
            rssRef.Group = grp;
            rssRef.Url = url;
            rssRef.Name = name;
            NHibernateHttpModule.CurrentSession.Save(rssRef);
            NHibernateHttpModule.CommitTranction();
        }
        catch (HibernateException e)
        {
            NHibernateHttpModule.RollbackTransaction();
            return false;
        }
        return true;
    }

    [WebMethod]
    public bool MarkAsRead(string session, string ItemHashCode)
    {
        Account acc = GetRegistered(session);
        if (acc == null)
        {
            return false;
        }
        try
        {
            NHibernateHttpModule.BeginTranaction();
            ReadRssItem rri = new ReadRssItem();
            rri.HashCode = ItemHashCode;
            rri.Account = acc;
            NHibernateHttpModule.CurrentSession.Save(rri);
            NHibernateHttpModule.CommitTranction();
        }
        catch(HibernateException e)
        {
            NHibernateHttpModule.RollbackTransaction();
            return false;
        }
        return true;
    }
    private Group GetDefaultGroup()
    {
        return (Group)NHibernateHttpModule.CurrentSession
                       .CreateQuery("from Group grp where grp.Name='default'")
                       .UniqueResult();
    }

    private Group GetMainUserGroup(string email)
    {
        return (Group)NHibernateHttpModule.CurrentSession
                       .CreateQuery("from Group grp where grp.Name=?")
                       .SetString(0, email)
                       .UniqueResult();
    }



}
