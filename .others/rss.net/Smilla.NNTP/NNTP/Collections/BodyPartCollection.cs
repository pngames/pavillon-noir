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
	/// Body parts collection.
	/// </summary>
	public class BodyPartCollection : NameObjectCollectionBase
	{
		public IBodyPart this[string name]
		{
			get
			{
				return (IBodyPart)this.BaseGet(name);
			}
			set
			{
				this.BaseSet(name, value);
			}
		}

		public IBodyPart this[int index]
		{
			get
			{
				return (IBodyPart)this.BaseGet(index);
			}
			set
			{
				this.BaseSet(index, value);
			}
		}

		internal void Add(string name, IBodyPart value)
		{
			this.BaseAdd(name, value);
		}

		public IBodyPart[] GetBodyPartList()
		{
			return (IBodyPart[])this.BaseGetAllValues(typeof(IBodyPart));
		}

		public XmlDocument ToXml(bool decodeContents)
		{
			XmlDocument doc = new XmlDocument();
			XmlElement xmlBodyParts = doc.CreateElement("BodyParts");
			doc.AppendChild(xmlBodyParts);
			foreach (string bodyPartName in this)
			{
				XmlElement xmlBodyPart = this[bodyPartName].ToXml(decodeContents).DocumentElement;
				xmlBodyParts.AppendChild(doc.ImportNode(xmlBodyPart, true));
			}
			return doc;
		}

	}
}
