using System;
using System.Collections.Generic;
using System.Text;
using Iesi.Collections;
using System.Collections;
using System.Xml.Serialization;

namespace NRSS.mapping
{
  [Serializable()]
  public class Item
  {
	#region constructor
	public Item()
	{ }
	#endregion

	#region datas
	private int _id;

	private string _messageID;

	private string _author;
	private DateTime _date;
	private string _title;
	private string _description;
	private string _content;
	private string _link;

	public int Id
	{
	  get { return _id; }
	  set { _id = value; }
	}

	public string MessageID
	{
	  get { return _messageID; }
	  set { _messageID = value; }
	}

	public string Author
	{
	  get { return _author; }
	  set { _author = value; }
	}

	public DateTime Date
	{
	  get { return _date; }
	  set { _date = value; }
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

	public string Content
	{
	  get { return _content; }
	  set { _content = value; }
	}

	public string Link
	{
	  get { return _link; }
	  set { _link = value; }
	}
	#endregion

	#region links
	private Item _parent;
	private Chan _chan;

	private IList _readerUsers;

	public Item Parent
	{
	  get { return _parent; }
	  set { _parent = value; }
	}

	[XmlIgnore]
	public Chan Chan
	{
	  get { return _chan; }
	  set { _chan = value; }
	}

	[XmlIgnore]
	public IList ReaderUsers
	{
	  get { return _readerUsers; }
	  set { _readerUsers = value; }
	}
	#endregion
  }
}