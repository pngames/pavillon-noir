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
            return "";
        }

        if (acc == null)
            return "";
        return acc.Autologin;
    }


    [WebMethod]
    [System.Xml.Serialization.XmlInclude(typeof(KKTRSS.Server.Model.Account))]
    public IList ListAccountInGroup(string sessionId, long groupId)
    {
        if (IsRegistered(sessionId) == false)
            return null;
        IList accList = null;
        Group grp = (Group)NHibernateHttpModule.CurrentSession.Load(typeof(Group), groupId);
        if (grp == null)
            return null;
        accList = new ArrayList(grp.Accounts);
        return accList;
    }


    [WebMethod]
    [System.Xml.Serialization.XmlInclude(typeof(KKTRSS.Server.Model.RssFeedRef))]
    public IList ListAvailableRssFeedsInGroup(string sessionId, long groupId)
    {
        if (IsRegistered(sessionId) == false)
            return null;
        IList feedList = null;
        feedList = NHibernateHttpModule.CurrentSession
        .CreateQuery("from RssFeedRef rfr where rfr.Group.Id=?")
        .SetInt64(0, groupId)
        .List();
        foreach (RssFeedRef it in feedList)
        {
            it.RssCache = "";
        }
        return feedList;
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
            // NHibernateHttpModule.CurrentSession.Load(rfr, RssFeedId);
            System.Type t = typeof(RssFeedRef);
            rfr = (RssFeedRef)NHibernateHttpModule.CurrentSession.Load(t, RssFeedId);
            if (rfr == null)
            {
                NHibernateHttpModule.RollbackTransaction();
                return false;
            }
            acc.SubscribedRssFeeds.Add(rfr);
            NHibernateHttpModule.CurrentSession.Update(acc);
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
    public bool RssFeedUnsubscribe(string sessionId, long RssFeedId)
    {
        Account acc = GetRegistered(sessionId);
        Boolean isSucceed = false;
        int index = -1;
        if (acc == null)
        {
            return isSucceed;
        }
        try
        {
            NHibernateHttpModule.BeginTranaction();


            foreach (RssFeedRef rfr in acc.SubscribedRssFeeds)
            {
                if (rfr.Id == RssFeedId)
                {
                    index = acc.SubscribedRssFeeds.IndexOf(rfr);
                    isSucceed = true;
                    break;
                }
            }

            if (index != -1)
            {
                acc.SubscribedRssFeeds.RemoveAt(index);
                NHibernateHttpModule.CurrentSession.Update(acc);
                NHibernateHttpModule.CommitTranction();
            }
            else
                NHibernateHttpModule.RollbackTransaction();
        }
        catch (HibernateException e)
        {
            NHibernateHttpModule.RollbackTransaction();
        }

        return isSucceed;


    }

   
    [WebMethod]
    public string GetMyRssFeed(string sessionId)
    {
        Account acc = GetRegistered(sessionId);
        if (acc == null)
            return null;
        RssFeed MyFeed = new RssFeed();
        //MyFeed.Encoding = System.Text.Encoding.GetEncoding("ISO-8859-1");
        IList myRssFeeds = acc.SubscribedRssFeeds;
        foreach (RssFeedRef anRssfeedRef in myRssFeeds)
        {
            RssFeed feed = RssFeed.ReadFromString(anRssfeedRef.RssCache);
            foreach (RssChannel chan in feed.Channels)
            {
                foreach (RssItem it in chan.Items)
                {
                    if (NHibernateHttpModule.CurrentSession
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
        string line = "";
        // erreur dans RSS.net si le feed ne contient pas de channel
        if (MyFeed.Channels.Count > 0)
        {
            MyFeed.Write(@"" + acc.Autologin + "temp.file");
            //  MyFeed.Write(@"C:\kktrss_db\" + acc.Autologin + "temp.file");
            StreamReader sr = new StreamReader(@"" + acc.Autologin + "temp.file", System.Text.Encoding.GetEncoding("ISO-8859-1"));
            //  StreamReader sr = new StreamReader(@"C:\kktrss_db\" + acc.Autologin + "temp.file", System.Text.Encoding.GetEncoding("ISO-8859-1"));
            MemoryStream ms = new MemoryStream();
            MyFeed.Write(ms);
            line = sr.ReadLine();
            while (sr.EndOfStream == false)
            {
                line += sr.ReadLine();
            }

            sr.Close();
        }
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
            return null;
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
            return null;
        }
        return ret;
    }


    [WebMethod]
    public bool AddGroup(string sessionId, string groupName, bool isPrivate)
    {
        Boolean isSucceed = false;
        Account acc = GetRegistered(sessionId);
        Group grp = null;
        if (acc == null)
            return isSucceed;
        try
        {
            NHibernateHttpModule.BeginTranaction();
            grp = new Group();
            grp.Name = groupName;
            grp.Owner = acc;
            grp.Privacy = isPrivate;
            if (grp.Accounts == null)
                grp.Accounts = new ArrayList();
            grp.Accounts.Add(acc);
            NHibernateHttpModule.CurrentSession.Save(grp);
            NHibernateHttpModule.CommitTranction();
            isSucceed = true;
        }
        catch(HibernateException e)
        {
            NHibernateHttpModule.RollbackTransaction();
            return isSucceed;
        }
        return isSucceed;
    }

    [WebMethod]
    public bool DelGroup(string sessionId, long groupId)
    {
        Boolean isSucceed = false;
        Account acc = GetRegistered(sessionId);
        Group grp = null;
        if (acc == null)
            return isSucceed;
        try
        {
            NHibernateHttpModule.BeginTranaction();
            grp = (Group) NHibernateHttpModule.CurrentSession.Load(typeof(Group), groupId);
            if (grp == null)
                return isSucceed;
            if (grp.Owner.Id == acc.Id || acc.Email == "default")
                NHibernateHttpModule.CurrentSession.Delete(grp);
            NHibernateHttpModule.CommitTranction();
            isSucceed = true;
        }
        catch (HibernateException e)
        {
            NHibernateHttpModule.RollbackTransaction();
            return isSucceed;
        }
        return isSucceed;
    }

    [WebMethod]
    public bool AddAccountToGroup(string sessionId, long groupId, long AccountId)
    {
        Boolean isSucceed = false;
        Account acc = GetRegistered(sessionId);
        Group grp = null;
        Account acc2Add = null;
        if (acc == null)
            return isSucceed;
        try
        {
            NHibernateHttpModule.BeginTranaction();
            grp = (Group)NHibernateHttpModule.CurrentSession.Load(typeof(Group), groupId);
            acc2Add = (Account)NHibernateHttpModule.CurrentSession.Load(typeof(Account), AccountId);
            if (grp == null || acc2Add == null)
                return isSucceed;
            if (grp.Owner.Id != acc.Id && acc.Email != "default")
                return isSucceed;
            grp.Accounts.Add(acc2Add);
            NHibernateHttpModule.CurrentSession.Update(grp);
            NHibernateHttpModule.CommitTranction();
            isSucceed = true;
        }
        catch (HibernateException e)
        {
            NHibernateHttpModule.RollbackTransaction();
            return isSucceed;
        }
        return isSucceed;
    }

    [WebMethod]
    public bool DelAccountFromGroup(string sessionId, long groupId, long AccountId)
    {
        Boolean isSucceed = false;
        Account acc = GetRegistered(sessionId);
        Group grp = null;
        Account acc2Add = null;
        if (acc == null)
            return isSucceed;
        try
        {
            NHibernateHttpModule.BeginTranaction();
            grp = (Group)NHibernateHttpModule.CurrentSession.Load(typeof(Group), groupId);
            acc2Add = (Account)NHibernateHttpModule.CurrentSession.Load(typeof(Account), AccountId);
            if (grp == null || acc2Add == null)
                return isSucceed;
            if (grp.Owner.Id != acc.Id && acc.Email != "default" && acc.Id != acc2Add.Id)
                return isSucceed;
            grp.Accounts.Remove(acc2Add);
            NHibernateHttpModule.CurrentSession.Update(grp);
            NHibernateHttpModule.CommitTranction();
            isSucceed = true;
        }
        catch (HibernateException e)
        {
            NHibernateHttpModule.RollbackTransaction();
            return isSucceed;
        }
        return isSucceed;
    }

    [WebMethod]
    public bool DelFeedFromGroup(string sessionId, long groupId, long FeedId)
    {
        //TODO
        return false;
    }

    [WebMethod]
    public bool AddFeedToGroup(string sessionId, long groupId, long FeedId)
    {
        //TODO
        return false;
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
        catch (HibernateException e)
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
