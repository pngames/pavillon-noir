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
using System.Collections;
using System.Xml;

namespace Smilla.Net.NNTPClient	
{
	/// <summary>
	/// Class that implements a newsgroup.
	/// </summary>
	public class NewsGroup
	{
		//		private NewsGroupDescription description;
		
		/// <summary>
		/// Private field.
		/// </summary>
		private Session session;
		
		/// <summary>
		/// Private field.
		/// </summary>
		private int lastNumber;
		
		/// <summary>
		/// Private field.
		/// </summary>
		private int firstNumber;
		
		/// <summary>
		/// Private field.
		/// </summary>
		private int numberOfArticles;
		
		/// <summary>
		/// Private field.
		/// </summary>
		private string groupName;
		
		/// <summary>
		/// Private field.
		/// </summary>
		private bool postingAllowed;
		
		/// <summary>
		/// Private field. Array with the article numbers.
		/// </summary>
		/// <remarks>Article number on the server does not actually correspond to the real ordinal number of the article in the list of articles. That's why we have to store server article numbers in this array.</remarks>
		private int[] articleNumbers;

		/// <summary>
		/// Gets the parent session of this newsgroup.
		/// </summary>
		public Session Session
		{
			get
			{
				return session;
			}
		}

		/// <summary>
		/// Gets the last article number in the group.
		/// </summary>
		/// <remarks>ATTENTION: This info is based on the information received from the server. DO NOT rely on it! It may be wrong. Use it only for a help information.</remarks>
		public int LastNumber 
		{
			get
			{
				return lastNumber;
			}
		}

		/// <summary>
		/// Gets the first article number in the group.
		/// </summary>
		/// <remarks>ATTENTION: This info is based on the information received from the server. DO NOT rely on it! It may be wrong. Use it only for a help information.</remarks>
		public int FirstNumber
		{
			get
			{
				return firstNumber;
			}
		}

		/// <summary>
		/// Gets estimated number of articles in the group.
		/// </summary>
		/// <remarks>This value may change during the session.</remarks>
		public int NumberOfArticles
		{
			get
			{
				if (articleNumbers != null)
					return articleNumbers.Length;
				else
					return numberOfArticles;
			}
		}

		/// <summary>
		/// Gets newsgroup name.
		/// </summary>
		public string Name
		{
			get
			{
				return groupName;
			}
		}

		/// <summary>
		/// Gets a value that indicates whether posting to this group is allowed.
		/// </summary>
		public bool PostingAllowed
		{
			get
			{
				return postingAllowed;
			}
		}

		/// <summary>
		/// Initializes a new instance of the NewsGroup class.
		/// </summary>
		/// <param name="name">The group name.</param>
		/// <param name="first">The first article number in the group.</param>
		/// <param name="last">The last article number in the group.</param>
		/// <param name="total">Estimated number of articles in the group.</param>
		/// <param name="posting">A value that indicates whether posting to this group is allowed.</param>
		/// <param name="parentSession">The parent session.</param>
		internal NewsGroup(string name, int first, int last, int total, bool posting, Session parentSession)
		{
			groupName = name;
			firstNumber = first;
			lastNumber = last;
			numberOfArticles = total;
			postingAllowed = posting;
			session = parentSession;
		}

		/// <summary>
		/// Gets article by its number.
		/// </summary>
		/// <param name="headersOnly">A value that indicates whether to retrieve only header of the article.</param>
		/// <param name="index">Number of the article (on the server).</param>
		/// <returns>The Article object.</returns>
		/// <remarks><paramref name="index"/> is a number of the article on the server.</remarks>
		public Article GetArticle(bool headersOnly, int index)
		{
			return this.GetArticle(headersOnly, index, true);
		}

		/// <summary>
		/// Internal method.
		/// </summary>
		/// <param name="headersOnly">A value that indicates whether to retrieve only header of the article.</param>
		/// <param name="index">Index of the article.</param>
		/// <param name="reconnect">A value that indicates whether to reconnect before the article retrieving.</param>
		/// <returns>The Article object.</returns>
		internal Article GetArticle(bool headersOnly, int index, bool reconnect)
		{
			string retrieveCommand = (headersOnly)?NNTPCommand.Header:NNTPCommand.Article;
			if (reconnect)
				this.session.Reconnect();
			this.Session.Select(this.groupName);
			string[] article = this.session.GetData(retrieveCommand, index.ToString());
			if (reconnect)
				this.session.Disconnect();
			ArticleResponse response = Utils.ParseArticleResponse(article[0]);
			if (response.StatusCode == NNTPStatus.NoSuchArticleNumber)
				throw new NoSuchArticleNumberException("Nu such article number!", index);
			return new Article(article, this);
		}

		/// <summary>
		/// Gets article by its message ID.
		/// </summary>
		/// <param name="messageID">Message ID.</param>
		/// <param name="headersOnly">A value that indicates whether to retrieve only header of the article.</param>
		/// <returns>The Article object.</returns>
		public Article GetArticle(bool headersOnly, string messageID)
		{
			return this.GetArticle(headersOnly, messageID, true);
		}

		/// <summary>
		/// This is a private method.
		/// </summary>
		/// <param name="messageID">Message ID.</param>
		/// <param name="headersOnly">A value that indicates whether to retrieve only headers of the articles.</param>
		/// <param name="reconnect">A value that indicates whether to reconnect before the article retrieving.</param>
		/// <returns>The Article object.</returns>
		private Article GetArticle(bool headersOnly, string messageID, bool reconnect)
		{
			string retrieveCommand = (headersOnly)?NNTPCommand.Header:NNTPCommand.Article;
			if (reconnect)
				this.session.Reconnect();
			this.Session.Select(this.groupName);
			string[] article = this.session.GetData(retrieveCommand, messageID);
			if (reconnect)
				this.session.Disconnect();
			ArticleResponse response = Utils.ParseArticleResponse(article[0]);
			if (response.StatusCode == NNTPStatus.NoSuchArticle)
				throw new NoSuchArticleException("Nu such article!", messageID);
			return new Article(article, this);
		}

		/// <summary>
		/// Gets a collection of articles posted or received to this newsgroup since "fromDate"
		/// </summary>
		/// <param name="headersOnly">A value that indicates whether to retrieve only headers of articles.</param>
		/// <param name="fromDate">The DateTime value</param>
		/// <returns>Collection of the Article objects.</returns>
		/// <remarks>This method is often disabled on servers</remarks>
		public ArticleCollection GetArticles(bool headersOnly, DateTime fromDate)
		{
			ArticleCollection results = new ArticleCollection();
			this.session.Reconnect();
			RefreshArticleNumbers();

			string[] articles = this.session.GetData(NNTPCommand.NewNews, this.groupName, Utils.DateToString(fromDate));
			NNTPStatusResponse response = Utils.ParseResponse(articles[0]);
			if (response.StatusCode == NNTPStatus.ListOfNewArticles)
			{
				for (int i = 1; i <= articles.Length - 3; i++)
				{
					Article article = this.GetArticle(headersOnly, articles[i], false);
					results.Add(article.Header.MessageID, article);
				}
			}
			else
				throw new NoSuchGroupException("No such group!", this.groupName);
			this.session.Disconnect();
			return results;
		}

		/// <summary>
		/// Gets all articles in the newsgroup.
		/// </summary>
		/// <param name="headersOnly">A value that indicates whether to retrieve only headers of articles.</param>
		/// <returns>Collection of the Article objects.</returns>
		public ArticleCollection GetArticles(bool headersOnly)
		{
			RefreshArticleNumbers();
			return GetArticles(headersOnly, articleNumbers.Length,false);
		}

		/// <summary>
		/// Gets several last articles.
		/// </summary>
		/// <param name="headersOnly">A value that indicates whether to retrieve only headers of articles.</param>
		/// <param name="numberOfArticles">Number of articles to retrieve.</param>
		/// <returns>Collection of the Article objects.</returns>
		public ArticleCollection GetArticles(bool headersOnly, int numberOfArticles)
		{
			return this.GetArticles(headersOnly, numberOfArticles, true);
		}

		/// <summary>
		/// This is a private method.
		/// </summary>
		/// <param name="headersOnly">A value that indicates whether to retrieve only headers of articles.</param>
		/// <param name="numberOfArticles">Number of articles to retrieve.</param>
		/// <param name="refreshArticles">A value thaat indicates whether to refresh articles numbers before retrieving articles from the server.</param>
		/// <returns>Collection of the Article objects.</returns>
		private ArticleCollection GetArticles(bool headersOnly, int numberOfArticles, bool refreshArticles)
		{
			if (refreshArticles)
				RefreshArticleNumbers(true);
			numberOfArticles = (numberOfArticles > articleNumbers.Length)?articleNumbers.Length:numberOfArticles;
			int startIndex = articleNumbers.Length - numberOfArticles;
			return GetArticles(headersOnly,startIndex, numberOfArticles, false);
		}

		/// <summary>
		/// Gets the specified range of articles.
		/// </summary>
		/// <param name="headersOnly">A value that indicates whether to retrieve only headers of articles.</param>
		/// <param name="startIndex">The index of the start of the range.</param>
		/// <param name="count">The number of articles in the range</param>
		/// <returns>Collection of the Article objects.</returns>
		/// <remarks><paramref name="startIndex"/> is a real ordinal number in the collection of articles. It is not the number of some article on the server. Article number on the server does not actually correspond to the real ordinal number of the article in the list of articles.</remarks>
		public ArticleCollection GetArticles(bool headersOnly, int startIndex, int count)
		{
			return this.GetArticles(headersOnly, startIndex, count, true);
		}

		/// <summary>
		/// This is a private method.
		/// </summary>
		/// <param name="headersOnly">A value that indicates whether to retrieve only headers of articles.</param>
		/// <param name="startIndex">The index of the start of the range.</param>
		/// <param name="count">The number of articles in the range</param>
		/// <param name="refreshArticles">A value thaat indicates whether to refresh articles numbers before retrieving articles from the server.</param>
		/// <returns>Collection of the Article objects.</returns>
		/// <remarks><paramref name="startIndex"/> is a real ordinal number in the collection of articles. It is not the number of some article on the server. Article number on the server does not actually correspond to the real ordinal number of the article in the list of articles.</remarks>
		private ArticleCollection GetArticles(bool headersOnly, int startIndex, int count, bool refreshArticles)
		{
			ArticleCollection results = new ArticleCollection();
			this.session.Reconnect();
			if (refreshArticles)
				RefreshArticleNumbers();
			this.session.Select(groupName);
			if (articleNumbers.Length > 0)
			{
				if (startIndex < 0 || startIndex >= articleNumbers.Length)
					throw new ArgumentOutOfRangeException("startIndex", startIndex, "startIndex is out of range");
				if (count < 0)
					throw new ArgumentOutOfRangeException("count", count, "count is out of range");
				if (startIndex + count > articleNumbers.Length)
				{
					count = articleNumbers.Length - startIndex;
				}
				for (int i = startIndex; i < startIndex + count; i++)
				{
					Article article = this.GetArticle(headersOnly, articleNumbers[i], false);
					if (article != null)
						results.Add(article.Header.MessageID, article);
				}
			}
			this.session.Disconnect();
			return results;
		}

		/// <summary>
		/// Refreshes articles numbers.
		/// </summary>
		private void RefreshArticleNumbers()
		{
			this.RefreshArticleNumbers(false);
		}

		/// <summary>
		/// Refreshes articles numbers.
		/// </summary>
		/// <param name="reconnect">A value that indicates whether to reconnect before refreshing.</param>
		private void RefreshArticleNumbers(bool reconnect)
		{
			if (reconnect)
				this.session.Reconnect();
			SelectGroupStatusResponse statusResponse = this.session.Select(this.Name);
			if (articleNumbers == null || statusResponse.SelectedGroupDescription.NumberOfArticles != articleNumbers.Length)
			{
				string[] groupList = this.session.GetData(NNTPCommand.ListGroup, this.groupName);
				NNTPStatusResponse response = Utils.ParseResponse(groupList[0]);
				if (response.StatusCode == NNTPStatus.GroupSelected)
				{
					articleNumbers = new Int32[groupList.Length - 3];
					for (int i = 0; i < groupList.Length - 3; i++)
						articleNumbers[i] = Int32.Parse(groupList[i+1]);
				}
				else
					throw new NoSuchGroupException("No such group!", groupName);
			}
			if (reconnect)
				this.session.Disconnect();
		}

		/// <summary>
		/// Exports the newsgroup info to XML.
		/// </summary>
		/// <returns>XmlDocument that contains the newsgroup info.</returns>
		public XmlDocument ToXml()
		{
			XmlDocument doc = new XmlDocument();
			XmlElement xmlNewsGroup = doc.CreateElement("NewsGroup");
			doc.AppendChild(xmlNewsGroup);
			xmlNewsGroup.SetAttribute("Name", this.groupName);
			xmlNewsGroup.SetAttribute("LastNumber", this.lastNumber.ToString());
			xmlNewsGroup.SetAttribute("FirstNumber", this.firstNumber.ToString());
			xmlNewsGroup.SetAttribute("NumberOfArticles", this.NumberOfArticles.ToString());
			return doc;
		}
	}
}
