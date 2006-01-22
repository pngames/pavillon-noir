/*
	.NET Communication Library
    Copyright (C) 2002 Dmitry Krakhmalnik
 
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
using System;
using System.Collections.Specialized;
using System.Xml;

namespace Smilla.Net.NNTPClient
{
	/// <summary>
	/// Newsgroups collection.
	/// </summary>
	public class NewsGroupCollection : NameObjectCollectionBase
	{
		public NewsGroup this[string key]
		{
			get
			{
				return (NewsGroup)this.BaseGet(key);
			}
			set
			{
				this.BaseSet(key, value);
			}
		}

		public NewsGroup this[int index]
		{
			get
			{
				return (NewsGroup)this.BaseGet(index);
			}
			set
			{
				this.BaseSet(index, value);
			}
		}

		public void Add(string key, NewsGroup value)
		{
			this.BaseAdd(key, value);
		}

		public NewsGroup[] GetNewsGroupList()
		{
			return (NewsGroup[])this.BaseGetAllValues(typeof(NewsGroup));
		}

		public XmlDocument ToXml()
		{
			XmlDocument doc = new XmlDocument();
			XmlElement xmlArticles = doc.CreateElement("NewsGroups");
			doc.AppendChild(xmlArticles);
			foreach (string messageID in this)
			{
				xmlArticles.AppendChild(doc.ImportNode(this[messageID].ToXml().DocumentElement, true));
			}
			return doc;
		}

	}
}
