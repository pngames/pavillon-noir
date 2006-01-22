using System;
using System.Collections.Generic;
using System.Text;
using System.Collections;
using Iesi.Collections;
using System.Xml.Serialization;

namespace NRSS.mapping
{
  public class Feed
  {
	#region constructor
	public Feed()
	{ }
	#endregion

	#region data
	private int _id;

	private string _type;
	private string _name;

	private string _fils;
	private int _filsPort;
	private string _filsUser;
	private string _filsPass;

	public int Id
	{
	  get { return _id; }
	  set { _id = value; }
	}

	public string Type
	{
	  get { return _type; }
	  set { _type = value; }
	}

	public string Name
	{
	  get { return _name; }
	  set { _name = value; }
	}

	public string Fils
	{
	  get { return _fils; }
	  set { _fils = value; }
	}

	public int FilsPort
	{
	  get { return _filsPort; }
	  set { _filsPort = value; }
	}

	public string FilsUser
	{
	  get { return _filsUser; }
	  set { _filsUser = value; }
	}

	public string FilsPass
	{
	  get { return _filsPass; }
	  set { _filsPass = value; }
	}
	#endregion

	#region links
	private IList _chans;
	private IList _groups;

	public IList Chans
	{
	  get { return _chans; }
	  set { _chans = value; }
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
