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
using System.Text;
using System.Text.RegularExpressions;
using System.Collections.Specialized;
using System.Xml;

namespace Smilla.Net.NNTPClient
{
	/// <summary>
	/// Class that implements an article body.
	/// </summary>
	public class Body : IBodyPart
	{
		private string text;
		private string[] originalBody;
		private bool readOnly = true;
		private BodyPartCollection bodyParts = new BodyPartCollection(); 

		internal Article article;

		internal Body()
		{
			//
			// TODO: Add constructor logic here
			//
			readOnly = false;
		}

		internal Body(string[] article, Article parent)
		{
			this.article = parent;
			ArticleResponse response = Utils.ParseArticleResponse(article[0]);
			int startBodyIndex = 1;
			if (response.StatusCode == NNTPStatus.ArticleHeadBodyRetrieved)
				startBodyIndex = Array.IndexOf(article, "")+1;
			text = String.Join(Environment.NewLine, article, startBodyIndex, article.Length - startBodyIndex - 2);

			if (parent.Header.Multipart)
			{
				bodyParts = Utils.ParseBodyParts(text, parent.Header.boundary, (IBodyPart)this);
			}
			else
			{
				/*
				if (parent.Header.Headers["Content-Transfer-Encoding"] == "base64")
					text = Encoding.Default.GetString(Convert.FromBase64String(text));
				if (parent.Header.Headers["Content-Type"] != null)
				{
					//string enc = Utils.GetCharset(parent.Header.Headers);
					text = NNTPClient.Charset.Decode(parent.Header.Charset, text);
				}
				

				text = text.Replace(Environment.NewLine + "..", Environment.NewLine + ".");
				*/
			}
			originalBody = new String[article.Length - startBodyIndex];
			Array.Copy(article, 1, originalBody,0, originalBody.Length);
		}

		public string Text
		{
			get
			{
				return text;
			}
			set
			{
				if (!readOnly)
				{
					text = value;
					originalBody = null;
				}
				else
					throw new InvalidOperationException("Article doesn't allow modifications");
			}
		}

		public string DecodedText
		{
			get
			{
				string result = text;
				switch (this.Headers["Content-Transfer-Encoding"])
				{
					case "base64":
						result = Encoding.Default.GetString(Convert.FromBase64String(result));
						break;
					case "quoted-printable":
						result = Encoding.Default.GetString(Utils.FromQuotedPrintableString(result));
						break;
				}

				return NNTPClient.Charset.Decode(this.Charset, result, true);
			}
		}

		public string Charset
		{
			get
			{
				return article.Header.Charset;
			}
		}

		public string ContentType
		{
			get
			{
				return article.Header.ContentType;
			}
		}

		public BodyPartCollection BodyParts
		{
			get
			{
				return bodyParts;
			}
		}

		public HeaderCollection Headers
		{
			get
			{
				return article.Header.Headers;
			}
		}

		public IBodyPart Parent
		{
			get
			{
				return null;
			}
		}

		public string HtmlBody
		{
			get
			{
				IBodyPart htmlPart = Utils.FindBodyParts("text/html", (IBodyPart)this);
				if (htmlPart != null)
					return htmlPart.Text;
				else
					return null;
			}
		}

		public string TextBody
		{
			get
			{
				IBodyPart textPart = Utils.FindBodyParts("text/plain", (IBodyPart)this);
				if (textPart != null)
					return textPart.Text;
				else
					return null;
			}
		}

		public IBodyPart HtmlBodyPart
		{
			get
			{
				return Utils.FindBodyParts("text/html", (IBodyPart)this);
			}
		}

		public IBodyPart TextBodyPart
		{
			get
			{
				return Utils.FindBodyParts("text/plain", (IBodyPart)this);
			}
		}

		public override string ToString()
		{
			return text;
		}

		public XmlDocument ToXml(bool decodeContents)
		{
			XmlDocument doc = new XmlDocument();
			XmlElement xmlBody = doc.CreateElement("Body");
			doc.AppendChild(xmlBody);
			if (this.bodyParts.Count == 0)
			{
				XmlElement textElement = doc.CreateElement("Text");
				XmlCDataSection textSection = doc.CreateCDataSection((decodeContents)?this.DecodedText:this.text);
				textElement.AppendChild(textSection);
				xmlBody.AppendChild(textElement);
			}
			else
			{
				xmlBody.AppendChild(doc.ImportNode(this.bodyParts.ToXml(decodeContents).DocumentElement, true));
			}
			return doc;
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
