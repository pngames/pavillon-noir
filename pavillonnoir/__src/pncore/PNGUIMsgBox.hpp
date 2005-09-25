#ifndef _PN_GUIMSGBOX_HPP_
#define _PN_GUIMSGBOX_HPP_

#include "myCEGUI.h"
#include "pndefs.h"
#include <fastdelegate/FastDelegate.h>

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
	  OK,
	  NO,
	  YES,
	  CANCEL,
	  CONF
	} msgboxtype;
	typedef fastdelegate::FastDelegate1<const unsigned int&> Callback;

  protected:
  private:
	Callback			fonctionCallback;
	CEGUI::FrameWindow*	_frameWin;
	CEGUI::StaticText*	_msgTxt;
	CEGUI::Window*		_parentWin;
	CEGUI::Window*		_backWin;
	float _boxWidth;
	float _boxHeight;
	float _textWidth;
	float _textHeight;

	/*/////////////////////////////////////////////////////////////////////////////
	/                                    Methods                                  /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
  protected:
  private:
	void	genericCreationWindow(const std::string& title, const std::string& text, unsigned int msgtype, CEGUI::Window* parentWin, std::string convert);
	bool	onClickOk(const CEGUI::EventArgs& arg);
	bool	onClickCancel(const CEGUI::EventArgs& arg);
	bool	onClickYes(const CEGUI::EventArgs& arg);
	bool	onClickNo(const CEGUI::EventArgs& arg);
	void	deleteMsgBox(msgboxtype msgt);
	bool	eventKeyConfHandler(const CEGUI::EventArgs& e);
	bool	eventMouseClickConfHandler(const CEGUI::EventArgs& e);
	bool	eventMouseWheelConfHandler(const CEGUI::EventArgs& e);
	int		str_to_vector(const std::string& str, const std::string& separators, std::vector<std::string>* p_result);
	/*/////////////////////////////////////////////////////////////////////////////
	/                           Constructors / Destructor                         /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	PNGUIMsgBox(const std::string& title, const std::string& text, unsigned int msgtype, const Callback& fonction, CEGUI::Window* parentWin = NULL);
	//PNGUIMsgBox(const std::string& text, unsigned int msgtype, const Callback& fonction, const std::string& actionName, CEGUI::Window* parentWin = NULL);
	~PNGUIMsgBox();
  };
}

#endif /*_PN_GUIMSGBOX_HPP_*/