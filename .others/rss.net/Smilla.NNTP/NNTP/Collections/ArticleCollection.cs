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
	/// Articles collection.
	/// </summary>
	public class ArticleCollection : NameObjectCollectionBase
	{
		public Article this[string name]
		{
			get
			{
				return (Article)this.BaseGet(name);
			}
			set
			{
				this.BaseSet(name, value);
			}
		}

		public Article this[int index]
		{
			get
			{
				return (Article)this.BaseGet(index);
			}
			set
			{
				this.BaseSet(index, value);
			}
		}

		internal void Add(string name, Article value)
		{
			this.BaseAdd(name, value);
		}


		public Article[] GetArticleList()
		{
			return (Article[])this.BaseGetAllValues(typeof(Article));
		}

		public XmlDocument ToXml(bool decodeContents)
		{
			XmlDocument doc = new XmlDocument();
			XmlElement xmlArticles = doc.CreateElement("Articles");
			doc.AppendChild(xmlArticles);
			foreach (string messageID in this)
			{
				xmlArticles.AppendChild(doc.ImportNode(this[messageID].ToXml(decodeContents).DocumentElement, true));
			}
			return doc;
		}
	}
}
