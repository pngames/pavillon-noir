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
using System.Net.Sockets;
using System.Collections;
using System.Collections.Specialized;
using System.Text;
using System.Text.RegularExpressions;

namespace Smilla.Net.NNTPClient
{
	/// <summary>
	/// Class that implements a communication session with a news server
	/// </summary>
	/// <example>
	/// This is quite simple to start working with Smilla .NET Communication Library. Here are some examples.
	/// <para>First of all you have to establish session with the new server</para>
	/// <code>
	/// Session session = new Session("msnews.microsoft.com", 119);
	/// </code>
	/// <para>Then you can get a list of newsgroups at this server</para>
	/// <code>
	/// NewsGroupCollection groups = session.GetNewsGroups();
	/// NewsGroup group = groups["microsoft.test"];
	/// </code>
	/// <para>or directly retrieve only specified newsgroup from the server.</para>
	/// <code>
	/// NewsGroup group = session.GetNewsGroup("microsoft.test");
	/// </code>
	/// <para>After that you can get articles from the server. For example, this code gets 300 latest articles from the server, but retrieves only headers:</para>
	/// <code>
	/// ArticleCollection articles = group.GetArticles(true, 300);
	/// </code>
	/// <para>When you want to read specified article, you retrieve article's body first</para>
	/// <code>
	/// article.RetrieveBody();
	/// </code>
	/// <para>and then you can read this article's text for example in such way:</para>
	/// <code>
	/// Console.WriteLine(String.Format("From: {0}", article.Header.From));
	/// Console.WriteLine(String.Format("Subject: {0}", article.Header.Subject));
	/// Console.WriteLine("-------------------------------------------------");
	/// Console.WriteLine(article.Body.TextBodyPart.DecodedText);
	/// </code>
	/// </example>
	public class Session
	{
		/// <summary>
		/// Private field
		/// </summary>
		private TcpClient newsClient = new TcpClient();
		
		/// <summary>
		/// Private field
		/// </summary>
		private Regex stringSplitter = new Regex(Environment.NewLine);
		
		/// <summary>
		/// Private field
		/// </summary>
		private string server;
		
		/// <summary>
		/// Private field
		/// </summary>
		private int port;
		
		/// <summary>
		/// Private field
		/// </summary>
		private bool postingAllowed;

		/// <summary>
		/// Private field
		/// </summary>
		private bool connected;

		/// <summary>
		/// Private field
		/// </summary>
		private string serverInfo;

		/// <summary>
		/// Connects to the specified port on the specified news server.
		/// </summary>
		/// <param name="Server">Server name.</param>
		/// <param name="Port">Port number.</param>
		public void Connect(string Server, int Port)
		{
			server = Server;
			port = Port;
			newsClient = new TcpClient(server, port);
			string[] Results = this.GetData();
			NNTPStatusResponse Result = Utils.ParseResponse(Results[0]);
			if (Result.StatusCode == NNTPStatus.ServerReadyPostingAllowed)
				postingAllowed = true; 
			if (Result.StatusCode == NNTPStatus.ServerReadyPostingNotAllowed)
				postingAllowed = false;
			connected = true;
			serverInfo = Result.StatusText;
		}

		/// <summary>
		/// Reconnects to the previously specified port on the previously news server.
		/// </summary>
		public void Reconnect()
		{
//			try
//			{
				newsClient = new TcpClient(server, port);
				string[] Results = this.GetData();
				NNTPStatusResponse Result = Utils.ParseResponse(Results[0]);
				if (Result.StatusCode == NNTPStatus.ServerReadyPostingAllowed)
					postingAllowed = true; 
				if (Result.StatusCode == NNTPStatus.ServerReadyPostingNotAllowed)
					postingAllowed = false;
				connected = true;
				serverInfo = Result.StatusText;
//			}
//			catch {}
		}

		/// <summary>
		/// Closes connection to the news server.
		/// </summary>
		public void Disconnect()
		{
			newsClient.Close();
		}

		/// <summary>
		/// Initializes a new instance of the Session class and connects to the default port (119) on the specified news server.
		/// </summary>
		/// <param name="Server"></param>
		public Session(string Server): this(Server, 119) {}

		/// <summary>
		/// Initializes a new instance of the Session class and connects to the specified port on the specified news server.
		/// </summary>
		/// <param name="Server">Server name</param>
		/// <param name="Port">Port number</param>
		public Session(string Server, int Port)
		{
			Connect(Server, Port);
		}
/*
		public Session(string Server, int Port, string Username, string Password): this(Server, Port)
		{

		}

		public Session(string Server, string UserName, string Password): this(Server, 119, UserName, Password) {}
*/
		/// <summary>
		/// Gets a value that indicates whether posting is allowed during this session.
		/// </summary>
		public bool PostingAllowed
		{
			get
			{
				return postingAllowed;
			}
		}

		/// <summary>
		/// Gets information received from the server during connect. Info may include server version etc.
		/// </summary>
		public string ServerInfo
		{
			get
			{
				return serverInfo;
			}
		}

		/// <summary>
		/// Sends data to the server.
		/// </summary>
		/// <param name="data">Data to send.</param>
		private void SendData(string data)
		{
//			this.Reconnect();
			byte[] CmdBytes = Encoding.Default.GetBytes(data);
			newsClient.GetStream().Write(CmdBytes, 0, CmdBytes.Length);
//			this.Disconnect();
		}

		/// <summary>
		/// Gets data from the server.
		/// </summary>
		/// <returns>Strings array with received data.</returns>
		internal string[] GetData()
		{
			return this.GetData("");
		}

		/// <summary>
		/// Sends command to the server and receives response from it.
		/// </summary>
		/// <param name="cmd">Command to send.</param>
		/// <param name="parameters">Parameters array</param>
		/// <returns>Strings array with received data.</returns>
		internal string[] GetData(string cmd, params string[] parameters)
		{
//			Reconnect();
			if (cmd != "")
			{
				string command;
				if (parameters.Length != 0)
					command = cmd + " " + String.Join(" ", parameters) + Environment.NewLine;
				else
					command = cmd + Environment.NewLine;
				byte[] CmdBytes = Encoding.Default.GetBytes(command);
				newsClient.GetStream().Write(CmdBytes, 0, CmdBytes.Length);
			}
			int BytesRead = 0;
			byte[] Buffer = new byte[256];
			StringBuilder Result = new StringBuilder();
			string stringBuffer = "";

			try
			{
				BytesRead = newsClient.GetStream().Read(Buffer, 0, Buffer.Length);
				stringBuffer = Encoding.Default.GetString(Buffer, 0, BytesRead);
				Result.Append(stringBuffer);
			}
			catch {}
			int statusCode;
			try
			{
				statusCode = Int32.Parse(Result.ToString().Substring(0,3));
			}
			catch (Exception e)
			{
				throw new ApplicationException("Incorrect response from news server!", e);
			}
			string endOfText = (Utils.TextFollows(cmd, (NNTPStatus)statusCode))?(Environment.NewLine + "." + Environment.NewLine):(Environment.NewLine);
			
			while ((BytesRead > 0) && Result.ToString().LastIndexOf(endOfText, Result.Length - 1, (Result.Length < 260)?Result.Length:260) == -1)
			{
				try
				{
					BytesRead = newsClient.GetStream().Read(Buffer, 0, Buffer.Length);
					stringBuffer = Encoding.Default.GetString(Buffer, 0, BytesRead);
					Result.Append(stringBuffer);
	
				}
				catch 
				{
					break;
				}
			}
			string[] ResultArray = stringSplitter.Split(Result.ToString());
//			this.Disconnect();
			return ResultArray;
		}

/*
		public bool Connected
		{
			get
			{                
				return connected;
			}
		}
*/

		/// <summary>
		/// Gets the single NewsGroup object by it's name.
		/// </summary>
		/// <param name="groupName">Name of the newsgroup.</param>
		/// <returns>The NewsGroup object according to the specified name.</returns>
		public NewsGroup GetNewsGroup(string groupName)
		{
			SelectGroupStatusResponse response = this.Select(groupName);
			if (response.StatusCode == NNTPStatus.GroupSelected)
			{
				return new NewsGroup(groupName, response.SelectedGroupDescription.FirstNumber, response.SelectedGroupDescription.LastNumber, response.SelectedGroupDescription.NumberOfArticles, response.SelectedGroupDescription.PostingAllowed, this);
			}
			else
				return null;
		}

		/// <summary>
		/// Gets a collection of newsgroups created since <paramref name="fromDate"/>.
		/// </summary>
		/// <param name="fromDate">Date and time of newsgroups creation.</param>
		/// <returns>Collection of the NewsGroup objects which contains newsgroups created since <paramref name="fromDate"/>.</returns>
		public NewsGroupCollection GetNewsGroups(DateTime fromDate)
		{
			this.Reconnect();
			string[] results = this.GetData(NNTPCommand.NewGroups, Utils.DateToString(fromDate));
			this.Disconnect();
			NNTPStatusResponse response = Utils.ParseResponse(results[0]);
			if (response.StatusCode == NNTPStatus.ListOfNewGroups)
			{
				NewsGroupCollection groupsList = new NewsGroupCollection();
				
				for (int i = 1; i < results.Length - 2; i++)
				{
					string[] groupInfo = results[i].Split(' ');
					bool posting;
					if (groupInfo[3] == "y")
						posting = true;
					else
						posting = false;
					groupsList.Add(groupInfo[0], new NewsGroup(groupInfo[0], Int32.Parse(groupInfo[2]), Int32.Parse(groupInfo[1]), -1, posting, this));
				}
				return groupsList;
			}
			else
				throw new NNTPException("Unrecognized response: " + response.StatusText);
		}

		/// <summary>
		/// Gets a connection of all newsgroups at the server.
		/// </summary>
		/// <returns>Collection of the NewsGroup objects which contains all newsgroups at the server.</returns>
		public NewsGroupCollection GetNewsGroups()
		{
			this.Reconnect();
			string[] results = this.GetData(NNTPCommand.List);
			this.Disconnect();
			NNTPStatusResponse response = Utils.ParseResponse(results[0]);
			if (response.StatusCode == NNTPStatus.ListOfGroups)
			{
				NewsGroupCollection groupsList = new NewsGroupCollection();
				
				for (int i = 1; i < results.Length - 2; i++)
				{
					string[] groupInfo = results[i].Split(' ');
					bool posting;
					if (groupInfo[3] == "y")
						posting = true;
					else
						posting = false;
					//					NewsGroupDescription groupDescription = new NewsGroupDescription(groupInfo[0], Int32.Parse(groupInfo[2]), Int32.Parse(groupInfo[1]), posting);
					groupsList.Add(groupInfo[0], new NewsGroup(groupInfo[0], Int32.Parse(groupInfo[2]), Int32.Parse(groupInfo[1]), -1, posting, this));
				}
				return groupsList;
			}
			else
				throw new NNTPException("Unrecognized response: " + response.StatusText);
		}

/*
		public NewsGroup GetNewsGroup(NewsGroupDescription group)
		{
			return new NewsGroup(group, this);
		}
*/

		/// <summary>
		/// Selects the specified group at the server.
		/// </summary>
		/// <param name="group">Group name.</param>
		/// <returns>Response with the group information.</returns>
		internal SelectGroupStatusResponse Select(string group)
		{
			string[] results = this.GetData(NNTPCommand.Group, group);
			SelectGroupStatusResponse response = Utils.ParseSelectGroupResponse(results[0]);
			if (response.StatusCode == NNTPStatus.GroupSelected)
			{
				return response;
			}
			else
				if (response.StatusCode == NNTPStatus.NoSuchGroup)
					throw new NoSuchGroupException("No such group", group);
				else
					throw new ApplicationException("Unknown Exception - " + results[0]);

		}

		/// <summary>
		/// Creates article for posting.
		/// </summary>
		/// <returns></returns>
		public Article CreateArticle()
		{
			return new Article(server);
		}

		/// <summary>
		/// Posts article to the server.
		/// </summary>
		/// <param name="article"></param>
		public void PostArticle(Article article)
		{
			article.Header.Date = DateTime.Now.ToUniversalTime();
			this.Reconnect();
			string[] beginPost = this.GetData(NNTPCommand.StartPost);
			NNTPStatusResponse startResponse = Utils.ParseResponse(beginPost[0]);
			if (startResponse.StatusCode == NNTPStatus.PostingStarted)
			{
				this.SendData(article.ToString());
				string[] endPost = this.GetData(NNTPCommand.EndPost);
				NNTPStatusResponse endResponse = Utils.ParseResponse(endPost[0]);
				if (endResponse.StatusCode != NNTPStatus.ArticlePosted)
					throw new NNTPException("Posting failed!");
			}
			this.Disconnect();
		}

		/// <summary>
		/// Gets server name for this session
		/// </summary>
		public string Server
		{
			get
			{
				return server;
			}
		}

		/// <summary>
		/// Gets port on the server
		/// </summary>
		public int Port
		{
			get
			{
				return port;
			}
		}

	}
}
