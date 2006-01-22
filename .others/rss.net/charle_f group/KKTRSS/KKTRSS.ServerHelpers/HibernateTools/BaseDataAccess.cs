using System;
using System.Collections;
using System.Reflection;
using NHibernate;
using NHibernate.Cfg;
using NHibernate.Expression;

namespace KKTRSS.Server.Helpers.DataAccess
{
  /// <summary> Summary description for BaseDataAccess. </summary>
  public class BaseDataAccess
  {
	protected ISession m_session;

	public BaseDataAccess()
	{
	  m_session = NHibernateHttpModule.CurrentSession;
	}

	/// <summary> Save a collection. </summary>
	/// <param name="items"></param>
	public virtual void Save(IList items)
	{
	  ITransaction tx = null;

	  try
	  {
		if (items != null)
		{
		  tx = m_session.BeginTransaction();

		  foreach (object item in items)
		  {
			m_session.SaveOrUpdate(item);
		  }

		  tx.Commit();
		}
	  }
	  catch (Exception ex)
	  {
		tx.Rollback();

		throw ex;
	  }
	}

	/// <summary> Saves an item and then saves the child items inside of a transaction. </summary>
	/// <param name="parentItem"></param>
	/// <param name="childItems"></param>
	public virtual void Save(object parentItem, IList childItems)
	{
	  ITransaction tx = null;

	  try
	  {
		if (childItems != null)
		{
		  tx = m_session.BeginTransaction();

		  m_session.SaveOrUpdate(parentItem);

		  foreach (object item in childItems)
		  {
			m_session.SaveOrUpdate(item);
		  }

		  tx.Commit();
		}
	  }
	  catch (Exception ex)
	  {
		tx.Rollback();

		throw ex;
	  }
	}

	/// <summary> Saves the item. </summary>
	/// <param name="item"></param>
	public virtual void Save(object item)
	{
	  ITransaction tx = null;

	  try
	  {
		tx = m_session.BeginTransaction();

		m_session.SaveOrUpdate(item);
		
		tx.Commit();
	  }
	  catch (Exception ex)
	  {
		if (tx != null)
		  tx.Rollback();

		throw ex;
	  }
	}

	/// <summary>
	/// Returns a list of items matching the type supplied.
	/// </summary>
	/// <param name="type"></param>
	/// <returns></returns>
	public IList Get(Type type)
	{
	  return GetByType(type);
	}

	public object Get(Type type, object id)
	{
	  object returnValue = null;

	  try
	  {
		returnValue = m_session.Load(type, id);

		return returnValue;
	  }
	  catch (Exception ex)
	  {
		throw ex;
	  }
	}

	public IList GetListByPropertyValue(Type type, string propertyName, object propertyValue)
	{
	  try
	  {
		ICriteria crit = m_session.CreateCriteria(type);

		crit.Add(Expression.Eq(propertyName, propertyValue));

		return crit.List();
	  }
	  catch (Exception ex)
	  {
		throw ex;
	  }
	}

	public IList GetListByPropertyValue(Type type, string propertyName, object propertyValue,
		string propertyName2, object propertyValue2)
	{
	  try
	  {
		ICriteria crit = m_session.CreateCriteria(type);

		crit.Add(Expression.Eq(propertyName, propertyValue));
		crit.Add(Expression.Eq(propertyName2, propertyValue2));

		return crit.List();
	  }
	  catch (Exception ex)
	  {
		throw ex;
	  }
	}

	public object Get(
		Type type,
		string propertyName, object propertyValue)
	{
	  try
	  {
		ICriteria crit = m_session.CreateCriteria(type);

		crit.Add(Expression.Eq(propertyName, propertyValue));

		IList list = crit.List();

		if (list == null || list.Count < 1)
		{
		  return null;
		}
		else
		{
		  return list[0];
		}
	  }
	  catch (Exception ex)
	  {
		throw ex;
	  }
	}


	public object Get(
		Type type,
		string propertyName, object propertyValue,
		string propertyName2, object propertyValue2)
	{
	  try
	  {
		ICriteria crit = m_session.CreateCriteria(type);

		crit.Add(Expression.Eq(propertyName, propertyValue));
		crit.Add(Expression.Eq(propertyName2, propertyValue2));

		IList list = crit.List();

		if (list == null || list.Count < 1)
		{
		  return null;
		}
		else
		{
		  return list[0];
		}
	  }
	  catch (Exception ex)
	  {
		throw ex;
	  }
	}

	private IList GetByType(Type type)
	{
	  IList items = null;
	  ITransaction tx = null;

	  try
	  {
		tx = m_session.BeginTransaction();

		items = m_session.CreateCriteria(type).List();

		tx.Commit();

		return items;
	  }
	  catch (Exception ex)
	  {
		if (tx != null) tx.Rollback();

		throw ex;
	  }
	}

	public void Delete(object item)
	{
	  ITransaction tx = null;

	  try
	  {
		tx = m_session.BeginTransaction();

		m_session.Delete(item);

		tx.Commit();
	  }
	  catch (Exception ex)
	  {
		if (tx != null) tx.Rollback();

		throw ex;
	  }
	}

	public void Delete(IList items)
	{
	  ITransaction tx = null;

	  try
	  {
		tx = m_session.BeginTransaction();

		foreach (object item in items)
		{
		  m_session.Delete(item);
		}

		tx.Commit();
	  }
	  catch (Exception ex)
	  {
		if (tx != null) tx.Rollback();

		throw ex;
	  }
	}
  }
}