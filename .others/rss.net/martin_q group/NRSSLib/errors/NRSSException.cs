using System;
using System.Collections.Generic;
using System.Text;

namespace NRSS.errors
{
  public class NRSSException : ApplicationException
  {
	public NRSSException(string message)
	  : base(message)
	{

	}
  }
}