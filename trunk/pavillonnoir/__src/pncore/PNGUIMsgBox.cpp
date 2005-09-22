#include "PNGUIMsgBox.hpp"

using namespace PN;

namespace PN
{
  static int winID = 0;
  PNGUIMsgBox::PNGUIMsgBox(const std::string& title, const std::string& text, unsigned int msgtype, const Callback& fonction, CEGUI::Window* parentWin)
  {
	/*CEGUI::Font* defaultFont = CEGUI::System::getSingleton().getDefaultFont();
	std::string tmp;
	fonctionCallback = fonction;

	if (!parentWin) 
	_parentWin = CEGUI::System::getSingleton().getGUISheet();
	else
	_parentWin = parentWin;

	std::vector<std::string> lines;
	str_to_vector(text, "\n", &lines);
	float textWidth  = 0;

	for (unsigned int cnt = 0; cnt < lines.size(); cnt++)
	{
	tmp = lines[cnt];
	float lineExtend = defaultFont->getTextExtent(tmp.c_str());
	if (textWidth < lineExtend)
	textWidth = lineExtend;
	}   

	float textHeight = defaultFont->getLineSpacing() * float(lines.size());

	float width, height;

	height = CEGUI::System::getSingleton().getRenderer()->getHeight();
	width = CEGUI::System::getSingleton().getRenderer()->getWidth();
	textWidth /= width;
	textHeight /= height;



	float boxWidth = 0;
	float boxHeight = 0;
	float minButtonWidth = 0.1f;
	float minButtonHeight = 0.05f;


	switch (msgtype)
	{
	case YES_NO:
	case OK_CANCEL:
	boxWidth = std::max(2.0f * minButtonWidth + 0.1f, textWidth + 0.05f);
	boxHeight = minButtonWidth + textHeight + 0.1f;
	break;
	case OK:
	boxWidth = std::max(minButtonWidth + 0.1f, textWidth + 0.05f);
	boxHeight = minButtonHeight + textHeight + 0.1f;
	break;

	}
	*/


	//	static int winID = 0;
	std::stringstream convert;
	convert << winID;
	winID++;
	genericCreationWindow(title, text, msgtype, fonction, parentWin, convert.str());

	//_frameWin = static_cast<CEGUI::FrameWindow*>(CEGUI::WindowManager::getSingleton().createWindow((CEGUI::utf8*)"Vanilla/FrameWindow", ("_msg_box_" + convert.str()).c_str()));
	//_frameWin->setText(title.c_str());
	//_frameWin->setAlwaysOnTop(true);
	//_frameWin->setCloseButtonEnabled(true);
	//_frameWin->setPosition(CEGUI::Point(0.5f - _boxWidth * 0.5f, 0.5f - _boxHeight * 0.5f));
	//_frameWin->setSize(CEGUI::Size(_boxWidth, _boxHeight));
	//_frameWin->setSizingEnabled(false);

	//_msgTxt = static_cast<CEGUI::StaticText*>(CEGUI::WindowManager::getSingleton().createWindow((CEGUI::utf8*)"Vanilla/StaticText", ("_msg_box_text_" + convert.str()).c_str() ) );
	//_msgTxt->setText(text.c_str());
	//_msgTxt->setPosition(CEGUI::Point(0.05f, 0.05f));
	//_msgTxt->setSize(CEGUI::Size(0.9f, 0.9f));
	//_msgTxt->setBackgroundEnabled(false);
	//_msgTxt->setFormatting(CEGUI::StaticText::HorzCentred, CEGUI::StaticText::VertCentred);
	//_msgTxt->setFrameEnabled(false);
	//_frameWin->addChildWindow(_msgTxt);

	switch (msgtype)
	{
	case YES_NO:
	  {
		CEGUI::PushButton* btnYES = static_cast<CEGUI::PushButton*>(CEGUI::WindowManager::getSingleton().createWindow("Vanilla/Button", ("_msg_box_btn_yes_" + convert.str()).c_str()));
		btnYES->setSize(CEGUI::Size(0.45f, 0.15f));
		btnYES->setPosition( CEGUI::Point(0.025f, 0.825f));
		btnYES->setText("Oui");
		_frameWin->addChildWindow(btnYES);
		btnYES->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PNGUIMsgBox::onClickYes , this));

		CEGUI::PushButton* btnNO = static_cast<CEGUI::PushButton*>(CEGUI::WindowManager::getSingleton().createWindow("Vanilla/Button", ("_msg_box_btn_no_" + convert.str()).c_str()));
		btnNO->setSize(CEGUI::Size(0.45f, 0.15f));
		btnNO->setPosition(CEGUI::Point(0.525f, 0.825f));
		btnNO->setText("Non");
		_frameWin->addChildWindow(btnNO);
		btnNO->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PNGUIMsgBox::onClickNo, this));
	  }
	  break;
	case OK_CANCEL:
	  {
		CEGUI::PushButton* btnOK = static_cast< CEGUI::PushButton* >( CEGUI::WindowManager::getSingleton().createWindow("Vanilla/Button", ("_msg_box_btn_ok_" + convert.str()).c_str()));
		btnOK->setSize(CEGUI::Size(0.45f, 0.15f));
		btnOK->setPosition( CEGUI::Point(0.025f, 0.825f));
		btnOK->setText("Ok");
		_frameWin->addChildWindow(btnOK);
		btnOK->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PNGUIMsgBox::onClickOk, this));

		CEGUI::PushButton* btnCANCEL = static_cast<CEGUI::PushButton*>(CEGUI::WindowManager::getSingleton().createWindow("Vanilla/Button", ( "_msg_box_btn_cancel_" + convert.str() ).c_str() ) );
		btnCANCEL->setSize(CEGUI::Size(0.45f, 0.15f));
		btnCANCEL->setPosition(CEGUI::Point(0.525f, 0.825f));
		btnCANCEL->setText("Annuler");
		_frameWin->addChildWindow(btnCANCEL);
		btnCANCEL->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PNGUIMsgBox::onClickCancel ,this));
	  }
	  break;
	case OK:
	  {
		CEGUI::PushButton* btnOK = static_cast<CEGUI::PushButton*>(CEGUI::WindowManager::getSingleton().createWindow("Vanilla/Button", ("_msg_box_btn_ok_" + convert.str()).c_str()));
		btnOK->setSize(CEGUI::Size(0.5f, 0.15f));
		btnOK->setPosition(CEGUI::Point(0.25f, 0.75f));
		btnOK->setText("Ok");
		_frameWin->addChildWindow(btnOK);
		btnOK->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PNGUIMsgBox::onClickOk, this));
	  }
	  break;
	}

	_parentWin->addChildWindow(_frameWin);
	_parentWin->setMutedState(true);
  }

  PNGUIMsgBox::PNGUIMsgBox(const std::string& text, unsigned int msgtype, const Callback& fonction, const std::string& actionName, CEGUI::Window* parentWin)
  {
	std::stringstream convert;
	convert << winID;
	winID++;
	genericCreationWindow(NULL, text, msgtype, fonction, parentWin, convert.str());	

  }

  PNGUIMsgBox::~PNGUIMsgBox()
  {
  }

  /********************************************************************************************/

  void PNGUIMsgBox::genericCreationWindow(const std::string& title, const std::string& text, unsigned int msgtype, const Callback& fonction, CEGUI::Window* parentWin, std::string convert)
  {
	CEGUI::Font* defaultFont = CEGUI::System::getSingleton().getDefaultFont();
	std::string tmp;
	fonctionCallback = fonction;

	if (!parentWin) 
	  _parentWin = CEGUI::System::getSingleton().getGUISheet();
	else
	  _parentWin = parentWin;

	std::vector<std::string> lines;
	str_to_vector(text, "\n", &lines);
	_textWidth = 0;

	for (unsigned int cnt = 0; cnt < lines.size(); cnt++)
	{
	  tmp = lines[cnt];
	  float lineExtend = defaultFont->getTextExtent(tmp.c_str());
	  if (_textWidth < lineExtend)
		_textWidth = lineExtend;
	}   

	_textHeight = defaultFont->getLineSpacing() * float(lines.size());

	float width, height;

	height = CEGUI::System::getSingleton().getRenderer()->getHeight();
	width = CEGUI::System::getSingleton().getRenderer()->getWidth();
	_textWidth /= width;
	_textHeight /= height;

	_boxWidth = 0;
	_boxHeight = 0;
	float minButtonWidth = 0.1f;
	float minButtonHeight = 0.05f;

	switch (msgtype)
	{
	case YES_NO:
	case OK_CANCEL:
	  _boxWidth = std::max(2.0f * minButtonWidth + 0.1f, _textWidth + 0.05f);
	  _boxHeight = minButtonWidth + _textHeight + 0.1f;
	  break;
	case OK:
	  _boxWidth = std::max(minButtonWidth + 0.1f, _textWidth + 0.05f);
	  _boxHeight = minButtonHeight + _textHeight + 0.1f;
	  break;
	case CONF:
	  break;
	}
	
	tmp = "_msg_box_";
	tmp += convert.c_str();
	_frameWin = static_cast<CEGUI::FrameWindow*>(CEGUI::WindowManager::getSingleton().createWindow((CEGUI::utf8*)"Vanilla/FrameWindow", tmp.c_str()));
	if (msgtype == CONF)
	{
	  _frameWin->setText("");
	  _frameWin->setTitleBarEnabled(false);
	}
	else
	  _frameWin->setText(title.c_str());
	_frameWin->setAlwaysOnTop(true);
	_frameWin->setCloseButtonEnabled(true);
	_frameWin->setPosition(CEGUI::Point(0.5f - _boxWidth * 0.5f, 0.5f - _boxHeight * 0.5f));
	_frameWin->setSize(CEGUI::Size(_boxWidth, _boxHeight));
	_frameWin->setSizingEnabled(false);

	tmp = "_msg_box_text_";
	tmp += convert.c_str();
	_msgTxt = static_cast<CEGUI::StaticText*>(CEGUI::WindowManager::getSingleton().createWindow((CEGUI::utf8*)"Vanilla/StaticText", tmp.c_str()));
	_msgTxt->setText(text.c_str());
	_msgTxt->setPosition(CEGUI::Point(0.05f, 0.05f));
	_msgTxt->setSize(CEGUI::Size(0.9f, 0.9f));
	_msgTxt->setBackgroundEnabled(false);
	_msgTxt->setFormatting(CEGUI::StaticText::HorzCentred, CEGUI::StaticText::VertCentred);
	_msgTxt->setFrameEnabled(false);
	_frameWin->addChildWindow(_msgTxt);
  }

  void PNGUIMsgBox::deleteMsgBox(msgboxtype msgt)
  {
	_parentWin->setMutedState(false);
	//TODO appeler le callback avec l'enum en param de la fonction : done
	_frameWin->destroy();
	fonctionCallback(msgt);
  }

  bool PNGUIMsgBox::onClickOk(const CEGUI::EventArgs& arg)
  {
	deleteMsgBox(OK);
	return true;
  }

  bool PNGUIMsgBox::onClickCancel(const CEGUI::EventArgs& arg)
  {
	deleteMsgBox(CANCEL);
	return true;
  }

  bool PNGUIMsgBox::onClickYes(const CEGUI::EventArgs& arg)
  {
	deleteMsgBox(YES);
	return true;
  }

  bool PNGUIMsgBox::onClickNo(const CEGUI::EventArgs& arg)
  {
	deleteMsgBox(NO);
	return true;
  }

  int PNGUIMsgBox::str_to_vector(const std::string& str, const std::string& separators, std::vector<std::string>* vresult)
  {
	std::string::size_type len = str.length();
	if (!len)
	  return 0;

	if (!separators.length())
	{
	  vresult->push_back(str);
	  return 1;
	}

	std::string::size_type token = 0;
	std::string::size_type end = 0;
	unsigned int org = vresult->size();

	while (end < len)
	{
	  token = str.find_first_not_of(separators, end);
	  end = str.find_first_of(separators, token);

	  if (token != std::string::npos)
		vresult->push_back(str.substr(token,(end != std::string::npos) ? (end - token) : std::string::npos));
	}
	return (vresult->size() - org);
  }
}