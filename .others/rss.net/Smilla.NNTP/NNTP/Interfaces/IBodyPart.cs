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
	/// Interface for MIME body parts.
	/// </summary>
	public interface IBodyPart
	{
		string Text
		{
			get;
			set;
		}

		BodyPartCollection BodyParts
		{
			get;
		}

		IBodyPart Parent
		{
			get;
		}

		string ContentType
		{
			get;
		}

		string Charset
		{
			get;
		}

		HeaderCollection Headers
		{
			get;
		}
		/// <summary>
		/// Gets text of the bodypart decoded using the information found in the bodypart headers. If you are not satisfied with a result of decoding (for example, if headers contain wrong information about encoding) you can use Text property and decode bodypart text by yourself.
		/// </summary>
		string DecodedText
		{
			get;
		}

		XmlDocument ToXml(bool decodeContents);

		void Save(string path, string filename);

		void Save(string filename);
	}
}
