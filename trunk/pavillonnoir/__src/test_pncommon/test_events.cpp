#include "pndefs.h"

#include <iostream>
#include <boost/thread/thread.hpp>

#include "pnevent.h"

using namespace PN;

class MyEventData : public PNEventData
{
public:
  int	nb;

  MyEventData(int nb)
  {
	this->nb = nb;
  }
};

static void	run1()
{
  for (int i = 1; i < 100; ++i)
  {
	PNEventManager::getInstance()->addEvent(PN_EVENT_GAME_INIT, NULL, new MyEventData(i));
  }
}

static void	run2()
{
  for (int i = 1; i < 100; ++i)
  {
	PNEventManager::getInstance()->addEvent(PN_EVENT_GAME_INIT, NULL, new MyEventData(i*100));
  }
}

static void	receive(pnEventType type, PNObject* source, PNEventData* data)
{
  std::cout << ((MyEventData*)data)->nb << std::endl;
}

void		test_events()
{
  PNEventManager::getInstance()->init();

  PNEventManager::getInstance()->addCallback(PN_EVENT_GAME_INIT, receive);

  boost::thread thrd1(run1);
  boost::thread thrd2(run2);

  thrd1.join();
  thrd2.join();
}
