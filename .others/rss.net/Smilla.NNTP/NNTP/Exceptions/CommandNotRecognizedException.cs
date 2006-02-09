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
	/// Exception for "Command not recognized" server response.
	/// </summary>
	public class CommandNotRecognizedException : NNTPException
	{
		public string Command;

		public CommandNotRecognizedException()
		{
			//
			// TODO: Add constructor logic here
			//
		}

		public CommandNotRecognizedException(string message): base(message){}

		public CommandNotRecognizedException(string message, Exception inner): base(message, inner){}

		public CommandNotRecognizedException(string message, string command) 
		{
			Command = command;
		}
	}
}