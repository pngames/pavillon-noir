using System;
using System.Data;
using System.Configuration;
using KKTRSS.Server.Helpers.Persistance;
using KKTRSS.Server.Helpers.DataAccess;

/// <summary>
/// Summary description for ReadedRssFeedItem
/// </summary>
namespace KKTRSS.Server.Model
{
    public class ReadRssItem : APersistant
    {
        public ReadRssItem()
        {
            //
            // TODO: Add constructor logic here
            //
        }
        /*********************************************************************/
        private string _hashCode;

        public string HashCode
        {
            get { return _hashCode; }
            set { _hashCode = value; }
        }
        /*********************************************************************/
        private RssFeedRef _rssFeedRef;

        public RssFeedRef RssFeedRef
        {
            get { return _rssFeedRef; }
            set { _rssFeedRef = value; }
        }
        /*********************************************************************/
        private Account _account;

        public Account Account
        {
            get { return _account; }
            set { _account = value; }
        }

        /*********************************************************************/
        /*********************************************************************/

    }
}