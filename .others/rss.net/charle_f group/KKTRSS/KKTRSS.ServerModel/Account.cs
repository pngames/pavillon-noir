using System;
using System.Data;
using System.Configuration;
using KKTRSS.Server.Helpers.Persistance;
using KKTRSS.Server.Helpers.DataAccess;
using NHibernate;
using Iesi.Collections;
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
        private ISet _readRssItems;

        public ISet ReadRssItems
        {
            get { return _readRssItems; }
            set { _readRssItems = value; }
        }
        #endregion
        /*********************************************************************/
        #region SubscribedRssFeeds
        private ISet _subscribedRssFeeds;

        public ISet SubscribedRssFeeds
        {
            get { return _subscribedRssFeeds; }
            set { _subscribedRssFeeds = value; }
        }
        #endregion
        /*********************************************************************/
        #region Groups
        private ISet _groups;

        public ISet Groups
        {
            get { return _groups; }
            set { _groups = value; }
        }
        #endregion
        /*********************************************************************/
        /*********************************************************************/
        #region OwnedGroups
        private ISet _ownedGroups;

        public ISet OwnedGroups
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
                this.Groups = new ListSet();
            this.Groups.Add(grp);
            return base.OnSave(s);
        }  

        void Validate()
         {
             if (Email == null || Email.Length > 0)
                 throw new NHibernate.ValidationFailure("Email must be specified\n");
             ISession s = NHibernateHttpModule.CreateSession();
             if (s.CreateQuery("FROM Accout acc WHERE acc.Email=?")
                  .SetString(0,Email)
                  .UniqueResult() != null)
                 throw new NHibernate.ValidationFailure("Email: '" + Email + "' already exists\n");
         }

    }
}