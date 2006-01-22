using System;
using System.Data;
using System.Configuration;
using System.Runtime.Serialization;
using NHibernate;
/// <summary>
/// Summary description for APersistant
/// </summary>
/// 
namespace KKTRSS.Server.Helpers.Persistance
{
    [Serializable()]
    public class APersistant : NHibernate.IValidatable, NHibernate.ILifecycle
    {
        public APersistant()
        {
            //
            // TODO: Add constructor logic here
            //
        }
        /*********************************************************************/

        private Int64 _id;

        public Int64 Id
        {
            get { return _id; }
            set { _id = value; }
        }
        /*********************************************************************/
        private DateTime _creationDate;

        public DateTime CreationDate
        {
            get { return _creationDate; }
            set { _creationDate = value; }
        }

        /*********************************************************************/
        private DateTime _lastUpdate;

        public DateTime LastUpdate
        {
            get { return _lastUpdate; }
            set { _lastUpdate = value; }
        }
        /*********************************************************************/

        public bool isNew()
        {
            DateTime crea = CreationDate;
            DateTime up = LastUpdate;
            if (crea != null && up != null && crea.Equals(up))
                return true;
            return false;
        }

        #region IValidatable Members

        public void Validate()
        {
          
        }

        #endregion

        #region ILifecycle Members

        public LifecycleVeto OnDelete(NHibernate.ISession s)
        {
            return LifecycleVeto.NoVeto;
        }

        public void OnLoad(NHibernate.ISession s, object id)
        {
            this.Id = (long)id;
        }

        public LifecycleVeto OnSave(NHibernate.ISession s)
        {
            LastUpdate = DateTime.Now;
            if (CreationDate == null){
                CreationDate = LastUpdate;
            }
            return LifecycleVeto.NoVeto;
        }

        public LifecycleVeto OnUpdate(NHibernate.ISession s)
        {
            LastUpdate = DateTime.Now;
            return LifecycleVeto.NoVeto;
        }

        #endregion

    }
}