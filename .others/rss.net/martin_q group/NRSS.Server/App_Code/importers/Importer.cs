using System;
using System.Data;
using System.Configuration;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using NRSS.mapping;
using Iesi.Collections;
using System.Collections.Generic;
using NRSS;

/// <summary> Summary description for Importer </summary>
public abstract class Importer
{
  protected ImportType _type;
  protected int _defaultPort;

  protected Importer()
  { }

  protected abstract void _updateFeed(Feed feed);

  public static void updateFeed(Feed feed)
  {
	Importers[feed.Type]._updateFeed(feed);
  }

  public ImportType Type
  {
	get { return _type; }
	set { _type = value; }
  }

  //////////////////////////////////////////////////////////////////////////

  private static Dictionary<string, Importer> _importers = new Dictionary<string, Importer>();

  public static Dictionary<string, Importer> Importers
  {
	get { return Importer._importers; }
	set { Importer._importers = value; }
  }
}