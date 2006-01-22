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
using System.Collections.Specialized;
using System.Text.RegularExpressions;
using System.Globalization;
using System.IO;

namespace Smilla.Net.NNTPClient
{
	/// <summary>
	/// Default constants.
	/// </summary>
	public struct NNTPDefaults
	{
		public const string ContentType = "text/plain";
		public const string Charset = "us-ascii";
	}

	/// <summary>
	/// Server status response codes.
	/// </summary>
	public enum NNTPStatus: int
	{
		HelpText = 100,
		ServerReadyPostingAllowed = 200,
		ServerReadyPostingNotAllowed = 201,
		GroupSelected = 211,
		NoSuchGroup = 411, // no such news group
		ListOfGroups = 215,
		ListOfNewGroups = 231,
		ArticleHeadBodyRetrieved = 220,
		ArticleHeadRetrieved = 221,
		ArticleBodyRetrieved = 222,
		ArticleNoTextRetrieved = 223,
		NoGroupSelected = 412, // no newsgroup has been selected
		NoCurrentArticleSelected = 420, // no current article has been selected
		NoNextArticleSelected = 421, // no next article in this group
		NoPreviousArticleSelected = 422, // no previous article in this group
		NoSuchArticleNumber = 423, // no such article number in this group
		NoSuchArticle = 430, // no such article found
		ListOfNewArticles = 230, // list of new articles by message-id follows		
		Quit = 205, // closing connection - goodbye!
		ArticlePosted = 240, // article posted ok
		PostingStarted = 340, // send article to be posted. End with <CR-LF>.<CR-LF>
		PostingNotAllowed = 440, // posting not allowed
		PostingFailed = 441, // posting failed
		GroupsUnavailable = 481, // Groups and descriptions unavailable
		PermissionDenied = 502,
	}

	/// <summary>
	/// NNTP commands.
	/// </summary>
	public struct NNTPCommand
	{
		public const string Help = "help";
		public const string List = "list";
		public const string Group = "group";
		public const string Article = "article";
		public const string Header = "head";
		public const string Body = "body";
		public const string Quit = "quit";
		public const string ListGroup = "listgroup";
		public const string NewNews = "newnews";
		public const string NewGroups = "newgroups";
		public const string StartPost = "post";
		public const string EndPost = ".";
	}

	/// <summary>
	/// Class that performs encoding/decoding
	/// </summary>
	public class Charset
	{
		private static ushort[] koi8 = new ushort[128] {
			0x2500,0x2502,0x250c,0x2510,0x2514,0x2518,0x251c,0x2524,
			0x252c,0x2534,0x253c,0x2580,0x2584,0x2588,0x258c,0x2590,
			0x2591,0x2592,0x2593,0x2320,0x25a0,0x2219,0x221a,0x2248,
			0x2264,0x2265,0x00a0,0x2321,0x00b0,0x00b2,0x00b7,0x00f7,
			0x2550,0x2551,0x2552,0x0451,0x2553,0x2554,0x2555,0x2556,
			0x2557,0x2558,0x2559,0x255a,0x255b,0x255c,0x255d,0x255e,
			0x255f,0x2560,0x2561,0x0401,0x2562,0x2563,0x2564,0x2565,
			0x2566,0x2567,0x2568,0x2569,0x256a,0x256b,0x256c,0x00a9,
			0x044e,0x0430,0x0431,0x0446,0x0434,0x0435,0x0444,0x0433,
			0x0445,0x0438,0x0439,0x043a,0x043b,0x043c,0x043d,0x043e,
			0x043f,0x044f,0x0440,0x0441,0x0442,0x0443,0x0436,0x0432,
			0x044c,0x044b,0x0437,0x0448,0x044d,0x0449,0x0447,0x044a,
			0x042e,0x0410,0x0411,0x0426,0x0414,0x0415,0x0424,0x0413,
			0x0425,0x0418,0x0419,0x041a,0x041b,0x041c,0x041d,0x041e,
			0x041f,0x042f,0x0420,0x0421,0x0422,0x0423,0x0416,0x0412,
			0x042c,0x042b,0x0417,0x0428,0x042d,0x0429,0x0427,0x042a};

		private static ushort[] iso8859_5 = new ushort[128]
{		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,
	0x00A0, 0x0401, 0x0402, 0x0403, 0x0404, 0x0405, 
	0x0406, 0x0407, 0x0408, 0x0409, 0x040A, 0x040B, 
	0x040C, 0x00AD, 0x040E, 0x040F, 0x0410, 0x0411, 
	0x0412, 0x0413, 0x0414, 0x0415, 0x0416, 0x0417, 
	0x0418, 0x0419, 0x041A, 0x041B, 0x041C, 0x041D, 
	0x041E, 0x041F, 0x0420, 0x0421, 0x0422, 0x0423, 
	0x0424, 0x0425, 0x0426, 0x0427, 0x0428, 0x0429, 
	0x042A, 0x042B, 0x042C, 0x042D, 0x042E, 0x042F, 
	0x0430, 0x0431, 0x0432, 0x0433, 0x0434, 0x0435, 
	0x0436, 0x0437, 0x0438, 0x0439, 0x043A, 0x043B, 
	0x043C, 0x043D, 0x043E, 0x043F, 0x0440, 0x0441, 
	0x0442, 0x0443, 0x0444, 0x0445, 0x0446, 0x0447, 
	0x0448, 0x0449, 0x044A, 0x044B, 0x044C, 0x044D, 
	0x044E, 0x044F, 0x2116, 0x0451, 0x0452, 0x0453, 
	0x0454, 0x0455, 0x0456, 0x0457, 0x0458, 0x0459, 
	0x045A, 0x045B, 0x045C, 0x00A7, 0x045E, 0x045F};

		public static string Decode(string charset, string value, bool replaceDots)
		{
/*
			byte[] stringBytes = Encoding.GetEncoding(0).GetBytes(value);
			for (int i = 0; i < stringBytes.Length; i++)
			{
				if (stringBytes[i] > 127)
					stringBytes[i] = koi8[stringBytes[i]-128];
			}
			return Encoding.GetEncoding(0).GetString(stringBytes);
*/
			ushort[] table;
			switch (charset)
			{
				case "koi8-r":
					table = koi8;
					break;
				case "iso-8859-5":
					table = iso8859_5;
					break;
				default:
					return value;
			}
			StringBuilder decodedString = new StringBuilder(value);
			byte[] stringBytes = Encoding.Default.GetBytes(value);
			for (int i = 0; i < decodedString.Length; i++)
			{
				//byte code = Convert.ToByte(decodedString[i]);
				if (stringBytes[i] > 127)
				{
					decodedString[i] = Convert.ToChar(table[stringBytes[i] - 128]);
				}
			}
			if (replaceDots)
				decodedString = decodedString.Replace(Environment.NewLine + "..", Environment.NewLine + ".");
			return decodedString.ToString();
		}
	}

	/// <summary>
	/// Common server response.
	/// </summary>
	public class NNTPStatusResponse
	{
		public NNTPStatus StatusCode;
		public string StatusText;

		public NNTPStatusResponse(NNTPStatus statusCode, string statusText)
		{
			StatusCode = statusCode;
			StatusText = statusText;
		}
	}

	/// <summary>
	/// Server response for select group command.
	/// </summary>
	public class SelectGroupStatusResponse : NNTPStatusResponse
	{
		public NewsGroupDescription SelectedGroupDescription;

		public SelectGroupStatusResponse(NNTPStatus statusCode, NewsGroupDescription group): base(statusCode, group.Name)
		{
			StatusCode = statusCode;
			SelectedGroupDescription = group;
		}
	}

	/// <summary>
	/// Server response for article command.
	/// </summary>
	public class ArticleResponse : NNTPStatusResponse
	{
		public string MessageID;
		public int ArticleNumber;

		public ArticleResponse(NNTPStatus statusCode, string messageID, int articleNumber):base(statusCode, messageID)
		{
			MessageID = messageID;
			ArticleNumber = articleNumber;
		}
	}

	/// <summary>
	/// Different utils
	/// </summary>
	public class Utils
	{
		internal static bool TextFollows(string command, NNTPStatus code)
		{
			switch (code)
			{
				case NNTPStatus.ArticleBodyRetrieved:
				case NNTPStatus.ArticleHeadBodyRetrieved:
				case NNTPStatus.ArticleHeadRetrieved:
				case NNTPStatus.HelpText:
				case NNTPStatus.ListOfGroups:
				case NNTPStatus.ListOfNewArticles:
				case NNTPStatus.ListOfNewGroups:
					return true;
				case NNTPStatus.GroupSelected:
				{
					if (command == NNTPCommand.ListGroup)
						return true;
					else
						return false;
				}
				default:
					return false;
			}
		}

		internal static NNTPStatusResponse ParseResponse(string statusResponse)
		{
			int Code = Int32.Parse(statusResponse.Substring(0,3));
			string Text = (statusResponse.Length > 3)?statusResponse.Substring(4):"";
			if (Enum.IsDefined(typeof(NNTPStatus), Code))
				return new NNTPStatusResponse((NNTPStatus)Code, Text);
			else
				throw new ArgumentOutOfRangeException("Invalid return code - " + statusResponse.Substring(0,3));
		}		

		internal static SelectGroupStatusResponse ParseSelectGroupResponse(string selectResponse)
		{
			NNTPStatusResponse response = Utils.ParseResponse(selectResponse);
			if (response.StatusCode == NNTPStatus.GroupSelected)
			{
				string[] groupInfo = response.StatusText.Split(' ');
				NewsGroupDescription group = new NewsGroupDescription(groupInfo[3], Int32.Parse(groupInfo[1]), Int32.Parse(groupInfo[2]),Int32.Parse(groupInfo[0]), true);
				return new SelectGroupStatusResponse(response.StatusCode, group);
			}
			else
				return null;
		}

		internal static ArticleResponse ParseArticleResponse(string selectResponse)
		{
			NNTPStatusResponse response = Utils.ParseResponse(selectResponse);
			if (response.StatusCode == NNTPStatus.ArticleBodyRetrieved || response.StatusCode == NNTPStatus.ArticleHeadBodyRetrieved || response.StatusCode == NNTPStatus.ArticleHeadRetrieved || response.StatusCode == NNTPStatus.ArticleNoTextRetrieved)
			{
				string[] articleInfo = response.StatusText.Split(' ');
				return new ArticleResponse(response.StatusCode, articleInfo[1], Int32.Parse(articleInfo[0]));
			}
			else
			{
				return new ArticleResponse(response.StatusCode, null, -1);
			}
		}

		public static string DateToString(DateTime dateTime)
		{
			return dateTime.ToString(@"yyMMdd HHmmss \G\M\T");
		}

		public static DateTime ParseDate(string dateTime)
		{
			int lastSpaceOccur = dateTime.LastIndexOf(" ");
			if (lastSpaceOccur != -1)
			{
				Match tz = Regex.Match(dateTime, @"(\+|\-)\d{4}");
				string timeZone;
				if (tz.Success)
				{
					timeZone = tz.Value;
					lastSpaceOccur = tz.Index - 1;
				}
				else
					timeZone = dateTime.Substring(lastSpaceOccur+1);
				int hourOffset = 0;
				int minOffset = 0;
				switch (timeZone)
				{
					case "GMT": 
						break;
					case "EST":
						hourOffset = -5;
						break;
					case "CST":
						hourOffset = -6;
						break;
					case "MST":
						hourOffset = -7;
						break;
					case "PST":
						hourOffset = -8;
						break;
					case "EDT":
						hourOffset = -4;
						break;
					case "CDT":
						hourOffset = -5;
						break;
					case "MDT":
						hourOffset = -6;
						break;
					case "PDT":
						hourOffset = -7;
						break;
					default:
						char sign = timeZone[0];
						hourOffset = Int32.Parse(timeZone.Substring(1,2));
						minOffset = Int32.Parse(timeZone.Substring(3,2));
						if (sign == '-')
						{
							hourOffset *= -1;
							minOffset *= -1;
						}
						break;
				}
				DateTime result = DateTime.Parse(dateTime.Remove(lastSpaceOccur, dateTime.Length - lastSpaceOccur));
				result.AddHours(-hourOffset);
				result.AddMinutes(-minOffset);
				return result;
			}
			else
				throw new ArgumentException("String cannot be parsed into datetime");
		}

		internal static string GetCharset(HeaderCollection headers)
		{
			Regex charsetSearch = new Regex("charset=\"?([^\"]+)\"?");
			Match result = charsetSearch.Match(headers["Content-Type"]);
			if (result.Groups.Count > 1)
				return result.Groups[1].Value;
			else
				return null;
		}

		internal static void SetCharset(HeaderCollection headers, string charset)
		{
			Regex charsetSearch = new Regex("charset=\"?([^\"]+)\"?");
			Match result = charsetSearch.Match(headers["Content-Type"]);
			
			if (result.Groups.Count > 1)
			{
				if (charset != "")
					headers["Content-Type"] = headers["Content-Type"].Replace(result.Groups[1].Value, charset);
				else
					headers["Content-Type"] = headers["Content-Type"].Remove(result.Groups[1].Index, result.Groups[1].Length);
			}
			else
			{
				if (charset != "")
				{
					headers["Content-Type"] = headers["Content-Type"].Trim();
					if (!headers["Content-Type"].EndsWith(";"))
						headers["Content-Type"] += ";";
					headers["Content-Type"] += String.Format(" charset={0};", charset);
				}
			}
		}

		public static string GetFilename(HeaderCollection headers)
		{
			Regex charsetSearch = new Regex("name=\"?([^\"]+)\"?");
			Match result = charsetSearch.Match(headers["Content-Type"]);
			if (result.Groups.Count > 1)
				return result.Groups[1].Value;
			else
				return null;
		}

		internal static void SetFilename(HeaderCollection headers, string filename)
		{
			Regex charsetSearch = new Regex("name=\"?([^\"]+)\"?");
			Match result = charsetSearch.Match(headers["Content-Type"]);
			
			if (result.Groups.Count > 1)
			{
				if (filename != "")
					headers["Content-Type"] = headers["Content-Type"].Replace(result.Groups[1].Value, filename);
				else
					headers["Content-Type"] = headers["Content-Type"].Remove(result.Groups[1].Index, result.Groups[1].Length);
			}
			else
			{
				if (filename != "")
				{
					headers["Content-Type"] = headers["Content-Type"].Trim();
					if (!headers["Content-Type"].EndsWith(";"))
						headers["Content-Type"] += ";";
					headers["Content-Type"] += String.Format(" name={0};", filename);
				}
			}
		}


		internal static string GetBoundary(HeaderCollection headers)
		{
			Regex boundarySearch = new Regex("boundary=\"?([^\"]+)\"?");
			Match result = boundarySearch.Match(headers["Content-Type"]);
			if (result.Groups.Count > 1)
				return result.Groups[1].Value;
			else
				return null;
		}

		internal static string GetContentType(HeaderCollection headers)
		{
			Regex typeSearch = new Regex(@"[^;\s]+");
			Match result = typeSearch.Match(headers["Content-Type"]);
			if (result.Success)
				return result.Value;
			else
				return null;
		}

		internal static string GetContentDisposition(HeaderCollection headers)
		{
			Regex typeSearch = new Regex(@"[^;\s]+");
			Match result = typeSearch.Match(headers["Content-Disposition"]);
			if (result.Success)
				return result.Value;
			else
				return null;
		}

		internal static void SetContentType(HeaderCollection headers, string contentType)
		{
			Regex typeSearch = new Regex(@"[^;\s]+");
			Match result = typeSearch.Match(headers["Content-Type"]);
			if (result.Success)
				typeSearch.Replace(headers["Content-Type"], contentType);
			else
			{
				headers["Content-Type"] = String.Format("{0}; {1}", contentType, headers["Content-Type"]);
				headers["Content-Type"] = headers["Content-Type"].Trim();
			}
		}

		internal static bool IsMultipart(HeaderCollection headers)
		{
			if (headers["Content-Type"] != null)
				if (headers["Content-Type"].IndexOf("multipart") == -1)
					return false;
				else
					return true;
			else
				return false;
		}

		internal static HeaderCollection ParseHeaders(string[] article)
		{
			Regex nameValueSplitter = new Regex(": ");
			HeaderCollection headers = new HeaderCollection();
			for (int i = 0; i < article.Length; i++)
			{
				if (article[i].Trim() != "" && article[i] != ".")
				{
					if (article[i][0] == ' ' || article[i][0] == '\t')
						headers[headers.GetKey(headers.Count - 1)] = headers[headers.GetKey(headers.Count - 1)] + article[i].Trim('\t');
					else
					{
						string[] headerParts = nameValueSplitter.Split(article[i],2);
						if (headerParts.Length > 1)
							headers.Add(headerParts[0], headerParts[1]);
						else
							continue;
					}
				}
				else
					break;
			}
			return headers;
		}
		public static IBodyPart FindBodyParts(string contentType, IBodyPart body)
		{
			if (body.ContentType == contentType)
				return body;
			for (int i = 0; i < body.BodyParts.Count; i++)
			{
				IBodyPart result = FindBodyParts(contentType, body.BodyParts[i]);
				if (result != null)
					return result;
			}
			return null;
		}

		public static IBodyPart FindBodyPartsByContentID(string contentID, IBodyPart body)
		{
			if (body.Headers["Content-ID"] == contentID)
				return body;
			for (int i = 0; i < body.BodyParts.Count; i++)
			{
				IBodyPart result = FindBodyPartsByContentID(contentID, body.BodyParts[i]);
				if (result != null)
					return result;
			}
			return null;
		}


		internal static BodyPartCollection ParseBodyParts(string text, string boundary, IBodyPart parent)
		{
			Regex boundSplitter = new Regex("--" + boundary);
			string[] parts = boundSplitter.Split(text);
			BodyPartCollection bodyParts = new BodyPartCollection();
			for (int i = 1; i < parts.Length - 1; i++)
			{
				BodyPart newPart = new BodyPart(Regex.Split(parts[i].Trim(),Environment.NewLine), parent);
				bodyParts.Add(newPart.ContentType, newPart);
			}
			return bodyParts;
		}

		public static byte[] FromQuotedPrintableString(string s)
		{
			Match symbols = Regex.Match(s, "=([0-9A-F]){2}");
			StringBuilder decodedString = new StringBuilder(s);
			decodedString.Replace("=" + Environment.NewLine, "");
			if (symbols.Success)
				do
				{
					string strByte = symbols.Value.Substring(1,2);
					byte myByte = Byte.Parse(strByte, NumberStyles.HexNumber); 
					string myStr = Encoding.Default.GetString(new Byte[1]{myByte});
					decodedString.Replace(symbols.Value, myStr);
					symbols = symbols.NextMatch();
				}
				while (symbols.Success);	

			return Encoding.Default.GetBytes(decodedString.ToString());
		}

		public static string DecodeHeaderString(string s)
		{
			Match header = Regex.Match(s, @"=\?(.+)\?(.+)\?(.+)\?=");
			if (header.Success)
			{
				string charset = header.Groups[1].Value;
				string encoding = header.Groups[2].Value;
				string text = header.Groups[3].Value;
				switch (encoding)
				{
					case "B":
						text = Encoding.Default.GetString(Convert.FromBase64String(text));
						break;
					case "Q":
						text = Encoding.Default.GetString(FromQuotedPrintableString(text));
						break;
				}
				text = Charset.Decode(charset, text, false);
				return text;
			}
			else
				return s;
		}

		internal static void SaveBodyPart(IBodyPart bodyPart, string filename)
		{
			FileStream dataFile = new FileStream(filename, FileMode.Create);
			byte[] dataContents;
			switch (bodyPart.Headers["Content-Transfer-Encoding"])
			{
				case "base64":
					dataContents = Convert.FromBase64String(bodyPart.Text);
					break;
				case "quoted-printable":
					dataContents = Utils.FromQuotedPrintableString(bodyPart.Text);
					break;
				default:
					dataContents = Encoding.Default.GetBytes(bodyPart.Text);
					break;
			}
			dataFile.Write(dataContents, 0, dataContents.Length);
			dataFile.Close();
		}
	}
}
