using System;
using System.Collections.Generic;
using System.Text;
using NHibernate;
using NHibernate.Cfg;
using NHibernate.Tool.hbm2ddl;

namespace NRSS.Server.DataAccess
{
  public class SchemaUtility
  {
	public static void ExportSchema()
	{
	  Configuration config = new Configuration();
	  config.Configure();

	  SchemaExport exporter = new SchemaExport(config);

	  exporter.Drop(true, true);
	  exporter.Create(true, true);

	  // exporter.Execute(true, true, false, true);
	}
  }
}