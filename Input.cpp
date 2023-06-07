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
	if (game_event != GameEvent::NONE)
	{
		this->notify_listeners(game_event);
	}
	else if (state == State::PRESSED)
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
