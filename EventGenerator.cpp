#include "EventGenerator.h"


void EventGenerator::add_event_listener(Event_listener_ptr listener)
{
	this->event_listeners.push_back(listener);
}

void EventGenerator::remove_event_listener(Event_listener_ptr listener)
{
	event_listeners.erase(
		std::remove_if(
			event_listeners.begin(),
			event_listeners.end(),
			[&](Event_listener_ptr v_listener) { return listener == v_listener; }
		),
		event_listeners.end()
	);
}

void EventGenerator::notify_listeners(GameEvent game_event)
{
	for (std::vector<Event_listener_ptr>::iterator it = event_listeners.begin(); it != event_listeners.end(); ++it)
	{
		(*it)->event_occured(game_event);
	}
}
