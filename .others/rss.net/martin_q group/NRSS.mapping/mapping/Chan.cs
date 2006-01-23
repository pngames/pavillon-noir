using System;
using System.Collections.Generic;
using System.Text;
using System.Collections;
using Iesi.Collections;
using System.Xml.Serialization;

namespace NRSS.mapping
{
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

	[XmlIgnore]
	public Feed Feed
	{
	  get { return _feed; }
	  set { _feed = value; }
	}

	[XmlIgnore]
	public IList iItems
	{
	  get { return _items; }
	  set { _items = value; }
	}

	[XmlElement(Type = typeof(Item))]
	public ArrayList Items
	{
	  get
	  {
		if (_items == null)
		  return null;

		if (_items is ArrayList)
		  return (ArrayList)_items;

		return new ArrayList(_items);
	  }
	  set { _items = value; }
	}
	#endregion

	#region specifics
	private bool _selected;

	public bool Selected
	{
	  get { return _selected; }
	  set { _selected = value; }
	}
	#endregion
  }
}
