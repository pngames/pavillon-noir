using System;
using System.Data;
using System.Configuration;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;

/// <summary>
/// Summary description for Feed
/// </summary>
public class KKTFeed
{
    string name;
    string url;

    #region Accessors
    public string Name
    {
        get { return name; }
        set { name = value; }
    }
    public string Url
    {
        get { return url; }
        set { url = value; }
    }
    #endregion
    
    
    public KKTFeed(string name, string url)
    {
        Name = name;
        Url = url;
    }
}
