using System;
using System.Collections.Generic;
using System.Text;
using System.Collections;
using Iesi.Collections;
using System.Xml.Serialization;

namespace NRSS.mapping
{
  [Serializable()]
  public class Chan
  {
	#region constructor
	public Chan()
	{ }
	#endregion

	#region data
	private int _id;

	private string _title;
	private string _description;
	private string _language;
	private string _link;

	public int Id
	{
	  get { return _id; }
	  set { _id = value; }
	}

	public string Title
	{
	  get { return _title; }
	  set { _title = value; }
	}

	public string Description
	{
	  get { return _description; }
	  set { _description = value; }
	}

	public string Language
	{
	  get { return _language; }
	  set { _language = value; }
	}

	public string Link
	{
	  get { return _link; }
	  set { _link = value; }
	}
	#endregion

	#region links
	private Feed _feed;
	private IList _items;

	private IList _groups;

	[XmlIgnore]
	public Feed Feed
	{
	  get { return _feed; }
	  set { _feed = value; }
	}

	public IList Items
	{
	  get { return _items; }
	  set { _items = value; }
	}

	[XmlIgnore]
	public IList Groups
	{
	  get { return _groups; }
	  set { _groups = value; }
	}
	#endregion
  }
}
