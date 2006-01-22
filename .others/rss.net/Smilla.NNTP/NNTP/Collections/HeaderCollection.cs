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
using System.Text;

namespace Smilla.Net.NNTPClient
{
	/// <summary>
	/// Headers collection
	/// </summary>
	public class HeaderCollection : NameValueCollection
	{
		public XmlDocument ToXml(bool decodeContents)
		{
			XmlDocument doc = new XmlDocument();
			XmlElement header = doc.CreateElement("Header");
			doc.AppendChild(header);
			foreach (string headerName in this)
			{
				XmlElement headerLine = doc.CreateElement("HeaderLine");
				headerLine.SetAttribute("Name", headerName);
				headerLine.InnerText = (decodeContents)?Utils.DecodeHeaderString(this[headerName]):this[headerName];
				header.AppendChild(headerLine);
			}
			return doc;
		}

		public override string ToString()
		{
			StringBuilder result = new StringBuilder();
			string newLine = Environment.NewLine;
			//if (headers["Content-Type"] == null)
			
			foreach (string header in this)
			{
				result.Append(header + ": " + this[header] + newLine);
			}
			return result.ToString();
		}

	}
}
