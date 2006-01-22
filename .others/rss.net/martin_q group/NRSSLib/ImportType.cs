using System;
using System.Collections.Generic;
using System.Text;

namespace NRSS
{
  public class ImportType
  {
	private string _name;
	private string _description;

	private int _defaultPort;

	public string Name
	{
	  get { return _name; }
	  set { _name = value; }
	}

	public string Description
	{
	  get { return _description; }
	  set { _description = value; }
	}

	public int DefaultPort
	{
	  get { return _defaultPort; }
	  set { _defaultPort = value; }
	}
  }
}