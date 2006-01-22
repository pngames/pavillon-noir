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
using System.Text.RegularExpressions;
using System.Text;
using System.Xml;
/*
 * The required header lines are "From", "Date",
    "Newsgroups", "Subject", "Message-ID", and "Path"
 */
namespace Smilla.Net.NNTPClient
{
	/// <summary>
	/// Class that implements an article header.
	/// </summary>
	public class Header
	{
		private HeaderCollection headers = new HeaderCollection();
// ============ Headers	===================
		private string from;
		private DateTime date;
		private string[] newsGroups;
		private string subject;
		private string messageID;
		private string path;
		private string[] followUpTo;
		private DateTime expires;
		private string replyTo;
		private string sender;
		private string[] references;
		private string[] distribution;
		private string keywords;
		private string summary;
		private string approved;
		private int lines = -1;
		private string xref;
		private string organization;
		private string mimeVersion;
		private bool multipart = false;
		internal string boundary;
		private string contentType = NNTPDefaults.ContentType;
		private string charset = NNTPDefaults.Charset;
// =========================================
		private bool readOnly = true;

		internal Article article;

		internal Header(string serverName)
		{
			readOnly = false;
			headers["MIME-Version"] = "1.0";
			mimeVersion = headers["MIME-Version"];
			headers["Content-Type"] = String.Format("{0}; charset={1}", contentType, charset);
			headers["Message-ID"] = String.Format("<{0}@{1}>",System.Guid.NewGuid().ToString(),serverName);
			messageID = headers["Message-ID"];
		}

		internal Header(string[] article, Article parent)
		{
			this.article = parent;
			BuildHeaders(article);
			//
			// TODO: Add constructor logic here
			//
		}

		public HeaderCollection Headers
		{
			get
			{
				return headers;
			}
		}

		internal void BuildHeaders(string[] article)
		{
			NNTPStatusResponse response = Utils.ParseResponse(article[0]);
			if (response.StatusCode == NNTPStatus.ArticleHeadBodyRetrieved || response.StatusCode == NNTPStatus.ArticleHeadRetrieved)
			{
				headers = Utils.ParseHeaders(article);
				if (headers["From"] != null)
					from = headers["From"];
				if (headers["Date"] != null)
				{
					try
					{
						date = Utils.ParseDate(headers["Date"]);
					}
					catch {}
				}
				if (headers["Newsgroups"] != null)
					newsGroups = headers["Newsgroups"].Split(',');
				if (headers["Subject"] != null)
					subject = headers["Subject"];
				if (headers["Message-ID"] != null)
					messageID = headers["Message-ID"];
				if (headers["Path"] != null)
					path = headers["Path"];
				if (headers["Followup-To"] != null)
					followUpTo = headers["Followup-To"].Split(',');
				if (headers["Expires"] != null)
					expires = Utils.ParseDate(headers["Expires"]);
				if (headers["Reply-To"] != null)
					replyTo = headers["Reply-To"];
				if (headers["Sender"] != null)
					sender = headers["Sender"];
				if (headers["References"] != null)
					references = headers["References"].Split(' ');
				if (headers["Distribution"] != null)
					distribution = headers["Distribution"].Split(',');
				if (headers["Keywords"] != null)
					keywords = headers["Keywords"];
				if (headers["Summary"] != null)
					summary = headers["Summary"];
				if (headers["Approved"] != null)
					approved = headers["Approved"];
				if (headers["Lines"] != null)
					lines = Int32.Parse(headers["Lines"]);
				if (headers["Xref"] != null)
					xref = headers["Xref"];
				if (headers["Organization"] != null)
					organization = headers["Organization"];
				if (headers["MIME-Version"] != null)
				{
					mimeVersion = headers["MIME-Version"];
					subject = Utils.DecodeHeaderString(subject);
					from = Utils.DecodeHeaderString(from);
					if (headers["Content-Type"] != null)
					{
						contentType = Utils.GetContentType(headers);
						if (headers["Content-Type"].IndexOf("multipart") != -1)
						{
							boundary = Utils.GetBoundary(headers);
							multipart = true;
						}
						else
						{
							charset = Utils.GetCharset(headers);
							if (charset != null)
							{
								subject = NNTPClient.Charset.Decode(charset, subject, false);
								headers["Subject"] = subject;
							}
						}
					}
				}
				else
				{
					contentType = NNTPDefaults.ContentType;
					charset = NNTPDefaults.Charset;
				}
				readOnly = true;
			}
		}

		public string From
		{
			get
			{
				return from;
			}
			set
			{
				if (!readOnly)
				{
					from = value;
					headers["From"] = value;
				}
				else
					throw new InvalidOperationException("Article doesn't allow modifications");
			}
		}

		public DateTime Date
		{
			get
			{
				return date;
			}
			set
			{
				if (!readOnly)
				{
					date = value;
					headers["Date"] = value.ToString("r");
				}
				else
					throw new InvalidOperationException("Article doesn't allow modifications");
			}
		}
	
		public string[] NewsGroups
		{
			get
			{
				return newsGroups;
			}
			set
			{
				if (!readOnly)
				{
					newsGroups = value;
					headers["Newsgroups"] = String.Join(",", value);
				}
				else
					throw new InvalidOperationException("Article doesn't allow modifications");
			}
		}

		public string[] References
		{
			get
			{
				return references;
			}
			set
			{
				if (!readOnly)
				{
					references = value;
					headers["References"] = String.Join(" ", value);
				}
				else
					throw new InvalidOperationException("Article doesn't allow modifications");
			}
		}

		public string Subject
		{
			get
			{
				return subject;
			}
			set
			{
				if (!readOnly)
				{
					subject = value;
					headers["Subject"] = value;
				}
				else
					throw new InvalidOperationException("Article doesn't allow modifications");
			}
		}

		public string MessageID
		{
			get
			{
				return messageID;
			}
			set
			{
				if (!readOnly)
				{
					messageID = value;
					headers["Message-ID"] = value;
				}
				else
					throw new InvalidOperationException("Article doesn't allow modifications");
			}
		}

		public string Path
		{
			get
			{
				return path;
			}
			set
			{
				if (!readOnly)
				{
					path = value;
					headers["Path"] = value;
				}
				else
					throw new InvalidOperationException("Article doesn't allow modifications");
			}
		}

		public string[] FollowupTo
		{
			get
			{
				return followUpTo;
			}
			set
			{
				if (!readOnly)
				{
					followUpTo = value;
					headers["From"] = String.Join(",", value);
				}
				else
					throw new InvalidOperationException("Article doesn't allow modifications");
			}
		}

		public DateTime Expires
		{
			get
			{
				return expires;
			}
			set
			{
				if (!readOnly)
				{
					expires = value;
					headers["Expires"] = value.ToString("r");
				}
				else
					throw new InvalidOperationException("Article doesn't allow modifications");
			}
		}

		public string ReplyTo
		{
			get
			{
				return replyTo;
			}
			set
			{
				if (!readOnly)
				{
					replyTo = value;
					headers["Reply-To"] = value;
				}
				else
					throw new InvalidOperationException("Article doesn't allow modifications");
			}
		}

		public string Sender
		{
			get
			{
				return sender;
			}
			set
			{
				if (!readOnly)
				{
					sender = value;
					headers["Sender"] = value;
				}
				else
					throw new InvalidOperationException("Article doesn't allow modifications");
			}
		}

		public string[] Distribution
		{
			get
			{
				return distribution;
			}
			set
			{
				if (!readOnly)
				{
					distribution = value;
					headers["Distribution"] = String.Join(",", value);
				}
				else
					throw new InvalidOperationException("Article doesn't allow modifications");
			}
		}

		public string Keywords
		{
			get
			{
				return keywords;
			}
			set
			{
				if (!readOnly)
				{
					keywords = value;
					headers["Keywords"] = value;
				}
				else
					throw new InvalidOperationException("Article doesn't allow modifications");
			}
		}

		public string Summary
		{
			get
			{
				return summary;
			}
			set
			{
				if (!readOnly)
				{
					summary = value;
					headers["Summary"] = value;
				}
				else
					throw new InvalidOperationException("Article doesn't allow modifications");
			}
		}

		public string Approved
		{
			get
			{
				return approved;
			}
			set
			{
				if (!readOnly)
				{
					approved = value;
					headers["Approved"] = value;
				}
				else
					throw new InvalidOperationException("Article doesn't allow modifications");
			}
		}

		public int Lines
		{
			get
			{
				return lines;
			}
		}

		public string Xref
		{
			get
			{
				return xref;
			}
			set
			{
				if (!readOnly)
				{
					xref = value;
					headers["Xref"] = value;
				}
				else
					throw new InvalidOperationException("Article doesn't allow modifications");
			}
		}

		public string Organization
		{
			get
			{
				return organization;
			}
			set
			{
				if (!readOnly)
				{
					organization = value;
					headers["Organization"] = value;
				}
				else
					throw new InvalidOperationException("Article doesn't allow modifications");
			}
		}

		public string[] ToStringArray()
		{
			string[] results = new string[headers.Count];
			for (int i = 0; i < results.Length; i++)
			{
				results[i] = String.Join(": ", new String[2] {headers.GetKey(i), headers[i]});
			}
			return results;
		}

		public string MimeVersion
		{
			get
			{
				return mimeVersion;
			}
			set
			{
				if (!readOnly)
				{
					mimeVersion = value;
					headers["MIME-Version"] = value;
				}
				else
					throw new InvalidOperationException("Article doesn't allow modifications");
			}
		}

		public bool Multipart
		{
			get
			{
				return multipart;
			}
		}

		public string ContentType
		{
			get
			{
				return contentType;
			}
			set
			{
				if (!readOnly)
				{
					contentType = value;
					Utils.SetContentType(headers, contentType);
				}
				else
					throw new InvalidOperationException("Article doesn't allow modifications");
			}
		}

		public string Charset
		{
			get
			{
				return charset;
			}
			set
			{
				if (!readOnly)
				{
					charset = value;
					Utils.SetCharset(headers, charset);
				}
				else
					throw new InvalidOperationException("Article doesn't allow modifications");
			}
		}

		internal new string ToString()
		{
//			headers["Content-Type"] = String.Format("{0};", contentType);
//			if (contentType.IndexOf("text/") != -1)
//				headers["Content-Type"] += String.Format(" charset={0}", charset);
			return headers.ToString();
		}

		
	}
}
