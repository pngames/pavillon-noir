using System;
using System.Data;
using System.Configuration;
using System.Collections;
using Iesi.Collections;
using System.Collections.Generic;
using System.Xml.Serialization;

namespace NRSS.mapping
{
  public class User
  {
	#region constructor
	public User()
	{ }
	#endregion

	#region datas
	private int _id;
	private string _autoLog;

	private string _email;
	private string _passwd;
	private bool _confirmed;
	private string _creation;
	private string _lastLogon;

	public int Id
	{
	  get { return _id; }
	  set { _id = value; }
	}

	[XmlIgnore]
	public string AutoLog
	{
	  get { return _autoLog; }
	  set { _autoLog = value; }
	}

	public string Email
	{
	  get { return _email; }
	  set { _email = value; }
	}

	public string Passwd
	{
	  get { return _passwd; }
	  set { _passwd = value; }
	}

	public bool Confirmed
	{
	  get { return _confirmed; }
	  set { _confirmed = value; }
	}

	public string Creation
	{
	  get { return _creation; }
	  set { _creation = value; }
	}

	public string LastLogon
	{
	  get { return _lastLogon; }
	  set { _lastLogon = value; }
	}
	#endregion

	#region links
	private IList _groups;
	private IList _readItems;

	[XmlIgnore]
	public IList iGroups
	{
	  get { return _groups; }
	  set { _groups = value; }
	}

	[XmlIgnore]
	public IList ReadItems
	{
	  get { return _readItems; }
	  set { _readItems = value; }
	}

	[XmlElement(Type = typeof(Group))]
	public ArrayList Groups
	{
	  get
	  {
		if (_groups == null)
		  return null;

		if (_groups is ArrayList)
		  return (ArrayList)_groups;

		return new ArrayList(_groups);
	  }
	  set { _groups = value; }
	}
	#endregion
  }
}