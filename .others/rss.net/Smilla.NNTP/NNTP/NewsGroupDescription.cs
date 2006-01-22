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

namespace Smilla.Net.NNTPClient
{
	/// <summary>
	/// Class that implements a newsgroup description.
	/// </summary>
	public class NewsGroupDescription
	{
		private int lastNumber;
		private int firstNumber;
		private int numberOfArticles;
		private string groupName;
		private bool postingAllowed;

		public int LastNumber 
		{
			get
			{
				return lastNumber;
			}
		}

		public int FirstNumber
		{
			get
			{
				return firstNumber;
			}
		}

		public int NumberOfArticles
		{
			get
			{
				return numberOfArticles;
			}
		}

		public string Name
		{
			get
			{
				return groupName;
			}
		}

		public bool PostingAllowed
		{
			get
			{
				return postingAllowed;
			}
		}

		public NewsGroupDescription(string name, int first, int last, int total, bool posting)
		{
			groupName = name;
			firstNumber = first;
			lastNumber = last;
			numberOfArticles = total;
			postingAllowed = posting;
		}
		
	}
}
