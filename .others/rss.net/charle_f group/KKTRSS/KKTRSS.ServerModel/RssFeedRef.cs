using System;
using System.Data;
using System.Configuration;
using KKTRSS.Server.Helpers.Persistance;
using Iesi.Collections;
using System.Collections;


/// <summary>
/// Summary description for RssFeedRef
/// </summary>
namespace KKTRSS.Server.Model
{
    public class RssFeedRef : APersistant
    {
        public RssFeedRef()
        {
            //
            // TODO: Add constructor logic here
            //
        }
        /*********************************************************************/
        private string _name;

        public string Name
        {
            get { return _name; }
            set { _name = value; }
        }
        /*********************************************************************/
        private string _url;

        public string Url
        {
            get { return _url; }
            set { _url = value; }
        }
        /*********************************************************************/
        private Group _group;

        public Group Group
        {
            get { return _group; }
            set { _group = value; }
        }
        /*********************************************************************/
        private IList _accounts;

        public IList Accounts
        {
            get { return _accounts; }
            set { _accounts = value; }
        }
        /*********************************************************************/
    }
}