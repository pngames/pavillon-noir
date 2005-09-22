#ifndef _PN_GUIMSGBOX_HPP_
#define _PN_GUIMSGBOX_HPP_

#include "myCEGUI.h"
#include "pndefs.h"

namespace PN
{
  class PNGUIMsgBox
  {
	/*/////////////////////////////////////////////////////////////////////////////
	/                                   Properties                                /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	typedef enum
	{
	  YES_NO,
	  OK_CANCEL,
	  OK
	} msgboxtype;
  protected:
  private:
	CEGUI::FrameWindow*	_frameWin;
	CEGUI::StaticText*	_msgTxt;
	CEGUI::Window*		_parentWin;
	/*/////////////////////////////////////////////////////////////////////////////
	/                                    Methods                                  /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
  protected:
  private:
	 bool	eventCloseMsgBox(const CEGUI::EventArgs& e);
	 int	str_to_vector(const std::string& str, const std::string& separators, std::vector<std::string>* p_result);
	/*/////////////////////////////////////////////////////////////////////////////
	/                           Constructors / Destructor                         /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	PNGUIMsgBox(const std::string& title, const std::string& text, unsigned int msgtype, CEGUI::Window* parentWin = NULL);
	~PNGUIMsgBox();
  };
}

#endif /*_PN_GUIMSGBOX_HPP_*/