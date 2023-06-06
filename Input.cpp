#include "Input.h"
#include "Key.h"
#include <SDL2/SDL.h>
#include <string>
#include "Event.h"

Input::Input()
{
}

void Input::check_input()
{
	Key       key;
	State     state;
	GameEvent game_event = GameEvent::NONE;

	this->input_implementation(state, key, game_event);
	if (game_event == GameEvent::EXIT_GAME)
	{
		for (std::vector<Event_listener_ptr>::iterator it = event_listeners.begin(); it != event_listeners.end(); ++it)
		{
			(*it)->event_occured(game_event);
		}
	}

	if (state == State::PRESSED)
	{
		for (std::vector<Listener_ptr>::iterator it = listeners.begin(); it != listeners.end(); ++it)
		{
			(*it)->button_pressed(key);
		}
	}
	else if (state == State::RELEASED)
	{
		for (std::vector<Listener_ptr>::iterator it = listeners.begin(); it != listeners.end(); ++it)
		{
			(*it)->button_released(key);
		}
	}
}


void Input::add_listener(Listener_ptr listener)
{
	this->listeners.push_back(listener);
}

void Input::remove_listener(Listener_ptr listener)
{
	listeners.erase(
		std::remove_if(
			listeners.begin(),
			listeners.end(),
			[&](Listener_ptr v_listener) { return listener.get() == v_listener.get(); }
		),
		listeners.end()
	);
}

void Input::add_event_listener(Event_listener_ptr listener)
{
	this->event_listeners.push_back(listener);
}

void Input::remove_event_listener(Event_listener_ptr listener)
{
	event_listeners.erase(
		std::remove_if(
			event_listeners.begin(),
			event_listeners.end(),
			[&](Event_listener_ptr v_listener) { return listener.get() == v_listener.get(); }
		),
		event_listeners.end()
	);
}
