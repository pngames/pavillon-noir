using System;
using System.Data;
using System.Configuration;
using KKTRSS.Server.Helpers.Persistance;
using KKTRSS.Server.Helpers.DataAccess;
using NHibernate;
using System.Collections;
using System.Xml.Serialization;
/// <summary>
/// Summary description for Account
/// </summary>
namespace KKTRSS.Server.Model
{

    public class Account : APersistant
    {
        public Account()
        {
            //base();
            //
            // TODO: Add constructor logic here
            //
        }
        #region Properties
        /*********************************************************************/
        #region Email
        private string _email;

        public string Email
        {
            get { return _email; }
            set { _email = value; }
        }
        #endregion
        /*********************************************************************/
        #region Password
        private string _password;

        public string Password
        {
            get { return _password; }
            set { _password = value; }
        }
        #endregion
        /*********************************************************************/
        #region Autologin
        private string _autologin;

        public string Autologin
        {
            get { return _autologin; }
            set { _autologin = value; }
        }
        #endregion
        /*********************************************************************/
        #region IsActive
        private Boolean _isActive;

        public Boolean IsActive
        {
            get { return _isActive; }
            set { _isActive = value; }
        }
        #endregion
        /*********************************************************************/
        #region ReadRssItems
        private IList _readRssItems;

        public IList ReadRssItems
        {
            get { return _readRssItems; }
            set { _readRssItems = value; }
        }
        #endregion
        /*********************************************************************/
        #region SubscribedRssFeeds
        private IList _subscribedRssFeeds;

        public IList SubscribedRssFeeds
        {
            get { return _subscribedRssFeeds; }
            set { _subscribedRssFeeds = value; }
        }
        #endregion
        /*********************************************************************/
        #region Groups
        private IList _groups;
        [XmlIgnore]
        public IList Groups
        {
            get { return _groups; }
            set { _groups = value; }
        }
        #endregion
        /*********************************************************************/
        /*********************************************************************/
        #region OwnedGroups
        private IList _ownedGroups;
        [XmlIgnore]
        public IList OwnedGroups
        {
            get { return _ownedGroups; }
            set { _ownedGroups = value; }
        }
        #endregion
        /*********************************************************************/
        #endregion


        public override LifecycleVeto OnSave(NHibernate.ISession s)
        {
            Guid uid = Guid.NewGuid();
            Autologin = uid.ToString();
            IsActive = false;
            Group grp = new Group();
            grp.Name = Email;
            grp.Privacy = true;
            grp.Owner = this;
            s.Save(grp);
            if (this.Groups == null)
                this.Groups = new ArrayList();
            this.Groups.Add(grp);
            return base.OnSave(s);
        }

        public override void Validate()
        {
            if (Email == null || Email.Length <= 0)
                throw new NHibernate.ValidationFailure("Email must be specified\n");
            NHibernateHttpModule.BeginTranaction();
            Account acc = null;
            try
            {
                acc = (Account) NHibernateHttpModule.CurrentSession
                    .CreateQuery("FROM Account acc WHERE acc.Email=?")
                    .SetString(0, Email)
                    .UniqueResult();
                if (acc != null)
                {
                    NHibernateHttpModule.RollbackTransaction();
                    throw new NHibernate.ValidationFailure("Email: '" + Email + "' already exists\n");
                }
                NHibernateHttpModule.CommitTranction();
            }
            catch (HibernateException e)
            {
                NHibernateHttpModule.RollbackTransaction();
                throw e;
            }
        }

    }
}