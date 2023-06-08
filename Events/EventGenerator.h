#pragma once
#include <vector>
#include "EventListener.h"

class EventGenerator
{

protected:
	typedef EventListener* Event_listener_ptr;

	std::vector<Event_listener_ptr> event_listeners;

public:
	virtual void add_event_listener(Event_listener_ptr listener);
	virtual void remove_event_listener(Event_listener_ptr listener);

	virtual void notify_listeners(GameEvent game_event);

};

