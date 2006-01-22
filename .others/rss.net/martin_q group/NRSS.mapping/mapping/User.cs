using System;
using System.Data;
using System.Configuration;
using System.Collections;
using Iesi.Collections;
using System.Collections.Generic;

namespace NRSS.mapping
{
  [Serializable()]
  public class User
  {
	#region constructor
	public User()
	{ }
	#endregion

	#region datas
	private Guid _id;
	private string _email;
	private string _passwd;
	private bool _confirmed;
	private string _creation;
	private string _lastLogon;

	public Guid Id
	{
	  get { return _id; }
	  set { _id = value; }
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

	public IList Groups
	{
	  get { return _groups; }
	  set { _groups = value; }
	}

	public IList ReadItems
	{
	  get { return _readItems; }
	  set { _readItems = value; }
	}
	#endregion
  }
}