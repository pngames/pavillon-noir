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
using System.Text;
using System.Xml;
using System.IO;

namespace Smilla.Net.NNTPClient
{
	/// <summary>
	/// Class that implements MIME body part.
	/// </summary>
	public class BodyPart : IBodyPart
	{
		private HeaderCollection headers = new HeaderCollection();
		private string contentType;
		private string charset;
		private IBodyPart parent;
		private BodyPartCollection bodyParts = new BodyPartCollection();
		private string boundary;
		private string text;

		internal BodyPart(string[] bodyPart, IBodyPart parent)
		{
			this.parent = parent;
			headers = Utils.ParseHeaders(bodyPart);
			int startBodyIndex = 1;
			startBodyIndex = Array.IndexOf(bodyPart, "")+1;
			text = String.Join(Environment.NewLine, bodyPart, startBodyIndex, bodyPart.Length - startBodyIndex);
			if (headers["Content-Type"] != null)
			{
				contentType = Utils.GetContentType(headers);
				charset = Utils.GetCharset(headers);
				if (Utils.IsMultipart(headers))
				{
					boundary = Utils.GetBoundary(headers);
					bodyParts = Utils.ParseBodyParts(text, boundary, this);
				}
			}
			else
			{
				contentType = NNTPDefaults.ContentType;
				charset = NNTPDefaults.Charset;
			}
		}

		public IBodyPart Parent
		{
			get
			{
				return parent;
			}	
		}

		public HeaderCollection Headers
		{
			get
			{
				return headers;
			}
		}

		public string ContentType
		{
			get
			{
				return contentType;
			}
		}

		public string Charset
		{
			get
			{
				return charset;
			}
		}

		public BodyPartCollection BodyParts
		{
			get
			{
				return bodyParts;
			}
		}

		public string Text
		{
			get
			{
				return text;
			}
			set
			{
				text = value;
			}
		}

		public string DecodedText
		{
			get
			{
				string result = text;
				switch (this.headers["Content-Transfer-Encoding"])
				{
					case "base64":
						result = Encoding.Default.GetString(Convert.FromBase64String(result));
						break;
					case "quoted-printable":
						result = Encoding.Default.GetString(Utils.FromQuotedPrintableString(result));
						break;
				}

				return NNTPClient.Charset.Decode(this.charset, result, true);
			}
		}

		public XmlDocument ToXml(bool decodeContents)
		{
			XmlDocument doc = new XmlDocument();
			XmlElement xmlBodyPart = doc.CreateElement("BodyPart");
			doc.AppendChild(xmlBodyPart);
			xmlBodyPart.AppendChild(doc.ImportNode(headers.ToXml(decodeContents).DocumentElement, true));
			if (this.bodyParts.Count == 0)
			{
				XmlElement textElement = doc.CreateElement("Text");
				XmlCDataSection textSection = doc.CreateCDataSection((decodeContents)?this.DecodedText:this.text);
				textElement.AppendChild(textSection);
				xmlBodyPart.AppendChild(textElement);
			}
			else
			{
				xmlBodyPart.AppendChild(doc.ImportNode(this.bodyParts.ToXml(decodeContents).DocumentElement, true));
			}
			return doc;
		}

		public string Filename
		{
			get
			{
				return Utils.GetFilename(this.headers);
			}
			set
			{
				Utils.SetFilename(this.headers, value);
			}
		}

		public bool IsAttachment
		{
			get
			{
				if (this.contentType.IndexOf("text") != -1)
					return false;
				else
					return true;
			}
		}

		public void Save(string path, string filename)
		{
			this.Save(String.Format("{0}\\{1}", path, filename));
		}

		public void Save(string filename)
		{
			Utils.SaveBodyPart((IBodyPart)this, filename);
		}
	}
}

