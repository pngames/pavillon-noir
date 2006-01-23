using System;
using System.Web;
using NHibernate;
using NHibernate.Cfg;
using System.Reflection;
using System.IO;
using NHibernate.Tool.hbm2ddl;
using NRSS.mapping;

namespace NRSS.Server.DataAccess
{
  /// <summary> Summary description for NHibernateHttpModule. </summary>
  public class NHibernateHttpModule : IHttpModule
  {
	// this is only used if not running in HttpModule mode
	protected static ISessionFactory m_factory;
	protected static bool _newbdd = false;

	// this is only used if not running in HttpModule mode
	private static ISession m_session;

	private static readonly string KEY_NHIBERNATE_FACTORY = "NHibernateSessionFactory";
	private static readonly string KEY_NHIBERNATE_SESSION = "NHibernateSession";

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
		throw new InvalidOperationException("NHibernate configuration is null.");

	  if (!File.Exists(@".\nrss.db"))
	  {
		_newbdd = true;

		config.SetProperty(@"hibernate.connection.connection_string", @"Data Source=.\nrss.db;Version=3;New=True");

		config.Configure();

		SchemaExport exporter = new SchemaExport(config);
		exporter.Drop(true, true);
		exporter.Create(true, true);

		config = new Configuration();
	  }

	  config.SetProperty(@"hibernate.connection.connection_string", @"Data Source=.\nrss.db;Version=3");

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

	  _newbdd = false;

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

	  if (_newbdd)
	  {
		ITransaction tx = null;

		try
		{
		  tx = session.BeginTransaction();

		  Feed feed1 = new Feed();
		  feed1.Type = "rss";
		  feed1.Fils = "http://pisani.blog.lemonde.fr/pisani/index.rdf";
		  feed1.FilsPort = 80;
		  Feed feed2 = new Feed();
		  feed2.Type = "rss";
		  feed2.Fils = "http://standblog.org/dotclear/rss.php";
		  feed2.FilsPort = 80;

		  Feed feed3 = new Feed();
		  feed3.Type = "nntp";
		  feed3.Fils = "news.epita.fr";
		  feed3.FilsPort = 119;

		  session.Save(feed1);
		  session.Save(feed2);
		  session.Save(feed3);

		  tx.Commit();
		}
		catch (Exception ex)
		{
		  if (tx != null)
			tx.Rollback();

		  throw ex;
		}
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
  }
}