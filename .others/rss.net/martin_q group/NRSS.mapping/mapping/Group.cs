using System;
using System.Data;
using System.Configuration;
using Iesi.Collections;
using System.Collections;
using System.Xml.Serialization;

namespace NRSS.mapping
{
  public class Group
  {
	#region constructor
	public Group()
	{ }
	#endregion

	#region datas
	private int _id;
	private string _name;
	private string _creation;

	public int Id
	{
	  get { return _id; }
	  set { _id = value; }
	}

	public string Name
	{
	  get { return _name; }
	  set { _name = value; }
	}

	public string Creation
	{
	  get { return _creation; }
	  set { _creation = value; }
	}
	#endregion

	#region links
	private IList _users;

	private IList _feeds;

	[XmlIgnore]
	public IList iUsers
	{
	  get { return _users; }
	  set { _users = value; }
	}

	[XmlElement(Type = typeof(Group))]
	public ArrayList Users
	{
	  get
	  {
		if (_users == null)
		  return null;

		if (_users is ArrayList)
		  return (ArrayList)_users;

		return new ArrayList(_users);
	  }
	  set { _users = value; }
	}

	[XmlIgnore]
	public IList Feeds
	{
	  get { return _feeds; }
	  set { _feeds = value; }
	}
	#endregion
  }
}