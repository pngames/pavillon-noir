using System;
using System.Data;
using System.Configuration;
using System.IO;
using System.Text;

/// <summary>Summary description for LogFile</summary>
public class LogFile
{
  string logfile = "log.txt";

  private LogFile()
  { 
	if (File.Exists(logfile))
	  File.Delete(logfile);

	using (File.Create("log.txt"))
	{ }
  }

  private static LogFile _instance = null;

  public static LogFile Instance
  {
	get
	{
	  if (_instance == null)
		_instance = new LogFile();

	  return _instance;
	}
  }

  public void write(string str)
  {
	using (StreamWriter sw = File.AppendText("log.txt"))
	{
	  sw.Write(str);
	  sw.Flush();
	  sw.Close();
	}
  }

  public void writeLine(string str)
  {
	using (StreamWriter sw = File.AppendText("log.txt"))
	{
	  sw.WriteLine(str);
	  sw.Flush();
	  sw.Close();
	}
  }
}