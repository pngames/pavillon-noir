using System;
using System.Data;
using System.Configuration;

/// <summary>Summary description for NRSSConfiguration</summary>
public class NRSSConfProxy : ConfigurationSection
{
  #region singleton
  private static NRSSConfProxy _instance = null;

  public static NRSSConfProxy Instance
  {
	get
	{
	  if (_instance == null)
		_instance = ConfigurationManager.GetSection("nrss_proxy") as NRSSConfProxy;

	  return _instance;
	}
  }

  private NRSSConfProxy()
  { }
  #endregion

  [ConfigurationProperty("proxy_enabled", DefaultValue = "false")]
  public bool ProxyEnabled
  {
	get
	{
	  return (bool)this["proxy_enabled"];
	}
	set
	{
	  this["proxy_enabled"] = value;
	}
  }

  [ConfigurationProperty("proxy_url", DefaultValue = "127.0.0.1")]
  public string ProxyUrl
  {
	get
	{
	  return (string)this["proxy_url"];
	}
	set
	{
	  this["proxy_url"] = value;
	}
  }

  [ConfigurationProperty("proxy_port", DefaultValue = "80")]
  public int ProxyPort
  {
	get
	{
	  return (int)this["proxy_port"];
	}
	set
	{
	  this["proxy_port"] = value;
	}
  }

  [ConfigurationProperty("proxy_login", DefaultValue = "")]
  public string ProxyLogin
  {
	get
	{
	  return (string)this["proxy_login"];
	}
	set
	{
	  this["proxy_login"] = value;
	}
  }

  [ConfigurationProperty("proxy_pass", DefaultValue = "")]
  public string ProxyPass
  {
	get
	{
	  return (string)this["proxy_pass"];
	}
	set
	{
	  this["proxy_pass"] = value;
	}
  }
}