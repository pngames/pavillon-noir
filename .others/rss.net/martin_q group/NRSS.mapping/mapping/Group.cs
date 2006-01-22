using System;
using System.Data;
using System.Configuration;
using Iesi.Collections;
using System.Collections;

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
	private IList _chans;

	public IList Users
	{
	  get { return _users; }
	  set { _users = value; }
	}

	public IList Feeds
	{
	  get { return _feeds; }
	  set { _feeds = value; }
	}

	public IList Chans
	{
	  get { return _chans; }
	  set { _chans = value; }
	}
	#endregion
  }
}