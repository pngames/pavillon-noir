#include "PNGUIMsgBox.hpp"

using namespace PN;

namespace PN
{
  PNGUIMsgBox::PNGUIMsgBox(const std::string& title, const std::string& text, unsigned int msgtype, CEGUI::Window* parentWin)
  {
	CEGUI::Font* defaultFont = CEGUI::System::getSingleton().getDefaultFont();
	std::string tmp;

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

	static int winID = 0;
	std::stringstream convert;
	convert << winID;
	winID++;

	_frameWin = static_cast<CEGUI::FrameWindow*>(CEGUI::WindowManager::getSingleton().createWindow((CEGUI::utf8*)"Vanilla/FrameWindow", ("_msg_box_" + convert.str()).c_str()));
	_frameWin->setText(title.c_str());
	_frameWin->setAlwaysOnTop(true);
	_frameWin->setCloseButtonEnabled(true);
	//_frameWin->setPosition(CEGUI::Point(0.5f - boxWidth * 0.5f, 0.5f - boxHeight * 0.5f));
	_frameWin->setSize(CEGUI::Size(boxWidth, boxHeight));
	//_frameWin->setSize(CEGUI::Size(0.5, 0.5));
	_frameWin->setSizingEnabled(false);
	


	_msgTxt = static_cast<CEGUI::StaticText*>(CEGUI::WindowManager::getSingleton().createWindow((CEGUI::utf8*)"Vanilla/StaticText", ("_msg_box_text_" + convert.str()).c_str() ) );
	_msgTxt->setText(text.c_str());
	_msgTxt->setPosition(CEGUI::Point(0.05f, 0.05f));
	_msgTxt->setSize(CEGUI::Size(0.9f, 0.9f));
	_msgTxt->setBackgroundEnabled(false);
	_msgTxt->setFormatting(CEGUI::StaticText::HorzCentred, CEGUI::StaticText::VertCentred);
	_msgTxt->setFrameEnabled(false);
	_frameWin->addChildWindow(_msgTxt);



	_parentWin->addChildWindow(_frameWin);
	_parentWin->setMutedState(true);
	_frameWin->subscribeEvent(CEGUI::Window::EventDestructionStarted, CEGUI::Event::Subscriber(&PNGUIMsgBox::eventCloseMsgBox, this));
  }

  PNGUIMsgBox::~PNGUIMsgBox()
  {
  }

  /********************************************************************************************/
 
  bool	PNGUIMsgBox::eventCloseMsgBox(const CEGUI::EventArgs& e)
  {

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