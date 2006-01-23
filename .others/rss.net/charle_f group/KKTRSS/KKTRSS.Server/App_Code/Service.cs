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


[WebService(Namespace = "http://tempuri.org/")]
[WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
public class Service : System.Web.Services.WebService
{
    public Service () {

        //Uncomment the following line if using designed components 
        //InitializeComponent(); 
    }


    private Boolean IsRegistered(string anAutologin)
    {
        Account acc = null;
        try
        {
            acc = (Account) NHibernateHttpModule.CurrentSession
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

    private Account  GetRegistered(string anAutologin)
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
    public string GenerateShema() {
        KKTRSS.Server.Helpers.DataAccess.SchemaUtility.ExportSchema() ;
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
    public int[] ListAvailableRssFeedsInGroup(string sessionId, int groupId)
    {
        int[] ret = {1, 2};
        return ret;
    }

    [WebMethod]
    public int[] ListAvailableRssFeeds(string sessionId)
    {
        return ListAvailableRssFeedsInGroup(sessionId, 0);
    }

    [WebMethod]
    public System.Collections.ArrayList RssFeedSubscribe(string sessionId, int RssRlowId)
    {
        return new System.Collections.ArrayList();
    }

    [WebMethod]
    public bool RssFeedUnSubscribe(string sessionId, int RssFeedId)
    {
        return false;
    }

    [WebMethod]
    public int[] GetMyRssFeedIdList(string sessionId)
    {
        int[] ret = { 1, 2 };
        return ret;
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
    public IList GetMyGroupList(string sessionId)
    {
        IList ret = null;
        Account acc = null;
        try
        {
            if ((acc = GetRegistered(sessionId)) == null)
                return ret;
            ret = (IList)acc.Groups;
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



}
