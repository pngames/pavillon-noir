using System;
using System.Web;
using System.Web.Services;
using System.Web.Services.Protocols;
using KKTRSS.Server.Model;
using KKTRSS.Server.Helpers.DataAccess;
using NHibernate;
using System.Collections;
using System.Collections.Generic;


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
        ISession s = NHibernateHttpModule.CreateSession();
        ITransaction tx = s.BeginTransaction();
        Account acc = null;
        try
        {
            acc = (Account)s.CreateQuery("FROM Account acc WHERE acc.Autologin=?")
                .SetString(0, anAutologin)
                .UniqueResult();
            tx.Commit();
        }
        catch (NHibernate.HibernateException e)
        {
            tx.Rollback();
            throw e;
        }
        finally
        {
            s.Close();
        }
        return (acc != null);
    }

    private Account  GetRegistered(string anAutologin)
    {
        ISession s = NHibernateHttpModule.CreateSession();
        ITransaction tx = s.BeginTransaction();
        Account acc = null;
        try
        {
            acc = (Account)s.CreateQuery("FROM Account acc WHERE acc.Autologin=?")
                .SetString(0, anAutologin)
                .UniqueResult();
            tx.Commit();
        }
        catch (NHibernate.HibernateException e)
        {
            tx.Rollback();
            throw e;
        }
        finally
        {
            s.Close();
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
        ISession s = NHibernateHttpModule.CreateSession();
        ITransaction tx =  s.BeginTransaction();
        Account acc = new Account();
        try
        {
            acc.Email = email;
            acc.Password = password;
            s.Save(acc);
            tx.Commit();
        }
        catch (NHibernate.HibernateException e)
        {
            tx.Rollback();
            throw e;
        }
        finally
        {
            s.Close();
        }
        return acc.Autologin;
    }

    [WebMethod]
    public string Login(string email, string password)
    {
        ISession s = NHibernateHttpModule.CreateSession();
        ITransaction tx = s.BeginTransaction();
        Account acc = null;
        IList list = null;
        try
        {
           acc = (Account)s.CreateQuery("FROM Account acc WHERE acc.Email=? AND acc.Password=?")
                             .SetString(0, email)
                             .SetString(1, password)
                             .UniqueResult();
            tx.Commit();
        }
        catch (NHibernate.HibernateException e)
        {
            tx.Rollback();
            throw e;
        }
        finally
        {
            s.Close();
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
        ISession s = NHibernateHttpModule.CreateSession();
        ITransaction tx = s.BeginTransaction();
        IList ret = null;
        try
        {
            if (IsRegistered(sessionId) == false)
                return ret;
            ret = s.CreateQuery("FROM Group").List();
            tx.Commit();
        }
        catch (HibernateException e)
        {
            tx.Rollback();
            throw e;
        }
        finally
        {
            s.Close();
        }
        return ret;
    }

    [WebMethod]
    public IList GetMyGroupList(string sessionId)
    {
        ISession s = NHibernateHttpModule.CreateSession();
        ITransaction tx = s.BeginTransaction();
        IList ret = null;
        Account acc = null;
        try
        {
            if ((acc = GetRegistered(sessionId)) == null)
                return ret;
            ret = (IList)  acc.Groups;
            tx.Commit();
        }
        catch (HibernateException e)
        {
            tx.Rollback();
            throw e;
        }
        finally
        {
            s.Close();
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
