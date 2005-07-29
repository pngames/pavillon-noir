/*
 * PNConsole.cpp
 * 
 * Description :
 * PNConsole definition
 *
 * Copyright (C) 2005 PAVILLON-NOIR TEAM, http://pavillon-noir.org
 * This software has been written in EPITECH <http://www.epitech.net>
 * EPITECH is computer science school in Paris - FRANCE -
 * under the direction of flav <http://www.epita.fr/~flav>.
 * and Jerome Landrieu.
 *
 * This file is part of Pavillon Noir.
 *
 * Pavillon Noir is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * Pavillon Noir is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * Pavillon Noir; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include <stdarg.h>
#include <time.h>

#ifdef WIN32
# include <Windows.h>
//#include <sys/timeb.h>
#else
# include <errno.h>
#endif

#include "pndefs.h"
#include "PNConsole.hpp"

using namespace PN;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNConsole*				PNConsole::_instance = NULL;
PNConsole::MapFonction	PNConsole::_fonctionMap;
std::FILE*				PNConsole::_consoleLogFile = NULL;

PNConsole::PNConsole()
{
  addFonction("help", Callback(this, &PNConsole::_cmdHelp), "List commands descriptions, \"help command\": print just \"command\" description");
}

PNConsole::~PNConsole()
{
  fclose(_consoleLogFile);
}

void	PNConsole::init()
{
  _consoleLogFile = fopen("pnConsole.log", "w");
}

void	PNConsole::_addFonction(const std::string& command, const Callback& fonction, const std::string& desc)
{
  
}

pnbool	PNConsole::addFonction(const std::string& command, const Callback& fonction, const std::string& desc)
{
  MapFonction::const_iterator iter = _fonctionMap.find(command);

  if (iter == _fonctionMap.end())
  {
	writeLine("command \"%s\" accepted", command.c_str());

	_fonctionMap[command].f = fonction;
	_fonctionMap[command].desc = desc;

	if (_instance != NULL)
	  _instance->_addFonction(command, fonction, desc);
  }
  else
  {
	writeLine("command \"%s\" already exists", command.c_str());

	return false;
  }

  return true;
}

void	PNConsole::_delFonction(const std::string& command)
{
  
}

pnbool	PNConsole::delFonction(const std::string& command)
{
  writeLine("not yet implemented");
  
  if (_instance != NULL)
	_instance->_delFonction(command);

  return true;
}

void	PNConsole::_callFonction(const std::string& command, std::istream &paramet)
{
  //parcours la map et appelle la fonction
  MapFonction::const_iterator iter = _fonctionMap.find(command);

  if (iter == _fonctionMap.end())
  {
	writeLine("\"%s\" is an invalid command", command.c_str());
  }
  else
  {
	//writeLine("\"%s\" successfull command", command.c_str());
	_fonctionMap[command].f(command, paramet);
  }
}

void	PNConsole::callFonction(const std::string& command, std::istream &paramet)
{
  if (_instance != NULL)
	_instance->_callFonction(command, paramet);
}

void	PNConsole::writeLine(const pnchar* format, ...)
{
  va_list	args;
  pnchar	buffer[1024];

  va_start(args, format);
  vsnprintf(buffer, 1023, format, args);
  va_end(args);

  if (_instance != NULL)
	_instance->_writeLine(buffer);
  else
  {
	 std::string tmp = buffer;
	 tmp += "\n";
	if (_consoleLogFile != NULL)
	{
	  tmp = _instance->getTime() + tmp;
	  fwrite( tmp.c_str(), sizeof( char ), tmp.length(), _consoleLogFile);
	}
	std::cout << tmp;
  }
}

void	PNConsole::writeError(pnloglevel lvl, const pnchar* format, ...)
{
  va_list	args;
  pnchar	buffer[1024];

  va_start(args, format);
  vsnprintf(buffer, 1023, format, args);
  va_end(args);

  if (_instance != NULL)
	_instance->_writeError(lvl, buffer);
  else
  {
	std::string tmp = format;
	switch (lvl)
	{
	case PN_LOGLVL_INFO:
	  tmp = "[Info: " + tmp + "]\n";
	  std::cout << tmp;
	  break ;
#ifdef DEBUG
	case PN_LOGLVL_DEBUG:
	  tmp = "[Info: " + tmp + "]\n";
	  std::cout << tmp;
	  break ;
#endif
	case PN_LOGLVL_TODO:
	  tmp = "[Todo: " + tmp + "]\n";
	  std::cout << tmp;
	  break ;
	case PN_LOGLVL_WARNING:
	  tmp = "[Warning: " + tmp + "]\n";
	  std::cout << tmp;
	  break ;
	case PN_LOGLVL_ERROR:
	  tmp = "[Error: " + tmp + "]\n";
	  std::cout << tmp;
	  break ;
	case PN_LOGLVL_CRITICAL:
	  tmp = "[Critical: " + tmp + "]\n";
	  std::cout << tmp;
	  break ;
	default:
	  break ;
	}
	if (_consoleLogFile != NULL)
	{
	 tmp = _instance->getTime() + tmp;
	 fwrite( tmp.c_str(), sizeof( char ), tmp.length(), _consoleLogFile);
	}
  }
}

void	PNConsole::writePerror(pnloglevel lvl, const pnchar* format, ...)
{
  bool isInstance = true;
  std::string		tmp;
#ifdef WIN32
  va_list		ap;
  DWORD			err;

  va_start(ap, format);

  LPVOID		lpMsgBuf;

  if (!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
	NULL, (err = GetLastError()), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
	(LPTSTR)&lpMsgBuf, 0,&ap))
  {
	va_end(ap);
	return ;
  }
  va_end(ap);

  if (_instance != NULL)
	_instance->_writePerror(lvl, (const pnchar*)lpMsgBuf);
  else
  {
	isInstance = false;
	tmp = format;
  }
  LocalFree(lpMsgBuf);
#else
  if (_instance != NULL)
	_instance->_writePerror(lvl, strerror(errno));
  else
  {
	isInstance = false;
	tmp = strerror(errno);
	//perror(format);
  }
#endif

  if (isInstance == false)
  {
	switch (lvl)
	{
	case PN_LOGLVL_INFO:
	  tmp = "[Info: " + tmp + "]\n";
	  std::cout << tmp;
	  break ;
#ifdef DEBUG
	case PN_LOGLVL_DEBUG:
	  tmp = "[Info: " + tmp + "]\n";
	  std::cout << tmp;
	  break ;
#endif
	case PN_LOGLVL_TODO:
	  tmp = "[Todo: " + tmp + "]\n";
	  std::cout << tmp;
	  break ;
	case PN_LOGLVL_WARNING:
	  tmp = "[Warning: " + tmp + "]\n";
	  std::cout << tmp;
	  break ;
	case PN_LOGLVL_ERROR:
	  tmp = "[Error: " + tmp + "]\n";
	  std::cout << tmp;
	  break ;
	case PN_LOGLVL_CRITICAL:
	  tmp = "[Critical: " + tmp + "]\n";
	  std::cout << tmp;
	  break ;
	default:
	  break ;
	}
	if (_consoleLogFile != NULL)
	{
	  tmp = _instance->getTime() + tmp;
	  fwrite( tmp.c_str(), sizeof( char ), tmp.length(), _consoleLogFile);
  	}
  }
}

std::string	PNConsole::getTime()
{
  std::string tmp;
  time_t t;

  time(&t);
  tmp = ctime(&t);
  tmp.replace(tmp.length()-1, 1, " ");

  return tmp;
}

//////////////////////////////////////////////////////////////////////////

void	PNConsole::_cmdHelp(const std::string&, std::istream& i)
{
  std::string param;

  i >> param;

  if (param.empty())
  {
	writeLine("");
	writeLine("Command list : ");
	for (MapFonction::iterator it = _instance->_fonctionMap.begin(); it != _instance->_fonctionMap.end(); ++it)
	{
	  writeLine("%s : %s", it->first.c_str(), it->second.desc.c_str());
	}
	writeLine("");
  }
  else
  {
	MapFonction::iterator it = _instance->_fonctionMap.find(param);

	if (it != _instance->_fonctionMap.end())
	{
	  writeLine("%s : %s", it->first.c_str(), it->second.desc.c_str());
	}
	else
	{
	  writeLine("\"%s\" is an invalid command", param.c_str());
	}
  }
}

//////////////////////////////////////////////////////////////////////////
};
