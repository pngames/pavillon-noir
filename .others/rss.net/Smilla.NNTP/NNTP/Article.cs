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
using System.Xml;

namespace Smilla.Net.NNTPClient
{
	/// <summary>
	/// Class that implements an article in a newsgroup.
	/// </summary>
	public class Article
	{
		private Header header = null;
		private Body body = null;
		internal NewsGroup newsGroup;
		private string messageID;
//		private int articleNumber;

		public NewsGroup NewsGroup
		{
			get
			{
				return newsGroup;
			}
		}

		internal Article(string[] article, NewsGroup parent)
		{
			ArticleResponse response = Utils.ParseArticleResponse(article[0]);
			messageID = response.MessageID;

			switch (response.StatusCode)
			{
				case NNTPStatus.ArticleHeadBodyRetrieved:
				{
					header = new Header(article, this);
					body = new Body(article, this);
					break;
				}
				case NNTPStatus.ArticleHeadRetrieved:
				{
					header = new Header(article, this);
					break;
				}
				case NNTPStatus.ArticleBodyRetrieved:
				{
					body = new Body(article, this);
					break;
				}
			}
			this.newsGroup = parent;
		}

		internal Article(string serverName)
		{
			header = new Header(serverName);
			body = new Body();
		}

		public void RetrieveHeader()
		{
			this.newsGroup.Session.Reconnect();
			this.newsGroup.Session.Select(this.newsGroup.Name);
			string[] results = this.newsGroup.Session.GetData(NNTPCommand.Header, this.messageID);
			this.newsGroup.Session.Disconnect();
			header = new Header(results, this);
		}

		/// <summary>
		/// Retrieves a body of the article from server.
		/// </summary>
		/// <remarks>If only header of the article was previously retrieved from server, call this method to retrieve article's body. </remarks>
		public void RetrieveBody()
		{
			this.newsGroup.Session.Reconnect();
			this.newsGroup.Session.Select(this.newsGroup.Name);
			string[] results = this.newsGroup.Session.GetData(NNTPCommand.Body, this.messageID);
			body = new Body(results, this);
			this.newsGroup.Session.Disconnect();
		}

		public Header Header
		{
			get
			{
				return header;
			}
		}

		public Body Body
		{
			get
			{
				return body;
			}
		}

		public override string ToString()
		{
			StringBuilder result = new StringBuilder();
			result.Append(header.ToString());
			result.Append(Environment.NewLine);
			string bodyText = body.ToString();
			if (!bodyText.EndsWith(Environment.NewLine))
				bodyText = bodyText + Environment.NewLine;
			result.Append(bodyText);
			return result.ToString();
		}

		/// <summary>
		/// Exports article's contents to XML.
		/// </summary>
		/// <param name="decodeContents">A value that indicates whether to decode contents during exporting.</param>
		/// <returns></returns>
		public XmlDocument ToXml(bool decodeContents)
		{
			XmlDocument doc = new XmlDocument();
			XmlElement xmlArticle = doc.CreateElement("Article");
			doc.AppendChild(xmlArticle);
			if (this.header != null)
				xmlArticle.AppendChild(doc.ImportNode(this.header.Headers.ToXml(decodeContents).DocumentElement, true));
			if (this.body != null)
				xmlArticle.AppendChild(doc.ImportNode(this.body.ToXml(decodeContents).DocumentElement, true));
			return doc;
		}
	}
}
