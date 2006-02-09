using System;
using System.Web;
using NHibernate;
using NHibernate.Cfg;

namespace KKTRSS.Server.Helpers.DataAccess
{
    /// <summary> Summary description for NHibernateHttpModule. </summary>
    public class NHibernateHttpModule : IHttpModule
    {
        // this is only used if not running in HttpModule mode
        protected static ISessionFactory m_factory;

        // this is only used if not running in HttpModule mode
        private static ISession m_session;

        private static readonly string KEY_NHIBERNATE_FACTORY = "NHibernateSessionFactory";
        private static readonly string KEY_NHIBERNATE_SESSION = "NHibernateSession";
        private static readonly string KEY_NHIBERNATE_TRANSACTION = "NHibernateTransaction";

        public void Init(HttpApplication context)
        {
            log4net.Config.XmlConfigurator.Configure();
            context.EndRequest += new EventHandler(context_EndRequest);
        }

        public void Dispose()
        {
            if (m_session != null)
            {
                m_session.Close();
                m_session.Dispose();
            }

            if (m_factory != null)
            {
                m_factory.Close();
            }
        }

        private void context_BeginRequest(object sender, EventArgs e)
        {
            HttpApplication application = (HttpApplication)sender;
            HttpContext context = application.Context;

            context.Items[KEY_NHIBERNATE_SESSION] = CreateSession();
        }

        private void context_EndRequest(object sender, EventArgs e)
        {
            HttpApplication application = (HttpApplication)sender;
            HttpContext context = application.Context;

            ISession session = context.Items[KEY_NHIBERNATE_SESSION] as ISession;
            if (session != null)
            {
                try
                {
                    session.Flush();
                    session.Close();
                }
                catch { }
            }

            context.Items[KEY_NHIBERNATE_SESSION] = null;
        }

        protected static ISessionFactory CreateSessionFactory()
        {
            Configuration config;
            ISessionFactory factory;

            config = new Configuration();

            if (config == null)
            {
                throw new InvalidOperationException("NHibernate configuration is null.");
            }

            config.Configure();

            factory = config.BuildSessionFactory();

            if (factory == null)
            {
                throw new InvalidOperationException("Call to Configuration.BuildSessionFactory() returned null.");
            }
            else
            {
                return factory;
            }
        }

        public static ISessionFactory CurrentFactory
        {
            get
            {
                if (HttpContext.Current == null)
                {
                    // running without an HttpContext (non-web mode)
                    // the nhibernate session is a singleton in the app domain
                    if (m_factory != null)
                    {
                        return m_factory;
                    }
                    else
                    {
                        m_factory = CreateSessionFactory();

                        return m_factory;
                    }
                }
                else
                {
                    // running inside of an HttpContext (web mode)
                    // the nhibernate session is a singleton to the http request
                    HttpContext currentContext = HttpContext.Current;

                    ISessionFactory factory = currentContext.Application[KEY_NHIBERNATE_FACTORY] as ISessionFactory;

                    if (factory == null)
                    {
                        factory = CreateSessionFactory();
                        currentContext.Application[KEY_NHIBERNATE_FACTORY] = factory;
                    }

                    return factory;
                }
            }
        }

        public static ISession CreateSession()
        {
            ISessionFactory factory;
            ISession session;

            factory = NHibernateHttpModule.CurrentFactory;

            if (factory == null)
            {
                throw new InvalidOperationException("Call to Configuration.BuildSessionFactory() returned null.");
            }

            session = factory.OpenSession();

            if (session == null)
            {
                throw new InvalidOperationException("Call to factory.OpenSession() returned null.");
            }

            return session;
        }

        public static ISession CurrentSession
        {
            get
            {

                if (HttpContext.Current == null)
                {
                    // running without an HttpContext (non-web mode)
                    // the nhibernate session is a singleton in the app domain
                    if (m_session != null)
                    {
                        return m_session;
                    }
                    else
                    {
                        m_session = CreateSession();

                        return m_session;
                    }
                }
                else
                {
                    // running inside of an HttpContext (web mode)
                    // the nhibernate session is a singleton to the http request
                    HttpContext currentContext = HttpContext.Current;

                    ISession session = currentContext.Items[KEY_NHIBERNATE_SESSION] as ISession;

                    if (session == null)
                    {
                        session = CreateSession();
                        currentContext.Items[KEY_NHIBERNATE_SESSION] = session;
                    }

                    return session;
                }
            }
        }

        public static void BeginTranaction()
        {
            HttpContext currentContext = HttpContext.Current;
            ITransaction tx = currentContext.Items[KEY_NHIBERNATE_TRANSACTION] as ITransaction;
            try
            {
                if (tx == null)
                {
                    tx = CurrentSession.BeginTransaction();
                    currentContext.Items[KEY_NHIBERNATE_TRANSACTION] = tx;
                }

            }
            catch (HibernateException e)
            {
                throw  e;// TODO: handle exception 
            } 

        }

        public static void CommitTranction()
        {
            HttpContext currentContext = HttpContext.Current;
            ITransaction tx = currentContext.Items[KEY_NHIBERNATE_TRANSACTION] as ITransaction;
            try
            {
                if (tx != null && !tx.WasCommitted && !tx.WasRolledBack)
                {
                    tx.Commit();
                }
                currentContext.Items[KEY_NHIBERNATE_TRANSACTION] = null;
            }
            catch (HibernateException e)
            {
                throw e;// TODO: handle exception 
            } 

        }

        public static void RollbackTransaction()
        {
            HttpContext currentContext = HttpContext.Current;
            ITransaction tx = currentContext.Items[KEY_NHIBERNATE_TRANSACTION] as ITransaction;
            try
            {
                currentContext.Items[KEY_NHIBERNATE_TRANSACTION] = null;
                if (tx != null && !tx.WasCommitted && !tx.WasRolledBack)
                {
                    tx.Rollback();
                }
                currentContext.Items[KEY_NHIBERNATE_TRANSACTION] = null;
            }
            catch (HibernateException e)
            {
                throw e;// TODO: handle exception 
            }
            finally
            {
                CurrentSession.Close();
            } 

        }

    }
}