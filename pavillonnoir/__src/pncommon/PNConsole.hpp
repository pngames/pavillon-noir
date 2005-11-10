/*
 * PNConsole.hpp
 * 
 * Description :
 * PNConsole declaration
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

#ifndef _PNCONSOLE_HPP_
# define _PNCONSOLE_HPP_

#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <fastdelegate/FastDelegate.h>

#include "PNObject.hpp"

namespace PN
{
//////////////////////////////////////////////////////////////////////////

/**
 * \breaf Pseudo terminal for in-game tests
 *
 * The command system take delegates:
 *
 * void staticFunction(const std::string&, std::istream&)
 * {}
 * 
 * class MyClass
 * {
 *   static void staticMemberFunction(const std::string&, std::istream&);
 *   void memberFunction(const std::string&, std::istream&);
 * }
 *
 * void test()
 * {
 *  MyClass toto;
 *
 *  addFonction("command", staticFunction, "description");
 *  addFonction("command", MyClass::staticMemberFunction, "description");
 *  addFonction("command", PNConsole::Callback(&toto, &MyClass::memberFunction), "description");
 *
 *  //same thing for delFonction
 * }
 */
class PNAPI					PNConsole : public PNObject
{
  /*/////////////////////////////////////////////////////////////////////////////
  /                                   Properties                                /
  /////////////////////////////////////////////////////////////////////////////*/
public:
  typedef fastdelegate::FastDelegate2<const std::string&, std::istream&> Callback;
protected:
  static PNConsole*			_instance;

  static std::ofstream		_logFile;
private:
  typedef struct			s_fctConsole
  {
	Callback				f;
	std::string				desc;
  }							t_fctConsole;

  typedef std::map<std::string, t_fctConsole>	MapFonction;
  static MapFonction		_fonctionMap;

  /*/////////////////////////////////////////////////////////////////////////////
  /                                    Methods                                  /
  /////////////////////////////////////////////////////////////////////////////*/
public:
  static	void			init();

  static	pnbool			addFonction(const std::string& command, const Callback& fonction, const std::string& desc = "");
  static	pnbool			delFonction(const std::string& command);

  static	void			writeLine(const pnchar* format, ...);
  static	void			writeError(pnloglevel lvl, const pnchar* format, ...);
  static	void			writePerror(pnloglevel lvl, const pnchar* format, ...);
  static	void			callFonction(const std::string& command, std::istream &paramet);
protected:
  virtual void				_addFonction(const std::string& command, const Callback& fonction, const std::string& desc);
  virtual void				_delFonction(const std::string& command);
  virtual void				_callFonction(const std::string& command, std::istream &paramet);
  virtual void				_writeLine(const pnchar* message)=0;

  virtual void				_writeError(pnloglevel lvl, const pnchar* message)=0;
  
  static std::string		getTime();
  static int				getFonctionCompletion(const std::string& cmd, std::vector<std::string>& candidates);
protected:
  void						_cmdHelp(const std::string&, std::istream& i);
private:

  /*/////////////////////////////////////////////////////////////////////////////
  /                           Constructors / Destructor                         /
  /////////////////////////////////////////////////////////////////////////////*/
protected:
  PNConsole();
  virtual ~PNConsole();
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PNCONSOLE_HPP_*/
