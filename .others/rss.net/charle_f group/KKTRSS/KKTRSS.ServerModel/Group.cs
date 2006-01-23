using System;
using System.Data;
using System.Configuration;
using KKTRSS.Server.Helpers.Persistance;
using Iesi.Collections;
using System.Collections;
using System.Xml.Serialization;

/// <summary>
/// Summary description for Group
/// </summary>
namespace KKTRSS.Server.Model
{
    public class Group : APersistant
    {
        public Group()
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
        private Boolean _privacy;

        public Boolean Privacy
        {
            get { return _privacy; }
            set { _privacy = value; }
        }
        /*********************************************************************/
        
        private IList _accounts;
        [XmlIgnore]
        public IList Accounts
        {
            get { return _accounts; }
            set { _accounts = value; }
        }
        /*********************************************************************/
        private IList _rssFeedRefs;
        public IList RssFeedRefs
        {
            get { return _rssFeedRefs; }
            set { _rssFeedRefs = value; }
        }
        /*********************************************************************/


        private Account _owner;

        public Account Owner
        {
            get { return _owner; }
            set { _owner = value; }
        }
        /*********************************************************************/
   
   
    }
}